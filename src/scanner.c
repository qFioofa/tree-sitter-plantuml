#include "tree_sitter/parser.h"

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

enum TokenType {
  RAW_STATEMENT,
  BRACE_AHEAD,
  TIMING_START,
  TIMING_END,
  ERROR_SENTINEL,
};

typedef struct {
  bool in_timing;
} Scanner;

static const char *const STRUCTURAL_KEYWORDS[] = {
  "abstract", "activate", "actor", "address", "agent", "allowmixing", "allow",
  "alt", "analog", "anchor", "annotation", "artifact", "as", "associate",
  "attribute", "autoactivate", "autonumber",
  "backward", "binary", "boundary", "box", "break", "caption", "card", "case",
  "center", "circle", "class", "clock", "cloud", "collections", "component",
  "concise", "constraint", "control", "create", "critical", "database",
  "dataclass", "deactivate", "description", "designconstraint",
  "destroy", "detach", "diamond", "direction", "do", "else", "elseif", "end",
  "enddeep", "endif", "endlegend", "endswitch", "endwhile", "entity",
  "entry", "enum", "exception", "exit", "file", "floating", "folder",
  "footer", "fork", "frame",
  "functionalrequirement", "goto", "group", "header", "hide", "highlight",
  "hnote", "if", "interface", "interfacerequirement", "kill",
  "label", "left", "legend", "link", "loop", "mainframe", "merge", "metaclass",
  "minwidth", "mode", "move",
  "namespace", "network", "newpage", "node", "note", "object", "opt", "order",
  "over", "package", "page", "par", "participant", "partition",
  "performancerequirement", "physicalrequirement", "pixel", "port",
  "portin", "portout", "pragma", "printscale", "project", "property",
  "protocol", "queue", "record", "rectangle", "ref", "relationship",
  "remove", "repeat", "requirement", "resume", "restore", "return", "right",
  "rnote", "robust", "rotate", "scale",
  "shape", "show", "skinparam", "split", "spot", "sprite", "stack", "start",
  "state", "storage",
  "stop", "struct", "style", "subclass", "switch", "then", "ticks", "title",
  "together",
  "today", "top", "usecase", "use", "weak", "while",
};

static bool is_ident_start(int32_t c) {
  if (c == '_' || c == '$') return true;
  if (c < 128) return isalpha((unsigned char)c) != 0;
  return true;
}

static bool is_ident_char(int32_t c) {
  if (c == '_' || c == '$') return true;
  if (c < 128) return isalnum((unsigned char)c) != 0;
  return true;
}

static void skip_horizontal(TSLexer *lexer) {
  while (lexer->lookahead == ' ' || lexer->lookahead == '\t') {
    lexer->advance(lexer, true);
  }
}

static void consume(TSLexer *lexer) { lexer->advance(lexer, false); }

static void consume_horizontal(TSLexer *lexer) {
  while (lexer->lookahead == ' ' || lexer->lookahead == '\t') {
    consume(lexer);
  }
}

static bool match_literal(TSLexer *lexer, const char *literal) {
  for (const char *p = literal; *p != '\0'; p++) {
    int32_t c = lexer->lookahead;
    if (c < 128) c = tolower((unsigned char)c);
    if (c != (unsigned char)*p) return false;
    consume(lexer);
  }
  return true;
}

static bool word_is_supported(const char *word) {
  size_t count = sizeof(STRUCTURAL_KEYWORDS) / sizeof(STRUCTURAL_KEYWORDS[0]);
  for (size_t i = 0; i < count; i++) {
    if (strcmp(word, STRUCTURAL_KEYWORDS[i]) == 0) return true;
  }
  return false;
}

static bool starts_relation(TSLexer *lexer) {
  int32_t c = lexer->lookahead;
  if (c == '-' || c == '.' || c == '<' || c == '*' || c == '+' ||
      c == '(' || c == ')' || c == '|' || c == '\\' || c == '/') {
    return true;
  }
  if (c == 'o' || c == 'x') {
    consume(lexer);
    return lexer->lookahead == '-' || lexer->lookahead == '.';
  }
  return false;
}

static bool skip_quoted(TSLexer *lexer) {
  if (lexer->lookahead != '"') return false;
  consume(lexer);
  while (lexer->lookahead != 0 && lexer->lookahead != '\n' &&
         lexer->lookahead != '\r') {
    if (lexer->lookahead == '"') {
      consume(lexer);
      return true;
    }
    if (lexer->lookahead == '\\') consume(lexer);
    consume(lexer);
  }
  return false;
}

static bool skip_bracketed(TSLexer *lexer) {
  if (lexer->lookahead != '[') return false;
  int depth = 0;
  while (lexer->lookahead != 0 && lexer->lookahead != '\n' &&
         lexer->lookahead != '\r') {
    if (lexer->lookahead == '[') depth++;
    if (lexer->lookahead == ']') {
      depth--;
      consume(lexer);
      if (depth == 0) return true;
      continue;
    }
    consume(lexer);
  }
  return false;
}

