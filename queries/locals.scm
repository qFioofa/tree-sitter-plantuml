; Scopes

(uml_diagram) @local.scope
(generic_diagram) @local.scope
(class_declaration) @local.scope
(enum_declaration) @local.scope
(entity_declaration) @local.scope
(component_shorthand) @local.scope
(state_declaration) @local.scope
(package_block) @local.scope
(namespace_block) @local.scope
(together_block) @local.scope
(sequence_frame) @local.scope
(if_block) @local.scope
(while_block) @local.scope
(repeat_block) @local.scope
(switch_block) @local.scope
(fork_block) @local.scope
(split_block) @local.scope
(partition_block) @local.scope
(box_block) @local.scope

; Definitions

(class_declaration name: (identifier) @local.definition.type)
(class_declaration alias: (identifier) @local.definition.type)
(entity_declaration name: (identifier) @local.definition.type)
(entity_declaration alias: (identifier) @local.definition.type)
(enum_declaration name: (identifier) @local.definition.type)
(enum_declaration alias: (identifier) @local.definition.type)
(enum_value) @local.definition.constant
(component_shorthand name: (component_ref name: (component_name) @local.definition.type))
(component_shorthand alias: (identifier) @local.definition.type)
(port_member name: (identifier) @local.definition.field)
(state_declaration name: (identifier) @local.definition.type)
(state_declaration alias: (identifier) @local.definition.type)
(package_block name: (identifier) @local.definition.module)
(namespace_block name: (identifier) @local.definition.module)
(method name: (identifier) @local.definition.method)
(attribute name: (identifier) @local.definition.field)

; References

(relation left: (identifier) @local.reference)
(relation right: (identifier) @local.reference)
(boundary_message left: (identifier) @local.reference)
(boundary_message right: (identifier) @local.reference)
(member_ref (identifier) @local.reference)
(sequence_lifecycle target: (identifier) @local.reference)
(reference target: (entity_list (identifier) @local.reference))
(note_statement target: (entity_list (identifier) @local.reference))
(component_ref name: (component_name) @local.reference)
(usecase_ref name: (usecase_name) @local.reference)
(actor_ref name: (actor_name) @local.reference)

; Extended scopes
[
  (mindmap_diagram)
  (wbs_diagram)
  (gantt_diagram)
  (timing_diagram)
  (json_diagram)
  (yaml_diagram)
  (hcl_diagram)
  (nwdiag_diagram)
  (salt_diagram)
  (chen_diagram)
  (git_diagram)
  (files_diagram)
  (ebnf_diagram)
  (regex_diagram)
  (flow_diagram)
  (bpm_diagram)
  (requirement_declaration)
  (nwdiag_network)
  (nwdiag_group)
  (salt_group)
  (chen_entity)
  (chen_group)
  (preprocessor_if_block)
  (preprocessor_while_block)
  (preprocessor_procedure)
  (preprocessor_function)
  (preprocessor_definelong)
  (preprocessor_sub)
] @local.scope

; Extended definitions
(requirement_declaration name: (identifier) @local.definition.type)
(requirement_declaration alias: (identifier) @local.definition.type)
(nwdiag_network name: (identifier) @local.definition.type)
(nwdiag_node name: (identifier) @local.definition.type)
(chen_entity name: (identifier) @local.definition.type)
(chen_attribute name: (identifier) @local.definition.field)
(chen_relationship name: (identifier) @local.definition.type)
(ebnf_rule name: (identifier) @local.definition.function)
(macro_call name: (identifier) @local.definition.macro)
(timing_player_decl alias: (identifier) @local.definition.type)
(timing_clock alias: (identifier) @local.definition.type)
(git_commit hash: (git_hash) @local.definition.commit)
(sprite_declaration name: (tag) @local.definition.type)
(map_member key: (string) @local.definition.field)
(preprocessor_define name: _ @local.definition.macro)
(preprocessor_procedure name: _ @local.definition.macro)
(preprocessor_function name: _ @local.definition.macro)
(preprocessor_definelong name: _ @local.definition.macro)
(preprocessor_sub name: _ @local.definition.macro)
(preprocessor_variable name: _ @local.definition.variable)

; Extended references
(timing_message left: (identifier) @local.reference)
(timing_message right: (identifier) @local.reference)
(timing_state player: (identifier) @local.reference)
(nwdiag_link left: (identifier) @local.reference)
(nwdiag_link right: (identifier) @local.reference)
(requirement_relation left: (identifier) @local.reference)
(requirement_relation right: (identifier) @local.reference)
(macro_call arguments: (macro_arguments (macro_argument (identifier) @local.reference)))
