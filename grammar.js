/**
 *
 * @param rule
 * @param separator
 */
function sep1(rule, separator) {
  return seq(rule, repeat(seq(separator, rule)));
}

function commonStatements($) {
  return [
    $.title_statement,
    $.caption_statement,
    $.header_statement,
    $.footer_statement,
    $.legend_block,
    $.skinparam_statement,
    $.style_block,
    $.display_directive,
    $.direction_statement,
    $.allow_mixing_statement,
    $.scale_statement,
    $.page_statement,
    $.newpage_statement,
    $.rotate_statement,
    $.minwidth_statement,
    $.namespace_separator,
    $.pragma_statement,
    $.sprite_declaration,
    $.comment,
    $._pp_statement,
  ];
}

function lineBody($) {
  return seq(
    choice($.raw_line, $._newline),
    repeat(choice($.raw_line, $._newline)),
  );
}

function rawBodyDiagram($, start, end, body) {
  return seq(
    alias(token(prec(6, start)), $.diagram_start),
    optional(field('name', $.diagram_name)),
    $._newline,
    optional(field('body', body)),
    alias(token(prec(6, end)), $.diagram_end),
  );
}

module.exports = grammar({
  name: 'plantuml',

  externals: ($) => [
    $._raw_statement,
    $._brace_ahead,
    $._timing_start,
    $._timing_end,
    $._error_sentinel,
  ],

  extras: ($) => [/[ \t]/, $.block_comment],

  word: ($) => $.identifier,

  conflicts: ($) => [
    [$.fork_again],
    [$.split_again],
    [$.relation, $._relation_end],
    [$.enum_member, $.attribute],
    [$._cpp_type_name, $._entity_name],
    [$.enum_member, $._cpp_type_name],
    [$.enum_body, $.enum_member, $._cpp_type_name],
    [$.enum_body, $.enum_member, $.attribute],
    [$.activity_control, $.sequence_frame],
    [$.sequence_else_clause],
    [$.regex_pattern],
    [$.json_content],
    [$.yaml_content],
    [$.hcl_content],
    [$.ditaa_body],
    [$.attribute, $._entity_name],
    [$.ebnf_expression],
    [$.ebnf_concatenation],
    [$.files_dir, $.files_file],
  ],

  rules: {
    source_file: ($) =>
      repeat(
        choice(
          $.uml_diagram,
          $.mindmap_diagram,
          $.wbs_diagram,
          $.gantt_diagram,
          $.timing_diagram,
          $.json_diagram,
          $.yaml_diagram,
          $.hcl_diagram,
          $.nwdiag_diagram,
          $.salt_diagram,
          $.ditaa_diagram,
          $.chen_diagram,
          $.git_diagram,
          $.files_diagram,
          $.chronology_diagram,
          $.ebnf_diagram,
          $.regex_diagram,
          $.packet_diagram,
          $.board_diagram,
          $.wire_diagram,
          $.flow_diagram,
          $.bpm_diagram,
          $.math_diagram,
          $.latex_diagram,
          $.creole_diagram,
          $.dot_diagram,
          $.sprites_diagram,
          $.chart_diagram,
          $.generic_diagram,
          $._statement,
          $._newline,
        ),
      ),

    uml_diagram: ($) =>
      seq(
        $.diagram_start,
        optional(field('name', $.diagram_name)),
        $._newline,
        repeat(choice($._statement, $._newline)),
        $.diagram_end,
      ),

    generic_diagram: ($) =>
      seq(
        alias($._generic_start, $.diagram_start),
        optional(field('name', $.diagram_name)),
        $._newline,
        optional(field('body', $.generic_body)),
        alias($._generic_end, $.diagram_end),
      ),

    mindmap_diagram: ($) =>
      seq(
        alias(token(prec(4, /@startmindmap/i)), $.diagram_start),
        optional(field('name', $.diagram_name)),
        $._newline,
        repeat(choice($._mindmap_statement, $._newline)),
        alias(token(prec(4, /@endmindmap/i)), $.diagram_end),
      ),

    wbs_diagram: ($) =>
      seq(
        alias(token(prec(4, /@startwbs/i)), $.diagram_start),
        optional(field('name', $.diagram_name)),
        $._newline,
        repeat(choice($._wbs_statement, $._newline)),
        alias(token(prec(4, /@endwbs/i)), $.diagram_end),
      ),

    gantt_diagram: ($) =>
      seq(
        alias(token(prec(4, /@startgantt/i)), $.diagram_start),
        optional(field('name', $.diagram_name)),
        $._newline,
        repeat(choice($._gantt_statement, $._newline)),
        alias(token(prec(4, /@endgantt/i)), $.diagram_end),
      ),

    timing_diagram: ($) =>
      seq(
        alias($._timing_start, $.diagram_start),
        optional(field('name', $.diagram_name)),
        $._newline,
        repeat(choice($._timing_statement, $._newline)),
        alias($._timing_end, $.diagram_end),
      ),

    _timing_statement: ($) =>
      choice(
        $.timing_clock,
        $.timing_player_decl,
        $.timing_scale,
        $.timing_directive,
        $.timing_time,
        $.timing_state,
        $.timing_message,
        $.timing_constraint,
        $.timing_highlight,
        $.timing_note,
        ...commonStatements($),
        $.raw_line,
      ),

    timing_time: ($) =>
      seq(token(prec(3, /@\d+(?:\.\d+)?/)), $._newline),

    timing_message: ($) =>
      seq(
        field('left', $.identifier),
        field('operator', token(prec(2, /-{1,2}>|<{1,2}-/))),
        field('right', $.identifier),
        optional(
          seq(':', field('label', alias(token(prec(2, /[^\r\n]+/)), $.label))),
        ),
        $._newline,
      ),

    timing_note: ($) =>
      seq(
        alias(token(prec(5, /note[ \t]+/i)), 'note'),
        optional(field('text', alias($._to_eol, $.label))),
        $._newline,
      ),

    timing_clock: ($) =>
      seq(
        alias(token(prec(5, /clock[ \t]+/i)), 'clock'),
        field('name', $.string),
        optional(seq('as', field('alias', $.identifier))),
        optional(field('options', alias($._to_eol, $.label))),
        $._newline,
      ),

    timing_player_decl: ($) =>
      seq(
        field(
          'kind',
          choice(
            alias(token(prec(5, /robust[ \t]+/i)), 'robust'),
            alias(token(prec(5, /concise[ \t]+/i)), 'concise'),
            alias(token(prec(5, /binary[ \t]+/i)), 'binary'),
            alias(token(prec(5, /analog[ \t]+/i)), 'analog'),
          ),
        ),
        field('name', $.string),
        optional(seq('as', field('alias', $.identifier))),
        optional(field('rest', alias($._to_eol, $.label))),
        $._newline,
      ),

    timing_scale: ($) =>
      prec(
        2,
        seq(
          'scale',
          field('value', $.number),
          'as',
          field('pixels', $.number),
          'pixels',
          $._newline,
        ),
      ),

    timing_directive: ($) =>
      choice(
        seq(
          alias(token(prec(5, /hide[ \t]+time[ \t]+axis/i)), 'hide time axis'),
          $._newline,
        ),
        seq(
          alias(token(prec(5, /use[ \t]+/i)), 'use'),
          'date',
          'format',
          field('format', alias($._to_eol, $.label)),
          $._newline,
        ),
        seq(
          alias(token(prec(5, /pixel[ \t]+/i)), 'pixel'),
          'height',
          field('value', alias($._to_eol, $.label)),
          $._newline,
        ),
        seq(
          alias(token(prec(5, /mode[ \t]+/i)), 'mode'),
          'compact',
          $._newline,
        ),
        seq(
          alias(token(prec(5, /ticks[ \t]+/i)), 'ticks'),
          field('value', alias($._to_eol, $.label)),
          $._newline,
        ),
        seq(
          alias(token(prec(5, /printscale[ \t]+/i)), 'printscale'),
          field('value', alias($._to_eol, $.label)),
          $._newline,
        ),
      ),

    timing_state: ($) =>
      seq(
        optional(seq('@', field('prefix_time', $.number))),
        field('player', $.identifier),
        optional(seq('@', field('time', $.number))),
        optional(seq('is', field('value', alias(token(/[^\r\n]+/), $.label)))),
        $._newline,
      ),

    timing_constraint: ($) =>
      seq(
        alias(token(prec(5, /constraint[ \t]+/i)), 'constraint'),
        optional(
          field('text', alias(token(/[^\r\n]+/), $.label)),
        ),
        $._newline,
      ),

    timing_highlight: ($) =>
      seq(
        alias(token(prec(5, /highlight[ \t]+/i)), 'highlight'),
        optional(field('text', alias($._to_eol, $.label))),
        $._newline,
      ),

    json_diagram: ($) =>
      seq(
        alias(token(prec(6, /@startjson/i)), $.diagram_start),
        optional(field('name', $.diagram_name)),
        $._newline,
        repeat(choice($.json_highlight, $.json_content, $._newline)),
        alias(token(prec(6, /@endjson/i)), $.diagram_end),
      ),

    json_content: ($) =>
      seq($._json_line, $._newline, repeat(seq($._json_line, $._newline))),

    json_highlight: ($) =>
      seq(
        alias(token(prec(6, /#highlight/)), '#highlight'),
        field('path', choice($.string, alias(token(prec(3, /all/)), $.keyword))),
        optional(seq('as', field('color', $.string))),
        choice(
          $._newline,
          seq(
            '{',
            $._newline,
            repeat(choice($._json_line, $._newline)),
            '}',
            $._newline,
          ),
        ),
      ),

    _json_line: ($) => token(prec(-5, /[^\r\n]+/)),

    yaml_diagram: ($) =>
      seq(
        alias(token(prec(6, /@startyaml/i)), $.diagram_start),
        optional(field('name', $.diagram_name)),
        $._newline,
        repeat(choice($.yaml_highlight, $.yaml_content, $._newline)),
        alias(token(prec(6, /@endyaml/i)), $.diagram_end),
      ),

    yaml_content: ($) =>
      seq($._yaml_line, $._newline, repeat(seq($._yaml_line, $._newline))),

    yaml_highlight: ($) =>
      seq(
        alias(token(prec(6, /#highlight/)), '#highlight'),
        field('path', choice($.string, alias(token(prec(3, /all/)), $.keyword))),
        optional(seq('as', field('color', $.string))),
        choice(
          $._newline,
          seq(
            '{',
            $._newline,
            repeat(choice($._yaml_line, $._newline)),
            '}',
            $._newline,
          ),
        ),
      ),

    _yaml_line: ($) => token(prec(-5, /[^\r\n]+/)),

    hcl_diagram: ($) =>
      seq(
        alias(token(prec(6, /@starthcl/i)), $.diagram_start),
        optional(field('name', $.diagram_name)),
        $._newline,
        repeat(choice($.hcl_highlight, $.hcl_content, $._newline)),
        alias(token(prec(6, /@endhcl/i)), $.diagram_end),
      ),

    hcl_content: ($) =>
      seq($._hcl_line, $._newline, repeat(seq($._hcl_line, $._newline))),

    hcl_highlight: ($) =>
      seq(
        alias(token(prec(6, /#highlight/)), '#highlight'),
        field('path', choice($.string, alias(token(prec(3, /all/)), $.keyword))),
        optional(seq('as', field('color', $.string))),
        choice(
          $._newline,
          seq(
            '{',
            $._newline,
            repeat(choice($._hcl_line, $._newline)),
            '}',
            $._newline,
          ),
        ),
      ),

    _hcl_line: ($) => token(prec(-5, /[^\r\n]+/)),

    nwdiag_diagram: ($) =>
      seq(
        alias(token(prec(6, /@startnwdiag/i)), $.diagram_start),
        optional(field('name', $.diagram_name)),
        $._newline,
        repeat(choice($._nwdiag_statement, $._newline)),
        alias(token(prec(6, /@endnwdiag/i)), $.diagram_end),
      ),

    _nwdiag_statement: ($) =>
      choice(
        $.nwdiag_network,
        $.nwdiag_group,
        $.nwdiag_link,
        $.nwdiag_node,
        $.nwdiag_element,
        $.nwdiag_property,
        ...commonStatements($),
        $.raw_line,
      ),

    nwdiag_network: ($) =>
      seq(
        'network',
        field('name', $.identifier),
        optional(field('label', alias($._to_eol, $.label))),
        '{',
        repeat(choice($._nwdiag_statement, $._newline)),
        '}',
        $._newline,
      ),

    nwdiag_group: ($) =>
      seq(
        'group',
        optional(field('label', alias($._to_eol, $.label))),
        '{',
        repeat(choice($._nwdiag_statement, $._newline)),
        '}',
        $._newline,
      ),

    nwdiag_element: ($) =>
      seq(
        field(
          'kind',
          choice('address', 'description', 'shape', 'color', 'text'),
        ),
        optional(field('value', alias($._to_eol, $.label))),
        $._newline,
      ),

    nwdiag_node: ($) =>
      seq(
        field('name', $.identifier),
        '[',
        optional(field('attributes', alias(token(/[^\]\r\n]+/), $.label))),
        ']',
        $._newline,
      ),

    nwdiag_property: ($) =>
      seq('property', field('value', alias($._to_eol, $.label)), $._newline),

    nwdiag_link: ($) =>
      seq(
        field('left', $.identifier),
        field('operator', token(prec(2, '--'))),
        field('right', $.identifier),
        optional(seq(':', field('label', $.label))),
        $._newline,
      ),

    salt_diagram: ($) =>
      seq(
        alias(token(prec(6, /@startsalt/i)), $.diagram_start),
        optional(field('name', $.diagram_name)),
        $._newline,
        repeat(choice($._salt_statement, $._newline)),
        alias(token(prec(6, /@endsalt/i)), $.diagram_end),
      ),

    _salt_statement: ($) =>
      choice(
        $.salt_group,
        $.salt_checkbox,
        $.salt_radio,
        $.salt_button,
        $.salt_textfield,
        $.salt_table_row,
        $.salt_separator,
        $.salt_text,
        ...commonStatements($),
      ),

    salt_group: ($) =>
      seq(
        '{',
        optional(
          field(
            'kind',
            alias(token(prec(3, /SI|T|\/|S|\+|-|#/)), $.salt_group_kind),
          ),
        ),
        $._newline,
        repeat(choice($._salt_statement, $._newline)),
        '}',
        $._newline,
      ),

    salt_checkbox: ($) =>
      seq(
        token(prec(3, /\[[Xx ]\]/)),
        optional(field('text', alias(token(prec(2, /[^\r\n]+/)), $.label))),
        $._newline,
      ),

    salt_radio: ($) =>
      seq(
        token(prec(3, /\([Xx ]\)/)),
        optional(field('text', alias(token(prec(2, /[^\r\n]+/)), $.label))),
        $._newline,
      ),

    salt_button: ($) =>
      seq(
        '[',
        field('text', alias(token(prec(-1, /[^\]\r\n]+/)), $.label)),
        ']',
        optional(field('rest', alias(token(prec(2, /[^\r\n]+/)), $.label))),
        $._newline,
      ),

    salt_textfield: ($) =>
      seq(
        field('text', $.string),
        optional(field('rest', alias(token(prec(2, /[^\r\n]+/)), $.label))),
        $._newline,
      ),

    salt_table_row: ($) =>
      seq(token(prec(2, /\|[^\r\n]*/)), $._newline),

    salt_separator: ($) =>
      seq(token(prec(2, /(?:--|\.\.|==)[^\r\n]*/)), $._newline),

    salt_text: ($) => seq(token(prec(-5, /[^\r\n]+/)), $._newline),

    ditaa_diagram: ($) =>
      seq(
        alias(token(prec(6, /@startditaa/i)), $.diagram_start),
        optional(field('name', $.diagram_name)),
        $._newline,
        repeat(choice($.ditaa_option, $.ditaa_body, $._newline)),
        alias(token(prec(6, /@endditaa/i)), $.diagram_end),
      ),

    ditaa_option: ($) =>
      seq(token(prec(3, /-{1,2}[A-Za-z][\w-]*/)), $._newline),

    ditaa_body: ($) =>
      seq($._ditaa_line, $._newline, repeat(seq($._ditaa_line, $._newline))),

    _ditaa_line: ($) => token(prec(-5, /[^\r\n]+/)),

    chen_diagram: ($) =>
      seq(
        alias(token(prec(6, /@startchen/i)), $.diagram_start),
        optional(field('name', $.diagram_name)),
        $._newline,
        repeat(choice($._chen_statement, $._newline)),
        alias(token(prec(6, /@endchen/i)), $.diagram_end),
      ),

    _chen_statement: ($) =>
      choice(
        $.chen_entity,
        $.chen_attribute,
        $.chen_relationship,
        $.chen_associate,
        $.chen_subclass,
        $.chen_group,
        $.chen_cardinality,
        $.chen_weak,
        ...commonStatements($),
        $.raw_line,
      ),

    chen_entity: ($) =>
      seq(
        'entity',
        field('name', $._entity_name),
        optional(
          seq(
            '{',
            repeat(choice($._chen_statement, $._newline)),
            '}',
          ),
        ),
        $._eos,
      ),

    chen_attribute: ($) =>
      seq(
        'attribute',
        field('name', $._entity_name),
        optional(seq('as', field('alias', $._entity_name))),
        $._eos,
      ),

    chen_relationship: ($) =>
      seq(
        'relationship',
        field('name', $._entity_name),
        optional(seq('as', field('alias', $._entity_name))),
        $._eos,
      ),

    chen_associate: ($) =>
      seq('associate', field('name', alias($._to_eol, $.label)), $._newline),

    chen_subclass: ($) =>
      seq('subclass', field('name', alias($._to_eol, $.label)), $._newline),

    chen_group: ($) =>
      seq(
        'group',
        optional(field('label', alias($._to_eol, $.label))),
        $._newline,
        repeat(choice($._chen_statement, $._newline)),
        alias(token(prec(6, /end[ \t]+group/i)), 'end group'),
        $._newline,
      ),

    chen_cardinality: ($) =>
      seq(token(prec(3, /\{[^}\r\n]*\}/)), $._newline),

    chen_weak: ($) => seq(token(prec(3, /weak[^\r\n]*/i)), $._newline),

    git_diagram: ($) =>
      seq(
        alias(token(prec(6, /@startgit/i)), $.diagram_start),
        optional(field('name', $.diagram_name)),
        $._newline,
        repeat(choice($._git_statement, $._newline)),
        alias(token(prec(6, /@endgit/i)), $.diagram_end),
      ),

    _git_statement: ($) =>
      choice(
        $.git_commit,
        $.git_graph_line,
        $.git_metadata,
        ...commonStatements($),
        $.raw_line,
      ),

    git_commit: ($) =>
      seq(
        '*',
        optional(field('hash', $.git_hash)),
        optional(field('refs', $.git_refs)),
        optional(field('message', alias($._to_eol, $.label))),
        $._newline,
      ),

    git_hash: ($) => token(prec(3, /[0-9a-f]{7,40}/)),

    git_refs: ($) => seq('(', sep1($.git_ref, ','), ')'),

    git_ref: ($) =>
      token(
        prec(
          2,
          /(?:tag:[ \t]*)?[^\s,)]+(?:[ \t]*->[ \t]*[^\s,)]+)?/,
        ),
      ),

    git_graph_line: ($) =>
      seq(token(prec(2, /[|\\\/][^\r\n]*/)), $._newline),

    git_metadata: ($) =>
      seq(
        field(
          'key',
          alias(token(prec(2, /Author:|Date:|Commit:|Merge:/)), $.label),
        ),
        field('value', alias($._to_eol, $.label)),
        $._newline,
      ),

    files_diagram: ($) =>
      seq(
        alias(token(prec(6, /@startfiles/i)), $.diagram_start),
        optional(field('name', $.diagram_name)),
        $._newline,
        repeat(choice($._files_statement, $._newline)),
        alias(token(prec(6, /@endfiles/i)), $.diagram_end),
      ),

    _files_statement: ($) =>
      choice(
        $.files_dir,
        $.files_file,
        $.files_comment,
        ...commonStatements($),
        $.raw_line,
      ),

    files_dir: ($) =>
      seq(
        optional(field('glyph', alias(token(/[│├└─┬┼|`+\- ]+/), $.files_tree))),
        field('path', $.path),
        optional(field('description', alias($._to_eol, $.label))),
        $._newline,
      ),

    files_file: ($) =>
      seq(
        optional(field('glyph', alias(token(/[│├└─┬┼|`+\- ]+/), $.files_tree))),
        field('path', $.path),
        optional(field('description', alias($._to_eol, $.label))),
        $._newline,
      ),

    files_comment: ($) =>
      seq(field('text', alias(token(prec(2, /#[^\r\n]*/)), $.label)), $._newline),

    path: ($) =>
      choice(
        token(prec(2, /[^\s\r\n]+\//)),
        token(/[^\s\r\n]+/),
      ),

    chronology_diagram: ($) =>
      seq(
        alias(token(prec(6, /@startchronology/i)), $.diagram_start),
        optional(field('name', $.diagram_name)),
        $._newline,
        repeat(choice($._chronology_statement, $._newline)),
        alias(token(prec(6, /@endchronology/i)), $.diagram_end),
      ),

    _chronology_statement: ($) =>
      choice(
        $.chronology_scale,
        $.chronology_time,
        $.chronology_sentence,
        ...commonStatements($),
      ),

    chronology_scale: ($) =>
      seq(
        token(prec(4, /(?:scale|date|time)[ \t]+[^\r\n]*/i)),
        $._newline,
      ),

    chronology_time: ($) =>
      seq(
        token(prec(3, /\d{1,4}[-/.]\d{1,2}[-/.]\d{1,4}[^\r\n]*/)),
        $._newline,
      ),

    chronology_sentence: ($) =>
      seq(token(prec(-5, /[^\r\n]+/)), $._newline),

    ebnf_diagram: ($) =>
      seq(
        alias(token(prec(6, /@startebnf/i)), $.diagram_start),
        optional(field('name', $.diagram_name)),
        $._newline,
        repeat(choice($._ebnf_statement, $._newline)),
        alias(token(prec(6, /@endebnf/i)), $.diagram_end),
      ),

    _ebnf_statement: ($) =>
      choice(
        $.ebnf_rule,
        $.ebnf_note,
        ...commonStatements($),
        $.raw_line,
      ),

    ebnf_rule: ($) =>
      seq(
        field('name', $.identifier),
        '=',
        optional($._newline),
        field('expression', $.ebnf_expression),
        optional($._newline),
        ';',
        $._newline,
      ),

    ebnf_expression: ($) =>
      seq(
        $.ebnf_concatenation,
        repeat(seq(optional($._newline), '|', optional($._newline), $.ebnf_concatenation)),
      ),

    ebnf_concatenation: ($) =>
      seq(
        $.ebnf_term,
        repeat(seq(optional($._newline), ',', optional($._newline), $.ebnf_term)),
      ),

    ebnf_term: ($) =>
      choice(
        $.ebnf_optional,
        $.ebnf_repeat,
        $.ebnf_group,
        $.ebnf_terminal,
        $.ebnf_special,
        $.ebnf_identifier,
        $.ebnf_comment,
      ),

    ebnf_optional: ($) =>
      seq('[', optional($._newline), $.ebnf_expression, optional($._newline), ']'),

    ebnf_repeat: ($) =>
      seq('{', optional($._newline), $.ebnf_expression, optional($._newline), '}'),

    ebnf_group: ($) =>
      seq('(', optional($._newline), $.ebnf_expression, optional($._newline), ')'),

    ebnf_terminal: ($) => $.string,
    ebnf_special: ($) => token(prec(2, /\?[^?\r\n]*\?/)),
    ebnf_identifier: ($) => $.identifier,
    ebnf_comment: ($) => token(prec(2, /\(\*[^*]*\*+([^)*][^*]*\*+)*\)/)),
    ebnf_note: ($) => seq(token(prec(3, /note[^\r\n]*/i)), $._newline),

    regex_diagram: ($) =>
      seq(
        alias(token(prec(6, /@startregex/i)), $.diagram_start),
        optional(field('name', $.diagram_name)),
        $._newline,
        repeat(choice($._regex_statement, $._newline)),
        alias(token(prec(6, /@endregex/i)), $.diagram_end),
      ),

    _regex_statement: ($) =>
      choice(
        $.regex_pattern,
        ...commonStatements($),
        $.raw_line,
      ),

    regex_pattern: ($) =>
      prec(-1, seq($.regex_atom, repeat($.regex_atom))),

    regex_atom: ($) =>
      choice(
        $.regex_group,
        $.regex_lookaround,
        $.regex_class,
        $.regex_escape,
        $.regex_anchor,
        $.regex_quantifier,
        $.regex_alternation,
        $.regex_literal,
      ),

    regex_group: ($) =>
      seq('(', optional('?:'), repeat($.regex_atom), ')'),

    regex_lookaround: ($) =>
      seq('(', choice('?=', '?!', '?<=', '?<!'), repeat($.regex_atom), ')'),

    regex_class: ($) => token(prec(2, /\[[^\]\r\n]*\]/)),
    regex_escape: ($) => token(prec(2, /\\./)),
    regex_anchor: ($) => token(prec(2, /[\^$]/)),
    regex_quantifier: ($) => token(prec(2, /\{\d+(,\d*)?\}|[*+?]/)),
    regex_alternation: ($) => token(prec(2, /\|/)),
    regex_literal: ($) => token(prec(-2, /[^\\\[\](){}|^$*+?\r\n]+/)),

    packet_diagram: ($) =>
      seq(
        alias(token(prec(6, /@startpacketdiag/i)), $.diagram_start),
        optional(field('name', $.diagram_name)),
        $._newline,
        repeat(choice($._packet_statement, $._newline)),
        alias(token(prec(6, /@endpacketdiag/i)), $.diagram_end),
      ),

    _packet_statement: ($) =>
      choice(
        $.packet_field,
        ...commonStatements($),
        $.raw_line,
      ),

    packet_field: ($) =>
      seq(
        field('range', $.packet_range),
        ':',
        field('label', alias($._to_eol, $.label)),
        $._newline,
      ),

    packet_range: ($) =>
      token(prec(3, /\d+(?:-\d+)?(?:\s*,\s*\d+(?:-\d+)?)*/)),

    board_diagram: ($) =>
      seq(
        alias(token(prec(6, /@startboard/i)), $.diagram_start),
        optional(field('name', $.diagram_name)),
        $._newline,
        repeat(choice($._board_statement, $._newline)),
        alias(token(prec(6, /@endboard/i)), $.diagram_end),
      ),

    _board_statement: ($) =>
      choice(
        $.board_column,
        $.board_card,
        ...commonStatements($),
        $.raw_line,
      ),

    board_column: ($) =>
      seq('+', optional(field('label', alias($._to_eol, $.label))), $._newline),

    board_card: ($) =>
      seq(token(prec(2, /-{2,}[^\r\n]*/)), $._newline),

    wire_diagram: ($) =>
      seq(
        alias(token(prec(6, /@startwire/i)), $.diagram_start),
        optional(field('name', $.diagram_name)),
        $._newline,
        repeat(choice($._wire_statement, $._newline)),
        alias(token(prec(6, /@endwire/i)), $.diagram_end),
      ),

    _wire_statement: ($) =>
      choice(
        $.wire_component,
        $.wire_command,
        ...commonStatements($),
        $.raw_line,
      ),

    wire_component: ($) =>
      seq(
        field('kind', choice('component', 'spot')),
        optional(field('name', alias($._to_eol, $.label))),
        $._newline,
      ),

    wire_command: ($) =>
      seq(
        field(
          'kind',
          choice(
            'link',
            'move',
            'goto',
            'new column',
            'new row',
            'left to right direction',
            'top to bottom direction',
          ),
        ),
        optional(field('value', alias($._to_eol, $.label))),
        $._newline,
      ),

    flow_diagram: ($) =>
      seq(
        alias(token(prec(6, /@startflow/i)), $.diagram_start),
        optional(field('name', $.diagram_name)),
        $._newline,
        repeat(choice($._flow_statement, $._newline)),
        alias(token(prec(6, /@endflow/i)), $.diagram_end),
      ),

    _flow_statement: ($) =>
      choice(
        $.activity_action,
        $.activity_arrow,
        $.activity_control,
        $.flow_link,
        $.if_block,
        $.while_block,
        $.repeat_block,
        $.switch_block,
        $.fork_block,
        $.split_block,
        ...commonStatements($),
        $.raw_line,
      ),

    flow_link: ($) =>
      seq(token(prec(2, /-{1,2}(\[[^\]\r\n]*\])?>[^\r\n]*/)), $._newline),

    bpm_diagram: ($) =>
      seq(
        alias(token(prec(6, /@startbpm/i)), $.diagram_start),
        optional(field('name', $.diagram_name)),
        $._newline,
        repeat(choice($._bpm_statement, $._newline)),
        alias(token(prec(6, /@endbpm/i)), $.diagram_end),
      ),

    _bpm_statement: ($) =>
      choice(
        $.bpm_task,
        $.bpm_command,
        ...commonStatements($),
        $.raw_line,
      ),

    bpm_task: ($) =>
      seq(
        alias(token(prec(2, /:[^;\r\n]*;/)), $.action_text),
        $._newline,
      ),

    bpm_command: ($) =>
      seq(
        field(
          'kind',
          choice(
            'if',
            'else',
            'endif',
            'fork',
            'end fork',
            'goto',
            'merge',
            'end merge',
            'resume',
          ),
        ),
        optional(field('value', alias($._to_eol, $.label))),
        $._newline,
      ),

    math_diagram: ($) =>
      rawBodyDiagram($, /@startmath/i, /@endmath/i, $.math_body),

    latex_diagram: ($) =>
      rawBodyDiagram($, /@startlatex/i, /@endlatex/i, $.latex_body),

    creole_diagram: ($) =>
      seq(
        alias(token(prec(6, /@startcreole/i)), $.diagram_start),
        optional(field('name', $.diagram_name)),
        $._newline,
        repeat(choice($._creole_statement, $._newline)),
        alias(token(prec(6, /@endcreole/i)), $.diagram_end),
      ),

    _creole_statement: ($) =>
      choice(
        $.creole_heading,
        $.creole_list_item,
        $.creole_table_row,
        $.creole_rule,
        $.creole_text,
        $.comment,
      ),

    creole_heading: ($) =>
      seq(token(prec(3, /={1,6}[^\r\n]*=*[ \t]*/)), $._newline),
    creole_list_item: ($) =>
      seq(token(prec(2, /[*#]+[ \t]+[^\r\n]*/)), $._newline),
    creole_table_row: ($) =>
      seq(token(prec(2, /\|[^\r\n]*\|?/)), $._newline),
    creole_rule: ($) =>
      seq(token(prec(2, /(?:-{4,}|={4,}|_{4,}|\.{4,})/)), $._newline),
    creole_text: ($) => seq(token(prec(-5, /[^\r\n]+/)), $._newline),

    dot_diagram: ($) =>
      rawBodyDiagram($, /@startdot/i, /@enddot/i, $.dot_body),

    sprites_diagram: ($) =>
      seq(
        alias(token(prec(6, /@startsprites/i)), $.diagram_start),
        optional(field('name', $.diagram_name)),
        $._newline,
        repeat(choice($.sprite_declaration, $._newline)),
        alias(token(prec(6, /@endsprites/i)), $.diagram_end),
      ),

    chart_diagram: ($) =>
      rawBodyDiagram($, /@startchart/i, /@endchart/i, $.chart_body),

    _mindmap_statement: ($) =>
      choice(
        $.mindmap_node,
        $.outline_separator,
        $.title_statement,
        $.caption_statement,
        $.header_statement,
        $.footer_statement,
        $.legend_block,
        $.skinparam_statement,
        $.style_block,
        $.preprocessor,
        $.comment,
        $.raw_line,
      ),

    _wbs_statement: ($) =>
      choice(
        $.wbs_node,
        $.outline_separator,
        $.title_statement,
        $.caption_statement,
        $.header_statement,
        $.footer_statement,
        $.legend_block,
        $.skinparam_statement,
        $.style_block,
        $.preprocessor,
        $.comment,
        $.raw_line,
      ),

    mindmap_node: ($) =>
      seq(
        field('marker', alias(token(prec(2, /\*+_?|\++_?|-+_?/)), $.outline_marker)),
        optional(field('color', $.outline_color)),
        $._outline_text,
      ),

    wbs_node: ($) =>
      seq(
        field('marker', alias(token(prec(2, /\*+_?|\++_?|-+_?/)), $.outline_marker)),
        optional(field('color', $.outline_color)),
        $._outline_text,
      ),

    _outline_text: ($) =>
      choice(
        seq(
          ':',
          field('text', alias(token(prec(1, /([^;]|\r?\n)*;/)), $.label)),
          $._newline,
        ),
        seq(optional(field('text', alias($._to_eol, $.label))), $._newline),
      ),

    outline_color: ($) => token(prec(2, /\[#[^\]\r\n]+\]/)),

    outline_separator: ($) =>
      seq(token(prec(3, /(?:--|==|\.\.)[^\r\n]*/)), $._newline),

    _gantt_statement: ($) =>
      choice(
        $.gantt_project_statement,
        $.gantt_task,
        $.gantt_group,
        $.gantt_today_statement,
        $.gantt_date_statement,
        $.gantt_directive,
        $.gantt_separator,
        $.title_statement,
        $.caption_statement,
        $.header_statement,
        $.footer_statement,
        $.legend_block,
        $.skinparam_statement,
        $.style_block,
        $._pp_statement,
        $.display_directive,
        $.scale_statement,
        $.note_statement,
        $.comment,
        $.delay,
        $.raw_line,
      ),

    gantt_project_statement: ($) =>
      seq('Project', 'starts', field('date', alias(token(/[^\r\n]+/), $.label)), $._newline),

    gantt_task: ($) =>
      seq(
        '[',
        field('name', alias(token(/[^\]\r\n]+/), $.gantt_task_name)),
        ']',
        optional(
          field('value', alias(token(prec(-2, /[^\r\n{]+/)), $.label)),
        ),
        repeat(field('status', $.gantt_status)),
        $._newline,
      ),

    gantt_status: ($) => token(prec(2, /\{[^}\r\n]*\}/)),

    gantt_group: ($) =>
      seq(
        alias(token(prec(4, /group[ \t]+/i)), 'group'),
        field('label', alias($._to_eol, $.label)),
        $._newline,
        repeat(choice($._gantt_statement, $._newline)),
        alias(token(prec(4, /end[ \t]+group/i)), 'end group'),
        $._newline,
      ),

    gantt_directive: ($) =>
      seq(
        field(
          'kind',
          choice(
            alias(token(prec(4, /printscale[ \t]+/i)), 'printscale'),
            alias(token(prec(4, /print[ \t]+between[ \t]+/i)), 'print between'),
            alias(token(prec(4, /label[ \t]+on[ \t]+column[ \t]+/i)), 'label on column'),
            alias(token(prec(4, /language[ \t]+/i)), 'language'),
            alias(token(prec(4, /week[ \t]+number[ \t]+strategy[ \t]+/i)), 'week number strategy'),
            alias(token(prec(4, /task[ \t]+complete[ \t]+default/i)), 'task complete default'),
          ),
        ),
        optional(field('value', alias($._to_eol, $.label))),
        $._newline,
      ),

    gantt_today_statement: ($) =>
      seq('today', 'is', field('date', alias(token(/[^\r\n]+/), $.label)), $._newline),

    gantt_date_statement: ($) =>
      seq(
        field('date', alias(token(/\d{4}-\d\d-\d\d/), $.date)),
        field('value', alias(token(/[^\r\n]+/), $.label)),
        $._newline,
      ),

    gantt_separator: ($) =>
      seq(token(prec(3, /(?:--|==)[^\r\n]*/)), $._newline),

    raw_body: ($) =>
      seq(
        choice($.raw_line, $._newline),
        repeat(choice($.raw_line, $._newline)),
      ),

    generic_body: ($) => lineBody($),
    math_body: ($) => lineBody($),
    latex_body: ($) => lineBody($),
    dot_body: ($) => lineBody($),
    chart_body: ($) => lineBody($),

    diagram_name: ($) => $._to_eol,
    diagram_start: ($) => token(prec(3, /@startuml/i)),
    diagram_end: ($) => token(prec(3, /@enduml/i)),
    _generic_start: ($) => token(prec(2, /@start[a-zA-Z]+/)),
    _generic_end: ($) => token(prec(2, /@end[a-zA-Z]+/)),

    _statement: ($) =>
      choice(
        $.class_declaration,
        $.enum_declaration,
        $.activity_container_block,
        $.entity_declaration,
        $.state_declaration,
        $.package_block,
        $.namespace_block,
        $.together_block,
        $.component_shorthand,
        $.relation,
        $.requirement_relation,
        $.boundary_message,
        $.colon_member,
        $.activity_action,
        $.activity_control,
        $.activity_arrow,
        $.activity_connector_arrow,
        $.activity_group_block,
        $.connector,
        $.autoactivate_statement,
        $.mainframe_statement,
        $.association_relation,
        $.circle_shorthand,
        $.diamond_shorthand,
        $.if_block,
        $.while_block,
        $.repeat_block,
        $.switch_block,
        $.fork_block,
        $.split_block,
        $.partition_block,
        $.swimlane,
        $.sequence_frame,
        $.sequence_lifecycle,
        $.return_statement,
        $.reference,
        $.box_block,
        $.delay,
        $.spacer,
        $.divider,
        $.note_statement,
        $.requirement_declaration,
        $.macro_call,
        $.link_anchor,
        $.autonumber_statement,
        $.state_concurrent,
        ...commonStatements($),
        $.raw_line,
      ),

    comment: ($) => $.comment_line,

    comment_line: ($) => token(prec(1, seq('\'', /[^\r\n]*/))),

    block_comment: ($) =>
      token(seq('/\'', /[^']*'+([^/'][^']*'+)*/, '/')),

    activity_container_block: ($) =>
      seq(
        field('kind', choice('rectangle', 'card')),
        $._entity_head,
        choice(
          $._eos,
          seq(
            '{',
            repeat(choice($._statement, $._newline)),
            '}',
            $._eos,
          ),
        ),
      ),

    class_declaration: ($) =>
      seq(
        optional(field('visibility', $.visibility)),
        choice(
          seq(field('abstract', alias('abstract', $.abstract)), optional('class')),
          field(
            'kind',
            choice(
              'class',
              'interface',
              'annotation',
              'protocol',
              'struct',
              'exception',
              'metaclass',
            ),
          ),
        ),
        $._entity_head,
        choice(
          $._eos,
          seq(field('body', $.entity_body), $._eos),
          seq($._newline, field('body', $.entity_body), $._eos),
          seq(':', field('description', $.label), $._eos),
        ),
      ),

    enum_declaration: ($) =>
      seq(
        'enum',
        $._entity_head,
        choice(
          $._eos,
          seq(field('body', $.enum_body), $._eos),
          seq($._newline, field('body', $.enum_body), $._eos),
        ),
      ),

    enum_body: ($) =>
      choice(
        seq(
          '{',
          repeat(
            choice(
              $.enum_member,
              $.member,
              $.member_separator,
              $.comment,
              $._newline,
            ),
          ),
          '}',
        ),
        seq(
          '{',
          repeat1(field('value', alias($.identifier, $.enum_value))),
          '}',
        ),
      ),

    enum_member: ($) =>
      seq(
        repeat1(field('value', alias($.identifier, $.enum_value))),
        $._newline,
      ),

    entity_declaration: ($) =>
      seq(
        field(
          'kind',
          alias(
            choice(
              'object',
              'participant',
              'actor',
              'boundary',
              'control',
              'entity',
              'database',
              'collections',
              'queue',
              'component',
              'node',
              'artifact',
              'folder',
              'frame',
              'cloud',
              'file',
              'stack',
              'storage',
              'circle',
              'diamond',
              'record',
              'dataclass',
              'agent',
              'usecase',
            ),
            $.entity_kind,
          ),
        ),
        $._entity_head,
        choice(
          $._eos,
          seq(field('body', $.entity_body), $._eos),
          seq($._newline, field('body', $.entity_body), $._eos),
          seq(
            '[',
            $._newline,
            repeat(choice($._bracket_body_line, $._newline)),
            ']',
            $._eos,
          ),
          seq(':', field('description', $.label), $._eos),
        ),
      ),

    state_declaration: ($) =>
      seq(
        'state',
        field('name', $._entity_name),
        optional(seq('as', field('alias', $._entity_name))),
        repeat(
          choice(
            field('stereotype', $.stereotype),
            field('color', $.color),
            field('link', $.hyperlink),
          ),
        ),
        choice(
          seq(field('body', $.state_body), $._eos),
          seq($._newline, field('body', $.state_body), $._eos),
          seq(':', field('description', $.label), $._eos),
          $._eos,
        ),
      ),

    package_block: ($) =>
      seq(
        'package',
        field('name', $._entity_name),
        repeat($._entity_head_suffix),
        choice(
          seq(
            '{',
            repeat(choice($._statement, $._newline)),
            '}',
            $._eos,
          ),
          seq(
            $._newline,
            '{',
            repeat(choice($._statement, $._newline)),
            '}',
            $._eos,
          ),
        ),
      ),

    namespace_block: ($) =>
      seq(
        'namespace',
        field('name', $._entity_name),
        repeat($._entity_head_suffix),
        choice(
          seq(
            '{',
            repeat(choice($._statement, $._newline)),
            '}',
            $._eos,
          ),
          seq(
            $._newline,
            '{',
            repeat(choice($._statement, $._newline)),
            '}',
            $._eos,
          ),
          $._newline,
        ),
      ),

    together_block: ($) =>
      seq(
        'together',
        choice(
          seq(
            '{',
            repeat(choice($._statement, $._newline)),
            '}',
            $._eos,
          ),
          seq(
            $._newline,
            '{',
            repeat(choice($._statement, $._newline)),
            '}',
            $._eos,
          ),
        ),
      ),

    entity_body: ($) =>
      seq(
        '{',
        repeat(
          choice(
            $.member,
            $.map_member,
            $.member_separator,
            $.comment,
            $._container_statement,
            $._newline,
          ),
        ),
        '}',
      ),

    map_member: ($) =>
      seq(
        field('key', $.string),
        ':',
        optional(field('value', alias($._to_eol, $.label))),
        $._eos,
      ),

    _container_statement: ($) =>
      choice(
        $.class_declaration,
        $.enum_declaration,
        $.entity_declaration,
        $.state_declaration,
        $.package_block,
        $.namespace_block,
        $.together_block,
        $.component_shorthand,
        $.relation,
        $.boundary_message,
        $.note_statement,
        $.autoactivate_statement,
        $.mainframe_statement,
        $.association_relation,
        $.circle_shorthand,
        $.diamond_shorthand,
      ),

    state_body: ($) =>
      seq(
        '{',
        repeat(
          choice(
            $.member,
            $.member_separator,
            $.state_behavior,
            $._statement,
            $._newline,
          ),
        ),
        '}',
      ),

    member: ($) =>
      seq(
        repeat(
          choice(
            field('visibility', alias($._member_visibility, $.visibility)),
            field('modifier', $.modifier),
          ),
        ),
        choice($.port_member, $.method, $.cpp_attribute, $.attribute, $.raw_member),
        $._eos,
      ),

    cpp_attribute: ($) =>
      seq(
        field('type', $.cpp_type_name),
        field('name', $.identifier),
      ),

    cpp_type_name: ($) => $._cpp_type_name,

    type: ($) => $._to_eol,

    port_member: ($) =>
      seq(
        field('kind', choice('port', 'portin', 'portout')),
        field('name', $._entity_name),
        optional(seq('as', field('alias', $._entity_name))),
        repeat(
          choice(
            field('stereotype', $.stereotype),
            field('color', $.color),
          ),
        ),
      ),

    visibility: ($) => choice('+', '-', '#', '~'),

    _member_visibility: ($) => choice(token(prec(2, '#')), '+', '-', '~'),

    modifier: ($) =>
      token(
        choice(
          '{static}',
          '{abstract}',
          '{field}',
          '{method}',
          '{classifier}',
        ),
      ),

    method: ($) =>
      seq(
        optional(field('template_parameters', $.generics)),
        optional(field('return_type', $.cpp_type_name)),
        field('name', $.identifier),
        optional(field('template_parameters', $.generics)),
        '(',
        optional(field('parameters', $.parameter_list)),
        ')',
        optional(seq(':', field('type', $.type))),
      ),

    _cpp_type_name: ($) =>
      seq(
        $.identifier,
        repeat(seq(token.immediate('::'), $.identifier)),
        optional($.generics),
        repeat(choice('*', '&')),
      ),

    attribute: ($) =>
      seq(
        field('name', $.identifier),
        optional(seq(':', field('type', $.type))),
      ),

    raw_member: ($) => alias($._to_eol, $.raw_text),

    parameter_list: ($) => sep1($.parameter, ','),

    parameter: ($) => token(prec(1, /[^,()\n]+/)),

    member_separator: ($) =>
      seq(
        token(
          choice(
            prec(1, /--[^\r\n]*/),
            prec(1, /\.\.[^\r\n]*/),
            prec(1, /==[^\r\n]*/),
            prec(1, /__[ \t][^\r\n]*/),
          ),
        ),
        $._eos,
      ),

    relation: ($) =>
      seq(
        field('left', $._relation_end),
        optional(field('qualifier', $.qualifier)),
        optional(
          seq(
            field('left_cardinality', alias($.string, $.cardinality)),
            optional(field('left_role', alias(token(/\/[\w.-]+/), $.role))),
          ),
        ),
        field('operator', $.relation_operator),
        optional(
          seq(
            field('right_cardinality', alias($.string, $.cardinality)),
            optional(field('right_role', alias(token(/\/[\w.-]+/), $.role))),
          ),
        ),
        field('right', $._relation_end),
        optional(field('activation', $.activation)),
        optional(field('color', $.color)),
        optional(field('link', $.hyperlink)),
        optional(seq(':', field('label', $.label))),
        $._eos,
      ),

    relation_operator: ($) =>
      token(
        choice(
          // eslint-disable-next-line max-len
          /(<\||<|\*|[ox]|\(\)|\+|\|\||o\{|\|\{|>\|)?-+(\[[^\]\n]+\]-*)?((left|right|up|down|l|r|u|d)-+)?(\|>|>>|>[xo]?|\*|o|x|\(\)|\+|\\\\|\\|\/\/|\/|o\{|\|\{|\|\||\}\||\|o|\|)?(\(\d+\))?/,
          // eslint-disable-next-line max-len
          /(<\||<|\*|[ox]|\(\)|\+|\|\||o\{|\|\{|>\|)?\.+(\[[^\]\n]+\]\.*)?((left|right|up|down|l|r|u|d)\.+)?(\|>|>>|>[xo]?|\*|o|x|\(\)|\+|\\\\|\\|\/\/|\/|o\{|\|\{|\|\||\}\||\|o|\|)?(\(\d+\))?/,
        ),
      ),

    activation: ($) => token(choice('++', '--', '**', '!!')),

    qualifier: ($) => token(seq('[', /[^\]\n]+/, ']')),

    pseudostate: ($) => token(prec(2, /\[(\*|[Hh]\*?)\]/)),

    colon_member: ($) =>
      seq(
        field('entity', $._entity_name),
        ':',
        field('member', $.label),
        $._eos,
      ),

    activity_action: ($) =>
      seq(
        optional(field('color', $._activity_color)),
        alias(
          token(prec(1, /:([^;|<>\/\\]|\r?\n)*[;|<>\/\\]/)),
          $.action_text,
        ),
        optional(field('stereotype', $.stereotype)),
        $._newline,
      ),

    _activity_color: ($) => token(prec(5, /#[\w-]+/)),

    activity_control: ($) =>
      seq(
        choice(
          field('kind', choice('start', 'stop', 'kill', 'detach', 'break', 'end')),
          seq(field('kind', choice('label', 'goto')), field('target', $.identifier)),
          seq('backward', optional(alias(token(/[^\r\n;]+/), $.action_text)), optional(';')),
        ),
        $._newline,
      ),

    activity_group_block: ($) =>
      seq(
        alias(token(prec(4, /group[ \t][^{\r\n]*\{/)), 'group'),
        $._newline,
        repeat(choice($._statement, $._newline)),
        '}',
        $._eos,
      ),

    activity_arrow: ($) =>
      seq(
        field('operator', alias(token(/-(\[[^\]\n]*\])?>/), $.arrow_operator)),
        optional(field('label', alias(token(/[^\r\n;]+/), $.label))),
        optional(';'),
        $._newline,
      ),

    connector: ($) =>
      seq(
        choice(
          token(prec(6, /#\w+:\(([^(),\n]|\([^(),\n]*\))+\)/)),
          token(prec(1, /\(([^(),\n]|\([^(),\n]*\))+\)/)),
        ),
        $._newline,
      ),

    activity_connector_arrow: ($) =>
      seq(
        field(
          'left',
          alias(
            choice(
              token(prec(6, /#\w+:\(([^(),\n]|\([^(),\n]*\))+\)/)),
              token(prec(1, /\(([^(),\n]|\([^(),\n]*\))+\)/)),
            ),
            $.connector_name,
          ),
        ),
        field(
          'operator',
          alias(token(prec(1, /-+(\[[^\]\n]*\])?>/)), $.arrow_operator),
        ),
        field(
          'right',
          alias(
            choice(
              token(prec(6, /#\w+:\(([^(),\n]|\([^(),\n]*\))+\)/)),
              token(prec(1, /\(([^(),\n]|\([^(),\n]*\))+\)/)),
            ),
            $.connector_name,
          ),
        ),
        optional(seq(':', field('label', $.label))),
        optional(';'),
        $._newline,
      ),

    autoactivate_statement: ($) =>
      seq(
        'autoactivate',
        optional(field('value', choice('on', 'off'))),
        $._newline,
      ),

    mainframe_statement: ($) =>
      seq('mainframe', field('label', $._to_eol), $._newline),

    swimlane: ($) =>
      seq(
        field('name', alias(token(prec(1, /\|(#[^|\n]+\|)?[^|\n]+\|[^\r\n]*/)), $.lane_text)),
        $._newline,
      ),

    if_block: ($) =>
      seq(
        'if',
        field('condition', choice(alias($._paren, $.condition), $.string)),
        optional($._branch_head),
        $._newline,
        repeat(choice($._statement, $._newline)),
        repeat($.elseif_clause),
        optional($.activity_else_clause),
        'endif',
        $._newline,
      ),

    elseif_clause: ($) =>
      seq(
        'elseif',
        field('condition', choice(alias($._paren, $.condition), $.string)),
        optional($._branch_head),
        $._newline,
        repeat(choice($._statement, $._newline)),
      ),

    activity_else_clause: ($) =>
      seq(
        'else',
        optional(field('label', alias($._paren, $.branch_label))),
        $._newline,
        repeat(choice($._statement, $._newline)),
      ),

    while_block: ($) =>
      seq(
        'while',
        field('condition', choice(alias($._paren, $.condition), $.string)),
        optional(seq('is', field('label', alias($._paren, $.branch_label)))),
        $._newline,
        repeat(choice($._statement, $._newline)),
        'endwhile',
        optional(field('end_label', alias($._paren, $.branch_label))),
        $._newline,
      ),

    repeat_block: ($) =>
      seq(
        'repeat',
        optional(alias($.activity_action, $.action)),
        $._newline,
        repeat(choice($._statement, $._newline)),
        'repeat',
        'while',
        field('condition', choice(alias($._paren, $.condition), $.string)),
        optional(seq('is', field('label', alias($._paren, $.branch_label)))),
        $._newline,
      ),

    switch_block: ($) =>
      seq(
        'switch',
        field('condition', choice(alias($._paren, $.condition), $.string)),
        $._newline,
        repeat(choice($._statement, $._newline)),
        repeat($.case_clause),
        'endswitch',
        $._newline,
      ),

    case_clause: ($) =>
      seq(
        'case',
        field('condition', choice(alias($._paren, $.condition), $.string)),
        $._newline,
        repeat(choice($._statement, $._newline)),
      ),

    fork_block: ($) =>
      seq(
        'fork',
        $._newline,
        repeat(choice($._statement, $._newline)),
        repeat($.fork_again),
        'end',
        choice('fork', 'merge'),
        optional(field('label', token(/\{[^}\r\n]*\}/))),
        $._newline,
      ),

    fork_again: ($) =>
      seq(
        'fork',
        'again',
        $._newline,
        repeat(choice($._statement, $._newline)),
      ),

    split_block: ($) =>
      seq(
        'split',
        $._newline,
        repeat(choice($._statement, $._newline)),
        repeat($.split_again),
        'end',
        'split',
        optional(field('label', token(/\{[^}\r\n]*\}/))),
        $._newline,
      ),

    split_again: ($) =>
      seq(
        'split',
        'again',
        $._newline,
        repeat(choice($._statement, $._newline)),
      ),

    partition_block: ($) =>
      seq(
        'partition',
        repeat(
          choice(
            field('color', $.color),
            field('name', $._entity_name),
          ),
        ),
        '{',
        repeat(choice($._statement, $._newline)),
        '}',
        $._eos,
      ),

    _paren: ($) => token(prec(1, /\(([^()\n]|\([^()\n]*\))*\)/)),

    _branch_head: ($) =>
      choice(
        seq('then', optional(field('label', alias($._paren, $.branch_label)))),
        seq(
          choice('is', 'equals'),
          field('label', alias($._paren, $.branch_label)),
          optional('then'),
        ),
      ),

    sequence_frame: ($) =>
      seq(
        field(
          'kind',
          choice('alt', 'opt', 'loop', 'par', 'break', 'critical', 'group'),
        ),
        optional(field('label', $.label)),
        $._newline,
        repeat(choice($._statement, $._newline)),
        repeat($.sequence_else_clause),
        'end',
        $._newline,
      ),

    sequence_else_clause: ($) =>
      seq(
        'else',
        optional(field('label', $.label)),
        $._newline,
        repeat(choice($._statement, $._newline)),
      ),

    sequence_lifecycle: ($) =>
      seq(
        choice(
          seq(
            field('kind', choice('activate', 'deactivate', 'destroy')),
            field('target', $._entity_name),
            optional(field('color', $.color)),
          ),
          seq(
            field('kind', 'create'),
            optional(
              field(
                'participant_kind',
                choice(
                  'participant',
                  'actor',
                  'boundary',
                  'control',
                  'entity',
                  'database',
                  'collections',
                  'queue',
                ),
              ),
            ),
            field('target', $._entity_name),
          ),
        ),
        $._newline,
      ),

    return_statement: ($) =>
      seq('return', optional(field('label', $.label)), $._newline),

    reference: ($) =>
      seq(
        alias(token(seq('ref', /[ \t]+/, 'over')), 'ref over'),
        field('target', $.entity_list),
        choice(
          seq(':', field('label', $.label), $._newline),
          seq(
            $._newline,
            repeat(choice($.raw_line, $._newline)),
            alias(token(prec(3, /end[ \t]+ref/)), 'end ref'),
            $._newline,
          ),
        ),
      ),

    box_block: ($) =>
      seq(
        'box',
        optional(
          choice(
            seq(field('name', $.string), optional(field('color', $.color))),
            field('label', $.label),
          ),
        ),
        $._newline,
        repeat(choice($._statement, $._newline)),
        alias(token(prec(3, /end[ \t]+box/)), 'end box'),
        $._newline,
      ),

    delay: ($) =>
      seq(alias(token(prec(1, /\.{3,}[^\r\n]*/)), $.delay_text), $._newline),

    spacer: ($) =>
      seq(token(prec(1, /\|\|(\||\d+\|\|)/)), $._newline),

    divider: ($) =>
      seq(token(prec(1, /==[^\r\n]*/)), $._newline),

    state_concurrent: ($) => seq('--', $._newline),

    note_statement: ($) =>
      choice(
        seq(
          choice('note', 'hnote', 'rnote'),
          field('position', $.note_position),
          'on',
          'link',
          choice(
            seq(':', field('text', $.label), $._newline),
            seq(
              $._newline,
              repeat(choice($.raw_line, $._newline)),
              alias(token(prec(3, /end[ \t]*(note|hnote|rnote)/)), 'end note'),
              $._newline,
            ),
          ),
        ),
        seq(
          choice('note', 'hnote', 'rnote'),
          'on',
          'link',
          choice(
            seq(':', field('text', $.label), $._newline),
            seq(
              $._newline,
              repeat(choice($.raw_line, $._newline)),
              alias(token(prec(3, /end[ \t]*(note|hnote|rnote)/)), 'end note'),
              $._newline,
            ),
          ),
        ),
        seq(
          'floating',
          'note',
          optional(field('position', $.note_position)),
          optional(
            seq(
              choice('of', 'over'),
              field('target', choice($.entity_list, $.member_ref)),
            ),
          ),
          choice(
            seq(':', field('text', $.label), $._newline),
            seq(
              $._newline,
              repeat(choice($.raw_line, $._newline)),
              alias(token(prec(3, /end[ \t]*(note|hnote|rnote)/)), 'end note'),
              $._newline,
            ),
          ),
        ),
        seq(
          choice('note', 'hnote', 'rnote'),
          field('position', $.note_position),
          optional(
            seq(
              choice('of', 'over'),
              field('target', choice($.entity_list, $.member_ref)),
            ),
          ),
          optional(field('color', $.color)),
          choice(
            seq(':', field('text', $.label), $._newline),
            seq(
              $._newline,
              repeat(choice($.raw_line, $._newline)),
              alias(token(prec(3, /end[ \t]*(note|hnote|rnote)/)), 'end note'),
              $._newline,
            ),
          ),
        ),
        seq(
          choice('note', 'hnote', 'rnote'),
          'over',
          field('target', $.entity_list),
          optional(field('color', $.color)),
          choice(
            seq(':', field('text', $.label), $._newline),
            seq(
              $._newline,
              repeat(choice($.raw_line, $._newline)),
              alias(token(prec(3, /end[ \t]*(note|hnote|rnote)/)), 'end note'),
              $._newline,
            ),
          ),
        ),
        seq(
          choice('note', 'hnote', 'rnote'),
          'on',
          'link',
          choice(
            seq(':', field('text', $.label), $._newline),
            seq(
              $._newline,
              repeat(choice($.raw_line, $._newline)),
              alias(token(prec(3, /end[ \t]*(note|hnote|rnote)/)), 'end note'),
              $._newline,
            ),
          ),
        ),
        seq(
          choice('note', 'hnote', 'rnote'),
          field('text', $.string),
          'as',
          field('alias', $.identifier),
          $._newline,
        ),
        seq(
          choice('note', 'hnote', 'rnote'),
          'as',
          field('alias', $.identifier),
          $._newline,
          repeat(choice($.raw_line, $._newline)),
          alias(token(prec(3, /end[ \t]*(note|hnote|rnote)/)), 'end note'),
          $._newline,
        ),
      ),

    note_position: ($) => choice('left', 'right', 'top', 'bottom', 'across'),

    state_behavior: ($) =>
      seq(
        field('kind', choice('entry', 'exit', 'do')),
        '/',
        field('action', alias($._to_eol, $.label)),
        $._newline,
      ),

    requirement_declaration: ($) =>
      seq(
        field(
          'kind',
          choice(
            'requirement',
            'functionalRequirement',
            'interfaceRequirement',
            'performanceRequirement',
            'physicalRequirement',
            'designConstraint',
          ),
        ),
        $._entity_head,
        choice(
          $._eos,
          seq(
            '{',
            repeat(choice($.requirement_field, $.comment, $._newline)),
            '}',
            $._eos,
          ),
          seq(
            $._newline,
            '{',
            repeat(choice($.requirement_field, $.comment, $._newline)),
            '}',
            $._eos,
          ),
        ),
      ),

    requirement_field: ($) =>
      seq(
        field(
          'name',
          choice('id', 'text', 'risk', 'verifymethod', 'type'),
        ),
        ':',
        field('value', alias(token(/[^\r\n;]+/), $.label)),
        optional(';'),
        $._newline,
      ),

    requirement_relation: ($) =>
      prec(
        3,
        seq(
          field('left', $._relation_end),
          field(
            'operator',
            token(
              prec(
                5,
                /-[ \t]*(?:satisfy|derive|trace|verify|refine|copy|contain)[ \t]*->/i,
              ),
            ),
          ),
          field('right', $._relation_end),
          optional(seq(':', field('label', $.label))),
          $._eos,
        ),
      ),

    macro_call: ($) =>
      prec(
        2,
        seq(
          field('name', $.identifier),
          '(',
          optional(field('arguments', $.macro_arguments)),
          ')',
          $._eos,
        ),
      ),

    macro_arguments: ($) => sep1($.macro_argument, ','),

    macro_argument: ($) =>
      choice($.string, $.identifier, alias(token(/[^,()\r\n]+/), $.label)),

    link_anchor: ($) =>
      seq(
        alias(token(prec(3, /anchor/i)), 'anchor'),
        optional(field('name', alias($._to_eol, $.label))),
        $._newline,
      ),

    rotate_statement: ($) =>
      seq(
        alias(token(prec(3, /rotate/i)), 'rotate'),
        optional(field('value', alias($._to_eol, $.label))),
        $._newline,
      ),

    minwidth_statement: ($) =>
      seq(
        alias(token(prec(3, /minwidth/i)), 'minwidth'),
        optional(field('value', alias($._to_eol, $.label))),
        $._newline,
      ),

    namespace_separator: ($) =>
      seq(
        alias(
          token(prec(4, /set[ \t]+namespaceSeparator/i)),
          'set namespaceSeparator',
        ),
        optional(field('value', alias($._to_eol, $.label))),
        $._newline,
      ),

    pragma_statement: ($) =>
      seq(
        alias(token(prec(3, /pragma/i)), 'pragma'),
        optional(field('value', alias($._to_eol, $.label))),
        $._newline,
      ),

    sprite_declaration: ($) =>
      seq(
        alias(token(prec(3, /sprite/i)), 'sprite'),
        field('name', $.tag),
        optional(field('size', token(prec(2, /\d+x\d+/)))),
        choice(
          $._newline,
          seq(field('source', alias($._to_eol, $.label)), $._newline),
          seq(
            '{',
            $._newline,
            repeat(choice($.raw_line, $._newline)),
            '}',
            $._newline,
          ),
        ),
      ),

    display_directive: ($) =>
      seq(
        field('verb', choice('hide', 'show', 'remove', 'restore')),
        field('target', alias($._to_eol, $.display_target)),
        $._newline,
      ),

    direction_statement: ($) =>
      seq(
        alias(
          token(/(?:top\s+to\s+bottom|left\s+to\s+right)\s+direction/i),
          $.direction,
        ),
        $._newline,
      ),

    allow_mixing_statement: ($) =>
      seq(alias(token(/allow[_ ]?mixing/i), $.keyword), $._newline),

    title_statement: ($) =>
      choice(
        seq('title', field('text', $._to_eol), $._newline),
        seq(
          'title',
          $._newline,
          repeat(choice($.raw_line, $._newline)),
          alias(token(prec(3, /end[ \t]+title/)), 'end title'),
          $._newline,
        ),
      ),

    caption_statement: ($) =>
      choice(
        seq('caption', field('text', $._to_eol), $._newline),
        seq(
          'caption',
          $._newline,
          repeat(choice($.raw_line, $._newline)),
          alias(token(prec(3, /end[ \t]+caption/)), 'end caption'),
          $._newline,
        ),
      ),

    header_statement: ($) =>
      choice(
        seq(
          alias(token(/(?:center|left|right)\s+header/), 'header'),
          field('text', $._to_eol),
          $._newline,
        ),
        seq('header', field('text', $._to_eol), $._newline),
        seq(
          choice('header', alias(token(/(?:center|left|right)\s+header/), 'header')),
          $._newline,
          repeat(choice($.raw_line, $._newline)),
          alias(token(prec(3, /end[ \t]+header/)), 'end header'),
          $._newline,
        ),
      ),

    footer_statement: ($) =>
      choice(
        seq(
          alias(token(/(?:center|left|right)\s+footer/), 'footer'),
          field('text', $._to_eol),
          $._newline,
        ),
        seq('footer', field('text', $._to_eol), $._newline),
        seq(
          choice('footer', alias(token(/(?:center|left|right)\s+footer/), 'footer')),
          $._newline,
          repeat(choice($.raw_line, $._newline)),
          alias(token(prec(3, /end[ \t]+footer/)), 'end footer'),
          $._newline,
        ),
      ),

    legend_block: ($) =>
      seq(
        alias(token(/(?:center|left|right)\s+legend|legend/), 'legend'),
        optional(field('text', $._to_eol)),
        $._newline,
        repeat(choice($.raw_line, $._newline)),
        alias(token(prec(3, /end[ \t]*legend/)), 'endlegend'),
        $._newline,
      ),

    scale_statement: ($) =>
      seq('scale', field('value', $._to_eol), $._newline),

    page_statement: ($) =>
      seq('page', field('value', $._to_eol), $._newline),

    newpage_statement: ($) =>
      seq('newpage', optional(field('value', $._to_eol)), $._newline),

    autonumber_statement: ($) =>
      seq('autonumber', optional(field('args', $._to_eol)), $._newline),

    skinparam_statement: ($) =>
      seq(
        'skinparam',
        field('name', $.identifier),
        choice(
          seq(field('value', $._to_eol), $._newline),
          seq(
            '{',
            $._newline,
            repeat(choice($.raw_line, $._newline)),
            '}',
            $._newline,
          ),
        ),
      ),

    style_block: ($) =>
      seq(
        '<style>',
        $._newline,
        optional(field('body', $.style_content)),
        alias(token(prec(3, '</style>')), '</style>'),
        $._newline,
      ),

    style_content: ($) =>
      seq($.raw_line, $._newline, repeat(choice($.raw_line, $._newline))),

    _pp_statement: ($) =>
      choice(
        $.preprocessor_if_block,
        $.preprocessor_while_block,
        $.preprocessor_procedure,
        $.preprocessor_function,
        $.preprocessor_definelong,
        $.preprocessor_sub,
        $.preprocessor_include,
        $.preprocessor_define,
        $.preprocessor_undef,
        $.preprocessor_theme,
        $.preprocessor_pragma,
        $.preprocessor_option,
        $.preprocessor_dump,
        $.preprocessor_log,
        $.preprocessor_assert,
        $.preprocessor_variable,
        $.preprocessor_return,
        $.preprocessor_unquoted,
        $.preprocessor,
      ),

    preprocessor: ($) =>
      seq(
        '!',
        field('name', $.identifier),
        optional(field('args', $._to_eol)),
        $._newline,
      ),

    _pp_body_line: ($) =>
      seq(token(prec(-5, /[^\r\n]+/)), $._newline),

    preprocessor_if_block: ($) =>
      seq(
        field(
          'kind',
          choice(
            alias(token(prec(6, /!ifdef/i)), '!ifdef'),
            alias(token(prec(6, /!ifndef/i)), '!ifndef'),
            alias(token(prec(6, /!if/i)), '!if'),
          ),
        ),
        optional(field('condition', alias($._to_eol, $.label))),
        $._newline,
        repeat(choice($._pp_body_line, $._newline)),
        repeat($.preprocessor_elseif),
        optional($.preprocessor_else),
        alias(token(prec(6, /!endif/i)), '!endif'),
        $._newline,
      ),

    preprocessor_elseif: ($) =>
      seq(
        alias(token(prec(6, /!elseif/i)), '!elseif'),
        optional(field('condition', alias($._to_eol, $.label))),
        $._newline,
        repeat(choice($._pp_body_line, $._newline)),
      ),

    preprocessor_else: ($) =>
      seq(
        alias(token(prec(6, /!else/i)), '!else'),
        $._newline,
        repeat(choice($._pp_body_line, $._newline)),
      ),

    preprocessor_while_block: ($) =>
      seq(
        alias(token(prec(6, /!while/i)), '!while'),
        optional(field('condition', alias($._to_eol, $.label))),
        $._newline,
        repeat(choice($._pp_body_line, $._newline)),
        alias(token(prec(6, /!endwhile/i)), '!endwhile'),
        $._newline,
      ),

    preprocessor_procedure: ($) =>
      seq(
        alias(token(prec(6, /!procedure/i)), '!procedure'),
        field('name', token(prec(2, /[^\s(]+/))),
        optional(
          seq(
            '(',
            field('parameters', alias(token(/[^)\r\n]*/), $.label)),
            ')',
          ),
        ),
        optional(field('value', alias($._to_eol, $.label))),
        $._newline,
        repeat(choice($._pp_body_line, $._newline)),
        alias(token(prec(6, /!endprocedure/i)), '!endprocedure'),
        $._newline,
      ),

    preprocessor_function: ($) =>
      seq(
        alias(token(prec(6, /!function/i)), '!function'),
        field('name', token(prec(2, /[^\s(]+/))),
        optional(
          seq(
            '(',
            field('parameters', alias(token(/[^)\r\n]*/), $.label)),
            ')',
          ),
        ),
        optional(field('value', alias($._to_eol, $.label))),
        $._newline,
        repeat(choice($._pp_body_line, $._newline)),
        alias(token(prec(6, /!endfunction/i)), '!endfunction'),
        $._newline,
      ),

    preprocessor_definelong: ($) =>
      seq(
        alias(token(prec(6, /!definelong/i)), '!definelong'),
        field('name', token(prec(2, /[^\s(]+/))),
        optional(
          seq(
            '(',
            field('parameters', alias(token(/[^)\r\n]*/), $.label)),
            ')',
          ),
        ),
        optional(field('value', alias($._to_eol, $.label))),
        $._newline,
        repeat(choice($._pp_body_line, $._newline)),
        alias(token(prec(6, /!enddefinelong/i)), '!enddefinelong'),
        $._newline,
      ),

    preprocessor_sub: ($) =>
      seq(
        alias(token(prec(6, /!startsub/i)), '!startsub'),
        field('name', token(prec(2, /[^\s]+/))),
        $._newline,
        repeat(choice($._pp_body_line, $._newline)),
        alias(token(prec(6, /!endsub/i)), '!endsub'),
        $._newline,
      ),

    preprocessor_include: ($) =>
      seq(
        field(
          'kind',
          choice(
            alias(token(prec(6, /!include_many/i)), '!include_many'),
            alias(token(prec(6, /!include_once/i)), '!include_once'),
            alias(token(prec(6, /!include_sub/i)), '!include_sub'),
            alias(token(prec(6, /!includesub/i)), '!includesub'),
            alias(token(prec(6, /!include/i)), '!include'),
          ),
        ),
        field('path', alias($._to_eol, $.label)),
        $._newline,
      ),

    preprocessor_define: ($) =>
      seq(
        alias(token(prec(6, /!define/i)), '!define'),
        field('name', token(prec(2, /[^\s(]+/))),
        optional(
          seq(
            '(',
            field('parameters', alias(token(/[^)\r\n]*/), $.label)),
            ')',
          ),
        ),
        optional(field('value', alias($._to_eol, $.label))),
        $._newline,
      ),

    preprocessor_undef: ($) =>
      seq(
        alias(token(prec(6, /!undef/i)), '!undef'),
        field('name', token(prec(2, /[^\s]+/))),
        $._newline,
      ),

    preprocessor_theme: ($) =>
      seq(
        alias(token(prec(6, /!theme/i)), '!theme'),
        optional(field('value', alias($._to_eol, $.label))),
        $._newline,
      ),

    preprocessor_pragma: ($) =>
      seq(
        alias(token(prec(6, /!pragma/i)), '!pragma'),
        optional(field('value', alias($._to_eol, $.label))),
        $._newline,
      ),

    preprocessor_option: ($) =>
      seq(
        alias(token(prec(6, /!option/i)), '!option'),
        optional(field('value', alias($._to_eol, $.label))),
        $._newline,
      ),

    preprocessor_dump: ($) =>
      seq(
        alias(token(prec(6, /!dump/i)), '!dump'),
        optional(field('value', alias($._to_eol, $.label))),
        $._newline,
      ),

    preprocessor_log: ($) =>
      seq(
        alias(token(prec(6, /!log/i)), '!log'),
        optional(field('value', alias($._to_eol, $.label))),
        $._newline,
      ),

    preprocessor_assert: ($) =>
      seq(
        alias(token(prec(6, /!assert/i)), '!assert'),
        optional(field('value', alias($._to_eol, $.label))),
        $._newline,
      ),

    preprocessor_variable: ($) =>
      seq(
        '!',
        field('name', token(prec(3, /\$[\w]+/))),
        optional(field('value', alias($._to_eol, $.label))),
        $._newline,
      ),

    preprocessor_return: ($) =>
      seq(
        alias(token(prec(6, /!return/i)), '!return'),
        optional(field('value', alias($._to_eol, $.label))),
        $._newline,
      ),

    preprocessor_unquoted: ($) =>
      seq(
        alias(token(prec(6, /!unquoted/i)), '!unquoted'),
        optional(field('value', alias($._to_eol, $.label))),
        $._newline,
      ),

    _entity_head: ($) =>
      seq(
        field('name', $._entity_name),
        optional(field('generics', $.generics)),
        repeat($._entity_head_suffix),
      ),

    _entity_head_suffix: ($) =>
      choice(
        field('stereotype', $.stereotype),
        seq('as', field('alias', $._entity_name)),
        seq('extends', field('extends', $.entity_list)),
        seq('implements', field('implements', $.entity_list)),
        field('color', $.color),
        seq('order', field('order', $.number)),
        field('tag', $.tag),
        field('link', $.hyperlink),
      ),

    association_relation: ($) =>
      seq(
        '(',
        field('left', $.entity_list),
        ')',
        field('operator', $.relation_operator),
        field('right', $._relation_end),
        optional(field('activation', $.activation)),
        optional(field('color', $.color)),
        optional(field('link', $.hyperlink)),
        optional(seq(':', field('label', $.label))),
        $._eos,
      ),

    circle_shorthand: ($) =>
      seq(
        '()',
        field('name', $._entity_name),
        repeat($._entity_head_suffix),
        choice(
          $._eos,
          seq(field('body', $.entity_body), $._eos),
          seq($._newline, field('body', $.entity_body), $._eos),
        ),
      ),

    diamond_shorthand: ($) =>
      seq(
        '<>',
        field('name', $._entity_name),
        repeat($._entity_head_suffix),
        choice(
          $._eos,
          seq(field('body', $.entity_body), $._eos),
          seq($._newline, field('body', $.entity_body), $._eos),
        ),
      ),

    component_shorthand: ($) =>
      seq(
        field('name', $.component_ref),
        repeat($._entity_head_suffix),
        choice(
          $._eos,
          seq(field('body', $.entity_body), $._eos),
          seq($._newline, field('body', $.entity_body), $._eos),
        ),
      ),

    boundary_message: ($) =>
      choice(
        seq(
          field(
            'operator',
            alias(
              token(
                prec(
                  2,
                  /[\[?][ox?]?[-.]+(>>|>[xo]?|\\\\|\\|\/\/|\/)?/,
                ),
              ),
              $.relation_operator,
            ),
          ),
          field('right', $._entity_name),
          optional(seq(':', field('label', $.label))),
          $._eos,
        ),
        seq(
          field('left', $._entity_name),
          field(
            'operator',
            alias(
              token(
                prec(2, /(<\||<|\*|[ox])?[-.]+(>>|>[xo]?|>\?)?[\]?]/),
              ),
              $.relation_operator,
            ),
          ),
          optional(seq(':', field('label', $.label))),
          $._eos,
        ),
      ),

    _entity_name: ($) => choice($.identifier, $.string, $.component_ref, $.usecase_ref, $.actor_ref),

    _relation_end: ($) =>
      choice($.identifier, $.string, $.pseudostate, $.member_ref, $.component_ref, $.usecase_ref, $.actor_ref),

    component_ref: ($) =>
      seq('[', field('name', alias(token(/[^\]\r\n]+/), $.component_name)), ']'),

    usecase_ref: ($) =>
      seq('(', field('name', alias(token(/[^()\r\n]+/), $.usecase_name)), ')'),

    actor_ref: ($) =>
      seq(':', field('name', alias(token(/[^:\r\n]+/), $.actor_name)), ':'),

    member_ref: ($) =>
      seq(
        $._entity_name,
        token.immediate('::'),
        choice($.identifier, $.string),
      ),

    entity_list: ($) => sep1($._entity_name, ','),

    generics: ($) => token(seq('<', /[^<>\n]+/, '>')),

    stereotype: ($) => token(seq('<<', /[^>\n]+/, '>>')),

    hyperlink: ($) => token(prec(2, seq('[[', /[^\]\n]+/, ']]'))),

    tag: ($) => token(/\$[\w-]+/),

    color: ($) => token(/#[\w;:.\/\\|-]+/),

    string: ($) => token(seq('"', /([^"\\\n]|\\.)*/, '"')),

    number: ($) => token(/\d+/),

    identifier: ($) =>
      token(/\$?[\p{L}_][\p{L}\p{N}_]*(?:[.-][\p{L}\p{N}_]+)*/),

    label: ($) => $._to_eol,

    _to_eol: ($) =>
      token(
        prec(
          -1,
          choice(
            /[^ \t\r\n}][^\r\n]*[^ \t\r\n}]/,
            /[^ \t\r\n}]/,
          ),
        ),
      ),

    _bracket_body_line: ($) =>
      seq(token(prec(-2, /[^\]\s][^\r\n]*/)), $._newline),

    raw_line: ($) =>
      choice(
        seq($._raw_statement, $._newline),
        seq(token(prec(-5, /[^ \t\r\n][^\r\n]*/)), $._newline),
      ),

    _newline: ($) => /\r?\n/,

    _eos: ($) => choice($._newline, $._brace_ahead),
  },
});
