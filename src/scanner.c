#include "tree_sitter/parser.h"

// External scanner for PlantUML block comments: /' ... '/
// The grammar declares three external tokens; this scanner is stateless
// (block comments do not nest in PlantUML), so (de)serialization is a no-op.

enum TokenType {
  BLOCK_COMMENT_START,    // /'
  BLOCK_COMMENT_CONTENT,  // everything up to the closing '/
  BLOCK_COMMENT_END,      // '/
};

void *tree_sitter_plantuml_external_scanner_create() { return NULL; }
void tree_sitter_plantuml_external_scanner_destroy(void *payload) {}
unsigned tree_sitter_plantuml_external_scanner_serialize(void *payload,
                                                         char *buffer) {
  return 0;
}
void tree_sitter_plantuml_external_scanner_deserialize(void *payload,
                                                       const char *buffer,
                                                       unsigned length) {}

static inline void advance(TSLexer *lexer) { lexer->advance(lexer, false); }

bool tree_sitter_plantuml_external_scanner_scan(void *payload, TSLexer *lexer,
                                                const bool *valid_symbols) {
  // During error recovery tree-sitter marks every external token valid.
  // Refuse to invent comment tokens in that situation, otherwise stray
  // characters (e.g. a trailing newline) get mis-scanned as comment content.
  if (valid_symbols[BLOCK_COMMENT_START] &&
      valid_symbols[BLOCK_COMMENT_CONTENT] &&
      valid_symbols[BLOCK_COMMENT_END]) {
    return false;
  }

  if (valid_symbols[BLOCK_COMMENT_START]) {
    // Skip leading whitespace; tree-sitter does not re-enter the external
    // scanner after consuming extras itself, so we must do it here.
    while (lexer->lookahead == ' ' || lexer->lookahead == '\t' ||
           lexer->lookahead == '\n' || lexer->lookahead == '\r') {
      lexer->advance(lexer, true);
    }
    if (lexer->lookahead == '/') {
      advance(lexer);
      if (lexer->lookahead == '\'') {
        advance(lexer);
        lexer->result_symbol = BLOCK_COMMENT_START;
        return true;
      }
    }
    return false;
  }

  if (valid_symbols[BLOCK_COMMENT_END] && lexer->lookahead == '\'') {
    advance(lexer);
    if (lexer->lookahead == '/') {
      advance(lexer);
      lexer->result_symbol = BLOCK_COMMENT_END;
      return true;
    }
    // A lone ' that is not followed by / is treated as content below only
    // when content is requested; here we simply report no end token.
  }

  if (valid_symbols[BLOCK_COMMENT_CONTENT]) {
    bool consumed = false;
    while (lexer->lookahead != 0) {
      if (lexer->lookahead == '\'') {
        // Peek: is this the closing '/ ? Stop before consuming it.
        lexer->mark_end(lexer);
        advance(lexer);
        if (lexer->lookahead == '/') {
          if (consumed) {
            lexer->result_symbol = BLOCK_COMMENT_CONTENT;
            return true;
          }
          return false;  // empty comment body: let END match directly
        }
        // A ' not part of '/ is ordinary content.
        consumed = true;
        continue;
      }
      advance(lexer);
      consumed = true;
      lexer->mark_end(lexer);
    }
    if (consumed) {
      lexer->result_symbol = BLOCK_COMMENT_CONTENT;
      return true;
    }
  }

  return false;
}
