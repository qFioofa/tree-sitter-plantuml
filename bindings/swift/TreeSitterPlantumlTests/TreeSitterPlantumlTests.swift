import XCTest
import SwiftTreeSitter
import TreeSitterPlantuml

final class TreeSitterPlantumlTests: XCTestCase {
    func testCanLoadGrammar() throws {
        let parser = Parser()
        let language = Language(language: tree_sitter_plantuml())
        XCTAssertNoThrow(try parser.setLanguage(language),
                         "Error loading Plantuml grammar")
    }
}
