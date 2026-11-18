# PLANS.md - Roadmap to Maximum PlantUML Coverage

> Living document. Created 2026-11-17.
>
> **Goal:** make `tree-sitter-plantuml` the most complete editor grammar for
> PlantUML: every documented `@start...` diagram, every common command, every
> text/preprocessor construct, and a full query set (`highlights`, `injections`,
> `folds`, `indents`, `locals`, `tags`, `textobjects`, `context`, `rainbow`).
>
> **Non-goal:** pixel-perfect rendering, layout, or full semantic validation.
> The parser must be lossless enough for editors: highlighting, folding,
> navigation, symbols, and code intelligence.
>
> **Source of truth:** <https://plantuml.com/> and the PlantUML source tree
> (`net.sourceforge.plantuml.*`, `DiagramType.java`, `CommonCommands.java`,
> command packages). When docs and source disagree, the source wins.
>
> **Definition of done for every feature:** grammar node + corpus test +
> fixture + query coverage + docs entry + no `ERROR`/`MISSING` on the fixture.

---

## 0. Legend

### Status

| Status | Meaning |
|---|---|
| `done` | Parsed structurally, tested, queries cover it. |
| `partial` | Parsed partly or only present in the current uncommitted rewrite. |
| `raw` | Falls back to `raw_line`/`raw_body`; no `ERROR`, but no structure. |
| `planned` | Not implemented. |
| `research` | Syntax not fully confirmed from docs/source yet. |
| `wontfix` | Deliberately out of scope (rendering-only, legacy internals). |

### Priority and size

| Tag | Meaning |
|---|---|
| `P0` | Blocks a usable release; correctness/regression risk. |
| `P1` | High value for daily editing and highlighting. |
| `P2` | Completeness for a diagram family. |
| `P3` | Niche / long tail. |
| `P4` | Research / optional. |

Size: `S` <= 1 day, `M` 2-4 days, `L` 1-2 weeks, `XL` > 2 weeks.

### Tag taxonomy

Use these exact tags in issues, commits, and backlog rows:

- Area: `area:grammar`, `area:scanner`, `area:query`, `area:test`, `area:docs`,
  `area:ci`, `area:bindings`, `area:perf`, `area:packaging`.
- Query: `query:highlights`, `query:injections`, `query:folds`,
  `query:indents`, `query:locals`, `query:tags`, `query:textobjects`,
  `query:context`, `query:rainbow`, `query:spell`.
- Diagram: `diagram:class`, `diagram:object`, `diagram:usecase`,
  `diagram:component`, `diagram:deployment`, `diagram:sequence`,
  `diagram:activity`, `diagram:state`, `diagram:timing`, `diagram:mindmap`,
  `diagram:wbs`, `diagram:gantt`, `diagram:chronology`, `diagram:json`,
  `diagram:yaml`, `diagram:hcl`, `diagram:nwdiag`, `diagram:salt`,
  `diagram:ditaa`, `diagram:archimate`, `diagram:requirement`, `diagram:er`,
  `diagram:git`, `diagram:files`, `diagram:chart`, `diagram:ebnf`,
  `diagram:regex`, `diagram:packet`, `diagram:board`, `diagram:wire`,
  `diagram:flow`, `diagram:bpm`, `diagram:math`, `diagram:creole`,
  `diagram:dot`, `diagram:sprites`, `diagram:composite`, `diagram:help`,
  `diagram:crash`, `diagram:definition`, `diagram:jcckit`, `diagram:sudoku`,
  `diagram:stdlib`.
- Cross-cutting: `common:envelope`, `common:commands`,
  `common:preprocessor`, `common:creole`, `common:style`,
  `common:skinparam`, `common:color`, `common:link`, `common:sprite`,
  `common:note`, `common:stereotype`, `common:macro`.

---

## 1. Current baseline (2026-11-17)

| Area | State | Notes |
|---|---|---|
| Envelope | `done` | `@startuml`/`@enduml`, named diagrams, multiple blocks, dedicated rules for every documented family, `generic_diagram` fallback for unknown `@startX`. |
| Class / object / component / deployment / use case | `partial` | Entity grammar, members, relations, packages, notes, object JSON shorthand, requirement/ArchiMate macro calls. |
| Sequence | `partial` | Participants, lifecycle, frames, notes, boxes, dividers, delays, refs, boundary messages. |
| Activity (beta) | `partial` | Actions, conditions, loops, fork/split, partition/group, swimlanes, notes. |
| Activity (legacy) | `raw` | No structured grammar. |
| State | `partial` | States, composite states, pseudostates, transitions, concurrent regions, entry/exit/do. |
| Timing | `done` | Players, clocks, scale, directives, time points, states, messages, constraints, highlights, notes. |
| Mindmap / WBS / Gantt | `partial` | Dedicated rules, nodes/separators/colors/no-box, Gantt statuses/groups/directives. |
| JSON / YAML / HCL | `done` | Dedicated envelopes, `#highlight` parsing, body injection. |
| nwdiag / salt / ditaa | `done` | Dedicated structured rules; ditaa text injection. |
| Chen ER / IE relations | `done` | Chen declarations/groups/cardinality and crow's-foot relation operators. |
| Git / files / chronology | `done` | Git commits/refs/graph, files tree, line-level chronology. |
| EBNF / regex | `done` | Structured expression grammars. |
| Packet / board / wire / flow / BPM | `done` | Structured or line-level rules. |
| Math / LaTeX / Creole / DOT / sprites / chart | `done` | Dedicated envelopes with body injection where applicable. |
| Queries | `done` | `highlights`, `injections`, `folds`, `indents`, `locals`, `tags`, `textobjects`, `context`, `rainbow` all registered and compile. |
| Tests | `done` | 68 corpus cases; all 19 fixtures wired into `npm test`; fixture smoke fails on `ERROR`/`MISSING`. |
| CI / packaging | `partial` | CI workflow added (generate check, lint, corpus, fixtures, query compile); no release/publish yet. |
| Performance | `risk` | Generated `src/parser.c` is ~78 MB / 30,598 states; state-heavy additions (e.g. relation tags) can push it past the 32k-state stability limit, so size/state budgets and benchmarks are still required. |

**Resolved blocker (2026-11-17):** parser regenerated, corpus and fixture smoke
tests wired into `npm test`, all fixtures parse with zero `ERROR`/`MISSING`.

---

## 2. Target architecture

### 2.1 Three-layer parsing

1. **Envelope layer** - `@start...`/`@end...`, diagram name, common commands,
   comments, preprocessor, multiple diagrams per file.
2. **Structured layer** - editor-relevant constructs per diagram family:
   declarations, bodies, relations, messages, branches, notes.
3. **Raw fallback layer** - `raw_line`, `raw_statement`, `raw_body` absorb
   anything not yet structured. Invariant: unknown input must not produce
   `ERROR` or `MISSING`.

New syntax is first accepted by the raw layer, then promoted to structure in a
follow-up, with tests.

### 2.2 Node design conventions

- Suffixes: `*_diagram`, `*_declaration`, `*_body`, `*_statement`, `*_clause`,
  `*_block`, `*_operator`, `*_marker`, `*_text`, `*_label`, `*_name`, `raw_*`.
- Stable editor-facing fields: `name`, `alias`, `kind`, `body`, `label`,
  `text`, `target`, `left`, `right`, `operator`, `stereotype`, `color`, `link`,
  `tag`, `description`, `date`, `value`, `condition`, `marker`.
- `raw_*` nodes are never aliased to structured nodes.
- One generic node per concept where possible (`entity_declaration` + `kind`
  instead of dozens of near-duplicate declaration rules), unless queries need
  different shapes.
- Keep raw bodies lossless and newline-preserving so folds/indents work.

### 2.3 Diagram registration

Each diagram gets a dedicated rule when it has meaningful structure, metadata
in `tree-sitter.json`, a fixture under `test/fixtures/<diagram>/`, a corpus
file under `test/corpus/<diagram>.txt`, docs, and a README status row.
`generic_diagram` remains the safety net and injection host.

---

## 3. Query system plan - maximum capability

### 3.1 Query files

| File | Purpose | Status |
|---|---|---|
| `queries/highlights.scm` | Full semantic capture tree. | `partial` |
| `queries/injections.scm` | Embed JSON/YAML/HCL/CSS/LaTeX/other grammars. | `partial` |
| `queries/folds.scm` | Fold every block, body, diagram, note, comment block. | `partial`, unregistered |
| `queries/indents.scm` | Begin/branch/end/auto for every block and clause. | `partial`, unregistered |
| `queries/locals.scm` | Scopes, definitions, references for navigation. | `partial` |
| `queries/tags.scm` | Symbol tags for editors/ctags/LSP. | `partial` |
| `queries/textobjects.scm` | `class`, `function`, `block`, `parameter`, `comment`, `statement`. | `planned` |
| `queries/context.scm` | Sticky context for `nvim-treesitter-context`. | `planned` |
| `queries/rainbow.scm` | Rainbow delimiters for `nvim-ts-rainbow2`. | `planned` |
| `queries/spell.scm` | Explicit spell regions if captures are not enough. | `research` |

Register every standard query in `tree-sitter.json` and copy it in
`scripts/nvim_deploy.sh` (currently only four files are copied).

### 3.2 Highlight capture contract

Use Neovim/Helix-compatible capture names. Minimum contract:

| Group | Captures |
|---|---|
| Comments | `@comment`, `@comment.documentation`, `@comment.error`, `@comment.warning`, `@comment.todo`, `@comment.note` |
| Keywords | `@keyword`, `@keyword.function`, `@keyword.operator`, `@keyword.conditional`, `@keyword.repeat`, `@keyword.return`, `@keyword.exception`, `@keyword.import`, `@keyword.export`, `@keyword.directive`, `@keyword.directive.define`, `@keyword.type`, `@keyword.modifier` |
| Types | `@type`, `@type.builtin`, `@type.definition`, `@type.qualifier`, `@constructor`, `@namespace`, `@module` |
| Functions | `@function`, `@function.call`, `@function.method`, `@function.method.call`, `@function.builtin`, `@function.macro` |
| Variables | `@variable`, `@variable.parameter`, `@variable.member`, `@variable.builtin`, `@property`, `@field`, `@constant`, `@constant.builtin`, `@constant.macro`, `@label` |
| Literals | `@string`, `@string.escape`, `@string.special`, `@string.special.url`, `@string.special.symbol`, `@string.special.path`, `@string.regexp`, `@character`, `@number`, `@boolean` |
| Operators | `@operator`, `@punctuation.bracket`, `@punctuation.delimiter`, `@punctuation.special` |
| Markup | `@markup`, `@markup.strong`, `@markup.italic`, `@markup.strikethrough`, `@markup.underline`, `@markup.heading`, `@markup.heading.1..6`, `@markup.link`, `@markup.link.label`, `@markup.link.url`, `@markup.raw`, `@markup.raw.block`, `@markup.list`, `@markup.list.checked`, `@markup.list.unchecked`, `@markup.quote`, `@markup.math`, `@markup.environment` |
| Misc | `@tag`, `@tag.attribute`, `@tag.delimiter`, `@attribute`, `@annotation`, `@none`, `@conceal`, `@spell`, `@nospell`, `@diff.plus`, `@diff.minus`, `@diff.delta`, `@text.literal`, `@text.reference`, `@text.title`, `@text.uri`, `@text.todo`, `@text.note`, `@text.warning`, `@text.danger` |

Rules:

- Prefer named nodes over string literals; alias one literal per keyword and
  reuse it.
- Set `#set! priority N` only for overlapping captures (e.g. `identifier` as a
  class name vs a relation endpoint).
- Add `@spell` to comments, notes, titles, headers, footers, legends, raw text,
  and diagram names; add `@nospell` to identifiers, URLs, paths, hashes, dates,
  numbers, and color literals.
- Add `(ERROR) @error` only after the raw fallback invariant is verified.
- Keep captures stable across diagrams: the same concept uses the same capture
  everywhere.

### 3.3 Injections contract

| Host | Injected language | Trigger | Priority |
|---|---|---|---|
| `@startjson`/`@endjson` body | `json` | diagram start match | P1 |
| `@startyaml`/`@endyaml` body | `yaml` | diagram start match | P1 |
| `@starthcl`/`@endhcl` body | `hcl` | diagram start match | P2 |
| `style_block` | `css` | `<style>` | P1 |
| `@startditaa` body | `text` (spell off) | diagram start match | P1 |
| `@startdot` body | `dot`/`graphviz` if available | diagram start match | P3 |
| `@startlatex`/`@startmath` | `latex` if available | diagram start match | P3 |
| `@startcreole` | markdown-like | diagram start match | P3 |
| `@startebnf`/`@startregex` | own grammar once implemented | diagram start match | P3 |
| `salt` body | `salt` once implemented | diagram start match | P2 |

Do not inject into arbitrary `raw_line`; inject only whole-body nodes to keep
ranges stable and avoid injection recursion.

