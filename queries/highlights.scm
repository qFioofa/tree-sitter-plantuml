; Директивы
(start_directive) @keyword
(end_directive) @keyword

; Ключевые слова
[
  "class" 
  "abstract"
  "object"
  "actor"
  "participant"
  "note"
  "title"
] @keyword

; Позиции примечаний
(note_position) @type

; Комментарии
(comment) @comment

; Строки
(string) @string

; Имена
(class_declaration (identifier) @type)
(object_declaration (identifier) @variable)
(actor_declaration (identifier) @variable)
(participant_declaration (identifier) @variable)

; Члены класса
(field_declaration (identifier) @property)
(method_declaration (identifier) @method)
(type_name) @type

; Видимость
(visibility) @operator

; Стрелки
(arrow) @operator

; Разделители
(divider) @punctuation.delimiter

; Обычные идентификаторы
(identifier) @variable
