; PlantUML Tree-sitter Highlight Queries
; Full coverage of every node produced by the grammar.
; Note: keyword sub-tokens baked into regex tokens (e.g. "if" inside
; activity_if) are not separately addressable, so whole nodes are captured.

; ==================== COMMENTS ====================
(comment_line) @comment
(comment_block) @comment @spell

; ==================== DIAGRAM BLOCKS ====================
(diagram_start) @keyword.import
(diagram_end) @keyword.import

; ==================== STRINGS ====================
(string) @string
(string "\"" @punctuation.special)

(quoted_definition) @string.special
(quoted_definition ":" @punctuation.delimiter)

; ==================== CLASS DEFINITIONS ====================
(class_keyword) @keyword.type
(class_name) @type
(class_alias) @variable.parameter

(class_stereotype) @attribute
(class_stereotype "<<" @punctuation.bracket)
(class_stereotype ">>" @punctuation.bracket)

(class_color) @constant
(class_color "#" @punctuation.special)

(class_body
  "{" @punctuation.bracket
  "}" @punctuation.bracket)

(class_separator) @punctuation.delimiter
(class_function) @function.method
(class_function "()" @punctuation.bracket)
(class_field) @variable.member
(class_field_other) @variable.member

(class_modifier) @keyword.modifier
(class_modifier
  "{" @punctuation.bracket
  "}" @punctuation.bracket)

(class_visibility) @keyword.operator

; ==================== OBJECT DEFINITIONS ====================
(object_keyword) @keyword.type
(object_name) @type

; ==================== ACTIVITY DIAGRAMS ====================
(activity_if) @keyword.conditional
(activity_else) @keyword.conditional
(activity_while) @keyword.repeat
(activity_endwhile) @keyword.repeat

(activity_if
  "(" @punctuation.bracket
  ")" @punctuation.bracket)
(activity_else
  "(" @punctuation.bracket
  ")" @punctuation.bracket)
(activity_while
  "(" @punctuation.bracket
  ")" @punctuation.bracket)
(activity_endwhile
  "(" @punctuation.bracket
  ")" @punctuation.bracket)

; ==================== SEQUENCE DIAGRAMS ====================
(sequence_divider) @punctuation.special
(sequence_ref_inline) @keyword
(sequence_ref_block) @keyword
(sequence_delay) @punctuation.special
(sequence_space) @punctuation.special

; ==================== STATE DIAGRAMS ====================
(state_concurrent) @punctuation.special

; ==================== KEYWORDS ====================
(keyword) @keyword

; ==================== STYLE / SKINPARAM ====================
(skinparam_keyword) @keyword.directive
(skinparam_name) @property
(skinparam_value) @string
(style_block
  "{" @punctuation.bracket
  "}" @punctuation.bracket)

; ==================== TITLES / CAPTION / SCALE ====================
(title_inline) @markup.heading
(title_multiline) @markup.heading
(caption) @markup.heading
(scale) @keyword

; ==================== NOTES ====================
(note_inline) @comment.note
(note_multiline) @comment.note
(note_of_inline) @comment.note
(note_of_multiline) @comment.note
(note_as) @comment.note

; ==================== HEADERS / LEGENDS / FOOTERS ====================
(header_inline) @comment.note
(header_multiline) @comment.note

; ==================== PREPROCESSING ====================
(preprocessing) @keyword.directive

; ==================== COLORS ====================
(color) @constant

; ==================== LINKS / RELATIONS ====================
(link) @operator

(arrow) @operator
(relation_label) @label
(relation_label ":" @punctuation.delimiter)

; ==================== IDENTIFIERS ====================
(identifier) @variable

; ==================== HIDE / SHOW / REMOVE ====================
(hide_show_remove) @keyword