### 3.4 Folds contract

Fold every construct with a body or multi-line payload:

- Top level: `uml_diagram`, `generic_diagram`, every `*_diagram`.
- Declarations: `class_declaration`, `enum_declaration`, `entity_declaration`,
  `state_declaration`, `package_block`, `namespace_block`, `together_block`,
  `component_shorthand`, `requirement_declaration`, `archimate_element`,
  `er_entity`, `chen_entity`, `nwdiag_network`, `git_commit`, `files_entry`.
- Bodies: `entity_body`, `enum_body`, `state_body`, `requirement_body`,
  `json_body`, `yaml_body`, `hcl_body`, `style_block`.
- Sequence: `sequence_frame`, `sequence_else_clause`, `box_block`, `reference`,
  `note_statement`, `mainframe_statement`.
- Activity: `if_block`, `elseif_clause`, `while_block`, `repeat_block`,
  `switch_block`, `case_clause`, `fork_block`, `split_block`,
  `partition_block`, `activity_group_block`, `activity_container_block`.
- State: composite state body, concurrent regions.
- Mindmap/WBS: every multi-line node (`mindmap_node`, `wbs_node`).
- Gantt: task groups, project block.
- Preprocessor: `!if`, `!ifdef`, `!ifndef`, `!while`, `!procedure`, `!function`,
  `!startsub`, `!definelong` blocks.
- Multi-line: `title_statement`, `caption_statement`, `header_statement`,
  `footer_statement`, `legend_block`, `skinparam_statement` block,
  `style_block`, `note_statement`, `reference`.
- Embedded: JSON/YAML/HCL/dot/CSS bodies (the nested language folds too).

### 3.5 Indents contract

- `@indent.begin`: every body/block listed in 3.4 and `{ ... }` containers.
- `@indent.branch`: `}`, `end`, `endif`, `endwhile`, `endswitch`, `end box`,
  `end note`, `end ref`, `end title`, `end header`, `end footer`, `endlegend`,
  `endfork`, `endsplit`, `endmerge`, `else`, `elseif`, `case`,
  `fork again`, `split again`, `repeat`.
- `@indent.end`: explicit closing delimiters that also close the scope.
- `@indent.auto`: `raw_line`, `comment_line`, `preprocessor`, `gantt_task`,
  `mindmap_node`, `wbs_node` when leaf lines.
- `@indent.align`: multi-line labels/notes/creole tables.
- `@indent.dedent`: case labels and `else` branches as needed.
- Round-trip test: format a fixture in Neovim with the indent query and assert
  stable output.

### 3.6 Locals contract

- `@local.scope`: every diagram, body, package, namespace, class, entity,
  state, requirement, sequence frame, activity block, preprocessor block.
- `@local.definition`: class/interface/enum/annotation/struct/exception/
  metaclass/record/dataclass/entity/object/participant/actor/usecase/component/
  node/artifact/folder/frame/cloud/database/queue/storage/file/state/package/
  namespace/requirement/ER entity/network/element; members, methods,
  parameters, enum values, ports, aliases, labels, macros, variables.
- `@local.definition-value` for aliases and assigned values where useful.
- `@local.reference`: relation endpoints, boundary messages, member refs,
  sequence lifecycles/messages, notes targets, state transitions, activity
  connectors, links, macro calls, variable uses.
- `@local.scope-inherits` only where nested scopes should see parent symbols
  (package/class body); never leak across diagrams.

### 3.7 Tags contract

- Definitions: `@definition.class`, `@definition.interface`,
  `@definition.enum`, `@definition.type`, `@definition.module`,
  `@definition.method`, `@definition.function`, `@definition.field`,
  `@definition.constant`, `@definition.label`, `@definition.macro`,
  `@definition.namespace`, `@definition.parameter`, `@definition.commit`.
- References: `@reference.class`, `@reference.interface`,
  `@reference.type`, `@reference.module`, `@reference.method`,
  `@reference.function`, `@reference.field`, `@reference.constant`,
  `@reference.label`, `@reference.macro`, `@reference.call`,
  `@reference.commit`.
- Always pair with `@name` on the identifier.
- Add tags for diagram names, aliases, include paths, and commit hashes.

### 3.8 Textobjects / context / rainbow

- `textobjects.scm`:
  - `@class.outer`/`@class.inner` - class/entity/state/requirement bodies.
  - `@function.outer`/`@function.inner` - methods, macros, procedures.
  - `@block.outer`/`@block.inner` - every `*_block`, frame, note, legend.
  - `@parameter.outer`/`@parameter.inner` - parameter lists.
  - `@comment.outer`/`@comment.inner` - comment lines and block comments.
  - `@statement.outer` - one diagram statement.
- `context.scm`: `uml_diagram`, `package_block`, `namespace_block`,
  `class_declaration`, `entity_body`, `state_declaration`, `sequence_frame`,
  `if_block`, `activity_group_block`, `requirement_declaration`,
  `nwdiag_network`.
- `rainbow.scm`: `{`/`}`, `[`/`]`, `(`/`)`, `<<`/`>>`,
  `<style>`/`</style>` where nested.
- Query tests must compile all files with `vim.treesitter.query.parse` and run
  capture snapshots on every fixture.

### 3.9 Per-diagram query matrix

`Y` = required, `P` = partial/optional, `-` = not applicable, `I` = via
injection.

| Diagram family | highlights | injections | folds | indents | locals | tags | textobjects | context | rainbow |
|---|---|---|---|---|---|---|---|---|---|
| Envelope / common commands | Y | - | Y | Y | P | P | Y | Y | P |
| Class / object | Y | - | Y | Y | Y | Y | Y | Y | Y |
| Use case / component / deployment | Y | - | Y | Y | Y | Y | Y | Y | Y |
| Sequence | Y | - | Y | Y | Y | Y | Y | Y | Y |
| Activity (beta) | Y | - | Y | Y | Y | Y | Y | Y | Y |
| State | Y | - | Y | Y | Y | Y | Y | Y | Y |
| Timing | Y | - | Y | Y | Y | Y | Y | P | P |
| Mindmap / WBS | Y | - | Y | Y | Y | Y | Y | Y | P |
| Gantt / chronology | Y | - | Y | Y | Y | Y | P | P | P |
| JSON / YAML / HCL | Y | Y (I) | Y | P | P | P | P | P | P |
| nwdiag / salt / ditaa | Y | P (ditaa text) | Y | Y | Y | Y | Y | Y | P |
| ArchiMate / requirement / ER | Y | - | Y | Y | Y | Y | Y | Y | Y |
| Git / files | Y | - | Y | Y | Y | Y | Y | P | P |
| Chart / EBNF / regex | Y | - | Y | Y | Y | Y | Y | P | P |
| Preprocessor | Y | - | Y | Y | Y | Y | Y | Y | - |
| Creole / text | Y | P (math/latex) | Y | P | - | - | P | P | P |
| Stdlib / macros | Y | - | P | - | Y | Y | P | P | - |

**Query release gate:** every `Y` cell must have a test; every `P` cell must
have a documented reason.

---

## 4. Feature inventory by diagram

The tables below are the working backlog. Each row is a feature. Add a new row
before implementing; close it only when grammar + test + query + docs are done.

**Backlog size:** 562 feature rows across 56 groups (UML, non-UML, common
commands, preprocessor, text/creole, queries, CI, packaging, docs). This is the
maximum-capability inventory; priority and status decide the order.

**Tag inheritance:** every row implicitly gets `area:grammar`, `area:test`, and
`area:docs`. Its section adds the matching `diagram:*` tag. Its `Query` column
adds the specific `query:*` tag(s). Cross-cutting rows add `common:*`
(`common:preprocessor`, `common:creole`, `common:style`, `common:macro`, etc.).
Use the row ID plus these tags when creating issues or commits.

### 4.1 Common envelope and commands (all diagrams)

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| ENV-01 | Diagram start/end | `@startuml` ... `@enduml` | `uml_diagram` | highlights/folds | P0 | done |
| ENV-02 | Named diagram | `@startuml Name` | `diagram_name` | `@string.special` | P0 | done |
| ENV-03 | Multiple diagrams per file | repeated blocks | `source_file` | folds | P0 | done |
| ENV-04 | Generic start/end | `@startX` ... `@endX` | `generic_diagram` | highlights | P0 | done |
| ENV-05 | Auto-detect type under `@startuml` | content-based | `uml_diagram` alternatives | tags | P1 | partial |
| ENV-06 | Quoted/creole diagram names | quoted names | `diagram_name` | spell | P2 | partial |
| CMD-01 | Title single-line | `title ...` | `title_statement` | `@markup.heading` | P0 | done |
| CMD-02 | Title block | `title` ... `end title` | `title_statement` | folds/highlights | P1 | partial |
| CMD-03 | Caption single/block | `caption` ... `end caption` | `caption_statement` | `@markup.heading` | P1 | partial |
| CMD-04 | Header single/block | `header` ... `end header` | `header_statement` | `@comment.note` | P1 | partial |
| CMD-05 | Footer single/block | `footer` ... `end footer` | `footer_statement` | `@comment.note` | P1 | partial |
| CMD-06 | Legend left/right/center | `legend` ... `endlegend` | `legend_block` | folds/highlights | P1 | partial |
| CMD-07 | Mainframe | `mainframe ...` | `mainframe_statement` | highlights | P2 | partial |
| CMD-08 | Scale all forms | `scale 1.5`, `scale 200 width`, `scale max 300*200` | `scale_statement` | highlights | P1 | partial |
| CMD-09 | Page / newpage | `page`, `newpage`, `newpage #color` | `page_statement`, `newpage_statement` | highlights | P1 | partial |
| CMD-10 | Rotate | `rotate`, `rotate 90` | `rotate_statement` | highlights | P3 | planned |
| CMD-11 | Minwidth | `minwidth`, skinparam minClassWidth | `minwidth_statement` | highlights | P3 | planned |
| CMD-12 | Direction | `left to right direction`, `top to bottom direction` | `direction_statement` | `@keyword.directive` | P1 | partial |
| CMD-13 | Allow mixing | `allowmixing`, `allow_mixing` | `allow_mixing_statement` | `@keyword.directive` | P2 | partial |
| CMD-14 | Namespace separator | `set namespaceSeparator ::` | `namespace_separator` | `@keyword.directive` | P2 | planned |
| CMD-15 | Hide/show/remove/restore | `hide empty members`, `show ...`, `remove @unlinked`, `restore ...` | `display_directive` | `@keyword.directive` | P1 | partial |
| CMD-16 | Hide by visibility/gender | `hide private`, `hide methods`, `hide class` | `display_directive` | highlights | P2 | planned |
| CMD-17 | Skinparam single-line | `skinparam name value` | `skinparam_statement` | `@property` | P1 | partial |
| CMD-18 | Skinparam block | `skinparam { ... }` | `skinparam_statement` | folds | P1 | partial |
| CMD-19 | Skinparam style/theme | `skinparam style strictuml`, `!theme` | `skinparam_statement`, `preprocessor` | highlights | P1 | partial |
| CMD-20 | Style block CSS | `<style> ... </style>` | `style_block` + CSS injection | injection/folds | P0 | partial |
| CMD-21 | Style import | `!include <style/...>` | preprocessor | tags | P2 | planned |
| CMD-22 | Pragma | `!pragma ...`, `pragma ...` | `preprocessor`/`pragma_statement` | `@keyword.directive` | P2 | partial |
| CMD-23 | Assume transparent | `!assume transparent` | `preprocessor` | highlights | P3 | planned |
| CMD-24 | URL/link on element | `[[url]]`, `[[url label]]`, `[[url{tooltip} label]]` | `hyperlink` | `@string.special.url` | P1 | partial |
| CMD-25 | URL on relation | `A --> B [[url]]` | relation link field | `@string.special.url` | P2 | partial |
| CMD-26 | Link anchor | `anchor`, `link anchor` | `link_anchor` | `@label` | P3 | planned |
| CMD-27 | Sprites | `sprite $name ...`, `<$name>` | `sprite_declaration`, `sprite_use` | tags/highlights | P2 | planned |
| CMD-28 | OpenIconic | `<&icon>` | creole inline | `@string.special.symbol` | P2 | partial |
| CMD-29 | Unicode | `<U+221E>` | creole inline | `@string.special` | P2 | partial |
| CMD-30 | Emoji | `<:smile:>`, `<#red:smile:>` | creole inline | `@string.special` | P2 | partial |
| CMD-31 | Image | `<img:url>`, `<img:url{scale}>` | creole inline | `@markup.link.url` | P2 | partial |
| CMD-32 | Math/LaTeX inline | `<math>`, `<latex>` | creole inline + injection | injection | P3 | planned |
| CMD-33 | QR code | `<qrcode>` | creole inline | `@string.special` | P4 | research |
| CMD-34 | Comments line | `' ...` | `comment_line` | `@comment`/`@spell` | P0 | done |
| CMD-35 | Comments block | `/' ... '/` | `block_comment` | `@comment`/`@spell` | P0 | done |

