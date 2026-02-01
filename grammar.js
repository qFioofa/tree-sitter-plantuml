module.exports = grammar({
	name: 'plantuml',

	extras: $ => [
		/\s/,
		$.comment,
	],

	rules: {
		source_file: $ => repeat(choice(
			$.diagram_block,
			$.standalone_statement
		)),

		diagram_block: $ => seq(
			$.start_directive,
			optional($.diagram_name),
			repeat($._statement),
			$.end_directive
		),

		start_directive: $ => /@start\w+/i,
		end_directive: $ => /@end\w+/i,
		diagram_name: $ => /[^\s\n\r]+/,

		_statement: $ => choice(
			$.class_declaration,
			$.object_declaration,
			$.actor_declaration,
			$.participant_declaration,
			$.note_statement,
			$.title_statement,
			$.comment,
			$.string,
			$.identifier,
			$.arrow,
			$.divider
		),

		standalone_statement: $ => choice(
			$.title_statement,
			$.comment,
			$.string,
			$.identifier
		),

		// Класс
		class_declaration: $ => seq(
			optional($.abstract_keyword),
			'class',
			$.identifier,
			optional($.class_body)
		),

		abstract_keyword: $ => 'abstract',

		class_body: $ => seq(
			'{',
			repeat($.class_member),
			'}'
		),

		// Члены класса - исправлено!
		class_member: $ => choice(
			$.field_declaration,
			$.method_declaration
		),

		// Объявление поля: name : type
		field_declaration: $ => seq(
			optional($.visibility),
			$.identifier,
			':',
			$.type_name
		),

		// Объявление метода: name() : return_type
		method_declaration: $ => seq(
			optional($.visibility),
			$.identifier,
			'()',
			optional(seq(':', $.type_name))
		),

		// Тип (простой идентификатор или составной)
		type_name: $ => $.identifier,

		// Видимость
		visibility: $ => choice('+', '-', '#', '~'),

		object_declaration: $ => seq('object', $.identifier),
		actor_declaration: $ => seq('actor', $.identifier),
		participant_declaration: $ => seq('participant', $.identifier),

		note_statement: $ => choice(
			seq('note', $.string),
			seq('note', $.note_position, ':', $.string)
		),

		note_position: $ => choice('left', 'right', 'top', 'bottom'),

		title_statement: $ => seq('title', $.string),

		comment: $ => /'.*/,

		string: $ => seq('"', /[^"]*/, '"'),

		identifier: $ => /[a-zA-Z_][a-zA-Z0-9_]*/,

		arrow: $ => choice('->', '-->', '<-', '<--'),

		divider: $ => /={2,}/,
	}
});
