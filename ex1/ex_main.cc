// The binary of this file can be run by 2 ways:
//
// 1. ./ex_main "This is content to be tokenized."
//    In this way, this binary will output all tokens of the string
//    sequentially.
//
// 2. ./ex_main
//    In this way, this binary will output all tokens of the content read from
//    std::cin sequentially.

#include <sstream>
#include <string>

#include "analysis/analyzer.h"
#include "analysis/token.h"
#include "analysis/token_stream.h"
#include "util/logging.h"

int main(int argc, char** argv) {
  search::Analyzer analyzer;
  search::TokenStream* token_stream;
  std::istringstream* istr = nullptr;
  if (argc == 1) {
    token_stream = analyzer.NewTextTokenStream(&std::cin);
  } else {
    istr = new std::istringstream(std::string(argv[1]));
    token_stream = analyzer.NewTextTokenStream(istr);
  }
  while (token_stream->HasNext()) {
    search::Token token = token_stream->Next();
    LOG(INFO) << token.DebugString();
  }
  delete token_stream;
  if (istr) delete istr;
  return 0;
}
