(class_declaration "class" name: (identifier) @name) @definition.class
(class_declaration "interface" name: (identifier) @name) @definition.interface
(enum_declaration name: (identifier) @name) @definition.enum
(class_declaration name: (identifier) @name) @definition.class
(entity_declaration name: (identifier) @name) @definition.type
(component_shorthand name: (component_ref name: (component_name) @name)) @definition.type
(state_declaration name: (identifier) @name) @definition.type
(package_block name: (identifier) @name) @definition.module
(namespace_block name: (identifier) @name) @definition.module
(method name: (identifier) @name) @definition.method
(attribute name: (identifier) @name) @definition.field

; Extended definitions
(requirement_declaration name: (identifier) @name) @definition.type
(requirement_declaration alias: (identifier) @name) @definition.type
(nwdiag_network name: (identifier) @name) @definition.type
(nwdiag_node name: (identifier) @name) @definition.type
(chen_entity name: (identifier) @name) @definition.type
(chen_attribute name: (identifier) @name) @definition.field
(chen_relationship name: (identifier) @name) @definition.type
(ebnf_rule name: (identifier) @name) @definition.function
(macro_call name: (identifier) @name) @reference.call
(timing_player_decl alias: (identifier) @name) @definition.type
(timing_clock alias: (identifier) @name) @definition.type
(git_commit hash: (git_hash) @name) @definition.commit
(sprite_declaration name: (tag) @name) @definition.type
(map_member key: (string) @name) @definition.field
(preprocessor_define name: _ @name) @definition.macro
(preprocessor_procedure name: _ @name) @definition.macro
(preprocessor_function name: _ @name) @definition.macro
(preprocessor_definelong name: _ @name) @definition.macro
(preprocessor_sub name: _ @name) @definition.macro
(preprocessor_variable name: _ @name) @definition.constant

; Extended references
(requirement_relation left: (identifier) @name) @reference.type
(requirement_relation right: (identifier) @name) @reference.type
(nwdiag_link left: (identifier) @name) @reference.type
(nwdiag_link right: (identifier) @name) @reference.type
(timing_message left: (identifier) @name) @reference.type
(timing_message right: (identifier) @name) @reference.type
(macro_argument (identifier) @name) @reference.call