static bool scan_raw_statement(TSLexer *lexer, bool in_timing) {
  skip_horizontal(lexer);

  if (lexer->lookahead == 0 || lexer->lookahead == '\n' ||
      lexer->lookahead == '\r') {
    return false;
  }

  if (lexer->lookahead == '@' || lexer->lookahead == '!' ||
      lexer->lookahead == '\'') {
    return false;
  }

  if (lexer->lookahead == '"') {
    for (int i = 0; i < 3; i++) {
      if (lexer->lookahead == '"') {
        if (!skip_quoted(lexer)) break;
      } else if (lexer->lookahead == '[') {
        if (!skip_bracketed(lexer)) break;
      } else {
        break;
      }
      consume_horizontal(lexer);
    }
    if (starts_relation(lexer)) return false;
    goto claim;
  }

  if (lexer->lookahead == '#') {
    consume(lexer);
    while (is_ident_char(lexer->lookahead) || lexer->lookahead == '-' ||
           lexer->lookahead == '_') {
      consume(lexer);
    }
    if (lexer->lookahead == ':') return false;
    goto claim;
  }

  if (lexer->lookahead >= '0' && lexer->lookahead <= '9') {
    int32_t first = lexer->lookahead;
    consume(lexer);
    int digits = 0;
    while (lexer->lookahead >= '0' && lexer->lookahead <= '9' && digits < 4) {
      consume(lexer);
      digits++;
    }
    if (lexer->lookahead == '-' || lexer->lookahead == '/' ||
        lexer->lookahead == '.') {
      return false;
    }
    (void)first;
    goto claim;
  }

  if (!is_ident_start(lexer->lookahead)) {
    if (lexer->lookahead == '"' || lexer->lookahead == '#' ||
        lexer->lookahead == '[' || lexer->lookahead == '(' ||
        lexer->lookahead == ':' || lexer->lookahead == '|' ||
        lexer->lookahead == '=' || lexer->lookahead == '-' ||
        lexer->lookahead == '.' || lexer->lookahead == '*' ||
        lexer->lookahead == '<' || lexer->lookahead == '+' ||
        lexer->lookahead == '{' || lexer->lookahead == '}' ||
        lexer->lookahead == '?' || lexer->lookahead == '/') {
      return false;
    }
    goto claim;
  }

  {
    char word[48];
    size_t length = 0;
    bool overflow = false;
    while (is_ident_char(lexer->lookahead)) {
      if (length + 1 < sizeof(word)) {
        int32_t c = lexer->lookahead;
        word[length++] = (char)(c < 128 ? tolower((unsigned char)c) : '?');
      } else {
        overflow = true;
      }
      consume(lexer);
    }
    word[length] = '\0';
    if (!overflow && word_is_supported(word)) return false;

    if (in_timing) {
      consume_horizontal(lexer);
      if (lexer->lookahead == '@') return false;
      if (lexer->lookahead == '\n' || lexer->lookahead == '\r' ||
          lexer->lookahead == 0) {
        return false;
      }
      if (lexer->lookahead == 'i' || lexer->lookahead == 'I') {
        consume(lexer);
        if (lexer->lookahead == 's' || lexer->lookahead == 'S') return false;
      }
    }

    consume_horizontal(lexer);
    if (lexer->lookahead == ':' || lexer->lookahead == '{' ||
        lexer->lookahead == '<' || lexer->lookahead == '[' ||
        lexer->lookahead == '#' || lexer->lookahead == '=') {
      return false;
    }
    if (starts_relation(lexer)) return false;
    if (lexer->lookahead == '[' && skip_bracketed(lexer)) {
      consume_horizontal(lexer);
      if (lexer->lookahead == '"') skip_quoted(lexer);
      consume_horizontal(lexer);
      if (starts_relation(lexer)) return false;
    } else if (lexer->lookahead == '"' && skip_quoted(lexer)) {
      consume_horizontal(lexer);
      if (starts_relation(lexer)) return false;
    }
  }

claim:
  while (lexer->lookahead != 0 && lexer->lookahead != '\n' &&
         lexer->lookahead != '\r') {
    consume(lexer);
  }
  lexer->mark_end(lexer);
  lexer->result_symbol = RAW_STATEMENT;
  return true;
}

void *tree_sitter_plantuml_external_scanner_create(void) {
  Scanner *scanner = calloc(1, sizeof(Scanner));
  return scanner;
}

void tree_sitter_plantuml_external_scanner_destroy(void *payload) {
  free(payload);
}

unsigned tree_sitter_plantuml_external_scanner_serialize(void *payload,
                                                         char *buffer) {
  Scanner *scanner = (Scanner *)payload;
  buffer[0] = scanner->in_timing ? 1 : 0;
  return 1;
}

void tree_sitter_plantuml_external_scanner_deserialize(void *payload,
                                                       const char *buffer,
                                                       unsigned length) {
  Scanner *scanner = (Scanner *)payload;
  scanner->in_timing = length > 0 && buffer[0] != 0;
}

bool tree_sitter_plantuml_external_scanner_scan(void *payload, TSLexer *lexer,
                                                const bool *valid_symbols) {
  Scanner *scanner = (Scanner *)payload;

  if (valid_symbols[ERROR_SENTINEL]) return false;

  if (valid_symbols[TIMING_START] && lexer->lookahead == '@') {
    if (!match_literal(lexer, "@starttiming")) return false;
    lexer->mark_end(lexer);
    lexer->result_symbol = TIMING_START;
    scanner->in_timing = true;
    return true;
  }

  if (valid_symbols[TIMING_END] && lexer->lookahead == '@') {
    if (!match_literal(lexer, "@endtiming")) return false;
    lexer->mark_end(lexer);
    lexer->result_symbol = TIMING_END;
    scanner->in_timing = false;
    return true;
  }

  if (valid_symbols[BRACE_AHEAD] && lexer->lookahead == '}') {
    lexer->result_symbol = BRACE_AHEAD;
    return true;
  }

  if (valid_symbols[RAW_STATEMENT]) {
    return scan_raw_statement(lexer, scanner->in_timing);
  }

  return false;
}
