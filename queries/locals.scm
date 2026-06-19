; PlantUML Tree-sitter Local Queries
; Scopes, definitions and references. Only real grammar nodes are referenced.

; ==================== SCOPES ====================
(diagram) @local.scope
(class_definition) @local.scope
(object_definition) @local.scope

; ==================== DEFINITIONS ====================
; A class/object introduces a named symbol.
(class_definition
  (class_name) @local.definition.type)

(object_definition
  (object_name) @local.definition.type)

; Aliases (as X) define an additional reachable name.
(class_alias) @local.definition.var

; ==================== REFERENCES ====================
; Bare identifiers refer to previously defined symbols.
(identifier) @local.reference
