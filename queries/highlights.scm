; Main diagram elements
(diagram_block) @keyword
(diagram_block (keyword_control_diagram) @keyword)
(diagram_block (name) @function)

; Comments
(comment_line) @comment
(comment_block) @comment)

; Styles
(style_inline (keyword) @keyword)
(style_inline (keyword) @property)
(style_inline (stereotype) @type)
(style_inline (value) @string)

(style_block (keyword) @keyword)
(style_block (keyword) @property)
(style_block (stereotype) @type)

; Keywords
(keyword_linebegin) @keyword
(keyword_wholeline) @keyword
(keyword_other) @keyword

; Titles
(title_single (content) @function)
(title_multi_start (content) @function)
(title_single (keyword_control_title) @keyword)
(title_multi_start (keyword_control_title) @keyword)

; Scale
(scale (keyword_scale) @keyword)
(scale (number) @number)
(scale (second_number) @number)

; Caption
(caption (keyword_caption) @keyword)
(caption (content) @text)

; Notes
(note_inline (content) @comment)
(note_inline (keyword_note) @keyword)

(note_multiline_start (content) @comment)
(note_multiline_start (keyword_note) @keyword)

(note_of_inline (keyword_note) @keyword)
(note_of_inline (participants) @variable)
(note_of_inline (color) @number)
(note_of_inline (content) @comment)

(note_of_multiline_start (keyword_note) @keyword)
(note_of_multiline_start (participants) @variable)
(note_of_multiline_start (color) @number)
(note_of_multiline_start (content) @comment)

(note_as (keyword_note) @keyword)
(note_as (content) @comment)
(note_as (variable) @variable)

; Header, legend, footer
(header_legend_footer_single (position) @type)
(header_legend_footer_single (keyword_header_legend_footer) @keyword)
(header_legend_footer_single (content) @comment)

(header_legend_footer_multi_start (position) @type)
(header_legend_footer_multi_start (keyword_header_legend_footer) @keyword)
(header_legend_footer_multi_start (content) @comment)

; Preprocessing
(preprocessing) @function

; Links
(link) @operator
(link (color) @number)
(link (direction) @constant)

; Actors and messages
(general_element (actor) @variable)
(general_element (message) @comment)

; Colors
(general_element (color) @number)

; Variables
(general_element (identifier) @variable)

; Quotes
(quoted_string (content) @string)

; Conditions
(activity_if (condition) @string)
(activity_if (then_part) @comment)
(activity_if) @keyword

(activity_else (else_part) @comment)
(activity_else) @keyword

(activity_while (condition) @string)
(activity_while (is_part) @comment)
(activity_while) @keyword

(activity_endwhile (end_part) @comment)
(activity_endwhile) @keyword

; Sequence
(sequence_divider (content) @string)
(sequence_divider (divider) @operator)

(sequence_omission) @operator

(sequence_ref_inline (participants) @variable)
(sequence_ref_inline (content) @comment)
(sequence_ref_inline) @keyword

(sequence_ref_multiline_start (participants) @variable)
(sequence_ref_multiline_start (content) @comment)
(sequence_ref_multiline_start) @keyword

(sequence_delay (content) @comment)
(sequence_delay (delay) @operator)

(sequence_space (number) @number)
(sequence_space (space) @operator)

; States
(state_concurrent) @keyword

; Objects
(object_add_fields (identifier) @variable)

; Classes
(class_group_start (name) @variable)
(class_group_start (alias) @variable)
(class_group_start) @keyword

(class_separator (content) @string)
(class_separator) @comment

(class_function (return_type) @type)
(class_function (name) @variable)
(class_function (type) @type)
(class_function (modifier) @modifier)
(class_function (access) @keyword)

(class_field (type) @type)
(class_field (name) @variable)
(class_field (modifier) @modifier)
(class_field (access) @keyword)

(class_other (content) @string)
(class_other (modifier) @modifier)
(class_other (access) @keyword)

(class_hide_show (action) @keyword)
(class_hide_show (target) @variable)
(class_hide_show (detail) @type)
