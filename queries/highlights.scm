; Comments

(comment_line) @comment
(block_comment) @comment @spell

; Diagram envelope

(diagram_start) @keyword.directive
(diagram_end) @keyword.directive
(diagram_name) @string.special

; Declarations and structural keywords

[
  "class"
  "interface"
  "enum"
  "annotation"
  "protocol"
  "struct"
  "exception"
  "metaclass"
] @keyword.type

(abstract) @keyword.modifier
(entity_kind) @keyword.type
(enum_value) @constant
(port_member kind: _ @keyword.type)
(autoactivate_statement) @keyword.operator
(boundary_message operator: (relation_operator) @operator)

[
  "state"
  "package"
  "namespace"
  "together"
] @keyword.type

[
  "as"
  "extends"
  "implements"
  "order"
] @keyword.operator

; Members

(visibility) @keyword.operator
(modifier) @keyword.modifier
(member_separator) @punctuation.special

(method name: (identifier) @function.method)
(attribute name: (identifier) @variable.member)
(method type: (type) @type)
(attribute type: (type) @type)
(parameter) @variable.parameter
(raw_text) @string.special

; Types and names

(class_declaration name: (identifier) @type)
(class_declaration alias: (identifier) @type)
(enum_declaration name: (identifier) @type)
(enum_declaration alias: (identifier) @type)
(component_shorthand name: (component_ref name: (component_name) @type))
(component_shorthand alias: (identifier) @type)
(entity_declaration name: (identifier) @type)
(entity_declaration alias: (identifier) @type)
(state_declaration name: (identifier) @type)
(state_declaration alias: (identifier) @type)
(package_block name: (identifier) @module)
(namespace_block name: (identifier) @module)
(component_name) @type
(usecase_name) @type
(actor_name) @type

; Relations

(relation left: (identifier) @type)
(relation right: (identifier) @type)
(relation left: (string) @string)
(relation right: (string) @string)
(relation operator: (relation_operator) @operator)
(boundary_message operator: (relation_operator) @operator)
(relation activation: (activation) @operator)
(relation qualifier: (qualifier) @string.special)
(member_ref (identifier) @type)
(pseudostate) @constant
(label) @string
(stereotype) @attribute
(color) @constant
(tag) @attribute
(hyperlink) @string.special.url
(string) @string
(number) @number

; Activity diagrams

[
  "start"
  "stop"
  "kill"
  "detach"
  "label"
  "goto"
  "backward"
] @keyword.control

[
  "if"
  "else"
  "elseif"
  "endif"
  "while"
  "endwhile"
  "repeat"
  "switch"
  "case"
  "endswitch"
  "fork"
  "split"
  "again"
  "partition"
] @keyword.conditional

[
  "alt"
  "opt"
  "loop"
  "par"
  "break"
  "critical"
  "group"
  "end"
] @keyword.conditional

(action_text) @string
(activity_control target: (identifier) @label)
(activity_arrow operator: (arrow_operator) @operator)
(activity_arrow label: (label) @string)
(connector) @label
(condition) @string.special
(branch_label) @string
(lane_text) @module

; Sequence diagrams

[
  "activate"
  "deactivate"
  "create"
  "destroy"
  "return"
  "ref over"
  "end ref"
  "box"
  "end box"
] @keyword.control

(sequence_lifecycle target: (identifier) @type)
(sequence_frame label: (label) @string)
(sequence_else_clause label: (label) @string)
(reference target: (entity_list (identifier) @type))
(return_statement label: (label) @string)
(box_block name: (string) @string)
(delay_text) @comment
(spacer) @punctuation.special
(divider) @punctuation.special
(autonumber_statement) @keyword.directive

; States

(state_concurrent) @punctuation.special
(state_declaration description: (label) @string)

; Notes

(note_position) @keyword.modifier
(note_statement position: (note_position) @keyword.modifier)
(note_statement target: (entity_list (identifier) @type))
(note_statement text: (label) @comment)
(note_statement text: (string) @comment)
"end note" @keyword

; Display and page directives

[
  "hide"
  "show"
  "remove"
  "restore"
  "skinparam"
  "title"
  "caption"
  "header"
  "footer"
  "legend"
  "scale"
  "page"
  "newpage"
] @keyword.directive

"end title" @keyword.directive
"end header" @keyword.directive
"end footer" @keyword.directive
"endlegend" @keyword.directive
(direction) @keyword.directive
(keyword) @keyword.directive

(display_directive target: (display_target) @string)
(skinparam_statement name: (identifier) @property)
(title_statement) @markup.heading
(caption_statement) @markup.heading
(header_statement) @comment.note
(footer_statement) @comment.note
(legend_block) @comment.note
(style_block) @markup.raw
(raw_line) @markup.raw

; Preprocessor

(preprocessor) @keyword.directive
(preprocessor name: (identifier) @property)

; Punctuation

