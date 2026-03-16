; PlantUML Tree-sitter Highlight Queries
; Comprehensive highlighting for all PlantUML grammar constructs

; ==================== COMMENTS ====================
(comment_line) @comment
(comment_block) @comment

; ==================== DIAGRAM BLOCKS ====================
(diagram_start) @keyword
(diagram_end) @keyword

; ==================== STRINGS ====================
(string) @string
(quoted_definition) @string

; ==================== CLASS DEFINITIONS ====================
(class_definition
  (class_keyword) @keyword)

(class_name) @type

(class_stereotype) @constant

(class_alias
  "as" @keyword)

(class_color) @constant

(class_body) @punctuation.bracket

(class_separator) @punctuation.delimiter

(class_function
  name: (_) @function)

(class_field
  name: (_) @variable)

(class_modifier) @keyword.modifier
  "static" @keyword.modifier
  "abstract" @keyword.modifier

(class_visibility) @keyword.operator
  "+" @keyword.operator
  "-" @keyword.operator
  "#" @keyword.operator
  "~" @keyword.operator

; ==================== OBJECT DEFINITIONS ====================
(object_keyword) @keyword

(object_name) @type

; ==================== ACTIVITY DIAGRAMS ====================
(activity_if
  "if" @keyword.conditional
  "else if" @keyword.conditional)

(activity_else
  "else" @keyword.conditional)

(activity_while
  "while" @keyword.repeat
  "repeat" @keyword.repeat)

(activity_endwhile
  "end" @keyword.conditional)

; ==================== SEQUENCE DIAGRAMS ====================
(sequence_divider) @punctuation.delimiter

(sequence_ref_inline
  "ref over" @keyword)

(sequence_ref_block
  "ref over" @keyword
  "end ref" @keyword)

(sequence_delay) @punctuation.special

(sequence_space) @punctuation.special

; ==================== STATE DIAGRAMS ====================
(state_concurrent) @punctuation.delimiter

; ==================== KEYWORDS ====================
(keyword) @keyword

; Activity flow keywords
(keyword) @keyword.conditional
  "if"
  "else"
  "switch"
  "case"
  "endif"
  "endswitch"

(keyword) @keyword.repeat
  "while"
  "repeat"
  "endwhile"
  "fork"
  "end fork"
  "split"
  "end split"

(keyword) @keyword.flow
  "start"
  "stop"
  "end"
  "detach"
  "goto"
  "backward"
  "diamond"

; Sequence keywords
(keyword) @keyword
  "activate"
  "deactivate"
  "return"
  "destroy"
  "autonumber"
  "newpage"
  "alt"
  "opt"
  "loop"
  "par"
  "break"
  "critical"
  "group"
  "box"
  "end box"
  "kill"
  "end merge"

; Direction keywords
(keyword) @keyword
  "top to bottom direction"
  "left to right direction"

; ==================== STYLE / SKINPARAM ====================
(style_inline) @keyword

(style_block) @keyword

; ==================== TITLES AND CAPTIONS ====================
(title_inline) @text.title
  "title" @keyword

(title_multiline) @text.title
  "title" @keyword
  "end title" @keyword

(caption) @text.note
  "caption" @keyword

; ==================== NOTES ====================
(note_inline) @text.note
  "note" @keyword

(note_multiline) @text.note
  "note" @keyword
  "end note" @keyword

(note_of_inline) @text.note
  "note" @keyword

(note_of_multiline) @text.note
  "note" @keyword
  "end note" @keyword

(note_as) @text.note
  "note" @keyword
  "as" @keyword

; ==================== HEADERS / LEGENDS / FOOTERS ====================
(header_inline) @text.note
  "header" @keyword
  "legend" @keyword
  "footer" @keyword

(header_multiline) @text.note
  "header" @keyword
  "legend" @keyword
  "footer" @keyword
  "end header" @keyword
  "end legend" @keyword
  "end footer" @keyword

; ==================== SCALE ====================
(scale) @keyword
  "scale" @keyword
  "max" @keyword
  "width" @keyword
  "height" @keyword

; ==================== PREPROCESSING ====================
(preprocessing) @preproc
  "!include" @preproc
  "!includesub" @preproc
  "!define" @preproc
  "!definelong" @preproc
  "!enddefinelong" @preproc
  "!ifdef" @preproc
  "!ifndef" @preproc
  "!else" @preproc
  "!endif" @preproc
  "!if" @preproc
  "!elseif" @preproc
  "!while" @preproc
  "!endwhile" @preproc
  "!startsub" @preproc
  "!endsub" @preproc
  "!procedure" @preproc
  "!function" @preproc
  "!end function" @preproc
  "!end procedure" @preproc
  "!return" @preproc
  "!import" @preproc
  "!includedef" @preproc
  "!includeurl" @preproc
  "!include_many" @preproc
  "!include_once" @preproc
  "!log" @preproc
  "!dump_memory" @preproc
  "!theme" @preproc
  "!pragma" @preproc
  "!assume transparent" @preproc

; ==================== COLORS ====================
(color) @constant

; ==================== LINKS ====================
(link) @keyword.operator

; ==================== IDENTIFIERS ====================
(identifier) @variable

; ==================== HIDE/SHOW/REMOVE ====================
(hide_show_remove) @keyword
  "hide" @keyword
  "show" @keyword
  "remove" @keyword
