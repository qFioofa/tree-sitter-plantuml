; PlantUML Tree-sitter Injection Queries
; PlantUML embeds free text in several constructs. We mark the comment-like
; blocks for spell-checking; no full host-language injection is reliable here
; because note/header bodies are single regex tokens without sub-structure.

((comment_block) @injection.content
 (#set! injection.language "comment"))

((note_multiline) @injection.content
 (#set! injection.language "comment"))

((note_of_multiline) @injection.content
 (#set! injection.language "comment"))
