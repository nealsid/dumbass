module;

export module parser;

import std;
import tokenizer;

using namespace std;

enum class ASTNodeTypes {
  ROOT,
  VAR_DECL,
  EXPRESSION,
  ASSIGNMENT,
};

struct ASTNode {
  ASTNodeTypes nodeType;
  vector<ASTNode> children;
};

struct ExpressionASTNode {
  vector<ASTNode> children;
};

unique_ptr<ASTNode> parseTokenizedProgram(const vector<Token>& tokenList) {
  ASTNode parent;
  parent.nodeType = ASTNodeTypes::ROOT;
  for (const Token& t : tokenList) {
    if (t.tokenType == TokenType::IDENTIFIER) {
      // Analyze the token to determine type of identifier

    }
  }
  return make_unique<ASTNode>();
}

export vector<ASTNode> ast;