[
  "{"
  "}"
  "("
  ")"
  "["
  "]"
  "<style>"
  "</style>"
] @punctuation.bracket

[
  ":"
  ","
  "::"
] @punctuation.delimiter

; ============================================================
; Extended diagram families
; ============================================================

; Timing
(timing_clock "clock" @keyword.type)
(timing_clock name: (string) @type)
(timing_clock alias: (identifier) @type)
(timing_clock options: (label) @string @spell)
(timing_player_decl kind: _ @keyword.type)
(timing_player_decl name: (string) @type)
(timing_player_decl alias: (identifier) @type)
(timing_player_decl rest: (label) @string @spell)
(timing_scale value: (number) @number)
(timing_scale pixels: (number) @number)
(timing_directive "hide time axis" @keyword.directive)
(timing_directive "use" @keyword.directive)
(timing_directive "pixel" @keyword.directive)
(timing_directive "mode" @keyword.directive)
(timing_directive "ticks" @keyword.directive)
(timing_directive "printscale" @keyword.directive)
(timing_directive format: (label) @string @nospell)
(timing_directive value: (label) @string @nospell)
(timing_time) @number
(timing_state player: (identifier) @type)
(timing_state prefix_time: (number) @number)
(timing_state time: (number) @number)
(timing_state value: (label) @string @spell)
(timing_message left: (identifier) @type)
(timing_message right: (identifier) @type)
(timing_message operator: _ @operator)
(timing_message label: (label) @string @spell)
(timing_constraint text: (label) @string @spell)
(timing_highlight text: (label) @string @spell)
(timing_note "note" @keyword)
(timing_note text: (label) @comment @spell)

; Embedded JSON / YAML / HCL
(json_highlight "#highlight" @keyword.directive)
(yaml_highlight "#highlight" @keyword.directive)
(hcl_highlight "#highlight" @keyword.directive)
(json_highlight path: (string) @string.special)
(yaml_highlight path: (string) @string.special)
(hcl_highlight path: (string) @string.special)
(json_highlight color: (string) @constant)
(yaml_highlight color: (string) @constant)
(hcl_highlight color: (string) @constant)
(json_content) @markup.raw
(yaml_content) @markup.raw
(hcl_content) @markup.raw

; nwdiag
(nwdiag_network "network" @keyword.type)
(nwdiag_network name: (identifier) @type)
(nwdiag_network label: (label) @string @spell)
(nwdiag_group "group" @keyword.type)
(nwdiag_group label: (label) @string @spell)
(nwdiag_node name: (identifier) @type)
(nwdiag_node attributes: (label) @property)
(nwdiag_element kind: _ @property)
(nwdiag_element value: (label) @string @spell)
(nwdiag_property "property" @keyword.directive)
(nwdiag_property value: (label) @property)
(nwdiag_link left: (identifier) @type)
(nwdiag_link right: (identifier) @type)
(nwdiag_link operator: _ @operator)
(nwdiag_link label: (label) @string @spell)

; Salt
(salt_group) @punctuation.bracket
(salt_group_kind) @keyword.type
(salt_button text: (label) @string @spell)
(salt_button rest: (label) @string @spell)
(salt_checkbox) @boolean
(salt_radio) @boolean
(salt_textfield text: (string) @string)
(salt_textfield rest: (label) @string @spell)
(salt_table_row) @markup
(salt_separator) @punctuation.special
(salt_text) @string @spell

; Ditaa
(ditaa_option) @keyword.option
(ditaa_body) @markup.raw @nospell

; Chen ER
(chen_entity "entity" @keyword.type)
(chen_entity name: (identifier) @type)
(chen_attribute "attribute" @keyword.type)
(chen_attribute name: (identifier) @variable.member)
(chen_relationship "relationship" @keyword.type)
(chen_relationship name: (identifier) @type)
(chen_associate "associate" @keyword.operator)
(chen_subclass "subclass" @keyword.operator)
(chen_group "group" @keyword.type)
(chen_group "end group" @keyword)
(chen_cardinality) @string.special
(chen_weak) @keyword.modifier

; Git
(git_commit) @type
(git_hash) @string.special @nospell
(git_ref) @label
(git_graph_line) @punctuation.special
(git_metadata key: _ @property)
(git_metadata value: (label) @string @spell)

; Files
(files_dir path: (path) @module)
(files_file path: (path) @string.special.path)
(files_tree) @punctuation.special
(files_dir description: (label) @comment @spell)
(files_file description: (label) @comment @spell)
(files_comment text: (label) @comment @spell)

; Chronology
(chronology_scale) @number
(chronology_time) @string.special @nospell
(chronology_sentence) @string @spell

