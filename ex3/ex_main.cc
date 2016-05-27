#include <string>
#include <vector>

#include "analysis/analyzer.h"
#include "index/document.h"
#include "index/inverted_index_writer.h"
#include "util/logging.h"
#include "util/mem_io.h"

int main(int argc, char** argv) {
  std::vector<std::string> data = {"1 2 3 4", "2 3 ", "3,4"};

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
  return 0;
}
