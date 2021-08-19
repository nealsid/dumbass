module;

import std;

export module tokenizer;

using namespace std;

using TokenLocation = std::pair<int, int>;

export enum class TokenType {
  IDENTIFIER,
  LEFT_CURLY_BRACE,
  RIGHT_CURLY_BRACE,
  LEFT_PAREN,
  RIGHT_PAREN,
  STRING_LITERAL,
  UNKNOWN
};

export struct Token {
  bool isOneChar = false;
  char ch = '\0';
  TokenType tokenType = TokenType::UNKNOWN;
  int line_number = -1;
  int column_number = -1;
  int begin_index = -1;
  int end_index = -1; // not inclusive
};

vector<char> program; // Used for keeping program text in memory.
vector<Token> tokenList; // Tokens used for parsing into AST.

const vector<char> INTRA_TOKEN_WHITESPACE_CHARACTERS = { ' ', '\t', '\n', '\r' };

auto tokens = std::array{
  Token{false, '\0', TokenType::IDENTIFIER},
  Token{true, '{', TokenType::LEFT_CURLY_BRACE},
  Token{true, '}', TokenType::RIGHT_CURLY_BRACE},
  Token{true, '(', TokenType::LEFT_PAREN},
  Token{true, ')', TokenType::RIGHT_PAREN},
  Token{false, '\0', TokenType::STRING_LITERAL},
};

int GetEndIndexOfCurrentToken(int token_start_index);
Token createTokenFromTextFragment(int start_idx, int end_idx);

bool IsWhitespace(char& ch) {
  return find(INTRA_TOKEN_WHITESPACE_CHARACTERS.begin(),
	      INTRA_TOKEN_WHITESPACE_CHARACTERS.end(),
	      ch) != INTRA_TOKEN_WHITESPACE_CHARACTERS.end();
}

export const vector<Token>& tokenizeFile(const string& filename) {
  program.clear();

  auto file_size = filesystem::file_size(filename);
  program.resize(file_size);
  ifstream input(filename);
  input.read(program.data(), file_size);
  input.close();

  // Main loop
  int idx = 0;

  do {
    while (IsWhitespace(program[idx])) {
      ++idx;
    }
    auto endOfCurrentToken = GetEndIndexOfCurrentToken(idx);
    tokenList.push_back(createTokenFromTextFragment(idx, endOfCurrentToken));
    idx = endOfCurrentToken;
  } while (idx < program.size());

  return tokenList;
}

bool IsOneCharacterToken(char currentToken) {
  return std::find_if(tokens.begin(), tokens.end(),
		      [&] (auto token) {
			return token.ch == currentToken && token.isOneChar;
		      }) != tokens.end();
}

int AdvanceToNextQuote(int current_token_idx) {
  assert(program[current_token_idx] == '"');
  int token = current_token_idx + 1;
  while (program[token] != '\0') {
    if (program[token] == '"' && program[token - 1] != '\\') {
      return token + 1;
    }
    token++;
  }
  return token;
}

int AdvanceToNextWhitespaceOrOneCharacterToken(int current_token_idx) {
  int token = current_token_idx;
  while (program[token] != '\0' && !IsWhitespace(program[token]) && !IsOneCharacterToken(program[token])) {
    token++;
  }

  return token;
}

Token createTokenFromTextFragment(int start_idx, int end_idx) {
  for (auto t : tokens) {
    if (end_idx - start_idx == 1 &&
	t.isOneChar && t.ch == char(program[start_idx])) {
      return t;
    }
  }

  // not a one char token
  if (program[start_idx] == '"' && program[end_idx - 1] == '"') {
    return tokens[5];
  }
  return tokens[0];
}

int GetEndIndexOfCurrentToken(int token_start_idx) {
  char currentTokenBegin = program[token_start_idx];
  if (IsOneCharacterToken(currentTokenBegin)) {
    return token_start_idx + 1;
  }

  if (currentTokenBegin != '"') {
    return AdvanceToNextWhitespaceOrOneCharacterToken(token_start_idx);
  } else {
    return AdvanceToNextQuote(token_start_idx);
  }
}

export const string TokenTypeString(TokenType t) {
  switch(t) {
  case TokenType::IDENTIFIER:
    return "Identifier";
  case TokenType::LEFT_CURLY_BRACE:
    return "Left Curly";
  case TokenType::RIGHT_CURLY_BRACE:
    return "Right Curly";
  case TokenType::LEFT_PAREN:
    return "Left Paren";
  case TokenType::RIGHT_PAREN:
    return "Right Paren";
  case TokenType::STRING_LITERAL:
    return "String Literal";
  case TokenType::UNKNOWN:
    return "Unknown";
  }
}
