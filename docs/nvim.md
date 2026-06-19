# Neovim Integration

## Quick Setup

1. Install with [lazy.nvim](https://github.com/folke/lazy.nvim):

```lua
{
  "nvim-treesitter/nvim-treesitter",
  build = ":TSUpdate",
  config = function()
    require("nvim-treesitter.configs").setup({
      ensure_installed = { "plantuml" },
      highlight = { enable = true },
    })
  end,
}
```

2. Set filetype for PlantUML files:

```lua
vim.cmd([[autocmd BufNewFile,BufRead *.puml,*.iuml,*.plantuml set filetype=plantuml]])
```

That's it! Syntax highlighting should now work for `.puml`, `.iuml`, and `.plantuml` files.

## Manual Install

If not using a plugin manager:

```bash
git clone https://github.com/qfioofa/tree-sitter-plantuml ~/.local/share/nvim/lazy/tree-sitter-plantuml
```

Then in Neovim:
```vim
:TSInstallFromGrammar plantuml
```

## No-plugin Deploy Script

To build the parser and install it straight into Neovim's runtime — no
`nvim-treesitter`, no plugin manager, just the built-in tree-sitter:

```bash
# from the repo root
./scripts/nvim_deploy.sh
```

This compiles `src/parser.c` + `src/scanner.c` and installs into your Neovim
site directory (`$XDG_DATA_HOME/nvim/site`, default `~/.local/share/nvim/site`):

| Path | Purpose |
|------|---------|
| `parser/plantuml.so` | compiled parser |
| `queries/plantuml/*.scm` | highlights / injections / locals / tags |
| `ftdetect/plantuml.lua` | `.puml .iuml .plantuml .wsd .pu` → `filetype=plantuml` |
| `after/ftplugin/plantuml.lua` | starts treesitter highlighting per buffer |

Open any `.puml` file and highlighting starts automatically. Options:

```bash
./scripts/nvim_deploy.sh --prefix /path/to/dir   # install elsewhere
./scripts/nvim_deploy.sh --uninstall             # remove it
CC=clang ./scripts/nvim_deploy.sh                # pick the compiler
```

## Supported Extensions

- `.puml`
- `.iuml`
- `.plantuml`
- `.wsd`
- `.pu`
