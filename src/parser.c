#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 13
#define STATE_COUNT 12
#define LARGE_STATE_COUNT 4
#define SYMBOL_COUNT 13
#define ALIAS_COUNT 0
#define TOKEN_COUNT 7
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 3
#define MAX_ALIAS_SEQUENCE_LENGTH 3
#define PRODUCTION_ID_COUNT 5

enum {
  sym_identifier = 1,
  anon_sym_SQUOTE = 2,
  aux_sym_comment_line_token1 = 3,
  anon_sym_SLASH_SQUOTE = 4,
  aux_sym_comment_block_token1 = 5,
  anon_sym_SQUOTE_SLASH = 6,
  sym_program = 7,
  sym__definition = 8,
  sym_comment = 9,
  sym_comment_line = 10,
  sym_comment_block = 11,
  aux_sym_program_repeat1 = 12,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_identifier] = "identifier",
  [anon_sym_SQUOTE] = "'",
  [aux_sym_comment_line_token1] = "comment_line_token1",
  [anon_sym_SLASH_SQUOTE] = "/'",
  [aux_sym_comment_block_token1] = "comment_block_token1",
  [anon_sym_SQUOTE_SLASH] = "'/",
  [sym_program] = "program",
  [sym__definition] = "_definition",
  [sym_comment] = "comment",
  [sym_comment_line] = "comment_line",
  [sym_comment_block] = "comment_block",
  [aux_sym_program_repeat1] = "program_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_identifier] = sym_identifier,
  [anon_sym_SQUOTE] = anon_sym_SQUOTE,
  [aux_sym_comment_line_token1] = aux_sym_comment_line_token1,
  [anon_sym_SLASH_SQUOTE] = anon_sym_SLASH_SQUOTE,
  [aux_sym_comment_block_token1] = aux_sym_comment_block_token1,
  [anon_sym_SQUOTE_SLASH] = anon_sym_SQUOTE_SLASH,
  [sym_program] = sym_program,
  [sym__definition] = sym__definition,
  [sym_comment] = sym_comment,
  [sym_comment_line] = sym_comment_line,
  [sym_comment_block] = sym_comment_block,
  [aux_sym_program_repeat1] = aux_sym_program_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_SQUOTE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_comment_line_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_SLASH_SQUOTE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_comment_block_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_SQUOTE_SLASH] = {
    .visible = true,
    .named = false,
  },
  [sym_program] = {
    .visible = true,
    .named = true,
  },
  [sym__definition] = {
    .visible = false,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_comment_line] = {
    .visible = true,
    .named = true,
  },
  [sym_comment_block] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_program_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum {
  field_content = 1,
  field_end = 2,
  field_start = 3,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_content] = "content",
  [field_end] = "end",
  [field_start] = "start",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 2},
  [3] = {.index = 3, .length = 2},
  [4] = {.index = 5, .length = 3},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_start, 0},
  [1] =
    {field_content, 1},
    {field_start, 0},
  [3] =
    {field_end, 1},
    {field_start, 0},
  [5] =
    {field_content, 1},
    {field_end, 2},
    {field_start, 0},
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
      if (eof) ADVANCE(4);
      if (lookahead == '\'') ADVANCE(5);
      if (lookahead == '/') ADVANCE(1);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(0)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(15);
      END_STATE();
    case 1:
      if (lookahead == '\'') ADVANCE(11);
      END_STATE();
    case 2:
      if (lookahead == '\'') ADVANCE(3);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(2)
      END_STATE();
    case 3:
      if (lookahead == '/') ADVANCE(14);
      END_STATE();
    case 4:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 5:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      END_STATE();
    case 6:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(9);
      END_STATE();
    case 7:
      ACCEPT_TOKEN(aux_sym_comment_line_token1);
      if (lookahead == '\'') ADVANCE(6);
      if (lookahead == '/') ADVANCE(8);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(7);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(9);
      END_STATE();
    case 8:
      ACCEPT_TOKEN(aux_sym_comment_line_token1);
      if (lookahead == '\'') ADVANCE(12);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(9);
      END_STATE();
    case 9:
      ACCEPT_TOKEN(aux_sym_comment_line_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(9);
      END_STATE();
    case 10:
      ACCEPT_TOKEN(aux_sym_comment_line_token1);
      if (eof) ADVANCE(4);
      if (lookahead == '\'') ADVANCE(6);
      if (lookahead == '/') ADVANCE(8);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(7);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(9);
      END_STATE();
    case 11:
      ACCEPT_TOKEN(anon_sym_SLASH_SQUOTE);
      END_STATE();
    case 12:
      ACCEPT_TOKEN(anon_sym_SLASH_SQUOTE);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(9);
      END_STATE();
    case 13:
      ACCEPT_TOKEN(aux_sym_comment_block_token1);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(13);
      END_STATE();
    case 14:
      ACCEPT_TOKEN(anon_sym_SQUOTE_SLASH);
      END_STATE();
    case 15:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(15);
      END_STATE();
    default:
      return false;
  }
}

