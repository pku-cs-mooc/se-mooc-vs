#include <iostream>
#include <string>
#include <vector>

#include "index/posting.h"
#include "index/storage_reader.h"
#include "scorer/scorer.h"
#include "scorer/term_scorer.h"
#include "util/logging.h"
#include "util/mem_io.h"

namespace search {
namespace {

class MockStorageReader : public StorageReader {
 public:
  MockStorageReader(util::MemIO* io) : StorageReader(io) {}

  int num_docs() const override { return 1234; }
};

}  // namespace search
}  // namespace

int main(int argc, char** argv) {
  std::vector<search::Posting> data = {
      search::Posting(2, 4),  search::Posting(17, 8), search::Posting(21, 3),
      search::Posting(29, 1), search::Posting(30, 5), search::Posting(37, 2)};

  search::util::MemIO mem_io;
  std::ostream* out = mem_io.NewPostingOut(0);
  for (const search::Posting& posting : data) {
    posting.Write(out);
  }
  mem_io.ClosePostingOut(out);
  delete out;

  std::istream* in = mem_io.NewPostingIn(0);
  search::MockStorageReader reader(&mem_io);
  search::TermScorer scorer(data.size(), in, 0, &reader);

  while (scorer.Next() < Scorer::kDocExhausted) {
    LOG(INFO) << "doc: " << scorer.doc() << ", score: " << scorer.score();
  }

  mem_io.ClosePostingIn(in);
  delete in;

  return 0;
}
