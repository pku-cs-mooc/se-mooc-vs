#include <fstream>
#include <string>
#include <vector>

#include "analysis/analyzer.h"
#include "index/document.h"
#include "index/index_searcher.h"
#include "index/index_writer.h"
#include "index/score_doc.h"
#include "query/conjunction_query.h"
#include "query/disjunction_query.h"
#include "query/query.h"
#include "query/req_excl_query.h"
#include "query/term_query.h"
#include "util/file_io.h"
#include "util/logging.h"
#include "util/util.h"

namespace search {
namespace {

void Index(const std::string& data_path, const std::string& index_path) {
  Analyzer analyzer;
  util::FileIO file_io(index_path);
  IndexWriter writer(analyzer, &file_io);

  auto add_to_index = [&writer](const std::string& full_path) {
    if (full_path.find(".cc") == std::string::npos &&
        full_path.find(".h") == std::string::npos)
      return;
    Document doc;
    doc.set_text(new std::ifstream(full_path));
    doc.set_stored(full_path);
    writer.AddDocument(&doc);
  };
  util::TraversePath(data_path, add_to_index);

  writer.Close();
}

void Search(const Query& query, IndexSearcher* searcher) {
  std::vector<ScoreDoc> tops = searcher->Search(query);
  LOG(INFO) << "Total hits(" << tops.size() << ") for " << query.DebugString()
            << ":";
  for (const ScoreDoc& doc : tops) {
    LOG(INFO) << "#" << doc.doc() << "(" << doc.score()
              << "): " << searcher->Stored(doc.doc());
  }
}

}  // namespace
}  // namespace search

int main(int argc, char** argv) {
  std::string base_path = search::util::BasePath(argv[0]);

#ifdef _WIN32
  base_path[base_path.length() - 1] = '\0';
  base_path = search::util::BasePath(base_path);
  std::string testdata_path = base_path;
  std::string index_path = base_path + "bin\\index\\";
  search::util::System("if exist \"" + index_path + "\" rmdir /Q /S \"" + index_path + "\"");
  search::util::System("mkdir \"" + index_path + "\"");
#else
  std::string testdata_path = base_path;
  std::string index_path = base_path + "bin/index/";
  search::util::System("rm -rf " + index_path);
  search::util::System("mkdir -p " + index_path);
#endif

  search::Index(testdata_path, index_path);

  search::util::FileIO file_io(index_path);
  search::IndexSearcher searcher(&file_io);

  search::TermQuery t1("scoredoc");
  search::TermQuery t2("system");
  search::Search(t1, &searcher);
  search::Search(t2, &searcher);
  search::Search(search::ConjunctionQuery({&t1, &t2}), &searcher);
  search::Search(search::DisjunctionQuery({&t1, &t2}), &searcher);
  search::Search(search::ReqExclQuery({&t1, &t2}), &searcher);
  searcher.Close();

  return 0;
}
