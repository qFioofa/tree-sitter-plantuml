; Generic envelopes
((generic_diagram
  (diagram_start) @_start
  body: (generic_body) @injection.content)
 (#match? @_start "^@startjson")
 (#set! injection.language "json"))

((generic_diagram
  (diagram_start) @_start
  body: (generic_body) @injection.content)
 (#match? @_start "^@startyaml")
 (#set! injection.language "yaml"))

((generic_diagram
  (diagram_start) @_start
  body: (generic_body) @injection.content)
 (#match? @_start "^@starthcl")
 (#set! injection.language "hcl"))

; Dedicated embedded diagrams
((json_diagram (json_content) @injection.content)
 (#set! injection.language "json"))

((yaml_diagram (yaml_content) @injection.content)
 (#set! injection.language "yaml"))

((hcl_diagram (hcl_content) @injection.content)
 (#set! injection.language "hcl"))

; CSS in style blocks
((style_content) @injection.content
 (#set! injection.language "css"))

; Plain-text bodies
((ditaa_diagram (ditaa_body) @injection.content)
 (#set! injection.language "text")
 (#set! injection.include-children))

((math_diagram body: (math_body) @injection.content)
 (#set! injection.language "text"))

((latex_diagram body: (latex_body) @injection.content)
 (#set! injection.language "latex"))

((dot_diagram body: (dot_body) @injection.content)
 (#set! injection.language "dot"))

((creole_diagram) @injection.content
 (#set! injection.language "markdown")
 (#set! injection.include-children))
