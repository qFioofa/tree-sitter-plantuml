module.exports = grammar({
	name: 'plantuml',

	extras: $ => [
		/\s/,
		$.comment,
	],

	word: $ => $.identifier,

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
			$.link
		),

		standalone_statement: $ => choice(
			$.title_statement,
			$.comment,
			$.string,
			$.identifier
		),

		class_declaration: $ => seq(
			optional('abstract'),
			'class',
			$.identifier,
			optional($.class_body)
		),

		class_body: $ => seq(
			'{',
			repeat($.class_member),
			'}'
		),

		class_member: $ => choice(
			$.field_declaration,
			$.method_declaration
		),

		field_declaration: $ => seq(
			optional($.visibility),
			$.identifier,
			':',
			$.type_name
		),

		method_declaration: $ => seq(
			optional($.visibility),
			$.identifier,
			'()',
			optional(seq(':', $.type_name))
		),

		type_name: $ => $.identifier,

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

		link: $ => seq($.identifier, $.arrow, $.identifier)
	}
});