**Acceptance:** every command has a corpus case and a fixture; `hide/show`
variants are data-driven, not copy-pasted rules.

---

### 4.2 Class diagram

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| CLS-01 | Class/abstract class | `class X`, `abstract class X`, `abstract X` | `class_declaration` | `@type.definition` | P0 | done |
| CLS-02 | Interface/annotation/protocol/struct/exception/metaclass | keywords | `class_declaration.kind` | `@keyword.type`/`@type` | P0 | done |
| CLS-03 | Record/dataclass | `record`, `dataclass` | `entity_declaration.kind` | `@type` | P1 | partial |
| CLS-04 | Enum | `enum X { ... }`, inline enum | `enum_declaration`, `enum_body` | `@type`/`@constant` | P0 | done |
| CLS-05 | Name/alias | `class "Long" as A`, `class X as Y` | `name`/`alias` fields | `@type` | P0 | done |
| CLS-06 | Generics | `class X<T>` | `generics` | `@type` | P1 | partial |
| CLS-07 | Stereotype/spot | `<<stereotype>>`, `<<(S,#color)>>` | `stereotype` | `@attribute` | P0 | partial |
| CLS-08 | Color/gradient | `#red`, `#red\|blue`, `#AABBCC` | `color` | `@constant` | P0 | partial |
| CLS-09 | Tag | `$tag` | `tag` | `@attribute` | P1 | partial |
| CLS-10 | Hyperlink | `[[url]]` | `hyperlink` | `@string.special.url` | P1 | partial |
| CLS-11 | Order | `order 10` | `order` field | `@number` | P2 | partial |
| CLS-12 | Extends/implements | `extends A`, `implements B` | fields | `@keyword.operator` | P1 | partial |
| CLS-13 | Fields | `+field : int`, `-field`, `#field`, `~field` | `attribute` | `@variable.member` | P0 | done |
| CLS-14 | Methods | `+m(a, b) : void`, `+void m()` | `method`, `parameter_list` | `@function.method` | P0 | done |
| CLS-15 | C++ style types | `+std::string qualified(int)` | `_cpp_type_name` | `@type` | P1 | partial |
| CLS-16 | Modifiers | `{static}`, `{abstract}`, `{classifier}`, `{field}`, `{method}` | `modifier` | `@keyword.modifier` | P1 | partial |
| CLS-17 | Visibility | `+`, `-`, `#`, `~` | `visibility` | `@keyword.modifier` | P0 | done |
| CLS-18 | Separators | `--`, `..`, `==`, `__`, and titled variants | `member_separator` | `@punctuation.special` | P1 | partial |
| CLS-19 | Body-less declaration | `class X` | `_eos` | `@type` | P0 | done |
| CLS-20 | One-line description | `class X : text` | `description` field | `@string` | P1 | done |
| CLS-21 | Allman body | `class X` newline `{ ... }` | newline body | - | P1 | done |
| CLS-22 | Class shorthand | `class $tag` | identifier | `@type` | P2 | partial |
| CLS-23 | Visibility before class | `-class X`, `+class X` | visibility | `@keyword.modifier` | P2 | done |
| CLS-24 | Diamond/circle shorthand | `<> X`, `() X` | `diamond_shorthand`, `circle_shorthand` | `@type` | P1 | done |
| CLS-25 | Relations all arrows | `<\|--`, `*--`, `o--`, `--`, `..`, `-->`, `..>`, `..\|>`, `<--*`, `#--`, `x--`, `}--`, `+--`, `^--` | `relation_operator` | `@operator` | P0 | partial |
| CLS-26 | Dotted/inheritance variants | `<\|..`, `--\|>` | `relation_operator` | `@operator` | P0 | partial |
| CLS-27 | Relation labels | `A --> B : label` | `label` | `@string` | P0 | done |
| CLS-28 | Cardinalities | `"1" --> "many"` | `cardinality` | `@string.special` | P1 | partial |
| CLS-29 | Roles | `A "1" *-- "many" B : contains` | `role` | `@string` | P1 | partial |
| CLS-30 | Qualifiers | `A [q] --> B` | `qualifier` | `@string.special` | P2 | partial |
| CLS-31 | Member refs | `A::field --> B` | `member_ref` | `@type` | P2 | partial |
| CLS-32 | Association class | `(A, B) .. C` | `association_relation` | `@operator` | P2 | partial |
| CLS-33 | Lollipop | `A ()-- B` | circle/relation | `@operator` | P2 | planned |
| CLS-34 | Hidden relation | `-[hidden]->` | `relation_operator` | `@operator` | P2 | partial |
| CLS-35 | Direction hints | `-up->`, `-left->`, `-right->`, `-down->` | `relation_operator` | `@operator` | P2 | planned |
| CLS-36 | Relation color/link | `-[#red]->`, `[[url]]` | fields | `@constant`/`@string.special.url` | P2 | partial |
| CLS-37 | Packages | `package "p" as P #EEE { ... }` | `package_block` | `@module` | P0 | done |
| CLS-38 | Namespaces | `namespace ns { ... }` | `namespace_block` | `@module` | P0 | done |
| CLS-39 | Together | `together { ... }` | `together_block` | `@module` | P1 | done |
| CLS-40 | Nested packages/namespaces | recursive bodies | same | folds | P0 | done |
| CLS-41 | Notes on class/member/link | `note left of X`, `note "..." as N`, `note on link` | `note_statement` | `@comment` | P0 | partial |
| CLS-42 | Floating notes | `floating note left : text` | `note_statement` | `@comment` | P1 | partial |
| CLS-43 | Notes with stereotype/color | `note ... #color` | fields | `@constant` | P1 | partial |
| CLS-44 | Hide/show class members | `hide empty members`, `hide methods` | `display_directive` | `@keyword.directive` | P1 | partial |
| CLS-45 | Remove/restore class | `remove X`, `restore X` | `display_directive` | `@keyword.directive` | P2 | partial |
| CLS-46 | `@unlinked` | `remove @unlinked` | display target | `@label` | P2 | partial |
| CLS-47 | Class layout | direction, `together` | direction/together | `@keyword.directive` | P1 | partial |
| CLS-48 | `namespaceSeparator` | `set namespaceSeparator ::` | common | `@keyword.directive` | P2 | planned |

**Acceptance:** `class_features.puml` and `elements.puml` parse with zero
`ERROR`; every row has a corpus case.

---

### 4.3 Object diagram

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| OBJ-01 | Object | `object X` | `entity_declaration.kind=object` | `@type` | P0 | done |
| OBJ-02 | Object alias/name | `object "Long" as O` | fields | `@type` | P0 | done |
| OBJ-03 | Object fields | `object O { name : "v" }` | `entity_body`/`attribute` | `@variable.member` | P0 | partial |
| OBJ-04 | Object map shorthand | `object O : field = value` | `colon_member` | `@variable.member` | P1 | partial |
| OBJ-05 | Object JSON shorthand | `object O { "k": v }` | map body | `@property` | P2 | planned |
| OBJ-06 | Object relations | all class relations | `relation` | `@operator` | P0 | done |
| OBJ-07 | Object notes | class notes | `note_statement` | `@comment` | P1 | partial |
| OBJ-08 | Object color/stereotype/link | class suffixes | same | same | P1 | partial |

---

### 4.4 Use case diagram

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| UC-01 | Use case | `usecase X`, `(X)` | `entity_declaration`/`usecase_ref` | `@type` | P0 | partial |
| UC-02 | Actor | `actor X`, `:actor:` | `entity_declaration`/`actor_ref` | `@type` | P0 | partial |
| UC-03 | Actor alias/name | `actor "Long" as A` | fields | `@type` | P0 | partial |
| UC-04 | Use case alias/name | `usecase "Long" as U` | fields | `@type` | P0 | partial |
| UC-05 | System boundary | rectangle/package with actors/usecases | entity containers | `@module` | P1 | partial |
| UC-06 | Links | `Actor --> (UC)` | relation/boundary | `@operator` | P0 | partial |
| UC-07 | Extend/include labels | `<<extend>>`, `<<include>>` | stereotype/label | `@attribute` | P1 | partial |
| UC-08 | Generalization | `A <\|-- B` | relation | `@operator` | P1 | partial |
| UC-09 | Use case descriptions | `usecase X : text` | description | `@string` | P2 | partial |
| UC-10 | Notes | same as class | `note_statement` | `@comment` | P1 | partial |
| UC-11 | Business actor/use case | `actor/`, `usecase/` variants | entity kind suffix | `@type` | P2 | research |

---

### 4.5 Component / deployment / description diagrams

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| CMP-01 | Component | `component X`, `[X]`, `component [X] as C` | `entity_declaration`/`component_shorthand` | `@type` | P0 | partial |
| CMP-02 | Component long name/alias | `component "Long" as C` | fields | `@type` | P0 | partial |
| CMP-03 | Node | `node X` | entity kind | `@type` | P0 | partial |
| CMP-04 | Artifact | `artifact X` | entity kind | `@type` | P0 | partial |
| CMP-05 | Folder/frame/cloud/database/queue/stack/storage/file | each keyword | entity kinds | `@type` | P0 | partial |
| CMP-06 | Rectangle/card/agent/boundary/control/collections/entity | each keyword | entity kinds | `@type` | P0 | partial |
| CMP-07 | Actor/usecase/participant in description | keywords | entity kinds | `@type` | P1 | partial |
| CMP-08 | Interfaces (lollipop) | `() Interface`, `interface X` | circle/class | `@type` | P1 | partial |
| CMP-09 | Ports | `port p`, `portin p`, `portout p` | `port_member` | `@property` | P1 | partial |
| CMP-10 | Port color | `port p #red` | color field | `@constant` | P2 | partial |
| CMP-11 | Nested components | `component X { ... }` | entity body | folds | P0 | partial |
| CMP-12 | Packages/frames/folders as containers | `package X <<frame>> { ... }` | package block | `@module` | P0 | partial |
| CMP-13 | Stereotypes/color/tags/links/order | common suffixes | fields | same | P1 | partial |
| CMP-14 | Relations | all class arrows | relation | `@operator` | P0 | partial |
| CMP-15 | Notes | class notes | `note_statement` | `@comment` | P1 | partial |
| CMP-16 | Deployment-specific nodes | `node`, `artifact`, `database`, `cloud`, `storage` | entity kinds | `@type` | P1 | partial |
| CMP-17 | `allowmixing` | mixing class/component/state | common | `@keyword.directive` | P2 | partial |
| CMP-18 | Bracket refs in relations | `[A] --> [B]` | `component_ref` | `@type` | P1 | partial |
| CMP-19 | Delete/unlinked | `remove @unlinked` | display | `@label` | P2 | partial |

---

