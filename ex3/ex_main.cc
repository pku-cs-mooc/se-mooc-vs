// The binary of this file can be run by ./ex_main
//
// It builds inverted index for `data`, and outputs human-readable inverted
// index twice:
// * The first one is the in-memory inverted index.
// * The second one is the on-disk inverted index.

#include <string>
#include <vector>

#include "analysis/analyzer.h"
#include "index/document.h"
#include "index/inverted_index_writer.h"
#include "util/logging.h"
#include "util/mem_io.h"

int main(int argc, char** argv) {
  std::vector<std::string> data = { "1 2 3 4", "2 3 ", "3,4" };

  search::Analyzer analyzer;
  search::util::MemIO mem_io;
  search::InvertedIndexWriter writer(analyzer, &mem_io, 0);
  int next_doc_id = 0;
  for (const std::string& item : data) {
    search::Document doc;
    doc.set_doc_id(next_doc_id++);
    doc.set_text(item);
    writer.AddDocument(&doc);
  }
  LOG(INFO) << "Inverted index:" << std::endl << writer.DebugString();

  writer.WriteAndClose();

  auto termIn = mem_io.NewTermIn(0);
  auto postingIn = mem_io.NewPostingIn(0);
  int postingSize = mem_io.kTermSize + sizeof(int) + sizeof(int);
  char *buffer = new char[postingSize];
  LOG(INFO) << "\tTERM\tPOSTING_LIST_POSITION\tdf";
  while (termIn->good()) {
    if (termIn->read(buffer, mem_io.kTermSize)) {
      buffer[mem_io.kTermSize] = '\0';
      std::string term(buffer);
      termIn->read(buffer, sizeof(int));
      int plp = *(int*)buffer;
      termIn->read(buffer, sizeof(int));
      int df = *(int*)buffer;
      LOG(INFO) << '\t' << term << "\t\t" << plp << "\t\t" << df;
      postingIn->seekg(plp);
      std::ostringstream debugString;
      for (int i = 0; i < df; i++) {
        postingIn->read(buffer, sizeof(int));
        int docId = *(int*)buffer;
        postingIn->read(buffer, sizeof(int));
        int tf = *(int*)buffer;
        debugString << '<' << docId << ',' << tf << '>' << ' ';
      }
      LOG(INFO) << debugString.str();
    }
  }
  mem_io.CloseAndDeletePostingIn(postingIn);
  mem_io.CloseAndDeleteTermIn(termIn);
  return 0;
}
