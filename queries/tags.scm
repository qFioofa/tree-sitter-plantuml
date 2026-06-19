; PlantUML Tree-sitter Tags Queries
; Symbol tags for navigation / outline views.
; Only the @name capture inside a @definition.* pattern is used by consumers.

; ==================== CLASS DEFINITIONS ====================
(class_definition
  (class_keyword)
  (class_name) @name) @definition.class

; ==================== OBJECT DEFINITIONS ====================
(object_definition
  (object_keyword)
  (object_name) @name) @definition.type