### 4.6 Sequence diagram

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| SEQ-01 | Participant kinds | `participant`, `actor`, `boundary`, `control`, `entity`, `database`, `collections`, `queue` | entity kinds | `@type` | P0 | done |
| SEQ-02 | Participant name/alias | `participant "Long" as P` | fields | `@type` | P0 | done |
| SEQ-03 | Participant stereotype/color/order/link | suffixes | fields | `@attribute`/`@constant` | P1 | partial |
| SEQ-04 | Multi-line participant | `participant P [ ... ]` | bracket body | `@type` | P1 | partial |
| SEQ-05 | Create participant | `create participant P`, `create actor A`, `create database D` | `sequence_lifecycle` | `@keyword.control` | P0 | partial |
| SEQ-06 | Activate/deactivate/destroy | `activate P`, `deactivate P`, `destroy P` | `sequence_lifecycle` | `@keyword.control` | P0 | done |
| SEQ-07 | Activation shortcuts | `A -> B ++`, `--`, `**`, `!!` | relation activation | `@operator` | P1 | partial |
| SEQ-08 | Autoactivate | `autoactivate on/off` | `autoactivate_statement` | `@keyword.operator` | P1 | partial |
| SEQ-09 | Messages normal/dotted/thin | `->`, `-->`, `->>`, `-->>` | relation operator | `@operator` | P0 | done |
| SEQ-10 | Lost/found/circle messages | `->x`, `->o`, `o->`, `x->`, `<-`, `<--` | relation operator | `@operator` | P0 | partial |
| SEQ-11 | Self messages | `A -> A : text` | relation | `@operator` | P0 | done |
| SEQ-12 | External messages | `[-> A`, `A ->]`, `[o->`, `->o]`, `[?->`, `->?]` | `boundary_message` | `@operator` | P1 | partial |
| SEQ-13 | Message label creole/newlines | `: text` | `label` | `@string`/`@markup` | P0 | partial |
| SEQ-14 | Message color | `-[#red]>` | color field | `@constant` | P1 | partial |
| SEQ-15 | Auto number | `autonumber`, `10`, `10 10`, `stop`, `resume`, quoted format | `autonumber_statement` | `@keyword.directive` | P1 | partial |
| SEQ-16 | Return | `return`, `return text` | `return_statement` | `@keyword.return` | P0 | done |
| SEQ-17 | Grouping alt/else | `alt`, `else`, `end` | `sequence_frame`/`sequence_else_clause` | `@keyword.conditional` | P0 | done |
| SEQ-18 | Grouping opt/loop/par/break/critical/group | each keyword | `sequence_frame.kind` | `@keyword.conditional` | P0 | done |
| SEQ-19 | Group labels/secondary label | `alt label`, `group label [secondary]` | fields | `@string` | P1 | partial |
| SEQ-20 | Nested groups | recursive | same | folds | P0 | done |
| SEQ-21 | Notes left/right/top/bottom/over/across | `note left of P`, `note over P,Q`, `note across` | `note_statement` | `@comment` | P0 | partial |
| SEQ-22 | Notes on messages | `note on link`, `note right on link` | `note_statement` | `@comment` | P1 | partial |
| SEQ-23 | hnote/rnote | `hnote`, `rnote` | note kind | `@comment` | P1 | partial |
| SEQ-24 | Note as/multi-line | `note as N`, `end note` | `note_statement` | `@comment` | P0 | done |
| SEQ-25 | Note color | `note ... #color` | color field | `@constant` | P1 | partial |
| SEQ-26 | Divider | `== text ==` | `divider` | `@punctuation.special` | P1 | done |
| SEQ-27 | Delay | `...5 minutes...` | `delay` | `@comment` | P1 | done |
| SEQ-28 | Spacer | `\|\|\|`, `\|\|20\|\|` | `spacer` | `@punctuation.special` | P1 | done |
| SEQ-29 | Reference | `ref over A, B : text`, multi-line ref | `reference` | `@keyword.control` | P1 | partial |
| SEQ-30 | Box | `box "Name" #color`, `end box` | `box_block` | `@module` | P1 | partial |
| SEQ-31 | Mainframe | `mainframe text` | `mainframe_statement` | `@markup.raw` | P2 | partial |
| SEQ-32 | Hide footbox | `hide footbox` | display directive | `@keyword.directive` | P1 | partial |
| SEQ-33 | Hide unlinked | `hide unlinked` | display directive | `@keyword.directive` | P2 | partial |
| SEQ-34 | Newpage/auto newpage | `newpage`, `auto newpage` | sequence/newpage command | `@keyword.directive` | P3 | research |
| SEQ-35 | URL on participant/message | `[[url]]` | hyperlink | `@string.special.url` | P2 | partial |
| SEQ-36 | Link anchor | `anchor` | `link_anchor` | `@label` | P3 | planned |
| SEQ-37 | Sequence skinparams | `skinparam sequence ...` | skinparam | `@property` | P1 | partial |
| SEQ-38 | `teoz` pragma | `!pragma teoz true` | preprocessor | `@keyword.directive` | P3 | partial |

---

### 4.7 Activity diagram (beta)

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| ACT-01 | Start/stop/end | `start`, `stop`, `end`, `kill`, `detach` | `activity_control` | `@keyword.control` | P0 | done |
| ACT-02 | Action | `:text;` | `activity_action` | `@string` | P0 | done |
| ACT-03 | Action color/style | `:text #red;`, `:text; <<stereotype>>` | fields | `@constant`/`@attribute` | P1 | partial |
| ACT-04 | Action creole | `:creole text;` | inline markup | `@markup` | P1 | partial |
| ACT-05 | Action multi-line | multi-line action text | action text | `@string` | P1 | partial |
| ACT-06 | Arrow | `->`, `-[#color]->`, `-[#color,dashed]->` | `activity_arrow` | `@operator` | P0 | partial |
| ACT-07 | Arrow label | `-> label`, staged arrow label | label field | `@string` | P0 | partial |
| ACT-08 | Connector | `(A)`, `(A) -> (B)` | `connector`/`activity_connector_arrow` | `@label` | P1 | partial |
| ACT-09 | Label/goto/backward | `label X`, `goto X`, `backward` | `activity_control` | `@keyword.control` | P1 | partial |
| ACT-10 | If/then/else/elseif/endif | `if (cond) then (yes)`, `elseif`, `else`, `endif` | `if_block`/`elseif_clause`/`activity_else_clause` | `@keyword.conditional` | P0 | done |
| ACT-11 | If with is/equals | `if (x) is (y) then`, `equals` | `_branch_head` | `@keyword.conditional` | P1 | partial |
| ACT-12 | While/endwhile | `while (cond) is (yes)` | `while_block` | `@keyword.repeat` | P0 | done |
| ACT-13 | Repeat/repeat while | `repeat`, `repeat while (cond) is (yes)` | `repeat_block` | `@keyword.repeat` | P0 | done |
| ACT-14 | Switch/case/endswitch | `switch (x)`, `case (a)`, `endswitch` | `switch_block`/`case_clause` | `@keyword.conditional` | P0 | done |
| ACT-15 | Fork/fork again/end fork | `fork`, `fork again`, `end fork` | `fork_block`/`fork_again` | `@keyword.conditional` | P0 | done |
| ACT-16 | Split/split again/end split | `split`, `split again`, `end split` | `split_block`/`split_again` | `@keyword.conditional` | P0 | done |
| ACT-17 | Partition | `partition Name { ... }` | `partition_block` | `@module` | P0 | done |
| ACT-18 | Group | `group Name { ... }` | `activity_group_block` | `@module` | P0 | done |
| ACT-19 | Package/rectangle/card containers | each keyword | `activity_container_block` | `@module` | P1 | done |
| ACT-20 | Swimlane | `\|Lane\|`, `\|#color\|Lane\|` | `swimlane` | `@module` | P0 | done |
| ACT-21 | Swimlane alias | `\|#color\|alias\| Title` | swimlane fields | `@module` | P1 | partial |
| ACT-22 | Notes | `note right : text`, `floating note left : text` | `note_statement` | `@comment` | P0 | partial |
| ACT-23 | Note body/multi-line | `note right ... end note` | `note_statement` | `@comment` | P1 | partial |
| ACT-24 | Note on group/partition | `floating note: ...` | `note_statement` | `@comment` | P1 | partial |
| ACT-25 | Legend | `legend ... endlegend` | `legend_block` | `@comment.note` | P1 | partial |
| ACT-26 | Stereotype on action | `:a; <<procedure>>` | `stereotype` | `@attribute` | P1 | partial |
| ACT-27 | Action box style | `:a; #red`, box color | color field | `@constant` | P1 | partial |
| ACT-28 | Break in loop | `break` | activity control | `@keyword.control` | P2 | planned |
| ACT-29 | Merge/end merge | `merge`, `end merge` | new block | `@keyword.conditional` | P2 | planned |
| ACT-30 | Detach/kill | `detach`, `kill` | activity control | `@keyword.control` | P1 | done |
| ACT-31 | Stop inside branch | `stop` | activity control | `@keyword.control` | P1 | done |
| ACT-32 | Activity notes on links | `note on link` | note | `@comment` | P3 | research |
| ACT-33 | Activity skinparam/theme | common | skinparam | `@property` | P1 | partial |

### 4.8 Activity diagram (legacy)

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| ACTL-01 | Legacy start/end | `(*)`, `(*) -->`, `--> (*)` | legacy activity | `@keyword.control` | P3 | raw |
| ACTL-02 | Legacy action | `--> "text"` | legacy action | `@string` | P3 | raw |
| ACTL-03 | Legacy if/endif/else | `if`, `endif`, `else` | legacy blocks | `@keyword.conditional` | P3 | raw |
| ACTL-04 | Legacy partition/groups | `partition`, `\|`, `end` | legacy containers | `@module` | P3 | raw |

**Decision:** keep legacy raw until beta is complete; do not block release on it.

---

### 4.9 State diagram

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| ST-01 | State | `state X` | `state_declaration` | `@type.definition` | P0 | done |
| ST-02 | State long name/alias | `state "Long" as S` | fields | `@type` | P0 | done |
| ST-03 | State description | `state X : text` | description | `@string` | P0 | done |
| ST-04 | Composite state | `state X { ... }` | `state_body` | folds | P0 | done |
| ST-05 | Pseudostates | `[*]`, `[H]`, `[H*]` | `pseudostate` | `@constant` | P0 | partial |
| ST-06 | Stereotype pseudostates | `<<choice>>`, `<<fork>>`, `<<join>>`, `<<end>>`, `<<start>>`, `<<entryPoint>>`, `<<exitPoint>>`, `<<inputPin>>`, `<<outputPin>>`, `<<expansionInput>>`, `<<expansionOutput>>` | stereotype | `@attribute` | P1 | partial |
| ST-07 | Concurrent regions | `--` | `state_concurrent` | `@punctuation.special` | P0 | done |
| ST-08 | Transitions | `A --> B`, `A -> B` | `relation` | `@operator` | P0 | done |
| ST-09 | Transition label/guard/action | `A --> B : event [guard] / action` | label fields | `@string` | P1 | partial |
| ST-10 | Entry/exit/do | `entry / action`, `exit / action`, `do / activity` | `state_body` members | `@keyword.function` | P1 | partial |
| ST-11 | State color/stereotype/link/tag | suffixes | fields | same | P1 | partial |
| ST-12 | State fields/methods | `state X { field; method() }` | body members | `@variable.member`/`@function.method` | P1 | partial |
| ST-13 | Notes | class notes | `note_statement` | `@comment` | P1 | partial |
| ST-14 | Hide empty description/members | `hide empty description`, `hide empty members` | display | `@keyword.directive` | P1 | partial |
| ST-15 | Remove/restore | `remove @unlinked`, `restore X` | display | `@keyword.directive` | P2 | partial |
| ST-16 | Direction | `left to right direction` | direction | `@keyword.directive` | P1 | partial |
| ST-17 | State description block | `state X { description }` | body | `@string` | P2 | partial |
| ST-18 | State without body | `state X` | `_eos` | `@type` | P0 | done |
| ST-19 | State alias with stereotype | `state "X" as Y <<s>> #c [[l]]` | fields | same | P1 | partial |

---

### 4.10 Timing diagram

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| TIM-01 | Envelope | `@starttiming` ... `@endtiming` | `timing_diagram` | highlights/folds | P0 | raw |
| TIM-02 | Robust/concise | `robust`, `concise`, `robust "X" as X` | `timing_player.kind` | `@keyword.type` | P0 | planned |
| TIM-03 | Clock | `clock "CLK" as C with period 100 offset 20 pulse 30` | `timing_clock` | `@type` | P0 | planned |
| TIM-04 | Compact clock | clock with `compact` | `timing_clock` | `@keyword.modifier` | P1 | planned |
| TIM-05 | Binary | `binary "B" as B` | `timing_player.kind` | `@keyword.type` | P0 | planned |
| TIM-06 | Analog | `analog "A" as A` | `timing_player.kind` | `@keyword.type` | P0 | planned |
| TIM-07 | Scale | `scale 1 as 10 pixels` | `timing_scale` | `@number` | P1 | planned |
| TIM-08 | Hide time axis | `hide time axis` | `timing_directive` | `@keyword.directive` | P1 | planned |
| TIM-09 | Date format | `use date format yyyy-mm-dd` | `timing_directive` | `@string` | P1 | planned |
| TIM-10 | Time points | `@0`, `@1.5`, `@100` | `timing_time` | `@number` | P0 | planned |
| TIM-11 | State at time | `A @1`, `A @1 is high`, `@1 A is high` | `timing_state` | `@constant` | P0 | planned |
| TIM-12 | Change state by time/player | `A is high at @10`, `A@10 is high` | `timing_change` | `@operator` | P1 | planned |
| TIM-13 | Time message | `A -> B : text` | `timing_message` | `@operator`/`@string` | P1 | planned |
| TIM-14 | Constraint | `constraint ...` | `timing_constraint` | `@string` | P2 | planned |
| TIM-15 | Note | `note ...` | `timing_note` | `@comment` | P1 | planned |
| TIM-16 | Highlight | `highlight ...` | `timing_highlight` | `@constant` | P2 | planned |
| TIM-17 | Ticks | `ticks ...` | `timing_ticks` | `@number` | P3 | planned |
| TIM-18 | Pixel height | `pixel height ...` | `timing_directive` | `@number` | P3 | planned |
| TIM-19 | Mode compact | `mode compact` | `timing_directive` | `@keyword.modifier` | P2 | planned |
| TIM-20 | Define state short/long | state declaration with label | `timing_state` | `@type` | P1 | planned |
| TIM-21 | Player code | player code syntax | `timing_player_code` | `@constant` | P3 | research |
| TIM-22 | Timing skinparam/theme | common | skinparam | `@property` | P2 | planned |

---

