#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 13
#define STATE_COUNT 65
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 54
#define ALIAS_COUNT 0
#define TOKEN_COUNT 32
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 5
#define PRODUCTION_ID_COUNT 1

enum {
  sym_start_directive = 1,
  sym_end_directive = 2,
  sym_diagram_name = 3,
  anon_sym_class = 4,
  sym_abstract_keyword = 5,
  anon_sym_LBRACE = 6,
  anon_sym_RBRACE = 7,
  anon_sym_COLON = 8,
  anon_sym_LPAREN_RPAREN = 9,
  anon_sym_PLUS = 10,
  anon_sym_DASH = 11,
  anon_sym_POUND = 12,
  anon_sym_TILDE = 13,
  anon_sym_object = 14,
  anon_sym_actor = 15,
  anon_sym_participant = 16,
  anon_sym_note = 17,
  anon_sym_left = 18,
  anon_sym_right = 19,
  anon_sym_top = 20,
  anon_sym_bottom = 21,
  anon_sym_title = 22,
  sym_comment = 23,
  anon_sym_DQUOTE = 24,
  aux_sym_string_token1 = 25,
  sym_identifier = 26,
  anon_sym_DASH_GT = 27,
  anon_sym_DASH_DASH_GT = 28,
  anon_sym_LT_DASH = 29,
  anon_sym_LT_DASH_DASH = 30,
  sym_divider = 31,
  sym_source_file = 32,
  sym_diagram_block = 33,
  sym__statement = 34,
  sym_standalone_statement = 35,
  sym_class_declaration = 36,
  sym_class_body = 37,
  sym_class_member = 38,
  sym_field_declaration = 39,
  sym_method_declaration = 40,
  sym_type_name = 41,
  sym_visibility = 42,
  sym_object_declaration = 43,
  sym_actor_declaration = 44,
  sym_participant_declaration = 45,
  sym_note_statement = 46,
  sym_note_position = 47,
  sym_title_statement = 48,
  sym_string = 49,
  sym_arrow = 50,
  aux_sym_source_file_repeat1 = 51,
  aux_sym_diagram_block_repeat1 = 52,
  aux_sym_class_body_repeat1 = 53,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_start_directive] = "start_directive",
  [sym_end_directive] = "end_directive",
  [sym_diagram_name] = "diagram_name",
  [anon_sym_class] = "class",
  [sym_abstract_keyword] = "abstract_keyword",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_COLON] = ":",
  [anon_sym_LPAREN_RPAREN] = "()",
  [anon_sym_PLUS] = "+",
  [anon_sym_DASH] = "-",
  [anon_sym_POUND] = "#",
  [anon_sym_TILDE] = "~",
  [anon_sym_object] = "object",
  [anon_sym_actor] = "actor",
  [anon_sym_participant] = "participant",
  [anon_sym_note] = "note",
  [anon_sym_left] = "left",
  [anon_sym_right] = "right",
  [anon_sym_top] = "top",
  [anon_sym_bottom] = "bottom",
  [anon_sym_title] = "title",
  [sym_comment] = "comment",
  [anon_sym_DQUOTE] = "\"",
  [aux_sym_string_token1] = "string_token1",
  [sym_identifier] = "identifier",
  [anon_sym_DASH_GT] = "->",
  [anon_sym_DASH_DASH_GT] = "-->",
  [anon_sym_LT_DASH] = "<-",
  [anon_sym_LT_DASH_DASH] = "<--",
  [sym_divider] = "divider",
  [sym_source_file] = "source_file",
  [sym_diagram_block] = "diagram_block",
  [sym__statement] = "_statement",
  [sym_standalone_statement] = "standalone_statement",
  [sym_class_declaration] = "class_declaration",
  [sym_class_body] = "class_body",
  [sym_class_member] = "class_member",
  [sym_field_declaration] = "field_declaration",
  [sym_method_declaration] = "method_declaration",
  [sym_type_name] = "type_name",
  [sym_visibility] = "visibility",
  [sym_object_declaration] = "object_declaration",
  [sym_actor_declaration] = "actor_declaration",
  [sym_participant_declaration] = "participant_declaration",
  [sym_note_statement] = "note_statement",
  [sym_note_position] = "note_position",
  [sym_title_statement] = "title_statement",
  [sym_string] = "string",
  [sym_arrow] = "arrow",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_diagram_block_repeat1] = "diagram_block_repeat1",
  [aux_sym_class_body_repeat1] = "class_body_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_start_directive] = sym_start_directive,
  [sym_end_directive] = sym_end_directive,
  [sym_diagram_name] = sym_diagram_name,
  [anon_sym_class] = anon_sym_class,
  [sym_abstract_keyword] = sym_abstract_keyword,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_LPAREN_RPAREN] = anon_sym_LPAREN_RPAREN,
  [anon_sym_PLUS] = anon_sym_PLUS,
  [anon_sym_DASH] = anon_sym_DASH,
  [anon_sym_POUND] = anon_sym_POUND,
  [anon_sym_TILDE] = anon_sym_TILDE,
  [anon_sym_object] = anon_sym_object,
  [anon_sym_actor] = anon_sym_actor,
  [anon_sym_participant] = anon_sym_participant,
  [anon_sym_note] = anon_sym_note,
  [anon_sym_left] = anon_sym_left,
  [anon_sym_right] = anon_sym_right,
  [anon_sym_top] = anon_sym_top,
  [anon_sym_bottom] = anon_sym_bottom,
  [anon_sym_title] = anon_sym_title,
  [sym_comment] = sym_comment,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [aux_sym_string_token1] = aux_sym_string_token1,
  [sym_identifier] = sym_identifier,
  [anon_sym_DASH_GT] = anon_sym_DASH_GT,
  [anon_sym_DASH_DASH_GT] = anon_sym_DASH_DASH_GT,
  [anon_sym_LT_DASH] = anon_sym_LT_DASH,
  [anon_sym_LT_DASH_DASH] = anon_sym_LT_DASH_DASH,
  [sym_divider] = sym_divider,
  [sym_source_file] = sym_source_file,
  [sym_diagram_block] = sym_diagram_block,
  [sym__statement] = sym__statement,
  [sym_standalone_statement] = sym_standalone_statement,
  [sym_class_declaration] = sym_class_declaration,
  [sym_class_body] = sym_class_body,
  [sym_class_member] = sym_class_member,
  [sym_field_declaration] = sym_field_declaration,
  [sym_method_declaration] = sym_method_declaration,
  [sym_type_name] = sym_type_name,
  [sym_visibility] = sym_visibility,
  [sym_object_declaration] = sym_object_declaration,
  [sym_actor_declaration] = sym_actor_declaration,
  [sym_participant_declaration] = sym_participant_declaration,
  [sym_note_statement] = sym_note_statement,
  [sym_note_position] = sym_note_position,
  [sym_title_statement] = sym_title_statement,
  [sym_string] = sym_string,
  [sym_arrow] = sym_arrow,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_diagram_block_repeat1] = aux_sym_diagram_block_repeat1,
  [aux_sym_class_body_repeat1] = aux_sym_class_body_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_start_directive] = {
    .visible = true,
    .named = true,
  },
  [sym_end_directive] = {
    .visible = true,
    .named = true,
  },
  [sym_diagram_name] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_class] = {
    .visible = true,
    .named = false,
  },
  [sym_abstract_keyword] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PLUS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_POUND] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_TILDE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_object] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_actor] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_participant] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_note] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_left] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_right] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_top] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_bottom] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_title] = {
    .visible = true,
    .named = false,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_string_token1] = {
    .visible = false,
    .named = false,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_DASH_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH_DASH_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT_DASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT_DASH_DASH] = {
    .visible = true,
    .named = false,
  },
  [sym_divider] = {
    .visible = true,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym_diagram_block] = {
    .visible = true,
    .named = true,
  },
  [sym__statement] = {
    .visible = false,
    .named = true,
  },
  [sym_standalone_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_class_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_class_body] = {
    .visible = true,
    .named = true,
  },
  [sym_class_member] = {
    .visible = true,
    .named = true,
  },
  [sym_field_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_method_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_type_name] = {
    .visible = true,
    .named = true,
  },
  [sym_visibility] = {
    .visible = true,
    .named = true,
  },
  [sym_object_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_actor_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_participant_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_note_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_note_position] = {
    .visible = true,
    .named = true,
  },
  [sym_title_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_string] = {
    .visible = true,
    .named = true,
  },
  [sym_arrow] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_diagram_block_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_class_body_repeat1] = {
    .visible = false,
    .named = false,
  },
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(40);
      if (lookahead == '"') ADVANCE(125);
      if (lookahead == '#') ADVANCE(103);
      if (lookahead == '\'') ADVANCE(124);
      if (lookahead == '(') ADVANCE(5);
      if (lookahead == '+') ADVANCE(100);
      if (lookahead == '-') ADVANCE(102);
      if (lookahead == ':') ADVANCE(98);
      if (lookahead == '<') ADVANCE(7);
      if (lookahead == '=') ADVANCE(8);
      if (lookahead == '@') ADVANCE(14);
      if (lookahead == 'a') ADVANCE(133);
      if (lookahead == 'b') ADVANCE(156);
      if (lookahead == 'c') ADVANCE(151);
      if (lookahead == 'l') ADVANCE(138);
      if (lookahead == 'n') ADVANCE(157);
      if (lookahead == 'o') ADVANCE(134);
      if (lookahead == 'p') ADVANCE(129);
      if (lookahead == 'r') ADVANCE(145);
      if (lookahead == 't') ADVANCE(148);
      if (lookahead == '{') ADVANCE(96);
      if (lookahead == '}') ADVANCE(97);
      if (lookahead == '~') ADVANCE(104);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(0)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('d' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 1:
      if (lookahead == '"') ADVANCE(125);
      if (lookahead == '\'') ADVANCE(124);
      if (lookahead == '-') ADVANCE(6);
      if (lookahead == '<') ADVANCE(7);
      if (lookahead == '=') ADVANCE(8);
      if (lookahead == '@') ADVANCE(13);
      if (lookahead == 'a') ADVANCE(133);
      if (lookahead == 'c') ADVANCE(151);
      if (lookahead == 'n') ADVANCE(157);
      if (lookahead == 'o') ADVANCE(134);
      if (lookahead == 'p') ADVANCE(129);
      if (lookahead == 't') ADVANCE(149);
      if (lookahead == '{') ADVANCE(96);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(1)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 2:
      if (lookahead == '"') ADVANCE(125);
      if (lookahead == '\'') ADVANCE(124);
      if (lookahead == 'b') ADVANCE(25);
      if (lookahead == 'c') ADVANCE(20);
      if (lookahead == 'l') ADVANCE(15);
      if (lookahead == 'r') ADVANCE(19);
      if (lookahead == 't') ADVANCE(23);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(2)
      END_STATE();
    case 3:
      if (lookahead == '"') ADVANCE(126);
      if (lookahead == '\'') ADVANCE(87);
      if (lookahead == '-') ADVANCE(44);
      if (lookahead == '<') ADVANCE(45);
      if (lookahead == '=') ADVANCE(46);
      if (lookahead == '@') ADVANCE(58);
      if (lookahead == 'a') ADVANCE(52);
      if (lookahead == 'c') ADVANCE(66);
      if (lookahead == 'n') ADVANCE(70);
      if (lookahead == 'o') ADVANCE(53);
      if (lookahead == 'p') ADVANCE(48);
      if (lookahead == 't') ADVANCE(64);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(3)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0) ADVANCE(90);
      END_STATE();
    case 4:
      if (lookahead == '#') ADVANCE(103);
      if (lookahead == '\'') ADVANCE(124);
      if (lookahead == '+') ADVANCE(100);
      if (lookahead == '-') ADVANCE(101);
      if (lookahead == ':') ADVANCE(98);
      if (lookahead == '}') ADVANCE(97);
      if (lookahead == '~') ADVANCE(104);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(4)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 5:
      if (lookahead == ')') ADVANCE(99);
      END_STATE();
    case 6:
      if (lookahead == '-') ADVANCE(9);
      if (lookahead == '>') ADVANCE(180);
      END_STATE();
    case 7:
      if (lookahead == '-') ADVANCE(184);
      END_STATE();
    case 8:
      if (lookahead == '=') ADVANCE(188);
      END_STATE();
    case 9:
      if (lookahead == '>') ADVANCE(182);
      END_STATE();
    case 10:
      if (lookahead == 'a') ADVANCE(27);
      END_STATE();
    case 11:
      if (lookahead == 'a') ADVANCE(30);
      END_STATE();
    case 12:
      if (lookahead == 'd') ADVANCE(37);
      END_STATE();
    case 13:
      if (lookahead == 'e') ADVANCE(22);
      END_STATE();
    case 14:
      if (lookahead == 'e') ADVANCE(22);
      if (lookahead == 's') ADVANCE(31);
      END_STATE();
    case 15:
      if (lookahead == 'e') ADVANCE(16);
      END_STATE();
    case 16:
      if (lookahead == 'f') ADVANCE(32);
      END_STATE();
    case 17:
      if (lookahead == 'g') ADVANCE(18);
      END_STATE();
    case 18:
      if (lookahead == 'h') ADVANCE(33);
      END_STATE();
    case 19:
      if (lookahead == 'i') ADVANCE(17);
      END_STATE();
    case 20:
      if (lookahead == 'l') ADVANCE(11);
      END_STATE();
    case 21:
      if (lookahead == 'm') ADVANCE(119);
      END_STATE();
    case 22:
      if (lookahead == 'n') ADVANCE(12);
      END_STATE();
    case 23:
      if (lookahead == 'o') ADVANCE(26);
      END_STATE();
    case 24:
      if (lookahead == 'o') ADVANCE(21);
      END_STATE();
    case 25:
      if (lookahead == 'o') ADVANCE(36);
      END_STATE();
    case 26:
      if (lookahead == 'p') ADVANCE(117);
      END_STATE();
    case 27:
      if (lookahead == 'r') ADVANCE(34);
      END_STATE();
    case 28:
      if (lookahead == 's') ADVANCE(31);
      END_STATE();
    case 29:
      if (lookahead == 's') ADVANCE(91);
      END_STATE();
    case 30:
      if (lookahead == 's') ADVANCE(29);
      END_STATE();
    case 31:
      if (lookahead == 't') ADVANCE(10);
      END_STATE();
    case 32:
      if (lookahead == 't') ADVANCE(113);
      END_STATE();
    case 33:
      if (lookahead == 't') ADVANCE(115);
      END_STATE();
    case 34:
      if (lookahead == 't') ADVANCE(38);
      END_STATE();
    case 35:
      if (lookahead == 't') ADVANCE(24);
      END_STATE();
    case 36:
      if (lookahead == 't') ADVANCE(35);
      END_STATE();
    case 37:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(42);
      END_STATE();
    case 38:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(41);
      END_STATE();
    case 39:
      if (eof) ADVANCE(40);
      if (lookahead == '"') ADVANCE(125);
      if (lookahead == '\'') ADVANCE(124);
      if (lookahead == '@') ADVANCE(28);
      if (lookahead == 't') ADVANCE(149);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(39)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(sym_start_directive);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(41);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(sym_end_directive);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(42);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(sym_end_directive);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(43);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == '-') ADVANCE(47);
      if (lookahead == '>') ADVANCE(181);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == '-') ADVANCE(185);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == '=') ADVANCE(90);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == '>') ADVANCE(183);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'a') ADVANCE(75);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'a') ADVANCE(69);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'a') ADVANCE(77);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'a') ADVANCE(56);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'b') ADVANCE(78);
      if (lookahead == 'c') ADVANCE(84);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'b') ADVANCE(65);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'c') ADVANCE(62);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'c') ADVANCE(80);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'c') ADVANCE(81);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'd') ADVANCE(89);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'e') ADVANCE(68);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'e') ADVANCE(112);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'e') ADVANCE(55);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'e') ADVANCE(122);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'i') ADVANCE(72);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'i') ADVANCE(54);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'i') ADVANCE(83);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'j') ADVANCE(60);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'l') ADVANCE(50);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'l') ADVANCE(61);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'n') ADVANCE(57);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'n') ADVANCE(82);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'o') ADVANCE(79);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'o') ADVANCE(73);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'p') ADVANCE(49);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'r') ADVANCE(108);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'r') ADVANCE(51);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 'r') ADVANCE(85);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 's') ADVANCE(93);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 's') ADVANCE(76);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 's') ADVANCE(86);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 't') ADVANCE(59);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 't') ADVANCE(106);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 't') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 't') ADVANCE(110);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 't') ADVANCE(67);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 't') ADVANCE(71);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 't') ADVANCE(63);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == 't') ADVANCE(74);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(124);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(87);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(sym_diagram_name);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(sym_diagram_name);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(43);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(sym_diagram_name);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(anon_sym_class);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(anon_sym_class);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(anon_sym_class);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(sym_abstract_keyword);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(sym_abstract_keyword);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(anon_sym_LPAREN_RPAREN);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(anon_sym_PLUS);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(anon_sym_DASH);
      if (lookahead == '-') ADVANCE(9);
      if (lookahead == '>') ADVANCE(180);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(anon_sym_POUND);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(anon_sym_TILDE);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(anon_sym_object);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(anon_sym_object);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(anon_sym_actor);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(anon_sym_actor);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(anon_sym_participant);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 110:
      ACCEPT_TOKEN(anon_sym_participant);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 111:
      ACCEPT_TOKEN(anon_sym_note);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 112:
      ACCEPT_TOKEN(anon_sym_note);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 113:
      ACCEPT_TOKEN(anon_sym_left);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(anon_sym_left);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 115:
      ACCEPT_TOKEN(anon_sym_right);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(anon_sym_right);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 117:
      ACCEPT_TOKEN(anon_sym_top);
      END_STATE();
    case 118:
      ACCEPT_TOKEN(anon_sym_top);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 119:
      ACCEPT_TOKEN(anon_sym_bottom);
      END_STATE();
    case 120:
      ACCEPT_TOKEN(anon_sym_bottom);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 121:
      ACCEPT_TOKEN(anon_sym_title);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 122:
      ACCEPT_TOKEN(anon_sym_title);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(88);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 123:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\n') ADVANCE(128);
      if (lookahead == '"') ADVANCE(124);
      if (lookahead != 0) ADVANCE(123);
      END_STATE();
    case 124:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(124);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 126:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 127:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead == '\'') ADVANCE(123);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(127);
      if (lookahead != 0 &&
          lookahead != '"') ADVANCE(128);
      END_STATE();
    case 128:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead != 0 &&
          lookahead != '"') ADVANCE(128);
      END_STATE();
    case 129:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(163);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 130:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(154);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 131:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(165);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(137);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 133:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'b') ADVANCE(166);
      if (lookahead == 'c') ADVANCE(172);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 134:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'b') ADVANCE(150);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 135:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(146);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 136:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(169);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 137:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(170);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 138:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(142);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 139:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(111);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 140:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(136);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 141:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(121);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 142:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'f') ADVANCE(167);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 143:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'g') ADVANCE(144);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 144:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'h') ADVANCE(168);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 145:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(143);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 146:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(160);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 147:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(135);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 148:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(173);
      if (lookahead == 'o') ADVANCE(159);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 149:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(173);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 150:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'j') ADVANCE(140);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 151:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(131);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 152:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(141);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 153:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'm') ADVANCE(120);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 154:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(171);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 155:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(153);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 156:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(178);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 157:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(174);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 158:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(161);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 159:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'p') ADVANCE(118);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 160:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'p') ADVANCE(130);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 161:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(107);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 162:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(132);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 163:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(175);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 164:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(92);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 165:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(164);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 166:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(176);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 167:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(114);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 168:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(116);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 169:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(105);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 170:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(94);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 171:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(109);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 172:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(158);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 173:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(152);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 174:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(139);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 175:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(147);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 176:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(162);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 177:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(155);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 178:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(177);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 179:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 180:
      ACCEPT_TOKEN(anon_sym_DASH_GT);
      END_STATE();
    case 181:
      ACCEPT_TOKEN(anon_sym_DASH_GT);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 182:
      ACCEPT_TOKEN(anon_sym_DASH_DASH_GT);
      END_STATE();
    case 183:
      ACCEPT_TOKEN(anon_sym_DASH_DASH_GT);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 184:
      ACCEPT_TOKEN(anon_sym_LT_DASH);
      if (lookahead == '-') ADVANCE(186);
      END_STATE();
    case 185:
      ACCEPT_TOKEN(anon_sym_LT_DASH);
      if (lookahead == '-') ADVANCE(187);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 186:
      ACCEPT_TOKEN(anon_sym_LT_DASH_DASH);
      END_STATE();
    case 187:
      ACCEPT_TOKEN(anon_sym_LT_DASH_DASH);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(90);
      END_STATE();
    case 188:
      ACCEPT_TOKEN(sym_divider);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 39},
  [2] = {.lex_state = 3},
  [3] = {.lex_state = 1},
  [4] = {.lex_state = 1},
  [5] = {.lex_state = 1},
  [6] = {.lex_state = 1},
  [7] = {.lex_state = 1},
  [8] = {.lex_state = 1},
  [9] = {.lex_state = 1},
  [10] = {.lex_state = 1},
  [11] = {.lex_state = 1},
  [12] = {.lex_state = 1},
  [13] = {.lex_state = 1},
  [14] = {.lex_state = 1},
  [15] = {.lex_state = 1},
  [16] = {.lex_state = 1},
  [17] = {.lex_state = 1},
  [18] = {.lex_state = 1},
  [19] = {.lex_state = 1},
  [20] = {.lex_state = 1},
  [21] = {.lex_state = 4},
  [22] = {.lex_state = 4},
  [23] = {.lex_state = 4},
  [24] = {.lex_state = 39},
  [25] = {.lex_state = 39},
  [26] = {.lex_state = 4},
  [27] = {.lex_state = 2},
  [28] = {.lex_state = 4},
  [29] = {.lex_state = 4},
  [30] = {.lex_state = 4},
  [31] = {.lex_state = 4},
  [32] = {.lex_state = 4},
  [33] = {.lex_state = 4},
  [34] = {.lex_state = 4},
  [35] = {.lex_state = 39},
  [36] = {.lex_state = 39},
  [37] = {.lex_state = 39},
  [38] = {.lex_state = 39},
  [39] = {.lex_state = 39},
  [40] = {.lex_state = 39},
  [41] = {.lex_state = 4},
  [42] = {.lex_state = 0},
  [43] = {.lex_state = 0},
  [44] = {.lex_state = 4},
  [45] = {.lex_state = 0},
  [46] = {.lex_state = 4},
  [47] = {.lex_state = 0},
  [48] = {.lex_state = 0},
  [49] = {.lex_state = 4},
  [50] = {.lex_state = 4},
  [51] = {.lex_state = 0},
  [52] = {.lex_state = 4},
  [53] = {.lex_state = 4},
  [54] = {.lex_state = 0},
  [55] = {.lex_state = 4},
  [56] = {.lex_state = 4},
  [57] = {.lex_state = 4},
  [58] = {.lex_state = 2},
  [59] = {.lex_state = 0},
  [60] = {.lex_state = 127},
  [61] = {.lex_state = 0},
  [62] = {.lex_state = 4},
  [63] = {.lex_state = 0},
  [64] = {.lex_state = 127},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_start_directive] = ACTIONS(1),
    [sym_end_directive] = ACTIONS(1),
    [anon_sym_class] = ACTIONS(1),
    [sym_abstract_keyword] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_LPAREN_RPAREN] = ACTIONS(1),
    [anon_sym_PLUS] = ACTIONS(1),
    [anon_sym_DASH] = ACTIONS(1),
    [anon_sym_POUND] = ACTIONS(1),
    [anon_sym_TILDE] = ACTIONS(1),
    [anon_sym_object] = ACTIONS(1),
    [anon_sym_actor] = ACTIONS(1),
    [anon_sym_participant] = ACTIONS(1),
    [anon_sym_note] = ACTIONS(1),
    [anon_sym_left] = ACTIONS(1),
    [anon_sym_right] = ACTIONS(1),
    [anon_sym_top] = ACTIONS(1),
    [anon_sym_bottom] = ACTIONS(1),
    [anon_sym_title] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [anon_sym_DASH_GT] = ACTIONS(1),
    [anon_sym_DASH_DASH_GT] = ACTIONS(1),
    [anon_sym_LT_DASH] = ACTIONS(1),
    [anon_sym_LT_DASH_DASH] = ACTIONS(1),
    [sym_divider] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(51),
    [sym_diagram_block] = STATE(25),
    [sym_standalone_statement] = STATE(25),
    [sym_title_statement] = STATE(36),
    [sym_string] = STATE(36),
    [aux_sym_source_file_repeat1] = STATE(25),
    [ts_builtin_sym_end] = ACTIONS(5),
    [sym_start_directive] = ACTIONS(7),
    [anon_sym_title] = ACTIONS(9),
    [sym_comment] = ACTIONS(11),
    [anon_sym_DQUOTE] = ACTIONS(13),
    [sym_identifier] = ACTIONS(15),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 13,
    ACTIONS(17), 1,
      sym_end_directive,
    ACTIONS(19), 1,
      sym_diagram_name,
    ACTIONS(21), 1,
      anon_sym_class,
    ACTIONS(23), 1,
      sym_abstract_keyword,
    ACTIONS(25), 1,
      anon_sym_object,
    ACTIONS(27), 1,
      anon_sym_actor,
    ACTIONS(29), 1,
      anon_sym_participant,
    ACTIONS(31), 1,
      anon_sym_note,
    ACTIONS(33), 1,
      anon_sym_title,
    ACTIONS(37), 1,
      anon_sym_DQUOTE,
    ACTIONS(35), 3,
      sym_comment,
      sym_identifier,
      sym_divider,
    ACTIONS(39), 4,
      anon_sym_DASH_GT,
      anon_sym_DASH_DASH_GT,
      anon_sym_LT_DASH,
      anon_sym_LT_DASH_DASH,
    STATE(5), 10,
      sym__statement,
      sym_class_declaration,
      sym_object_declaration,
      sym_actor_declaration,
      sym_participant_declaration,
      sym_note_statement,
      sym_title_statement,
      sym_string,
      sym_arrow,
      aux_sym_diagram_block_repeat1,
  [54] = 14,
    ACTIONS(21), 1,
      anon_sym_class,
    ACTIONS(23), 1,
      sym_abstract_keyword,
    ACTIONS(25), 1,
      anon_sym_object,
    ACTIONS(27), 1,
      anon_sym_actor,
    ACTIONS(29), 1,
      anon_sym_participant,
    ACTIONS(31), 1,
      anon_sym_note,
    ACTIONS(33), 1,
      anon_sym_title,
    ACTIONS(39), 1,
      anon_sym_LT_DASH,
    ACTIONS(41), 1,
      sym_end_directive,
    ACTIONS(45), 1,
      anon_sym_DQUOTE,
    ACTIONS(47), 1,
      sym_identifier,
    ACTIONS(43), 2,
      sym_comment,
      sym_divider,
    ACTIONS(49), 3,
      anon_sym_DASH_GT,
      anon_sym_DASH_DASH_GT,
      anon_sym_LT_DASH_DASH,
    STATE(4), 10,
      sym__statement,
      sym_class_declaration,
      sym_object_declaration,
      sym_actor_declaration,
      sym_participant_declaration,
      sym_note_statement,
      sym_title_statement,
      sym_string,
      sym_arrow,
      aux_sym_diagram_block_repeat1,
  [109] = 14,
    ACTIONS(21), 1,
      anon_sym_class,
    ACTIONS(23), 1,
      sym_abstract_keyword,
    ACTIONS(25), 1,
      anon_sym_object,
    ACTIONS(27), 1,
      anon_sym_actor,
    ACTIONS(29), 1,
      anon_sym_participant,
    ACTIONS(31), 1,
      anon_sym_note,
    ACTIONS(33), 1,
      anon_sym_title,
    ACTIONS(39), 1,
      anon_sym_LT_DASH,
    ACTIONS(45), 1,
      anon_sym_DQUOTE,
    ACTIONS(51), 1,
      sym_end_directive,
    ACTIONS(55), 1,
      sym_identifier,
    ACTIONS(53), 2,
      sym_comment,
      sym_divider,
    ACTIONS(49), 3,
      anon_sym_DASH_GT,
      anon_sym_DASH_DASH_GT,
      anon_sym_LT_DASH_DASH,
    STATE(6), 10,
      sym__statement,
      sym_class_declaration,
      sym_object_declaration,
      sym_actor_declaration,
      sym_participant_declaration,
      sym_note_statement,
      sym_title_statement,
      sym_string,
      sym_arrow,
      aux_sym_diagram_block_repeat1,
  [164] = 14,
    ACTIONS(21), 1,
      anon_sym_class,
    ACTIONS(23), 1,
      sym_abstract_keyword,
    ACTIONS(25), 1,
      anon_sym_object,
    ACTIONS(27), 1,
      anon_sym_actor,
    ACTIONS(29), 1,
      anon_sym_participant,
    ACTIONS(31), 1,
      anon_sym_note,
    ACTIONS(33), 1,
      anon_sym_title,
    ACTIONS(39), 1,
      anon_sym_LT_DASH,
    ACTIONS(41), 1,
      sym_end_directive,
    ACTIONS(45), 1,
      anon_sym_DQUOTE,
    ACTIONS(55), 1,
      sym_identifier,
    ACTIONS(53), 2,
      sym_comment,
      sym_divider,
    ACTIONS(49), 3,
      anon_sym_DASH_GT,
      anon_sym_DASH_DASH_GT,
      anon_sym_LT_DASH_DASH,
    STATE(6), 10,
      sym__statement,
      sym_class_declaration,
      sym_object_declaration,
      sym_actor_declaration,
      sym_participant_declaration,
      sym_note_statement,
      sym_title_statement,
      sym_string,
      sym_arrow,
      aux_sym_diagram_block_repeat1,
  [219] = 14,
    ACTIONS(57), 1,
      sym_end_directive,
    ACTIONS(59), 1,
      anon_sym_class,
    ACTIONS(62), 1,
      sym_abstract_keyword,
    ACTIONS(65), 1,
      anon_sym_object,
    ACTIONS(68), 1,
      anon_sym_actor,
    ACTIONS(71), 1,
      anon_sym_participant,
    ACTIONS(74), 1,
      anon_sym_note,
    ACTIONS(77), 1,
      anon_sym_title,
    ACTIONS(83), 1,
      anon_sym_DQUOTE,
    ACTIONS(86), 1,
      sym_identifier,
    ACTIONS(92), 1,
      anon_sym_LT_DASH,
    ACTIONS(80), 2,
      sym_comment,
      sym_divider,
    ACTIONS(89), 3,
      anon_sym_DASH_GT,
      anon_sym_DASH_DASH_GT,
      anon_sym_LT_DASH_DASH,
    STATE(6), 10,
      sym__statement,
      sym_class_declaration,
      sym_object_declaration,
      sym_actor_declaration,
      sym_participant_declaration,
      sym_note_statement,
      sym_title_statement,
      sym_string,
      sym_arrow,
      aux_sym_diagram_block_repeat1,
  [274] = 4,
    ACTIONS(99), 1,
      anon_sym_LBRACE,
    STATE(11), 1,
      sym_class_body,
    ACTIONS(95), 7,
      sym_end_directive,
      sym_comment,
      anon_sym_DQUOTE,
      anon_sym_DASH_GT,
      anon_sym_DASH_DASH_GT,
      anon_sym_LT_DASH_DASH,
      sym_divider,
    ACTIONS(97), 9,
      anon_sym_class,
      sym_abstract_keyword,
      anon_sym_object,
      anon_sym_actor,
      anon_sym_participant,
      anon_sym_note,
      anon_sym_title,
      sym_identifier,
      anon_sym_LT_DASH,
  [301] = 4,
    ACTIONS(99), 1,
      anon_sym_LBRACE,
    STATE(15), 1,
      sym_class_body,
    ACTIONS(101), 7,
      sym_end_directive,
      sym_comment,
      anon_sym_DQUOTE,
      anon_sym_DASH_GT,
      anon_sym_DASH_DASH_GT,
      anon_sym_LT_DASH_DASH,
      sym_divider,
    ACTIONS(103), 9,
      anon_sym_class,
      sym_abstract_keyword,
      anon_sym_object,
      anon_sym_actor,
      anon_sym_participant,
      anon_sym_note,
      anon_sym_title,
      sym_identifier,
      anon_sym_LT_DASH,
  [328] = 2,
    ACTIONS(105), 7,
      sym_end_directive,
      sym_comment,
      anon_sym_DQUOTE,
      anon_sym_DASH_GT,
      anon_sym_DASH_DASH_GT,
      anon_sym_LT_DASH_DASH,
      sym_divider,
    ACTIONS(107), 9,
      anon_sym_class,
      sym_abstract_keyword,
      anon_sym_object,
      anon_sym_actor,
      anon_sym_participant,
      anon_sym_note,
      anon_sym_title,
      sym_identifier,
      anon_sym_LT_DASH,
  [349] = 2,
    ACTIONS(109), 7,
      sym_end_directive,
      sym_comment,
      anon_sym_DQUOTE,
      anon_sym_DASH_GT,
      anon_sym_DASH_DASH_GT,
      anon_sym_LT_DASH_DASH,
      sym_divider,
    ACTIONS(111), 9,
      anon_sym_class,
      sym_abstract_keyword,
      anon_sym_object,
      anon_sym_actor,
      anon_sym_participant,
      anon_sym_note,
      anon_sym_title,
      sym_identifier,
      anon_sym_LT_DASH,
  [370] = 2,
    ACTIONS(113), 7,
      sym_end_directive,
      sym_comment,
      anon_sym_DQUOTE,
      anon_sym_DASH_GT,
      anon_sym_DASH_DASH_GT,
      anon_sym_LT_DASH_DASH,
      sym_divider,
    ACTIONS(115), 9,
      anon_sym_class,
      sym_abstract_keyword,
      anon_sym_object,
      anon_sym_actor,
      anon_sym_participant,
      anon_sym_note,
      anon_sym_title,
      sym_identifier,
      anon_sym_LT_DASH,
  [391] = 2,
    ACTIONS(117), 7,
      sym_end_directive,
      sym_comment,
      anon_sym_DQUOTE,
      anon_sym_DASH_GT,
      anon_sym_DASH_DASH_GT,
      anon_sym_LT_DASH_DASH,
      sym_divider,
    ACTIONS(119), 9,
      anon_sym_class,
      sym_abstract_keyword,
      anon_sym_object,
      anon_sym_actor,
      anon_sym_participant,
      anon_sym_note,
      anon_sym_title,
      sym_identifier,
      anon_sym_LT_DASH,
  [412] = 2,
    ACTIONS(121), 7,
      sym_end_directive,
      sym_comment,
      anon_sym_DQUOTE,
      anon_sym_DASH_GT,
      anon_sym_DASH_DASH_GT,
      anon_sym_LT_DASH_DASH,
      sym_divider,
    ACTIONS(123), 9,
      anon_sym_class,
      sym_abstract_keyword,
      anon_sym_object,
      anon_sym_actor,
      anon_sym_participant,
      anon_sym_note,
      anon_sym_title,
      sym_identifier,
      anon_sym_LT_DASH,
  [433] = 2,
    ACTIONS(125), 7,
      sym_end_directive,
      sym_comment,
      anon_sym_DQUOTE,
      anon_sym_DASH_GT,
      anon_sym_DASH_DASH_GT,
      anon_sym_LT_DASH_DASH,
      sym_divider,
    ACTIONS(127), 9,
      anon_sym_class,
      sym_abstract_keyword,
      anon_sym_object,
      anon_sym_actor,
      anon_sym_participant,
      anon_sym_note,
      anon_sym_title,
      sym_identifier,
      anon_sym_LT_DASH,
  [454] = 2,
    ACTIONS(95), 7,
      sym_end_directive,
      sym_comment,
      anon_sym_DQUOTE,
      anon_sym_DASH_GT,
      anon_sym_DASH_DASH_GT,
      anon_sym_LT_DASH_DASH,
      sym_divider,
    ACTIONS(97), 9,
      anon_sym_class,
      sym_abstract_keyword,
      anon_sym_object,
      anon_sym_actor,
      anon_sym_participant,
      anon_sym_note,
      anon_sym_title,
      sym_identifier,
      anon_sym_LT_DASH,
  [475] = 2,
    ACTIONS(129), 7,
      sym_end_directive,
      sym_comment,
      anon_sym_DQUOTE,
      anon_sym_DASH_GT,
      anon_sym_DASH_DASH_GT,
      anon_sym_LT_DASH_DASH,
      sym_divider,
    ACTIONS(131), 9,
      anon_sym_class,
      sym_abstract_keyword,
      anon_sym_object,
      anon_sym_actor,
      anon_sym_participant,
      anon_sym_note,
      anon_sym_title,
      sym_identifier,
      anon_sym_LT_DASH,
  [496] = 2,
    ACTIONS(133), 7,
      sym_end_directive,
      sym_comment,
      anon_sym_DQUOTE,
      anon_sym_DASH_GT,
      anon_sym_DASH_DASH_GT,
      anon_sym_LT_DASH_DASH,
      sym_divider,
    ACTIONS(135), 9,
      anon_sym_class,
      sym_abstract_keyword,
      anon_sym_object,
      anon_sym_actor,
      anon_sym_participant,
      anon_sym_note,
      anon_sym_title,
      sym_identifier,
      anon_sym_LT_DASH,
  [517] = 2,
    ACTIONS(137), 7,
      sym_end_directive,
      sym_comment,
      anon_sym_DQUOTE,
      anon_sym_DASH_GT,
      anon_sym_DASH_DASH_GT,
      anon_sym_LT_DASH_DASH,
      sym_divider,
    ACTIONS(139), 9,
      anon_sym_class,
      sym_abstract_keyword,
      anon_sym_object,
      anon_sym_actor,
      anon_sym_participant,
      anon_sym_note,
      anon_sym_title,
      sym_identifier,
      anon_sym_LT_DASH,
  [538] = 2,
    ACTIONS(141), 7,
      sym_end_directive,
      sym_comment,
      anon_sym_DQUOTE,
      anon_sym_DASH_GT,
      anon_sym_DASH_DASH_GT,
      anon_sym_LT_DASH_DASH,
      sym_divider,
    ACTIONS(143), 9,
      anon_sym_class,
      sym_abstract_keyword,
      anon_sym_object,
      anon_sym_actor,
      anon_sym_participant,
      anon_sym_note,
      anon_sym_title,
      sym_identifier,
      anon_sym_LT_DASH,
  [559] = 2,
    ACTIONS(145), 7,
      sym_end_directive,
      sym_comment,
      anon_sym_DQUOTE,
      anon_sym_DASH_GT,
      anon_sym_DASH_DASH_GT,
      anon_sym_LT_DASH_DASH,
      sym_divider,
    ACTIONS(147), 9,
      anon_sym_class,
      sym_abstract_keyword,
      anon_sym_object,
      anon_sym_actor,
      anon_sym_participant,
      anon_sym_note,
      anon_sym_title,
      sym_identifier,
      anon_sym_LT_DASH,
  [580] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(149), 1,
      anon_sym_RBRACE,
    ACTIONS(153), 1,
      sym_identifier,
    STATE(57), 1,
      sym_visibility,
    STATE(23), 2,
      sym_class_member,
      aux_sym_class_body_repeat1,
    STATE(29), 2,
      sym_field_declaration,
      sym_method_declaration,
    ACTIONS(151), 4,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_POUND,
      anon_sym_TILDE,
  [607] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(153), 1,
      sym_identifier,
    ACTIONS(155), 1,
      anon_sym_RBRACE,
    STATE(57), 1,
      sym_visibility,
    STATE(21), 2,
      sym_class_member,
      aux_sym_class_body_repeat1,
    STATE(29), 2,
      sym_field_declaration,
      sym_method_declaration,
    ACTIONS(151), 4,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_POUND,
      anon_sym_TILDE,
  [634] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(157), 1,
      anon_sym_RBRACE,
    ACTIONS(162), 1,
      sym_identifier,
    STATE(57), 1,
      sym_visibility,
    STATE(23), 2,
      sym_class_member,
      aux_sym_class_body_repeat1,
    STATE(29), 2,
      sym_field_declaration,
      sym_method_declaration,
    ACTIONS(159), 4,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_POUND,
      anon_sym_TILDE,
  [661] = 8,
    ACTIONS(165), 1,
      ts_builtin_sym_end,
    ACTIONS(167), 1,
      sym_start_directive,
    ACTIONS(170), 1,
      anon_sym_title,
    ACTIONS(173), 1,
      sym_comment,
    ACTIONS(176), 1,
      anon_sym_DQUOTE,
    ACTIONS(179), 1,
      sym_identifier,
    STATE(36), 2,
      sym_title_statement,
      sym_string,
    STATE(24), 3,
      sym_diagram_block,
      sym_standalone_statement,
      aux_sym_source_file_repeat1,
  [689] = 8,
    ACTIONS(7), 1,
      sym_start_directive,
    ACTIONS(9), 1,
      anon_sym_title,
    ACTIONS(11), 1,
      sym_comment,
    ACTIONS(13), 1,
      anon_sym_DQUOTE,
    ACTIONS(15), 1,
      sym_identifier,
    ACTIONS(182), 1,
      ts_builtin_sym_end,
    STATE(36), 2,
      sym_title_statement,
      sym_string,
    STATE(24), 3,
      sym_diagram_block,
      sym_standalone_statement,
      aux_sym_source_file_repeat1,
  [717] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(186), 1,
      anon_sym_COLON,
    ACTIONS(184), 6,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_POUND,
      anon_sym_TILDE,
      sym_identifier,
  [732] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(45), 1,
      anon_sym_DQUOTE,
    STATE(19), 1,
      sym_string,
    STATE(59), 1,
      sym_note_position,
    ACTIONS(188), 4,
      anon_sym_left,
      anon_sym_right,
      anon_sym_top,
      anon_sym_bottom,
  [751] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(192), 1,
      anon_sym_COLON,
    ACTIONS(190), 6,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_POUND,
      anon_sym_TILDE,
      sym_identifier,
  [766] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(194), 6,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_POUND,
      anon_sym_TILDE,
      sym_identifier,
  [778] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(196), 6,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_POUND,
      anon_sym_TILDE,
      sym_identifier,
  [790] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(198), 6,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_POUND,
      anon_sym_TILDE,
      sym_identifier,
  [802] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(200), 6,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_POUND,
      anon_sym_TILDE,
      sym_identifier,
  [814] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(202), 6,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_POUND,
      anon_sym_TILDE,
      sym_identifier,
  [826] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(204), 6,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_POUND,
      anon_sym_TILDE,
      sym_identifier,
  [838] = 2,
    ACTIONS(208), 2,
      anon_sym_title,
      sym_identifier,
    ACTIONS(206), 4,
      ts_builtin_sym_end,
      sym_start_directive,
      sym_comment,
      anon_sym_DQUOTE,
  [849] = 2,
    ACTIONS(212), 2,
      anon_sym_title,
      sym_identifier,
    ACTIONS(210), 4,
      ts_builtin_sym_end,
      sym_start_directive,
      sym_comment,
      anon_sym_DQUOTE,
  [860] = 2,
    ACTIONS(127), 2,
      anon_sym_title,
      sym_identifier,
    ACTIONS(125), 4,
      ts_builtin_sym_end,
      sym_start_directive,
      sym_comment,
      anon_sym_DQUOTE,
  [871] = 2,
    ACTIONS(216), 2,
      anon_sym_title,
      sym_identifier,
    ACTIONS(214), 4,
      ts_builtin_sym_end,
      sym_start_directive,
      sym_comment,
      anon_sym_DQUOTE,
  [882] = 2,
    ACTIONS(147), 2,
      anon_sym_title,
      sym_identifier,
    ACTIONS(145), 4,
      ts_builtin_sym_end,
      sym_start_directive,
      sym_comment,
      anon_sym_DQUOTE,
  [893] = 2,
    ACTIONS(220), 2,
      anon_sym_title,
      sym_identifier,
    ACTIONS(218), 4,
      ts_builtin_sym_end,
      sym_start_directive,
      sym_comment,
      anon_sym_DQUOTE,
  [904] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(222), 1,
      sym_identifier,
    STATE(31), 1,
      sym_type_name,
  [914] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(224), 1,
      anon_sym_COLON,
    ACTIONS(226), 1,
      anon_sym_LPAREN_RPAREN,
  [924] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(45), 1,
      anon_sym_DQUOTE,
    STATE(20), 1,
      sym_string,
  [934] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(222), 1,
      sym_identifier,
    STATE(30), 1,
      sym_type_name,
  [944] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(13), 1,
      anon_sym_DQUOTE,
    STATE(39), 1,
      sym_string,
  [954] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(222), 1,
      sym_identifier,
    STATE(33), 1,
      sym_type_name,
  [964] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(45), 1,
      anon_sym_DQUOTE,
    STATE(9), 1,
      sym_string,
  [974] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(228), 1,
      anon_sym_COLON,
    ACTIONS(230), 1,
      anon_sym_LPAREN_RPAREN,
  [984] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(222), 1,
      sym_identifier,
    STATE(32), 1,
      sym_type_name,
  [994] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(232), 1,
      sym_identifier,
  [1001] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(234), 1,
      ts_builtin_sym_end,
  [1008] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(236), 1,
      sym_identifier,
  [1015] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(238), 1,
      sym_identifier,
  [1022] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(240), 1,
      anon_sym_DQUOTE,
  [1029] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(242), 1,
      sym_identifier,
  [1036] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(244), 1,
      sym_identifier,
  [1043] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(246), 1,
      sym_identifier,
  [1050] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(248), 1,
      anon_sym_class,
  [1057] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(250), 1,
      anon_sym_COLON,
  [1064] = 2,
    ACTIONS(252), 1,
      sym_comment,
    ACTIONS(254), 1,
      aux_sym_string_token1,
  [1071] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(256), 1,
      anon_sym_COLON,
  [1078] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(258), 1,
      sym_identifier,
  [1085] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(260), 1,
      anon_sym_DQUOTE,
  [1092] = 2,
    ACTIONS(252), 1,
      sym_comment,
    ACTIONS(262), 1,
      aux_sym_string_token1,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 54,
  [SMALL_STATE(4)] = 109,
  [SMALL_STATE(5)] = 164,
  [SMALL_STATE(6)] = 219,
  [SMALL_STATE(7)] = 274,
  [SMALL_STATE(8)] = 301,
  [SMALL_STATE(9)] = 328,
  [SMALL_STATE(10)] = 349,
  [SMALL_STATE(11)] = 370,
  [SMALL_STATE(12)] = 391,
  [SMALL_STATE(13)] = 412,
  [SMALL_STATE(14)] = 433,
  [SMALL_STATE(15)] = 454,
  [SMALL_STATE(16)] = 475,
  [SMALL_STATE(17)] = 496,
  [SMALL_STATE(18)] = 517,
  [SMALL_STATE(19)] = 538,
  [SMALL_STATE(20)] = 559,
  [SMALL_STATE(21)] = 580,
  [SMALL_STATE(22)] = 607,
  [SMALL_STATE(23)] = 634,
  [SMALL_STATE(24)] = 661,
  [SMALL_STATE(25)] = 689,
  [SMALL_STATE(26)] = 717,
  [SMALL_STATE(27)] = 732,
  [SMALL_STATE(28)] = 751,
  [SMALL_STATE(29)] = 766,
  [SMALL_STATE(30)] = 778,
  [SMALL_STATE(31)] = 790,
  [SMALL_STATE(32)] = 802,
  [SMALL_STATE(33)] = 814,
  [SMALL_STATE(34)] = 826,
  [SMALL_STATE(35)] = 838,
  [SMALL_STATE(36)] = 849,
  [SMALL_STATE(37)] = 860,
  [SMALL_STATE(38)] = 871,
  [SMALL_STATE(39)] = 882,
  [SMALL_STATE(40)] = 893,
  [SMALL_STATE(41)] = 904,
  [SMALL_STATE(42)] = 914,
  [SMALL_STATE(43)] = 924,
  [SMALL_STATE(44)] = 934,
  [SMALL_STATE(45)] = 944,
  [SMALL_STATE(46)] = 954,
  [SMALL_STATE(47)] = 964,
  [SMALL_STATE(48)] = 974,
  [SMALL_STATE(49)] = 984,
  [SMALL_STATE(50)] = 994,
  [SMALL_STATE(51)] = 1001,
  [SMALL_STATE(52)] = 1008,
  [SMALL_STATE(53)] = 1015,
  [SMALL_STATE(54)] = 1022,
  [SMALL_STATE(55)] = 1029,
  [SMALL_STATE(56)] = 1036,
  [SMALL_STATE(57)] = 1043,
  [SMALL_STATE(58)] = 1050,
  [SMALL_STATE(59)] = 1057,
  [SMALL_STATE(60)] = 1064,
  [SMALL_STATE(61)] = 1071,
  [SMALL_STATE(62)] = 1078,
  [SMALL_STATE(63)] = 1085,
  [SMALL_STATE(64)] = 1092,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(45),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(36),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(40),
  [19] = {.entry = {.count = 1, .reusable = false}}, SHIFT(3),
  [21] = {.entry = {.count = 1, .reusable = false}}, SHIFT(50),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(58),
  [25] = {.entry = {.count = 1, .reusable = false}}, SHIFT(62),
  [27] = {.entry = {.count = 1, .reusable = false}}, SHIFT(53),
  [29] = {.entry = {.count = 1, .reusable = false}}, SHIFT(55),
  [31] = {.entry = {.count = 1, .reusable = false}}, SHIFT(27),
  [33] = {.entry = {.count = 1, .reusable = false}}, SHIFT(43),
  [35] = {.entry = {.count = 1, .reusable = false}}, SHIFT(5),
  [37] = {.entry = {.count = 1, .reusable = false}}, SHIFT(64),
  [39] = {.entry = {.count = 1, .reusable = false}}, SHIFT(16),
  [41] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [43] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [45] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [47] = {.entry = {.count = 1, .reusable = false}}, SHIFT(4),
  [49] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [51] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [53] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [55] = {.entry = {.count = 1, .reusable = false}}, SHIFT(6),
  [57] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_diagram_block_repeat1, 2),
  [59] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_diagram_block_repeat1, 2), SHIFT_REPEAT(50),
  [62] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_diagram_block_repeat1, 2), SHIFT_REPEAT(58),
  [65] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_diagram_block_repeat1, 2), SHIFT_REPEAT(62),
  [68] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_diagram_block_repeat1, 2), SHIFT_REPEAT(53),
  [71] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_diagram_block_repeat1, 2), SHIFT_REPEAT(55),
  [74] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_diagram_block_repeat1, 2), SHIFT_REPEAT(27),
  [77] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_diagram_block_repeat1, 2), SHIFT_REPEAT(43),
  [80] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_diagram_block_repeat1, 2), SHIFT_REPEAT(6),
  [83] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_diagram_block_repeat1, 2), SHIFT_REPEAT(64),
  [86] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_diagram_block_repeat1, 2), SHIFT_REPEAT(6),
  [89] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_diagram_block_repeat1, 2), SHIFT_REPEAT(16),
  [92] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_diagram_block_repeat1, 2), SHIFT_REPEAT(16),
  [95] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_class_declaration, 3),
  [97] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_class_declaration, 3),
  [99] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [101] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_class_declaration, 2),
  [103] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_class_declaration, 2),
  [105] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_note_statement, 4),
  [107] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_note_statement, 4),
  [109] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_class_body, 3),
  [111] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_class_body, 3),
  [113] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_class_declaration, 4),
  [115] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_class_declaration, 4),
  [117] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_actor_declaration, 2),
  [119] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_actor_declaration, 2),
  [121] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_class_body, 2),
  [123] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_class_body, 2),
  [125] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 3),
  [127] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string, 3),
  [129] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arrow, 1),
  [131] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_arrow, 1),
  [133] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_object_declaration, 2),
  [135] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_object_declaration, 2),
  [137] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_participant_declaration, 2),
  [139] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_participant_declaration, 2),
  [141] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_note_statement, 2),
  [143] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_note_statement, 2),
  [145] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_title_statement, 2),
  [147] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_title_statement, 2),
  [149] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [151] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [153] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [155] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [157] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_class_body_repeat1, 2),
  [159] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_class_body_repeat1, 2), SHIFT_REPEAT(52),
  [162] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_class_body_repeat1, 2), SHIFT_REPEAT(42),
  [165] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [167] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(2),
  [170] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(45),
  [173] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(36),
  [176] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(60),
  [179] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(36),
  [182] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [184] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_method_declaration, 2),
  [186] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [188] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [190] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_method_declaration, 3),
  [192] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [194] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_class_member, 1),
  [196] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_method_declaration, 5),
  [198] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_declaration, 4),
  [200] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_method_declaration, 4),
  [202] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_declaration, 3),
  [204] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_name, 1),
  [206] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_diagram_block, 3),
  [208] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_diagram_block, 3),
  [210] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_standalone_statement, 1),
  [212] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_standalone_statement, 1),
  [214] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_diagram_block, 4),
  [216] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_diagram_block, 4),
  [218] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_diagram_block, 2),
  [220] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_diagram_block, 2),
  [222] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [224] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [226] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [228] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [230] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [232] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [234] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [236] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_visibility, 1),
  [238] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [240] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [242] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [244] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [246] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [248] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [250] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [252] = {.entry = {.count = 1, .reusable = false}}, SHIFT_EXTRA(),
  [254] = {.entry = {.count = 1, .reusable = false}}, SHIFT(54),
  [256] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_note_position, 1),
  [258] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [260] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [262] = {.entry = {.count = 1, .reusable = false}}, SHIFT(63),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_plantuml(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
