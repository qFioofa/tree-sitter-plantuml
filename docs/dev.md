# Development

## Setup

```bash
npm install
```

## Commands

| Command | Description |
|---------|-------------|
| `npm run generate` | Generate parser from grammar.js |
| `npm test` | Corpus + bindings + fixture smoke tests |
| `npm run test:corpus` | Run `tree-sitter test` only |
| `npm run test:fixtures` | Parse every fixture; fail on `ERROR`/`MISSING` |
| `npx tree-sitter parse <file>` | Parse a file and show syntax tree |
| `npx tree-sitter query queries/highlights.scm <file>` | Compile/run a query |

## Adding Tests

1. Add tests to `test/corpus/*.txt`
2. Format:
   ```
   ==================
   Test name
   ==================
   input code
   ---
   (expected S-expression)
   ```
3. Run `npm test`

## Project Structure

```
├── grammar.js          # Grammar definition
├── src/                # Generated parser
├── test/corpus/        # Corpus tests
├── test/fixtures/      # Fixture smoke inputs
├── queries/            # highlights, injections, folds, indents, locals, tags, textobjects, context, rainbow
├── scripts/            # nvim deploy + fixture smoke
└── bindings/           # Language bindings
```
