; Classes / entities / states / requirements
(class_declaration body: (entity_body) @class.inner) @class.outer
(entity_declaration body: (entity_body) @class.inner) @class.outer
(state_declaration body: (state_body) @class.inner) @class.outer
(requirement_declaration) @class.outer
(enum_declaration body: (enum_body) @class.inner) @class.outer

; Functions / methods / macros
(method) @function.outer
(preprocessor_procedure) @function.outer
(preprocessor_function) @function.outer
(preprocessor_definelong) @function.outer
(preprocessor_sub) @function.outer
(ebnf_rule) @function.outer
(macro_call) @function.outer
(parameter_list) @function.inner

; Blocks
[
  (package_block)
  (namespace_block)
  (together_block)
  (sequence_frame)
  (if_block)
  (while_block)
  (repeat_block)
  (switch_block)
  (fork_block)
  (split_block)
  (partition_block)
  (activity_group_block)
  (box_block)
  (note_statement)
  (legend_block)
  (title_statement)
  (caption_statement)
  (header_statement)
  (footer_statement)
  (style_block)
  (nwdiag_network)
  (nwdiag_group)
  (salt_group)
  (chen_group)
  (preprocessor_if_block)
  (preprocessor_while_block)
  (ebnf_optional)
  (ebnf_repeat)
  (ebnf_group)
  (regex_group)
] @block.outer

(entity_body) @block.inner
(state_body) @block.inner
(enum_body) @block.inner
(style_content) @block.inner

; Parameters
(parameter) @parameter.inner
(macro_argument) @parameter.inner

; Comments
(comment_line) @comment.outer
(block_comment) @comment.outer

; Statements
(relation) @statement.outer
(sequence_lifecycle) @statement.outer
(activity_action) @statement.outer
(activity_control) @statement.outer
(note_statement) @statement.outer
(gantt_task) @statement.outer
(mindmap_node) @statement.outer
(wbs_node) @statement.outer
