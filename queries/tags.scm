; Diagram definitions
(diagram_block (name) @definition.diagram)

; Function definitions (titles)
(title_single (content) @definition.function)
(title_multi_start (content) @definition.function)

; Type definitions (classes, enums)
(class_group_start (name) @definition.type)
(class_group_start (alias) @definition.type)

; Variable definitions (objects, class members)
(object_add_fields (identifier) @definition.variable)
(class_function (name) @definition.function)
(class_field (name) @definition.variable)
(note_as (variable) @definition.variable)

; References (actors, participants, etc.)
(general_element (actor) @reference)
(general_element (identifier) @reference)
(sequence_ref_inline (participants) @reference)
(sequence_ref_multiline_start (participants) @reference)
(note_of_inline (participants) @reference)
(note_of_multiline_start (participants) @reference)
