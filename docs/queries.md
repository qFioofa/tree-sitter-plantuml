# Queries

All standard query files live in `queries/` and are registered in
`tree-sitter.json`.

| File | Purpose |
|---|---|
| `highlights.scm` | Semantic highlighting for every structured node. |
| `injections.scm` | JSON, YAML, HCL, CSS, LaTeX, DOT, Markdown, and text bodies. |
| `folds.scm` | Diagrams, declarations, bodies, frames, notes, preprocessor blocks. |
| `indents.scm` | Begin/branch/end/auto/align for every block and clause. |
| `locals.scm` | Scopes, definitions, references for navigation. |
| `tags.scm` | Symbol tags for ctags/LSP. |
| `textobjects.scm` | `class`, `function`, `block`, `parameter`, `comment`, `statement`. |
| `context.scm` | Sticky context for `nvim-treesitter-context`. |
| `rainbow.scm` | Bracket pairs and nested scopes for rainbow delimiters. |

## Highlight captures

The grammar follows the Neovim/Helix capture naming convention:

- Comments: `@comment`, `@comment.documentation`, `@comment.note`.
- Keywords: `@keyword`, `@keyword.type`, `@keyword.function`,
  `@keyword.operator`, `@keyword.conditional`, `@keyword.repeat`,
  `@keyword.return`, `@keyword.import`, `@keyword.directive`,
  `@keyword.directive.define`, `@keyword.modifier`.
- Types: `@type`, `@type.definition`, `@module`, `@label`.
- Functions: `@function`, `@function.method`, `@function.macro`,
  `@function.builtin`.
- Variables: `@variable`, `@variable.parameter`, `@variable.member`,
  `@property`, `@constant`, `@constant.builtin`.
- Literals: `@string`, `@string.escape`, `@string.special`,
  `@string.special.url`, `@string.special.path`, `@string.special.symbol`,
  `@string.regexp`, `@number`, `@boolean`.
- Operators and punctuation: `@operator`, `@punctuation.bracket`,
  `@punctuation.delimiter`, `@punctuation.special`.
- Markup: `@markup`, `@markup.heading`, `@markup.list`, `@markup.raw`,
  `@markup.link`, `@markup.math`, `@markup.strong`, `@markup.italic`.
- Misc: `@attribute`, `@tag`, `@spell`, `@nospell`, `@error`.

The same concept uses the same capture across diagram families: a declaration
name is always `@type`, a relation endpoint is always `@type`, a label is
always `@string`, a color is always `@constant`, and a directive is always
`@keyword.directive`.

## Injections

Whole-body nodes are injected, never individual `raw_line` nodes:

- `json_content` → `json`
- `yaml_content` → `yaml`
- `hcl_content` → `hcl`
- `style_content` → `css`
- `ditaa_body` → `text`
- `math_diagram` body → `text`
- `latex_diagram` body → `latex`
- `dot_diagram` body → `dot`
- `creole_diagram` → `markdown`

## Testing queries

```bash
npx tree-sitter query queries/highlights.scm test/fixtures/class_features.puml
```

A query file must compile before it is merged. Corpus and fixture tests run in
`npm test`.