### 4.11 Mindmap

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| MM-01 | Envelope | `@startmindmap` ... `@endmindmap` | `mindmap_diagram` | folds | P0 | done |
| MM-02 | Root/child depth | `* root`, `** child`, `*** ...` | `mindmap_node.marker` | `@label` | P0 | done |
| MM-03 | Left/right branches | `+`, `++`, `-`, `--` | marker | `@label` | P0 | partial |
| MM-04 | No-box node | `*_ node`, `**_ node` | marker suffix | `@keyword.modifier` | P1 | planned |
| MM-05 | Color | `**[#red] node` | `outline_color` | `@constant` | P1 | done |
| MM-06 | Multi-line node | `**: text ;` | label | `@string` | P0 | done |
| MM-07 | Separator | `--`, `==`, `...` | `outline_separator` | `@punctuation.special` | P1 | done |
| MM-08 | Direction | `left to right direction` | direction | `@keyword.directive` | P1 | partial |
| MM-09 | Common commands | title/caption/header/footer | common | same | P1 | done |
| MM-10 | Legend | `legend` ... `endlegend` | legend | `@comment.note` | P1 | done |
| MM-11 | Skinparam/style | common | common | same | P1 | done |
| MM-12 | Creole in nodes | bold/italic/mono/strike/underline/lists/tables/images | inline markup | `@markup.*` | P1 | partial |
| MM-13 | HTML creole | `<b>`, `<color>`, `<img>` | inline markup | `@markup.*` | P2 | partial |
| MM-14 | Orgmode syntax | org-style markers | `CommandMindMapOrgmode` shape | `@label` | P3 | research |
| MM-15 | Links in nodes | `[[url]]` | hyperlink | `@string.special.url` | P2 | partial |

---

### 4.12 WBS

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| WBS-01 | Envelope | `@startwbs` ... `@endwbs` | `wbs_diagram` | folds | P0 | done |
| WBS-02 | Root/child depth | `*`, `**`, `***` | `wbs_node.marker` | `@label` | P0 | done |
| WBS-03 | `+`/`-` branches | `+`, `++`, `-`, `--` | marker | `@label` | P0 | partial |
| WBS-04 | No-box node | `*_` | marker suffix | `@keyword.modifier` | P1 | planned |
| WBS-05 | Color | `*[#red] node` | color | `@constant` | P1 | partial |
| WBS-06 | Multi-line node | `**: text ;` | label | `@string` | P0 | done |
| WBS-07 | Separator | `--`, `==`, `..` | separator | `@punctuation.special` | P1 | done |
| WBS-08 | Direction | `left to right direction` | direction | `@keyword.directive` | P1 | partial |
| WBS-09 | Creole/HTML creole in nodes | markup | inline | `@markup.*` | P1 | partial |
| WBS-10 | Common commands | title/caption/header/footer/legend/skinparam/style/preprocessor | common | same | P1 | done |
| WBS-11 | Links in nodes | `[[url]]` | hyperlink | `@string.special.url` | P2 | partial |

---

### 4.13 Gantt / project

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| GNT-01 | Envelope | `@startgantt`/`@startproject` ... end | `gantt_diagram` | folds | P0 | partial |
| GNT-02 | Project start/end | `Project starts 2024-01-01` | `gantt_project_statement` | `@string` | P0 | partial |
| GNT-03 | Task start date | `[T] starts 2024-01-01` | `gantt_task` | `@string` | P0 | done |
| GNT-04 | Task end date | `[T] ends 2024-01-15` | `gantt_task` | `@string` | P0 | partial |
| GNT-05 | Task duration | `[T] lasts 5 days` | `gantt_task` | `@string` | P0 | partial |
| GNT-06 | Relative start/end | `[T] starts at [U]'s end` | `gantt_task` | `@string` | P1 | partial |
| GNT-07 | Task arrow/dependency | `[T] -> [U]`, `[T] --> [U]` | `gantt_arrow` | `@operator` | P0 | partial |
| GNT-08 | Task color | `[T] is colored in LightBlue` | `gantt_task` | `@constant` | P1 | partial |
| GNT-09 | Completion | `[T] is 50% completed` | `gantt_task` | `@number` | P1 | partial |
| GNT-10 | Milestone event | `[T] happens on 2024-01-20` | `gantt_task` | `@keyword` | P1 | partial |
| GNT-11 | Delete task | `[T] is deleted` | `gantt_task` | `@keyword.modifier` | P2 | partial |
| GNT-12 | Task status | `{closed}`, `{open}`, `{done}`, `{critical}`, `{milestone}`, `{start}`, `{end}`, `{display on}`, `{hide}` | `gantt_task` | `@keyword.modifier` | P2 | planned |
| GNT-13 | Today | `today is 2024-01-10` | `gantt_today_statement` | `@string` | P1 | done |
| GNT-14 | Date color | `2024-01-01 is colored in red` | `gantt_date_statement` | `@constant` | P1 | partial |
| GNT-15 | Separator | `--`, `...` | `gantt_separator` | `@punctuation.special` | P1 | done |
| GNT-16 | Hide footbox/resource | `hide footbox`, `hide resource footbox`, `hide resource name` | display | `@keyword.directive` | P1 | partial |
| GNT-17 | Print scale/between | `printscale`, `print between ...` | `gantt_directive` | `@keyword.directive` | P2 | planned |
| GNT-18 | Label on column | `label on column ...` | `gantt_directive` | `@string` | P2 | planned |
| GNT-19 | Language | `language ...` | `gantt_directive` | `@string` | P2 | planned |
| GNT-20 | Week number strategy | `week number strategy ...` | `gantt_directive` | `@keyword.directive` | P3 | planned |
| GNT-21 | Task complete default | `task complete default` | `gantt_directive` | `@keyword.modifier` | P3 | planned |
| GNT-22 | Group start/end | `group ...`, `end group` | `gantt_group` | `@module` | P2 | planned |
| GNT-23 | Notes | `note bottom ...` | `gantt_note` | `@comment` | P2 | planned |
| GNT-24 | Gantt skinparam/theme | common | skinparam | `@property` | P1 | partial |
| GNT-25 | Natural-language tasks | starts/lasts/ends forms | `gantt_task` | `@string` | P1 | partial |

---

### 4.14 Chronology

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| CHR-01 | Envelope | `@startchronology` ... `@endchronology` | `chronology_diagram` | folds | P2 | raw |
| CHR-02 | Natural-language sentences | subject-verb-complement | `chronology_sentence` | `@string` | P2 | research |
| CHR-03 | Time header/scale | scale/time header | `chronology_scale` | `@number` | P2 | research |
| CHR-04 | Subject/task | task sentences | `chronology_task` | `@label` | P2 | research |
| CHR-05 | Hours/dates | date/time patterns | `chronology_time` | `@string` | P2 | research |
| CHR-06 | Completion/status | status sentences | `chronology_task` | `@keyword.modifier` | P3 | research |
| CHR-07 | Common commands | title/legend/skinparam | common | same | P2 | planned |

**Research:** confirm exact sentences from `ChronologyDiagram` and
`SentenceHappensChronology`; keep raw fallback until then.

---

### 4.15 JSON / YAML / HCL

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| JSN-01 | JSON envelope | `@startjson` ... `@endjson` | dedicated or generic | folds | P0 | raw |
| JSN-02 | JSON body | object/array/scalars | inject `json` | injection | P0 | partial |
| JSN-03 | Highlight key | `#highlight "key"` | `json_highlight` | `@keyword.directive` | P1 | planned |
| JSN-04 | Highlight with color | `#highlight "key" as "color"` | `json_highlight` | `@constant` | P1 | planned |
| JSN-05 | Highlight block | `#highlight "key" { ... }` | `json_highlight` | ranges | P2 | planned |
| JSN-06 | Highlight all/subkey | `#highlight all`, `"key"/"sub"` | `json_highlight` | `@string` | P2 | planned |
| YML-01 | YAML envelope | `@startyaml` ... `@endyaml` | dedicated/generic | folds | P0 | raw |
| YML-02 | YAML body | mappings/lists/scalars/anchors | inject `yaml` | injection | P0 | partial |
| YML-03 | Highlight key/color/all | `#highlight ...` | `yaml_highlight` | same as JSON | P1 | planned |
| HCL-01 | HCL envelope | `@starthcl` ... `@endhcl` | dedicated/generic | folds | P2 | raw |
| HCL-02 | HCL body | blocks/attributes/expressions | inject `hcl` | injection | P2 | planned |
| HCL-03 | HCL terms | strings/numbers/bools/lists/maps/functions | `hcl_*` if no injection | `@type` | P3 | planned |

---

### 4.16 Network / nwdiag

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| NW-01 | Envelope | `@startnwdiag` ... `@endnwdiag` | `nwdiag_diagram` | folds | P1 | raw |
| NW-02 | Network | `network Name { ... }` | `nwdiag_network` | `@type` | P1 | planned |
| NW-03 | Group | `group { ... }` | `nwdiag_group` | `@module` | P1 | planned |
| NW-04 | Element | `address`, `description`, `shape`, `color` | `nwdiag_element` | `@property`/`@constant` | P1 | planned |
| NW-05 | Link | `a -- b`, `a -- b : label` | `nwdiag_link` | `@operator` | P1 | planned |
| NW-06 | Property | `property key = value` | `nwdiag_property` | `@property` | P2 | planned |
| NW-07 | Comment | comment syntax | comment | `@comment` | P1 | planned |
| NW-08 | Vertical line | vertical separator | `nwdiag_separator` | `@punctuation.special` | P2 | research |
| NW-09 | Init | `nwdiag { ... }` | init block | folds | P2 | research |
| NW-10 | End something | `end` | close token | `@keyword` | P1 | planned |

---

### 4.17 Salt (UI mockups)

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| SALT-01 | Envelope | `@startsalt` ... `@endsalt` | `salt_diagram` | folds | P1 | raw |
| SALT-02 | Group/box | `{ ... }` | `salt_group` | `@punctuation.bracket` | P1 | planned |
| SALT-03 | Button | `[Button]` | `salt_button` | `@string` | P1 | planned |
| SALT-04 | Radio | `(X)`, `( )` | `salt_radio` | `@boolean` | P1 | planned |
| SALT-05 | Checkbox | `[X]`, `[ ]` | `salt_checkbox` | `@boolean` | P1 | planned |
| SALT-06 | Text field | `"text"` | `salt_textfield` | `@string` | P1 | planned |
| SALT-07 | Table | `{SI ... }`, `\|` | `salt_table` | `@markup` | P1 | planned |
| SALT-08 | Tree | `{T ... }` | `salt_tree` | `@markup.list` | P2 | planned |
| SALT-09 | Tabs | `{/ ... }` | `salt_tabs` | `@markup` | P2 | planned |
| SALT-10 | Scroll | `{S ... }` | `salt_scroll` | `@markup` | P2 | planned |
| SALT-11 | Menu | `{+ ... }`, `{- ... }` | `salt_menu` | `@markup.list` | P2 | planned |
| SALT-12 | Separator | `--`, `..`, `==` | `salt_separator` | `@punctuation.special` | P2 | planned |
| SALT-13 | Free text | arbitrary text lines | `salt_text` | `@string`/`@spell` | P1 | planned |
| SALT-14 | Salt skinparam/theme | common | skinparam | `@property` | P2 | planned |

---

### 4.18 Ditaa

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| DIT-01 | Envelope | `@startditaa` ... `@endditaa` | `ditaa_diagram` | folds | P1 | raw |
| DIT-02 | Options | `-E`, `-S`, `--no-separation` | `ditaa_option` | `@keyword.option` | P2 | planned |
| DIT-03 | ASCII body | boxes/arrows/text | `ditaa_body` + `text` injection | raw/spell off | P1 | partial |
| DIT-04 | Comments | comment syntax | `ditaa_comment` | `@comment` | P2 | research |

---

### 4.19 ArchiMate

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| ARC-01 | Envelope/macros | `@startuml`, `!include <archimate/Archimate>` | preprocessor + entity | `@keyword.directive` | P1 | raw |
| ARC-02 | Element macros | `Archimate(element, name)` | `archimate_element`/macro call | `@type` | P1 | planned |
| ARC-03 | Business layer | `Business_*` | `archimate_element.kind` | `@type` | P1 | planned |
| ARC-04 | Application layer | `Application_*` | kind | `@type` | P1 | planned |
| ARC-05 | Technology layer | `Technology_*` | kind | `@type` | P1 | planned |
| ARC-06 | Motivation layer | `Motivation_*` | kind | `@type` | P2 | planned |
| ARC-07 | Strategy layer | `Strategy_*` | kind | `@type` | P2 | planned |
| ARC-08 | Implementation/Migration | `Implementation_*` | kind | `@type` | P2 | planned |
| ARC-09 | Physical | `Physical_*` | kind | `@type` | P2 | planned |
| ARC-10 | Relations | `Rel_Triggering`, `Rel_Serving`, `Rel_Realization`, `Rel_Influence`, `Rel_Flow`, `Rel_Composition`, `Rel_Association`, `Rel_Assignment`, `Rel_Aggregation`, `Rel_Access`, `Rel_Access_r`, `Rel_Access_w`, `Rel_Access_rw`, `Rel_Specialization` | `archimate_relation`/macro | `@operator` | P1 | planned |
| ARC-11 | ArchiMate packages/groups | `package`, `ArchimatePackage` | `archimate_package` | `@module` | P2 | planned |
| ARC-12 | ArchiMate notes/legends | common | note/legend | `@comment` | P2 | planned |