; EBNF
(ebnf_rule name: (identifier) @function)
(ebnf_identifier) @variable
(ebnf_terminal) @string
(ebnf_special) @string.special @nospell
(ebnf_comment) @comment @spell
(ebnf_note) @comment @spell
(ebnf_optional) @punctuation.bracket
(ebnf_repeat) @punctuation.bracket
(ebnf_group) @punctuation.bracket
(ebnf_expression "|" @operator)
(ebnf_concatenation "," @operator)

; Regex
(regex_class) @string.regexp
(regex_escape) @string.escape
(regex_anchor) @keyword.operator
(regex_quantifier) @keyword.operator
(regex_alternation) @operator
(regex_group) @punctuation.bracket
(regex_lookaround) @keyword.operator
(regex_literal) @string

; Packet
(packet_field range: (packet_range) @number)
(packet_field label: (label) @property @spell)

; Board
(board_column "+" @keyword.type)
(board_column label: (label) @module @spell)
(board_card) @string @spell

; Wire
(wire_component kind: _ @keyword.type)
(wire_component name: (label) @type @spell)
(wire_command kind: _ @keyword.operator)
(wire_command value: (label) @string @spell)

; Flow / BPM
(flow_link) @operator
(bpm_task (action_text) @string @spell)
(bpm_command kind: _ @keyword.control)
(bpm_command value: (label) @string @spell)

; Math / LaTeX / Creole / DOT / sprites / chart
(math_diagram body: (math_body) @markup.math @nospell)
(latex_diagram body: (latex_body) @markup.math @nospell)
(creole_heading) @markup.heading.1 @spell
(creole_list_item) @markup.list @spell
(creole_table_row) @markup @spell
(creole_rule) @punctuation.special
(creole_text) @markup @spell
(dot_diagram body: (dot_body) @markup.raw @nospell)
(sprites_diagram) @module
(sprite_declaration "sprite" @keyword.type)
(sprite_declaration name: (tag) @type)
(sprite_declaration source: (label) @string.special.path)
(chart_diagram body: (chart_body) @markup.raw @spell)

; Requirement diagrams
(requirement_declaration kind: _ @keyword.type)
(requirement_declaration name: (identifier) @type)
(requirement_declaration alias: (identifier) @type)
(requirement_field name: _ @property)
(requirement_field value: (label) @string @spell)
(requirement_relation operator: _ @operator)
(requirement_relation left: (identifier) @type)
(requirement_relation right: (identifier) @type)
(requirement_relation label: (label) @string @spell)

; Macros / stdlib
(macro_call name: (identifier) @function.macro)
(macro_argument) @variable.parameter
(macro_argument (label) @string @spell)

; Additional common constructs
(state_behavior kind: _ @keyword.function)
(state_behavior action: (label) @string @spell)
(map_member key: (string) @property)
(map_member value: (label) @string @spell)
(link_anchor "anchor" @keyword.directive)
(link_anchor name: (label) @label)
(rotate_statement "rotate" @keyword.directive)
(minwidth_statement "minwidth" @keyword.directive)
(namespace_separator "set namespaceSeparator" @keyword.directive)
(pragma_statement "pragma" @keyword.directive)

; Structured preprocessor
(preprocessor_if_block kind: _ @keyword.conditional)
(preprocessor_elseif "!elseif" @keyword.conditional)
(preprocessor_else "!else" @keyword.conditional)
(preprocessor_if_block "!endif" @keyword.conditional)
(preprocessor_while_block "!while" @keyword.repeat)
(preprocessor_while_block "!endwhile" @keyword.repeat)
(preprocessor_procedure "!procedure" @keyword.function)
(preprocessor_procedure name: _ @function.macro)
(preprocessor_procedure "!endprocedure" @keyword)
(preprocessor_function "!function" @keyword.function)
(preprocessor_function name: _ @function.macro)
(preprocessor_function "!endfunction" @keyword)
(preprocessor_definelong "!definelong" @keyword.function)
(preprocessor_definelong name: _ @function.macro)
(preprocessor_definelong "!enddefinelong" @keyword)
(preprocessor_sub "!startsub" @keyword.function)
(preprocessor_sub name: _ @function.macro)
(preprocessor_sub "!endsub" @keyword)
(preprocessor_include kind: _ @keyword.import)
(preprocessor_include path: (label) @string.special.path @nospell)
(preprocessor_define "!define" @keyword.directive.define)
(preprocessor_define name: _ @function.macro)
(preprocessor_undef "!undef" @keyword.directive)
(preprocessor_theme "!theme" @keyword.directive)
(preprocessor_pragma "!pragma" @keyword.directive)
(preprocessor_option "!option" @keyword.directive)
(preprocessor_dump "!dump" @keyword.directive)
(preprocessor_log "!log" @keyword.directive)
(preprocessor_assert "!assert" @keyword.directive)
(preprocessor_variable name: _ @variable)
(preprocessor_return "!return" @keyword.return)
(preprocessor_unquoted "!unquoted" @keyword.modifier)

; Error recovery
(ERROR) @error
