# Development

## Install tree sitter cli

```bash
npm install
```

## Use tree sitter cli

- `npm run generate` rebuilds all parser.
- `npx tree-sitter test` runs all tests for both parsers.
- `npx tree-sitter parse $file` run the `fsharp` parser on `$file` and outputs the parse tree.
- `npx tree-sitter parse -d $file` run the `fsharp` parser on `$file` and prints debug information.
