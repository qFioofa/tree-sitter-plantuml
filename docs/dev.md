# Development

## Setup

```bash
npm install
```

## Commands

| Command | Description |
|---------|-------------|
| `npm run generate` | Generate parser from grammar.js |
| `npm test` | Run all tests |
| `npx tree-sitter parse <file>` | Parse a file and show syntax tree |

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
├── test/corpus/        # Tests
├── queries/            # Highlight/local queries
└── bindings/           # Language bindings
```
