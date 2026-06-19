package tree_sitter_plantuml_test

import (
	"testing"

	tree_sitter "github.com/tree-sitter/go-tree-sitter"
	tree_sitter_plantuml "github.com/qfioofa/tree-sitter-plantuml/bindings/go"
)

func TestCanLoadGrammar(t *testing.T) {
	language := tree_sitter.NewLanguage(tree_sitter_plantuml.Language())
	if language == nil {
		t.Errorf("Error loading Plantuml grammar")
	}
}
