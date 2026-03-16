; PlantUML Tree-sitter Tags Queries
; Defines symbol tags for navigation and outline views

; ==================== CLASS DEFINITIONS ====================
(class_definition
  (class_name) @definition.class)

; ==================== OBJECT DEFINITIONS ====================
(object_definition
  (object_name) @definition.object)

; ==================== CLASS MEMBERS ====================
(class_body
  (class_function
    name: (_) @definition.method))

(class_body
  (class_field
    name: (_) @definition.field))

; ==================== ALIASES ====================
(class_alias
  (_) @definition.alias)

(object_definition
  "as" @keyword
  (_) @definition.alias)

; ==================== TITLES ====================
(title_inline) @definition.title

(title_multiline) @definition.title

; ==================== NOTES ====================
(note_inline) @definition.note

(note_multiline) @definition.note

(note_as
  (_) @definition.note)

; ==================== CAPTIONS ====================
(caption) @definition.caption

; ==================== HEADERS / LEGENDS / FOOTERS ====================
(header_inline) @definition.header

(header_multiline) @definition.header

; ==================== REFERENCES ====================
; References in notes
(note_of_inline
  (_) @reference)

(note_of_multiline
  (_) @reference)

; Sequence references
(sequence_ref_inline
  (_) @reference)

(sequence_ref_block
  (_) @reference)
