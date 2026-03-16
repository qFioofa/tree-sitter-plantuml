; PlantUML Tree-sitter Local Queries
; Defines local variable scoping for PlantUML

; ==================== DIAGRAM BLOCKS ====================
; Each diagram block creates its own scope
(diagram) @local.scope

; ==================== CLASS DEFINITIONS ====================
; Class definitions create a scope for their members
(class_definition) @local.scope

; Class members are local to the class
(class_body
  (class_function
    name: (_) @local.definition))

(class_body
  (class_field
    name: (_) @local.definition))

; ==================== OBJECT DEFINITIONS ====================
; Object definitions create a scope
(object_definition) @local.scope

(object_name) @local.definition

; ==================== NOTES WITH REFERENCES ====================
; Notes that reference elements
(note_of_inline
  (_) @local.reference)

(note_of_multiline
  (_) @local.reference)

; ==================== SEQUENCE REFERENCES ====================
; References to lifelines/participants
(sequence_ref_inline
  (_) @local.reference)

(sequence_ref_block
  (_) @local.reference)

; ==================== ACTIVITY REFERENCES ====================
; Labels and goto references
(activity_if
  (_) @local.reference)

(activity_else
  (_) @local.reference)

(activity_while
  (_) @local.reference)

; ==================== ALIASES ====================
; Class aliases
(class_alias
  (_) @local.definition)

; Object aliases
(object_definition
  "as" @keyword
  (_) @local.definition)

; Note aliases
(note_as
  "as" @keyword
  (_) @local.definition)