**Design choice:** ArchiMate is a stdlib macro layer, not a separate diagram
type. Support it by parsing macro calls generically, recognizing ArchiMate
element/relation names, and tagging definitions/references. Do not hardcode
thousands of macros; use a data-driven name table.

---

### 4.20 Requirement diagram

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| REQ-01 | Envelope | `@startuml` + `requirement` | `requirement_declaration` | `@type` | P1 | planned |
| REQ-02 | Requirement kinds | `requirement`, `functionalRequirement`, `interfaceRequirement`, `performanceRequirement`, `physicalRequirement`, `designConstraint` | kind | `@keyword.type` | P1 | planned |
| REQ-03 | Requirement body | `{ id: ...; text: ...; risk: ...; verifymethod: ... }` | `requirement_body` | `@property` | P1 | planned |
| REQ-04 | Body fields with multiline text | `text: ...` | `requirement_field` | `@string` | P1 | planned |
| REQ-05 | Requirement relations | `- satisfy ->`, `- derive ->`, `- trace ->`, `- verify ->`, `- refine ->`, `- copy ->`, `- contain ->` | `requirement_relation` | `@operator` | P1 | planned |
| REQ-06 | Nested requirements/packages | `package ... { requirement ... }` | package/requirement | `@module` | P2 | planned |
| REQ-07 | Requirement notes | common | note | `@comment` | P2 | planned |
| REQ-08 | Stereotypes/colors/links | common | fields | same | P2 | planned |

---

