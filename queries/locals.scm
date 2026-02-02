; locals.scm

; Define scopes for variable definitions and references within diagrams
(scope) @local.scope

; Diagram blocks create a new scope
(diagram_block) @local.scope

; Class definitions introduce member variables and methods
(class_group_start
  (name) @local.definition.type
  (alias)? @local.definition.type
  .
  (class_body)? @local.scope)

; Members inside class body
(class_function (name) @local.definition.function)
(class_field (name) @local.definition.variable)

; Object definitions introduce instance variables
(object_add_fields (identifier) @local.definition.variable)

; General identifiers used as variables/actors
(general_element (actor) @local.reference)
(general_element (identifier) @local.reference)

; Links might reference actors/elements defined elsewhere in the diagram scope
(link) @local.reference
