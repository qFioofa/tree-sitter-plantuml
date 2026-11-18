#!/usr/bin/env node

const { spawnSync } = require("node:child_process");
const fs = require("node:fs");
const path = require("node:path");

const root = path.resolve(__dirname, "..");
const dir = path.join(root, "test", "fixtures");
const files = fs
  .readdirSync(dir)
  .filter((name) => name.endsWith(".puml"))
  .map((name) => path.join(dir, name));

if (files.length === 0) {
  console.error("No fixture files found in test/fixtures");
  process.exit(1);
}

const result = spawnSync(
  process.platform === "win32" ? "npx.cmd" : "npx",
  ["tree-sitter", "parse", "--no-ranges", ...files],
  { cwd: root, encoding: "utf8" },
);

const output = `${result.stdout || ""}\n${result.stderr || ""}`;
const failures = output
  .split("\n")
  .filter((line) => line.includes("ERROR") || line.includes("MISSING"));

if (result.status !== 0 || failures.length > 0) {
  console.error(output);
  console.error(`Fixture smoke test failed (${failures.length} error lines).`);
  process.exit(1);
}

console.log(`Fixture smoke test passed (${files.length} files).`);