### 4.21 ER / Chen / Information Engineering

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| ER-01 | Chen envelope | `@startchen` ... `@endchen` | `chen_diagram` | folds | P2 | raw |
| ER-02 | Entity | `entity Name` | `chen_entity` | `@type` | P2 | planned |
| ER-03 | Attribute | `attribute name` | `chen_attribute` | `@variable.member` | P2 | planned |
| ER-04 | Relationship | `relationship name` | `chen_relationship` | `@type` | P2 | planned |
| ER-05 | Associate | `associate ...` | `chen_associate` | `@operator` | P2 | planned |
| ER-06 | Subclass | `subclass ...` | `chen_subclass` | `@type` | P2 | planned |
| ER-07 | Group | `group ... end group` | `chen_group` | `@module` | P3 | planned |
| ER-08 | Cardinality | `{1,N}`, `{0,1}`, `(min,max)` | `chen_cardinality` | `@string.special` | P2 | planned |
| ER-09 | Weak entity/identifying relationship | weak syntax | `chen_weak` | `@keyword.modifier` | P3 | planned |
| ER-10 | IE notation (crow's foot) | `entity` + `\|\|--o{` | `ie_entity`/`ie_relation` | `@operator` | P2 | planned |
| ER-11 | IE entity attributes | `entity X { * id : int }` | `ie_body` | `@variable.member` | P2 | planned |
| ER-12 | ER notes/legend | common | note/legend | `@comment` | P2 | planned |

**Note:** PlantUML IE support uses `entity` + crow's-foot relations in
description diagrams; Chen is a separate `@startchen` diagram. Implement both.

---

### 4.22 Git log diagram

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| GIT-01 | Envelope | `@startgit` ... `@endgit` | `git_diagram` | folds | P2 | raw |
| GIT-02 | Commit line | `* hash (refs) message` | `git_commit` | `@type`/`@string` | P2 | planned |
| GIT-03 | Commit hash | 7-40 hex chars | `git_hash` | `@string.special` | P2 | planned |
| GIT-04 | Branch/tag refs | `(HEAD -> main, origin/main, tag: v1)` | `git_ref` | `@label` | P2 | planned |
| GIT-05 | Merge graph lines | `\|`, `\`, `/`, `*` | `git_graph_line` | `@punctuation.special` | P2 | planned |
| GIT-06 | Tags | `tag: v1` | `git_tag` | `@label` | P2 | planned |
| GIT-07 | Commit message | text after refs | `git_message` | `@string`/`@spell` | P2 | planned |
| GIT-08 | Author/date metadata | `Author:`, `Date:` | `git_metadata` | `@property` | P3 | research |
| GIT-09 | Common commands | title/legend/skinparam | common | same | P2 | planned |
| GIT-10 | Tags query | commits/refs | `tags.scm` | `@definition.commit`/`@reference.commit` | P2 | planned |

---

### 4.23 Files tree diagram

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| FIL-01 | Envelope | `@startfiles` ... `@endfiles` | `files_diagram` | folds | P3 | raw |
| FIL-02 | Directory | `dir/` | `files_dir` | `@module` | P3 | planned |
| FIL-03 | File | `file.ext` | `files_file` | `@string.special.path` | P3 | planned |
| FIL-04 | Tree glyphs/indent | tree characters | `files_tree` | `@punctuation.special` | P3 | planned |
| FIL-05 | Descriptions/annotations | trailing text | `files_comment` | `@comment` | P3 | planned |
| FIL-06 | File type/icons | extension mapping | `files_type` | `@type` | P4 | research |

---

### 4.24 Chart diagram

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| CHT-01 | Envelope | `@startchart` ... `@endchart` | `chart_diagram` | folds | P3 | raw |
| CHT-02 | Chart type | bar/line/pie/radar etc. | `chart_type` | `@keyword.type` | P3 | research |
| CHT-03 | Title/axes/legend | title/axis labels | `chart_metadata` | `@markup.heading` | P3 | research |
| CHT-04 | Series/data points | label + number pairs | `chart_series`, `chart_point` | `@number`/`@string` | P3 | research |
| CHT-05 | Colors | series colors | `color` | `@constant` | P3 | research |
| CHT-06 | Common commands | skinparam/legend | common | same | P3 | planned |

**Research:** fetch current `@startchart` docs/examples before designing the
grammar; do not guess the data syntax.

---

### 4.25 EBNF diagram

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| EBNF-01 | Envelope | `@startebnf` ... `@endebnf` | `ebnf_diagram` | folds | P3 | raw |
| EBNF-02 | Rule | `id = expression ;` | `ebnf_rule` | `@function` | P3 | planned |
| EBNF-03 | Alternation | `a \| b` | `ebnf_alternation` | `@operator` | P3 | planned |
| EBNF-04 | Concatenation | `a , b` | `ebnf_concatenation` | `@operator` | P3 | planned |
| EBNF-05 | Optional | `[ ... ]` | `ebnf_optional` | `@punctuation.bracket` | P3 | planned |
| EBNF-06 | Repetition | `{ ... }`, `*`, `+` | `ebnf_repeat` | `@keyword.operator` | P3 | planned |
| EBNF-07 | Grouping | `( ... )` | `ebnf_group` | `@punctuation.bracket` | P3 | planned |
| EBNF-08 | Terminal/identifier | `"string"`, `id` | `ebnf_terminal`/`ebnf_identifier` | `@string`/`@label` | P3 | planned |
| EBNF-09 | Comments | `(* ... *)` | `ebnf_comment` | `@comment` | P3 | planned |
| EBNF-10 | Notes/multiline | note syntax | `ebnf_note` | `@comment` | P3 | planned |
| EBNF-11 | Special sequences | `? ... ?` | `ebnf_special` | `@string.special` | P3 | planned |

---

### 4.26 Regex diagram

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| RGX-01 | Envelope | `@startregex` ... `@endregex` | `regex_diagram` | folds | P3 | raw |
| RGX-02 | Literal | `abc` | `regex_literal` | `@string` | P3 | planned |
| RGX-03 | Char class | `[a-z]`, `[^0-9]` | `regex_class` | `@string.regexp` | P3 | planned |
| RGX-04 | Group | `(...)`, `(?:...)` | `regex_group` | `@punctuation.bracket` | P3 | planned |
| RGX-05 | Alternation | `a\|b` | `regex_alternation` | `@operator` | P3 | planned |
| RGX-06 | Quantifiers | `*`, `+`, `?`, `{n,m}` | `regex_quantifier` | `@keyword.operator` | P3 | planned |
| RGX-07 | Anchors | `^`, `$` | `regex_anchor` | `@keyword.operator` | P3 | planned |
| RGX-08 | Escapes | `\d`, `\w`, `\.` | `regex_escape` | `@string.escape` | P3 | planned |
| RGX-09 | Lookaround | `(?=...)`, `(?!...)`, `(?<=...)`, `(?<!...)` | `regex_lookaround` | `@keyword.operator` | P3 | planned |
| RGX-10 | Comments/notes | comment syntax | `regex_comment` | `@comment` | P3 | research |

---

### 4.27 Packetdiag / board / wire / flow / BPM / math / creole / dot / sprites

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| PKT-01 | Packetdiag envelope | `@startpacketdiag` ... end | `packet_diagram` | folds | P3 | raw |
| PKT-02 | Packet fields | `0-15: Field`, ranges | `packet_field` | `@property`/`@number` | P3 | research |
| BRD-01 | Board envelope | `@startboard` ... `@endboard` | `board_diagram` | folds | P3 | raw |
| BRD-02 | Columns/cards | `+`, `--` | `board_column`/`board_card` | `@markup.list` | P3 | research |
| WIR-01 | Wire envelope | `@startwire` ... `@endwire` | `wire_diagram` | folds | P3 | raw |
| WIR-02 | Components/spots | `component`, `spot` | `wire_component`/`wire_spot` | `@type` | P3 | research |
| WIR-03 | Links/moves | `link`, `move`, `goto`, `new column` | `wire_command` | `@operator` | P3 | research |
| FLW-01 | Flow envelope | `@startflow` ... `@endflow` | `flow_diagram` | folds | P3 | raw |
| FLW-02 | Activity boxes/links | `:text;`, `->` | `flow_activity`/`flow_link` | `@string`/`@operator` | P3 | research |
| BPM-01 | BPM envelope | `@startbpm` ... `@endbpm` | `bpm_diagram` | folds | P3 | raw |
| BPM-02 | BPM tasks/branches | `:task;`, `if`, `else`, `endif`, `fork`, `end fork`, `goto`, `merge`, `resume` | `bpm_*` | `@keyword.control` | P3 | research |
| BPM-03 | Docked events | docked event syntax | `bpm_event` | `@type` | P3 | research |
| MATH-01 | Math envelope | `@startmath` ... `@endmath` | `math_diagram` | folds | P3 | raw |
| MATH-02 | AsciiMath body | AsciiMath | injection `text`/math | `@markup.math` | P3 | planned |
| MATH-03 | LaTeX envelope | `@startlatex` ... `@endlatex` | `latex_diagram` | folds | P3 | raw |
| MATH-04 | LaTeX body | LaTeX | injection `latex` if available | `@markup.math` | P3 | planned |
| CRE-01 | Creole envelope | `@startcreole` ... `@endcreole` | `creole_diagram` | folds | P3 | raw |
| CRE-02 | Creole markup | headings/lists/tables/links/images | `creole_*` | `@markup.*` | P3 | planned |
| DOT-01 | DOT envelope | `@startdot` ... `@enddot` | `dot_diagram` | folds | P3 | raw |
| DOT-02 | DOT body | Graphviz DOT | injection `dot`/`graphviz` | injection | P3 | planned |
| SPR-01 | Sprites envelope | `@startsprites` ... `@endsprites` | `sprites_diagram` | folds | P4 | raw |
| SPR-02 | Sprite declarations | `sprite $name ...` | `sprite_declaration` | `@type` | P4 | research |

---

### 4.28 Internal/auxiliary and remaining diagram types

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| COMP-01 | Composite structure | `component`, `port`, `portin`, `portout`, interfaces | `component_port`/`port_member` | `@type`/`@property` | P1 | partial |
| COMP-02 | Port with color/stereotype | `port p #red <<s>>` | port fields | `@constant`/`@attribute` | P2 | partial |
| COMP-03 | Provided/required interfaces | `() Interface`, lollipop relations | class/relation | `@type`/`@operator` | P1 | partial |
| HELP-01 | Help diagram | `@starthelp` ... `@endhelp` | raw/generic | folds | P4 | raw |
| CRASH-01 | Crash/test diagram | `@startcrash` ... `@endcrash` | raw/generic | folds | P4 | raw |
| DEF-01 | Definition diagram | `@startdef` ... `@enddef` | raw/generic | folds | P4 | research |
| JCC-01 | JCCKit chart | `@startjcckit` ... `@endjcckit` | raw/generic | folds | P4 | raw |
| SUD-01 | Sudoku (if exposed) | `@startsudoku` ... `@endsudoku` | raw/generic | folds | P4 | research |
| AUX-01 | `@startuml` help/sprites modes | content-based | `uml_diagram` alternatives | tags | P4 | research |

### 4.29 Stdlib / macro ecosystems

PlantUML ships large stdlib macro libraries. They are not separate diagram
types; they expand into class/description/sequence syntax. Maximum capability
means parsing macro calls generically, tagging definitions/references, and
recognizing well-known names without hardcoding thousands of macros.

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| MAC-01 | Generic macro call | `Name(arg1, arg2)` | `macro_call` | `@function.macro`/`@reference.call` | P1 | planned |
| MAC-02 | Macro definition | `!define Name(...) ...`, `!procedure` | preprocessor | `@function.macro` | P0 | partial |
| MAC-03 | Macro include | `!include <lib/...>` | preprocessor include | `@keyword.import`/`@string.special.path` | P0 | partial |
| MAC-04 | C4-PlantUML | `Person`, `System`, `Container`, `Component`, `Rel`, `Boundary`, `Deployment_Node` | `c4_element`/macro | `@type`/`@operator` | P2 | planned |
| MAC-05 | C4 relations | `Rel`, `Rel_Back`, `Rel_Neighbor`, `BiRel`, `Rel_Up`, `Rel_Down`, `Rel_Left`, `Rel_Right` | `c4_relation`/macro | `@operator` | P2 | planned |
| MAC-06 | Cloud icon libs | AWS/Azure/GCP/Kubernetes/Docker macros | data-driven macro names | `@type` | P3 | planned |
| MAC-07 | Icon/sprites libs | Font Awesome, Material, Office, Cloudinsight | `sprite_use`/macro | `@string.special.symbol` | P3 | planned |
| MAC-08 | ArchiMate stdlib | see 4.19 | macro table | `@type`/`@operator` | P2 | planned |
| MAC-09 | Macro tags | definitions/calls | `tags.scm` | `@definition.macro`/`@reference.call` | P2 | planned |

**Design:** keep a data-driven `stdlib` name/kind table in the scanner or
grammar. Do not generate one rule per macro. Macro calls must never produce
`ERROR`; unknown macros are generic `macro_call`.

---

## 5. Preprocessor and variables

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| PP-01 | Include | `!include path`, `!include <stdlib>` | `preprocessor_include` | `@keyword.import`/`@string.special.path` | P0 | partial |
| PP-02 | Include many/once/sub | `!include_many`, `!include_once`, `!include_sub` | `preprocessor_include` | `@keyword.import` | P1 | planned |
| PP-03 | Define object | `!define NAME value` | `preprocessor_define` | `@function.macro` | P0 | partial |
| PP-04 | Define long | `!definelong NAME ... !enddefinelong` | `preprocessor_block` | `@function.macro` | P1 | planned |
| PP-05 | Undef | `!undef NAME` | `preprocessor_undef` | `@keyword.directive` | P1 | planned |
| PP-06 | If/ifdef/ifndef | `!if`, `!ifdef`, `!ifndef`, `!else`, `!elseif`, `!endif` | `preprocessor_if_block` | `@keyword.conditional` | P0 | partial |
| PP-07 | While loop | `!while`, `!endwhile` | `preprocessor_while_block` | `@keyword.repeat` | P1 | planned |
| PP-08 | Procedure | `!procedure name(args) ... !endprocedure` | `preprocessor_procedure` | `@function.macro` | P0 | partial |
| PP-09 | Function | `!function name(args) ... !endfunction` | `preprocessor_function` | `@function.macro` | P0 | partial |
| PP-10 | Return | `!return value` | `preprocessor_return` | `@keyword.return` | P0 | partial |
| PP-11 | Startsub/endsub | `!startsub name ... !endsub` | `preprocessor_sub` | `@function.macro` | P1 | partial |
| PP-12 | Includesub | `!includesub file!name` | `preprocessor_include` | `@keyword.import` | P1 | planned |
| PP-13 | Theme | `!theme name` | `preprocessor_theme` | `@keyword.directive` | P1 | partial |
| PP-14 | Pragma | `!pragma name value` | `preprocessor_pragma` | `@keyword.directive` | P0 | partial |
| PP-15 | Option | `!option name value` | `preprocessor_option` | `@keyword.directive` | P1 | planned |
| PP-16 | Dump | `!dump` | `preprocessor_dump` | `@keyword.directive` | P2 | planned |
| PP-17 | Log | `!log text` | `preprocessor_log` | `@keyword.directive` | P2 | planned |
| PP-18 | Assert | `!assert condition` | `preprocessor_assert` | `@keyword.directive` | P2 | planned |
| PP-19 | Variable | `!$var = value`, `!$var++`, `!$var +=` | `preprocessor_variable` | `@variable` | P0 | partial |
| PP-20 | Unquoted | `!unquoted` | `preprocessor_unquoted` | `@keyword.modifier` | P2 | planned |
| PP-21 | Builtin functions | `%date()`, `%dirpath()`, `%filename()`, `%get_variable_value()`, `%intval()`, `%load_json()`, `%lower()`, `%newline()`, `%null()`, `%string()`, `%strlen()`, `%substr()`, `%upper()`, `%variable_exists()`, `%version()`, `%ceil()`, `%floor()`, `%mod()`, `%size()`, `%splitstr()` | `preprocessor_function_call` | `@function.builtin` | P1 | planned |
| PP-22 | Macro invocation | `NAME(args)` | `macro_call` | `@function.macro`/`@reference.call` | P1 | planned |
| PP-23 | Include guards | `!ifndef` + `!define` | PP-06/03 | - | P2 | planned |
| PP-24 | Preprocessor in raw bodies | any line starting `!` | `preprocessor` | `@keyword.directive` | P0 | partial |

**Design:** preprocessor must be structurally parsed before diagram-specific
rules, because macros can generate any construct. At minimum, never let `!...`
lines become `ERROR`.

---

## 6. Text, Creole, HTML Creole, colors, links, sprites, styles

### 6.1 Creole / HTML Creole

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| TXT-01 | Bold | `**bold**` | inline markup | `@markup.strong` | P0 | partial |
| TXT-02 | Italic | `//italic//` | inline markup | `@markup.italic` | P0 | partial |
| TXT-03 | Monospace | `""mono""` | inline markup | `@markup.raw` | P0 | partial |
| TXT-04 | Strikethrough | `--strike--` | inline markup | `@markup.strikethrough` | P1 | partial |
| TXT-05 | Underline | `__underline__` | inline markup | `@markup.underline` | P1 | partial |
| TXT-06 | Wave underline | `~~wave~~` | inline markup | `@markup.underline` | P2 | partial |
| TXT-07 | Headings | `== heading ==`, `.. heading ..`, `-- heading --`, `__ heading __` | inline markup | `@markup.heading.*` | P1 | partial |
| TXT-08 | Horizontal rules | `----`, `====`, `____`, `....` | inline markup | `@punctuation.special` | P2 | partial |
| TXT-09 | Bullet list | `* item`, `** sub` | block markup | `@markup.list` | P1 | partial |
| TXT-10 | Numbered list | `# item`, `## sub` | block markup | `@markup.list` | P1 | partial |
| TXT-11 | Table | `\| a \| b \|`, `\|= header \|` | table node | `@markup` | P2 | planned |
| TXT-12 | HTML creole bold/italic | `<b>`, `<i>` | inline markup | `@markup.strong`/`@markup.italic` | P1 | partial |
| TXT-13 | HTML creole underline/strike/wave | `<u>`, `<s>`, `<w>` | inline markup | `@markup.underline`/`@markup.strikethrough` | P1 | partial |
| TXT-14 | HTML creole color/background | `<color:blue>`, `<back:orange>` | inline markup | `@markup` | P1 | partial |
| TXT-15 | HTML creole size/font | `<size:20>`, `<font:monospace>` | inline markup | `@markup` | P2 | partial |
| TXT-16 | Superscript/subscript | `<sup>`, `<sub>` | inline markup | `@markup` | P2 | planned |
| TXT-17 | Escape | `~` | inline markup | `@string.escape` | P1 | partial |
| TXT-18 | Line break | `\\n`, `<br>` | inline markup | `@markup` | P1 | partial |
| TXT-19 | Link | `[[url]]`, `[[url label]]`, `[[url{tooltip} label]]` | `hyperlink` | `@markup.link` | P0 | partial |
| TXT-20 | Image | `<img:url>`, `<img:url{scale}>` | inline markup | `@markup.link.url` | P1 | partial |
| TXT-21 | OpenIconic | `<&icon>` | inline markup | `@string.special.symbol` | P1 | partial |
| TXT-22 | Emoji | `<:smile:>`, `<#red:smile:>` | inline markup | `@string.special` | P1 | partial |
| TXT-23 | Unicode | `<U+221E>` | inline markup | `@string.special` | P2 | partial |
| TXT-24 | Math | `<math>...</math>` | inline + injection | `@markup.math` | P3 | planned |
| TXT-25 | LaTeX | `<latex>...</latex>` | inline + injection | `@markup.math` | P3 | planned |
| TXT-26 | QR code | `<qrcode>` | inline markup | `@string.special` | P4 | research |
| TXT-27 | Code block | `<code>...</code>` | inline markup | `@markup.raw.block` | P2 | planned |
| TXT-28 | Spell checking | text bodies | `@spell`/`@nospell` | `query:spell` | P1 | partial |

### 6.2 Colors

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| COL-01 | Named colors | 140+ CSS names | `color` | `@constant` | P0 | partial |
| COL-02 | Hex colors | `#RGB`, `#RRGGBB` | `color` | `@constant` | P0 | partial |
| COL-03 | Alpha/gradient | `#AABBCCDD`, `#red\|blue` | `color` | `@constant` | P1 | partial |
| COL-04 | Transparent/automatic/none | keywords | `color` | `@constant.builtin` | P1 | partial |
| COL-05 | Style suffixes | `#color;line:red;line.bold;text:blue;back:white` | `color`/style attrs | `@attribute` | P1 | partial |
| COL-06 | Color in arrows | `-[#red]->` | relation color | `@constant` | P1 | partial |
| COL-07 | Color in notes/actions/states | `#color` suffix | color field | `@constant` | P0 | partial |
| COL-08 | Gradient direction | `#red-blue`, `#red\|blue` variants | `color` | `@constant` | P2 | research |

### 6.3 Links, stereotypes, tags

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| LNK-01 | Hyperlink | `[[url]]` | `hyperlink` | `@string.special.url` | P0 | partial |
| LNK-02 | Link label | `[[url label]]` | `hyperlink` | `@markup.link.label` | P1 | partial |
| LNK-03 | Tooltip | `[[url{tooltip} label]]` | `hyperlink` | `@string.special` | P2 | partial |
| LNK-04 | Link on element/relation/note | `[[url]]` suffix | fields | `@string.special.url` | P1 | partial |
| LNK-05 | URL in sequence participant/message | `[[url]]` | hyperlink | `@string.special.url` | P2 | partial |
| STE-01 | Stereotype | `<<stereotype>>` | `stereotype` | `@attribute` | P0 | partial |
| STE-02 | Spot stereotype | `<<(S,#color) stereotype>>` | `stereotype` | `@attribute` | P1 | partial |
| STE-03 | Multiple stereotypes | `<<a>><<b>>` | repeat stereotype | `@attribute` | P2 | partial |
| STE-04 | Tag | `$tag` | `tag` | `@attribute` | P1 | partial |
| STE-05 | Tag on relation | `$tag` suffix | fields | `@attribute` | P2 | partial |
| STE-06 | ArchiMate stereotypes | stdlib names | data-driven | `@attribute` | P2 | planned |

### 6.4 Sprites

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| SPRT-01 | Sprite definition | `sprite $name [w x h] { ... }` | `sprite_declaration` | `@type` | P2 | planned |
| SPRT-02 | Sprite from file | `sprite $name file` | `sprite_declaration` | `@string.special.path` | P2 | planned |
| SPRT-03 | Sprite base64/md5 | `sprite $name base64 ...`, `md5 ...` | `sprite_declaration` | `@string` | P3 | planned |
| SPRT-04 | Sprite SVG | `sprite $name svg ...` | `sprite_declaration` | `@markup.raw` | P3 | planned |
| SPRT-05 | Sprite use | `<$name>`, `<$name{scale}>` | `sprite_use` | `@string.special.symbol` | P2 | planned |
| SPRT-06 | Stdlib sprites | `!include <...>`, `<$...>` | preprocessor/sprite use | `@reference` | P2 | planned |

### 6.5 Styles, skinparams, themes

| ID | Feature | Syntax | Grammar plan | Query | Prio | Status |
|---|---|---|---|---|---|---|
| STY-01 | CSS style block | `<style> ... </style>` | `style_block` + CSS injection | injection/folds | P0 | partial |
| STY-02 | Style selectors | `classDiagram { ... }`, `class { ... }` | CSS-like | `@type`/`@property` | P1 | planned |
| STY-03 | Skinparam scalar | `skinparam name value` | `skinparam_statement` | `@property` | P1 | partial |
| STY-04 | Skinparam block | `skinparam { ... }` | `skinparam_statement` | folds | P1 | partial |
| STY-05 | Skinparam stereotypes | `skinparam class<<stereo>> ...` | `skinparam_statement` | `@attribute` | P2 | planned |
| STY-06 | Themes | `!theme name` | preprocessor | `@keyword.directive` | P1 | partial |
| STY-07 | Handwritten/monochrome/shadowing | skinparams | `skinparam_statement` | `@property` | P1 | partial |
| STY-08 | Style import | `!include <style/...>` | preprocessor | `@keyword.import` | P2 | planned |

---

## 7. Testing strategy

### 7.1 Test layers

| Layer | Tool | Purpose | Gate |
|---|---|---|---|
| Grammar generation | `tree-sitter generate` | Parser compiles with no unresolved conflicts. | P0 |
| Corpus | `tree-sitter test` | Exact S-expression trees per feature. | P0 |
| Fixture smoke | Node script | Parse every `.puml`; fail on `ERROR`/`MISSING`. | P0 |
| Query compile | `tree-sitter query --check` / `vim.treesitter.query.parse` | Every `.scm` is valid. | P0 |
| Query snapshots | Node/Neovim headless | Capture ranges/names are stable. | P1 |
| Bindings | Node/Python/Go/Rust/Swift tests | Load and parse smoke test. | P1 |
| Fuzz | `tree-sitter test --fuzz` or custom | No crash/hang on mutations. | P2 |
| Performance | benchmark script | Budgets on 1k/10k-line files and incremental edits. | P1 |
| Editor integration | Neovim headless | Highlight/fold/indent/locals work on fixtures. | P1 |

### 7.2 Corpus layout

```
test/
  corpus/
    common.txt
    class.txt
    object.txt
    usecase.txt
    component.txt
    sequence.txt
    activity.txt
    state.txt
    timing.txt
    mindmap.txt
    wbs.txt
    gantt.txt
    chronology.txt
    json.txt
    yaml.txt
    hcl.txt
    nwdiag.txt
    salt.txt
    ditaa.txt
    archimate.txt
    requirement.txt
    er.txt
    git.txt
    files.txt
    chart.txt
    ebnf.txt
    regex.txt
    packet.txt
    board.txt
    wire.txt
    flow.txt
    bpm.txt
    math.txt
    creole.txt
    preprocessor.txt
    queries.txt
  fixtures/
    <diagram>/*.puml
```

### 7.3 Required tests per feature

1. A corpus case with the smallest valid input.
2. A corpus case with aliases/colors/stereotypes/links where applicable.
3. A fixture with the feature combined with other constructs.
4. A negative case proving raw fallback (no `ERROR`).
5. Query assertions: expected captures and folds/indents.
6. A docs example (copy from plantuml.com, with attribution).

### 7.4 Performance budgets

- `parser.c` size budget: target < 8 MB, hard fail > 20 MB without review.
- Parse 10k lines: target < 150 ms on CI hardware (single parse), no
  pathological backtracking.
- Incremental edit: < 20 ms for one-line edits in a 10k-line file.
- Memory: parser binary < 5 MB; wasm build < 5 MB gzip.
- Add `benchmark/` with fixtures and a `npm run bench` script.

---

## 8. CI, packaging, release

| ID | Task | Detail | Prio |
|---|---|---|---|
| CI-01 | Generate check | `tree-sitter generate && git diff --exit-code src/` | P0 |
| CI-02 | Corpus + fixture tests | `tree-sitter test` + fixture smoke | P0 |
| CI-03 | Query compile | all `.scm` files | P0 |
| CI-04 | Lint | `npm run lint`, `clang-format`, `prettier` for docs | P1 |
| CI-05 | Build matrix | Linux/macOS/Windows, Node/Python/Rust/Go/Swift | P1 |
| CI-06 | WASM build | `tree-sitter build --wasm`, size check | P2 |
| CI-07 | Fuzz job | nightly | P2 |
| CI-08 | Release workflow | tag -> prebuilds + npm + crates.io + PyPI | P1 |
| PKG-01 | Version `0.1.0` | update package.json/Cargo/pyproject/tree-sitter.json | P1 |
| PKG-02 | CHANGELOG | Keep a Changelog format | P1 |
| PKG-03 | npm publish | prebuildify, `files` whitelist | P1 |
| PKG-04 | crates.io publish | include queries + grammar | P1 |
| PKG-05 | PyPI publish | cibuildwheel | P2 |
| PKG-06 | nvim-treesitter registry | `main` branch + parser config docs | P1 |
| PKG-07 | Helix/Zed/Emacs | query + grammar registration docs | P2 |
| PKG-08 | GitHub Linguist | `.puml` detection | P2 |
| DOC-01 | README | supported diagrams matrix, install, limitations | P0 |
| DOC-02 | docs/dev.md | build/test/query workflow, architecture | P0 |
| DOC-03 | docs/nvim.md | folds/indents, textobjects, context | P1 |
| DOC-04 | docs/queries.md | capture contract and examples | P1 |
| DOC-05 | CONTRIBUTING.md | feature workflow, tags, corpus rules | P1 |

---

## 9. Roadmap phases

### Phase 0 - Stabilize the current rewrite (P0, 2-3 days)

- Rebuild `src/parser.c`, bindings, and `build/Release`.
- Run `tree-sitter generate`, `tree-sitter test`, fixture smoke.
- Fix all `ERROR`/`MISSING` in existing fixtures or convert to raw fallback.
- Wire `npm test` to run corpus + fixture tests.
- Register `folds.scm`/`indents.scm` in `tree-sitter.json` and deploy script.
- Commit the rewrite in logical commits; update README status.

**Exit:** all existing fixtures parse cleanly, `npm test` is meaningful.

### Phase 1 - Query maximum (P0/P1, 1 week)

- Expand `highlights.scm` to the full capture contract in 3.2.
- Add JSON/YAML/HCL/CSS/text injections.
- Complete `folds.scm`, `indents.scm`, `locals.scm`, `tags.scm`.
- Add `textobjects.scm`, `context.scm`, `rainbow.scm`.
- Add query compile + snapshot tests across all fixtures.
- Add `queries.md` docs.

**Exit:** every existing node has a capture; every block folds/indents; every
definition/reference is local/tagged.

### Phase 2 - UML completeness (P1, 2-3 weeks)

- Class: all relations, direction hints, lollipop, member refs, association
  classes, hide/show variants.
- Sequence: external messages, activation shortcuts, multi-line participants,
  all note forms, refs, anchors, newpage.
- Activity beta: merge, break, connectors, all note/container forms.
- State: pseudostate stereotypes, guards/actions, concurrent regions.
- Component/deployment: ports, all node kinds, nested containers.
- Use case: extend/include, system boundaries, business actors.
- Object: JSON/map shorthand.
- Timing: full structured grammar.

**Exit:** all UML fixtures and a real-world corpus parse with zero `ERROR`.

### Phase 3 - Non-UML completeness (P1/P2, 3-4 weeks)

- Mindmap/WBS/Gantt full command sets.
- JSON/YAML/HCL highlights + injections.
- nwdiag, salt, ditaa.
- ArchiMate macro recognition + tags.
- Requirement diagram.
- ER/Chen/IE.
- Git log, files tree.
- Chronology after research.

**Exit:** every `@start...` type from `DiagramType` has either structure or an
intentional raw/injection contract.

### Phase 4 - Niche diagrams (P3, 2-3 weeks)

- Chart, EBNF, regex, packetdiag, board, wire, flow, BPM.
- Math/LaTeX, Creole, DOT, sprites, help/crash/definition.
- Injections for nested languages.

### Phase 5 - Performance and release (P1, 1-2 weeks)

- Reduce parser size/conflicts and meet performance budgets.
- CI matrix, fuzz, release automation.
- Publish npm/crates/PyPI, submit to nvim-treesitter/Helix/Zed.

### Phase 6 - Ecosystem (ongoing)

- Real-world corpus, issue triage, docs examples, editor integrations.
- Track new PlantUML releases and diagram types.

---

## 10. Risks, decisions, open questions

| Risk / decision | Impact | Mitigation |
|---|---|---|
| 42 MB `parser.c` / state explosion | Slow builds, large packages, slow parse | Refactor repeated `_statement`/`raw_line`, reduce ambiguity, set size/perf budgets, measure with `--report-states-for-rule`. |
| 10 grammar conflicts | `ERROR` on edge cases, unstable parse | Convert ambiguous lines to raw fallback; add precedence/tokens; corpus tests for each conflict. |
| Raw fallback hides missing structure | Features look supported but have no queries | Track `raw` status explicitly; fixture smoke + query assertions per feature. |
| PlantUML syntax is permissive | Impossible to validate fully with LR | Raw fallback invariant; structure only where editor value is high. |
| Docs/source drift | Missing features | Use `DiagramType.java`, command packages, and release notes as source of truth. |
| Macro-generated syntax (ArchiMate/C4) | Parser cannot see expanded syntax | Parse macro calls generically; data-driven name tables; tags on macro definitions/calls. |
| Legacy activity syntax | Low ROI | Keep raw; do not block release. |
| Query capture naming drift | Inconsistent editor support | Single capture contract (3.2), query tests, docs. |
| Injection recursion/performance | Slow editors | Inject only whole bodies; avoid nested self-injection. |
| No CI | Regressions land silently | Phase 0 CI: generate/corpus/fixtures/queries. |
| Unknown chart/chronology syntax | Wrong grammar design | `research` status; fetch docs/examples before implementation. |

### Open questions

1. Should each diagram get a dedicated top-level rule, or should `@startuml`
   auto-detection remain the only UML entry point?
2. Do we expose `raw_*` nodes publicly or hide them behind aliases? (Decision:
   keep public for debugging and editor fallback.)
3. How much Creole should be structured vs left as text? (Decision: structure
   only editor-relevant markup; keep text lossless.)
4. Do we support legacy activity at all? (Decision: raw fallback, P3.)
5. Which nested languages are worth shipping? (json/yaml/hcl/css first; dot/
   latex/ebnf/regex own grammars later.)
6. How do we version query capture changes? (Add a `docs/queries.md` changelog
   and query tests.)

---

## 11. First 10 tasks (start here)

1. Rebuild and run `tree-sitter generate && tree-sitter test`; record failures.
2. Add fixture smoke test and wire `tree-sitter test` into `npm test`.
3. Register `folds.scm`/`indents.scm`; copy all queries in the deploy script.
4. Fix all `ERROR` in `class_features.puml`, `component_features.puml`,
   `sequence_features.puml`, `activity_features.puml`, `state_features.puml`.
5. Add corpus files for class/sequence/activity/state/component.
6. Expand highlights for existing nodes (class/sequence/activity/state/notes).
7. Add JSON/YAML/CSS injections and test them.
8. Complete locals/tags for existing declarations and references.
9. Add textobjects/context queries and Neovim headless tests.
10. Update README/docs with the supported-diagram matrix and query contract.

---

## 12. Coverage checklist (definition of complete)

- [ ] Every `DiagramType` enum value has a documented status and fixture.
- [ ] Every `@start...` variant is accepted without `ERROR`.
- [ ] Every common command in `CommonCommands.java` is parsed or explicitly raw.
- [ ] Every preprocessor directive is parsed or explicitly raw.
- [ ] Every diagram family has corpus tests and a fixture.
- [ ] Every block folds; every branch indents; every declaration is a local
      definition; every reference is local/tagged.
- [ ] Every capture in 3.2 has at least one test.
- [ ] All queries compile in `tree-sitter` and Neovim.
- [ ] `npm test` runs grammar, corpus, fixtures, queries, and bindings.
- [ ] CI is green on Linux/macOS/Windows.
- [ ] Parser size and parse-time budgets are met.
- [ ] Package published and editor registries updated.

---

## 13. Reference index

Use these PlantUML pages while implementing (docs may lag source):

- UML: `/class-diagram`, `/object-diagram`, `/usecase-diagram`,
  `/component-diagram`, `/deployment-diagram`, `/sequence-diagram`,
  `/activity-diagram-beta`, `/state-diagram`, `/timing-diagram`.
- Non-UML: `/mindmap-diagram`, `/wbs-diagram`, `/gantt-diagram`,
  `/chronology-diagram`, `/json`, `/yaml`, `/hcl`, `/nwdiag`,
  `/salt`, `/ditaa`, `/archimate-diagram`, `/requirement-diagram`,
  `/er-diagram`, `/git-diagram`, `/files`, `/chart`, `/ebnf`, `/regex`,
  `/packetdiag`, `/board`, `/wire`, `/flow`, `/bpm`, `/math`, `/creole`,
  `/dot`, `/sprites`.
- Common: `/preprocessing`, `/creole`, `/style-evolution`, `/skinparam`,
  `/color`, `/link`, `/openiconic`, `/emoji`, `/unicode`, `/commons`.
- Source: `net/sourceforge/plantuml/core/DiagramType.java`,
  `net/sourceforge/plantuml/command/CommonCommands.java`, and the
  `*/command/*.java` packages.

