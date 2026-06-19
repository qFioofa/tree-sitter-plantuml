# Neovim Integration

This grammar is **not** in the official `nvim-treesitter` registry, so a plain
`ensure_installed = { "plantuml" }` will not find it. Pick one of the two
install paths below.

- [Option A — No plugin manager (deploy script)](#option-a--no-plugin-manager-deploy-script) — simplest, recommended.
- [Option B — nvim-treesitter](#option-b--nvim-treesitter) — if you already use it.

Requirements: Neovim **0.9+** (0.10+ recommended) and a C compiler (`cc`,
`gcc`, or `clang`).

---

## Option A — No plugin manager (deploy script)

The repo ships a script that builds the parser and installs everything Neovim's
**built-in** tree-sitter needs — no `nvim-treesitter`, no plugin manager.

```bash
git clone https://github.com/qFioofa/tree-sitter-plantuml
cd tree-sitter-plantuml
./scripts/nvim_deploy.sh
```

This compiles `src/parser.c` + `src/scanner.c` and installs into your Neovim
site directory (`$XDG_DATA_HOME/nvim/site`, default `~/.local/share/nvim/site`):

| Path | Purpose |
|------|---------|
| `parser/plantuml.so` | compiled parser |
| `queries/plantuml/*.scm` | highlights / injections / locals / tags |
| `ftdetect/plantuml.lua` | `.puml .iuml .plantuml .wsd .pu` → `filetype=plantuml` |
| `after/ftplugin/plantuml.lua` | starts treesitter highlighting + sets `commentstring` per buffer |

Open any `.puml` file and highlighting starts automatically. Options:

```bash
./scripts/nvim_deploy.sh --prefix /path/to/dir   # install elsewhere
./scripts/nvim_deploy.sh --uninstall             # remove it
CC=clang ./scripts/nvim_deploy.sh                # pick the compiler
```

> If you clone the repo as-is, `src/parser.c` is already committed. If it is
> missing, run `npx tree-sitter generate` (see [docs/dev.md](./dev.md)) first.

---

## Option B — nvim-treesitter

`nvim-treesitter` can build any grammar if you register it manually. Use the
block that matches your installed branch.

### `master` branch (the classic, most common)

```lua
-- run once, before nvim-treesitter's setup
local parser_config = require("nvim-treesitter.parsers").get_parser_configs()
parser_config.plantuml = {
  install_info = {
    url = "https://github.com/qFioofa/tree-sitter-plantuml",
    files = { "src/parser.c", "src/scanner.c" },
    branch = "main",
  },
  filetype = "plantuml",
}

require("nvim-treesitter.configs").setup({
  ensure_installed = { "plantuml" }, -- now resolvable
  highlight = { enable = true },
})

-- map the file extensions to the plantuml filetype
vim.filetype.add({
  extension = {
    puml = "plantuml",
    iuml = "plantuml",
    plantuml = "plantuml",
    wsd = "plantuml",
    pu = "plantuml",
  },
})
```

Then in Neovim:

```vim
:TSInstall plantuml
```

### `main` branch (the rewrite)

The newer branch keeps a parser registry; add the grammar before installing:

```lua
require("nvim-treesitter.parsers").plantuml = {
  install_info = {
    url = "https://github.com/qFioofa/tree-sitter-plantuml",
    branch = "main",
  },
}
vim.filetype.add({
  extension = {
    puml = "plantuml", iuml = "plantuml", plantuml = "plantuml",
    wsd = "plantuml", pu = "plantuml",
  },
})
```

```vim
:TSInstall plantuml
```

> The queries (`highlights.scm`, etc.) live in this repo's `queries/`. With
> Option A the deploy script copies them for you. With nvim-treesitter you
> normally also want them on your runtimepath — the simplest way is to also run
> the deploy script once, or copy `queries/` into
> `~/.local/share/nvim/site/queries/plantuml/`.

---

## General Use

Once installed, highlighting is automatic for any file with a supported
extension. There are no commands to run per file.

### Supported extensions

`.puml`, `.iuml`, `.plantuml`, `.wsd`, `.pu`

### Force the filetype manually

For an unrecognized extension or a scratch buffer:

```vim
:set filetype=plantuml
```

### Verify it's working

```vim
" should print 'plantuml'
:set ft?

" should print 'true' if the treesitter highlighter is attached
:lua print(vim.treesitter.highlighter.active[vim.api.nvim_get_current_buf()] ~= nil)

" inspect the parse tree of the current buffer live
:InspectTree

" show the highlight groups under the cursor
:Inspect
```

`:InspectTree` (built into Neovim 0.9+) is the quickest way to see how the
grammar parses your diagram and to debug a missing highlight.

### Comments

The deploy script sets `commentstring` to `' %s`, so `gcc` / `gc` (with a
comment plugin or Neovim 0.10's built-in `gc`) comment lines with PlantUML's
single-quote syntax.

### What gets highlighted

The bundled queries cover the full grammar, including:

- diagram delimiters (`@startuml` / `@enduml`)
- class / object / state definitions, fields, methods, visibility
- stereotypes (`<< >>`), colors (`#...`), aliases
- relationships / arrows
- notes, headers, strings
- comments (line `'` and block `/' ... '/`), with spell-checking in comment
  and note bodies via injections

### Folding (optional)

To fold by the parse tree:

```lua
vim.wo.foldmethod = "expr"
vim.wo.foldexpr = "v:lua.vim.treesitter.foldexpr()"
vim.wo.foldenable = false -- start unfolded
```

---

## Troubleshooting

| Symptom | Fix |
|---------|-----|
| No highlighting | Confirm `:set ft?` reports `plantuml`. If not, the extension isn't mapped — re-run the deploy script or add the `vim.filetype.add` block. |
| `ensure_installed` can't find `plantuml` | You skipped the parser registration in Option B — add the `parser_config.plantuml` block before `setup()`. |
| Parser builds but no colors | Queries aren't on the runtimepath. Run the deploy script, or copy `queries/` into `~/.local/share/nvim/site/queries/plantuml/`. |
| `cc: command not found` | Install a C compiler, or run with `CC=clang ./scripts/nvim_deploy.sh`. |
| Want a clean slate | `./scripts/nvim_deploy.sh --uninstall` |
