; Diagram bodies
[
  (uml_diagram)
  (generic_diagram)
  (mindmap_diagram)
  (wbs_diagram)
  (gantt_diagram)
  (timing_diagram)
  (json_diagram)
  (yaml_diagram)
  (hcl_diagram)
  (nwdiag_diagram)
  (salt_diagram)
  (ditaa_diagram)
  (chen_diagram)
  (git_diagram)
  (files_diagram)
  (chronology_diagram)
  (ebnf_diagram)
  (regex_diagram)
  (packet_diagram)
  (board_diagram)
  (wire_diagram)
  (flow_diagram)
  (bpm_diagram)
  (math_diagram)
  (latex_diagram)
  (creole_diagram)
  (dot_diagram)
  (sprites_diagram)
  (chart_diagram)
] @indent.begin

; Containers
[
  (entity_body)
  (enum_body)
  (state_body)
  (package_block)
  (namespace_block)
  (together_block)
  (activity_container_block)
  (nwdiag_network)
  (nwdiag_group)
  (salt_group)
  (chen_entity)
  (chen_group)
  (style_block)
  (style_content)
  (json_content)
  (yaml_content)
  (hcl_content)
  (ditaa_body)
] @indent.begin

; Sequence
[
  (sequence_frame)
  (sequence_else_clause)
  (box_block)
  (reference)
  (note_statement)
  (mainframe_statement)
] @indent.begin

; Activity
[
  (if_block)
  (elseif_clause)
  (activity_else_clause)
  (while_block)
  (repeat_block)
  (switch_block)
  (case_clause)
  (fork_block)
  (fork_again)
  (split_block)
  (split_again)
  (partition_block)
  (activity_group_block)
] @indent.begin

; EBNF / regex
[
  (ebnf_rule)
  (ebnf_optional)
  (ebnf_repeat)
  (ebnf_group)
  (regex_group)
  (regex_lookaround)
] @indent.begin

; Preprocessor
[
  (preprocessor_if_block)
  (preprocessor_elseif)
  (preprocessor_else)
  (preprocessor_while_block)
  (preprocessor_procedure)
  (preprocessor_function)
  (preprocessor_definelong)
  (preprocessor_sub)
] @indent.begin

; Branches and closers
[
  "}"
  "end"
  "endif"
  "endwhile"
  "endswitch"
  "end box"
  "end note"
  "end ref"
  "end title"
  "end header"
  "end footer"
  "endlegend"
  "end group"
  "end fork"
  "end merge"
  "!endif"
  "!else"
  "!elseif"
  "!endwhile"
  "!endprocedure"
  "!endfunction"
  "!enddefinelong"
  "!endsub"
] @indent.branch

(activity_else_clause "else" @indent.branch)
(elseif_clause "elseif" @indent.branch)
(sequence_else_clause "else" @indent.branch)
(case_clause "case" @indent.branch)
(fork_again "fork" @indent.branch)
(split_again "split" @indent.branch)
(repeat_block "repeat" @indent.branch)
(preprocessor_else "!else" @indent.branch)
(preprocessor_elseif "!elseif" @indent.branch)

; Leaf lines
[
  (raw_line)
  (comment)
  (gantt_task)
  (gantt_group)
  (mindmap_node)
  (wbs_node)
  (salt_text)
  (chronology_sentence)
  (creole_text)
] @indent.auto

; Multi-line text payloads
[
  (title_statement)
  (caption_statement)
  (header_statement)
  (footer_statement)
  (legend_block)
  (note_statement)
  (reference)
] @indent.align
