module.exports = grammar({
	name: 'plantuml',

	extras: $ => [
		/\s/,
	],

	word: $ => $.identifier,

	rules: {
		program: $ => repeat($._definition),

		_definition: $ => choice(
			$.comment
		),

		// Comment
		comment: $ => choice(
			$.comment_line,
			$.comment_block,
		),

		// Line comment: starts with ' and continues until end of line
		comment_line: $ => seq(
			field("start", "'"),
			field("content", optional(/[^\r\n]*/))
		),

		// Block comment: starts with /' and ends with '/
		comment_block: $ => seq(
			field("start", "/'"),
			field("content", optional(/[\s\S]*?/)),
			field("end", "'/")
		),

		identifier: $ => /[a-zA-Z_][a-zA-Z0-9_]*/,
	}
});
