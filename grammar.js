module.exports = grammar({
	name : "plantuml",

	externals : ($) => [$._block_comment_start,
						$._block_comment_content,
						$._block_comment_end,
],

	extras : ($) => [/\s/],

	word : ($) => $.identifier,

	rules : {
		program : ($) => repeat(choice($.diagram, $._definition)),

		// ==================== DIAGRAM BLOCK ====================
		diagram : ($) => seq($.diagram_start, repeat($._diagram_content),
							 $.diagram_end),

		diagram_start : ($) => /@start[a-zA-Z]+[^\r\n]*/,
		diagram_end : ($) => /@end[a-zA-Z]+[^\r\n]*/,

		_diagram_content : ($) => choice(
							 $.class_definition,
							 $.object_definition,
							 $.style_inline,
							 $.style_block,
							 $.activity,
							 $.sequence,
							 $.state,
							 $.comment,
							 $.quoted_definition,
							 $.string,
							 $.keyword,
							 $._general_definition,
							 ),

		// ==================== OUTSIDE BLOCK ELEMENTS ====================
		_definition : ($) => choice(
						$.class_definition,
						$.object_definition,
						$.style_inline,
						$.style_block,
						$.activity,
						$.sequence,
						$.state,
						$.comment,
						$.quoted_definition,
						$.string,
						$.keyword,
						$._general_definition,
						),

		// ==================== QUOTED ====================
		quoted_definition : ($) => seq(":", optional(/[^:;|<>\r\n]*/), ":"),

		string : ($) => seq('"', optional(/[^"]*/), '"'),

		// ==================== COMMENT ====================
		comment : ($) => choice($.comment_line, $.comment_block),

		comment_line : ($) => seq("'", optional(/[^\r\n]*/)),

		comment_block : ($) => seq(
						  $._block_comment_start,
						  optional($._block_comment_content),
						  $._block_comment_end,
						  ),

		// ==================== STYLE ====================
		style_inline : ($) => /skinparam\s+\w+(<<[^>]+>>)?\s+[^\{\}\r\n]+/i,

		style_block : ($) => seq(/skinparam\s+\w+(<<[^>]+>>)?/i, "{",
								 repeat(/.*/), "}"),

		// ==================== CLASS ====================
		class_definition : ($) => seq(
							 choice(/enum/i, /abstract\s+class/i, /abstract/i,
									/class/i),
							 $.class_name,
							 optional($.class_stereotype),
							 optional($.class_alias),
							 optional($.class_color),
							 $.class_body,
							 ),

		class_name : ($) => choice(/\w[\w\d_.]*/, seq('"', /[^"]+/, '"')),

		class_stereotype : ($) => seq("<<", /[^>]+/, ">>"),

		class_alias : ($) => seq(/as/i,
								 choice(/\w[\w\d_.]*/, seq('"', /[^"]+/, '"'))),

		class_color : ($) => seq("#", /[\w|\\/-]+/),

		class_body : ($) => seq("{", repeat($.class_body_item), "}"),

		class_body_item : ($) => choice(
							$.class_separator,
							$.class_function,
							$.class_field,
							$.class_field_other,
							),

		class_separator : ($) => /[.=_-]{2,}/,

		class_function : ($) => seq(
						   optional($.class_modifier),
						   optional($.class_visibility),
						   choice(
							   seq(
								   optional(
									   seq(/\w[\w\d_]*(\[\])?/, /\w[\w\d_]*/)),
								   /\w[\w\d_]+/,
								   "()",
								   ),
							   seq(/\w[\w\d_]+/, "()", ":", /\w[\w\d_]*/),
							   ),
						   ),

		class_field : ($) => seq(
						optional($.class_modifier),
						optional($.class_visibility),
						choice(
							seq(optional(
									seq(/\w[\w\d_]*(\[\])?/, /\w[\w\d_]*/)),
								/\w[\w\d_]+/),
							seq(/\w[\w\d_]+/, ":", /\w[\w\d_]*/),
							),
						),

		class_field_other : ($) => seq(
							  optional($.class_modifier),
							  optional($.class_visibility),
							  /[^{}\r\n]+/,
							  ),

		class_modifier : ($) => seq("{", choice(/static/i, /abstract/i), "}"),

		class_visibility : ($) => /[~#+-]/,

		// ==================== OBJECT ====================
		object_definition : ($) => seq($.object_keyword, $.object_name,
									   optional(/[^\r\n]*/)),

		object_keyword : ($) => choice(
						   /object/i,
						   /participant/i,
						   /boundary/i,
						   /control/i,
						   /entity/i,
						   /database/i,
						   /component/i,
						   /interface/i,
						   /package/i,
						   /node/i,
						   /folder/i,
						   /frame/i,
						   /cloud/i,
						   /annotation/i,
						   /rectangle/i,
						   /namespace/i,
						   /partition/i,
						   /agent/i,
						   /artifact/i,
						   /card/i,
						   /circle/i,
						   /collections/i,
						   /file/i,
						   /hexagon/i,
						   /label/i,
						   /person/i,
						   /queue/i,
						   /stack/i,
						   /storage/i,
						   /mainframe/i,
						   /map/i,
						   /binary/i,
						   /clock/i,
						   /concise/i,
						   /robust/i,
						   /json/i,
						   /protocol/i,
						   /struct/i,
						   /exception/i,
						   /metaclass/i,
						   /stereotype/i,
						   ),

		object_name : ($) => choice(/\w[\w\d_]*/, seq('"', /[^"]+/, '"')),

		// ==================== ACTIVITY ====================
		activity : ($) => choice(
					 $.activity_if,
					 $.activity_else,
					 $.activity_while,
					 $.activity_endwhile,
					 ),

		activity_if : ($) => seq(
						choice(/if/i, /else\s+if/i),
						optional(seq("(", /[^)]+/, ")")),
						optional(/then/i),
						optional(seq("(", /[^)]+/, ")")),
						),

		activity_else : ($) => seq(/else/i, optional(seq("(", /[^)]+/, ")"))),

		activity_while : ($) => seq(
						   optional(/repeat\s+/i),
						   /while/i,
						   "(",
						   /[^)]+/,
						   ")",
						   optional(seq(/is/i, "(", /[^)]+/, ")")),
						   ),

		activity_endwhile : ($) => seq(/end/i, /while/i,
									   optional(seq("(", /[^)]+/, ")"))),

		// ==================== SEQUENCE ====================
		sequence : ($) => choice(
					 $.sequence_divider,
					 $.sequence_ref_inline,
					 $.sequence_ref_block,
					 $.sequence_delay,
					 $.sequence_space,
					 ),

		sequence_divider : ($) => seq(/=+/, optional(/[^=]+/), /=+/),

		sequence_ref_inline : ($) => seq(/ref\s+over/i, /\w[\w\d_]*/, ":",
										 /[^\r\n]+/),

		sequence_ref_block : ($) => seq(/ref\s+over/i, /\w[\w\d_]*/, /[^\r\n]*/,
										/end\s+ref/i),

		sequence_delay : ($) => seq(/\.{3,}/, optional(/[^\r\n]+/), /\.{3,}/),

		sequence_space : ($) => seq(/\|{2,}/, optional(/\d+/), /\|{1,}/),

		// ==================== STATE ====================
		state : ($) => $.state_concurrent,

		state_concurrent : ($) => /-+/,

		// ==================== KEYWORD ====================
		keyword : ($) => choice(
					// Activity keywords (not overlapping with activity rules)
					/end\s+fork/i,
					/end\s+split/i,
					/fork/i,
					/fork\s+again/i,
					/detach/i,
					/split/i,
					/split\s+again/i,
					/endif/i,
					/repeat/i,
					/endswitch/i,
					/switch/i,
					/case/i,
					/usecase/i,
					/actor/i,
					/autonumber/i,
					/autonumber\s+stop/i,
					/autonumber\s+resume/i,
					/autonumber\s+inc/i,
					/activate/i,
					/deactivate/i,
					/return/i,
					/destroy/i,
					/newpage/i,
					/alt/i,
					/opt/i,
					/loop/i,
					/par/i,
					/break/i,
					/critical/i,
					/group/i,
					/box/i,
					/end\s+box/i,
					/top\s+to\s+bottom\s+direction/i,
					/left\s+to\s+right\s+direction/i,
					/kill/i,
					/end\s+merge/i,
					/allow_mixing/i,
					/allow\s+mixing/i,
					/goto/i,
					/backward/i,
					/diamond/i,
					/compact\s+concise/i,
					/compact\s+robust/i,
					/state/i,
					// Object keywords (for standalone usage)
					/create/i,
					// General
					/as/i,
					seq("{", choice(/static/i, /abstract/i), "}"),
					),

		// ==================== GENERAL ====================
		_general_definition : ($) => choice(
								$.title_multiline,
								$.title_inline,
								$.scale,
								$.caption,
								$.note_inline,
								$.note_multiline,
								$.note_of_inline,
								$.note_of_multiline,
								$.note_as,
								$.header_multiline,
								$.header_inline,
								$.preprocessing,
								$.link,
								$.color,
								$.identifier,
								$.hide_show_remove,
								),

		// Title
		title_multiline : ($) => /title[^\r\n]*end\s+title/i,

		title_inline : ($) => /title[^\r\n]+/i,

		// Scale
		scale : ($) => /scale[^\r\n]+/i,

		// Caption
		caption : ($) => /caption[^\r\n]+/i,

		// Note
		note_inline : ($) => /note\s+(left|right):[^\r\n]+/i,

		note_multiline : ($) => /note\s+(left|right)[^\r\n]*end\s*note/i,

		note_of_inline : ($) =>
						   /[rh]?note\s+(right|left|top|bottom)?\s+(of|over|on\s+link)\s+(\w[\w\s]+|"[^"]+")(#\w+)?:[^\r\n]+/i,

		note_of_multiline : ($) =>
							  /[rh]?note\s+(right|left|top|bottom)?\s+(of|over|on\s+link)\s+(\w[\w\s]+|"[^"]+")(#\w+)?[^\r\n]*end\s*[rh]?note/i,

		note_as : ($) => /note\s+"[^"]+"\s+as\s+\w[\w\d]+/i,

		// Header, Legend, Footer
		header_multiline : ($) =>
							 /(center|left|right)?\s*(header|legend|footer)[^\r\n]*end\s?(header|legend|footer)/i,

		header_inline : ($) =>
						  /(center|left|right)?\s*(header|legend|footer)[^\r\n]+/i,

		// Preprocessing
		preprocessing : ($) => choice(
						  /!includesub/i,
						  /!include/i,
						  /!enddefinelong/i,
						  /!definelong/i,
						  /!define/i,
						  /!startsub/i,
						  /!endsub/i,
						  /!ifdef/i,
						  /!else/i,
						  /!endif/i,
						  /!ifndef/i,
						  /!if/i,
						  /!elseif/i,
						  /!while/i,
						  /!endwhile/i,
						  /!procedure/i,
						  /!function/i,
						  /!end\s+function/i,
						  /!end\s+procedure/i,
						  /!return/i,
						  /!import/i,
						  /!includedef/i,
						  /!includeurl/i,
						  /!include_many/i,
						  /!include_once/i,
						  /!log/i,
						  /!dump_memory/i,
						  /!theme/i,
						  /!pragma/i,
						  /!assume\s+transparent\s+(dark|light)/i,
						  ),

		// Link
		link : ($) => /[-.~=]+/,

		// Color
		color : ($) => /#(?:[0-9a-f]{6}|[0-9a-f]{3}|\w+)/i,

		// Identifier
		identifier : ($) => /[\w_]+/,

		// Hide/Show/Remove
		hide_show_remove : ($) => seq(choice(/hide/i, /show/i, /remove/i),
									  /[^\r\n]+/),
	},
});
