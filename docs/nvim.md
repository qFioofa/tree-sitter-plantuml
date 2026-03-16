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

## Supported Extensions

- `.puml`
- `.iuml`
- `.plantuml`
- `.wsd`
- `.pu`