static bool ts_lex_keywords(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 0},
  [2] = {.lex_state = 0},
  [3] = {.lex_state = 0},
  [4] = {.lex_state = 10},
  [5] = {.lex_state = 0},
  [6] = {.lex_state = 0},
  [7] = {.lex_state = 0},
  [8] = {.lex_state = 0},
  [9] = {.lex_state = 13},
  [10] = {.lex_state = 0},
  [11] = {.lex_state = 2},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [anon_sym_SQUOTE] = ACTIONS(1),
    [anon_sym_SLASH_SQUOTE] = ACTIONS(1),
  },
  [1] = {
    [sym_program] = STATE(10),
    [sym__definition] = STATE(2),
    [sym_comment] = STATE(2),
    [sym_comment_line] = STATE(5),
    [sym_comment_block] = STATE(5),
    [aux_sym_program_repeat1] = STATE(2),
    [ts_builtin_sym_end] = ACTIONS(3),
    [anon_sym_SQUOTE] = ACTIONS(5),
    [anon_sym_SLASH_SQUOTE] = ACTIONS(7),
  },
  [2] = {
    [sym__definition] = STATE(3),
    [sym_comment] = STATE(3),
    [sym_comment_line] = STATE(5),
    [sym_comment_block] = STATE(5),
    [aux_sym_program_repeat1] = STATE(3),
    [ts_builtin_sym_end] = ACTIONS(9),
    [anon_sym_SQUOTE] = ACTIONS(5),
    [anon_sym_SLASH_SQUOTE] = ACTIONS(7),
  },
  [3] = {
    [sym__definition] = STATE(3),
    [sym_comment] = STATE(3),
    [sym_comment_line] = STATE(5),
    [sym_comment_block] = STATE(5),
    [aux_sym_program_repeat1] = STATE(3),
    [ts_builtin_sym_end] = ACTIONS(11),
    [anon_sym_SQUOTE] = ACTIONS(13),
    [anon_sym_SLASH_SQUOTE] = ACTIONS(16),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 3,
    ACTIONS(19), 1,
      ts_builtin_sym_end,
    ACTIONS(23), 1,
      aux_sym_comment_line_token1,
    ACTIONS(21), 2,
      anon_sym_SQUOTE,
      anon_sym_SLASH_SQUOTE,
  [11] = 1,
    ACTIONS(25), 3,
      ts_builtin_sym_end,
      anon_sym_SQUOTE,
      anon_sym_SLASH_SQUOTE,
  [17] = 1,
    ACTIONS(27), 3,
      ts_builtin_sym_end,
      anon_sym_SQUOTE,
      anon_sym_SLASH_SQUOTE,
  [23] = 1,
    ACTIONS(29), 3,
      ts_builtin_sym_end,
      anon_sym_SQUOTE,
      anon_sym_SLASH_SQUOTE,
  [29] = 1,
    ACTIONS(31), 3,
      ts_builtin_sym_end,
      anon_sym_SQUOTE,
      anon_sym_SLASH_SQUOTE,
  [35] = 2,
    ACTIONS(33), 1,
      aux_sym_comment_block_token1,
    ACTIONS(35), 1,
      anon_sym_SQUOTE_SLASH,
  [42] = 1,
    ACTIONS(37), 1,
      ts_builtin_sym_end,
  [46] = 1,
    ACTIONS(39), 1,
      anon_sym_SQUOTE_SLASH,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(4)] = 0,
  [SMALL_STATE(5)] = 11,
  [SMALL_STATE(6)] = 17,
  [SMALL_STATE(7)] = 23,
  [SMALL_STATE(8)] = 29,
  [SMALL_STATE(9)] = 35,
  [SMALL_STATE(10)] = 42,
  [SMALL_STATE(11)] = 46,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_program, 0),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [9] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_program, 1),
  [11] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_program_repeat1, 2),
  [13] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_program_repeat1, 2), SHIFT_REPEAT(4),
  [16] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_program_repeat1, 2), SHIFT_REPEAT(9),
  [19] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comment_line, 1, .production_id = 1),
  [21] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comment_line, 1, .production_id = 1),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(6),
  [25] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comment, 1),
  [27] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comment_line, 2, .production_id = 2),
  [29] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comment_block, 2, .production_id = 3),
  [31] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comment_block, 3, .production_id = 4),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [35] = {.entry = {.count = 1, .reusable = false}}, SHIFT(7),
  [37] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [39] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
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
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .keyword_lex_fn = ts_lex_keywords,
    .keyword_capture_token = sym_identifier,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
