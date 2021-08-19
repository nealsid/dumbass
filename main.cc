import std;
import parser;
import tokenizer;

using namespace std;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cout << "Specify filename to tokenize on command-line." << endl;
    return 1;
  }

  auto tokenList = tokenizeFile(argv[1]);

  for (auto t : tokenList) {
    cout << TokenTypeString(t.tokenType) << endl;
  }
}
