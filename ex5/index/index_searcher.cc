#include "index/index_searcher.h"

#include <algorithm>
#include <string>
#include <vector>

#include "index/inverted_index_searcher.h"
#include "index/score_doc.h"
#include "index/storage_reader.h"
#include "query/query.h"
#include "util/io.h"

namespace search {

IndexSearcher::IndexSearcher(util::IO* io)
    : storage_reader_(new StorageReader(io)) {
  int id = 0;
  while (io->HasIdForIn(id)) {
    inv_index_searcher_vec_.push_back(new InvertedIndexSearcher(io, id));
    ++id;
  }
}

IndexSearcher::~IndexSearcher() {
  Close();

  for (InvertedIndexSearcher* inv_index_searcher : inv_index_searcher_vec_) {
    delete inv_index_searcher;
  }
  delete storage_reader_;
}

std::vector<ScoreDoc> IndexSearcher::Search(const Query& query, int n) {
  std::vector<ScoreDoc> ans;

  auto greater_score_doc = [](const ScoreDoc& sd1, const ScoreDoc& sd2) {
    return sd1.score() > sd2.score();
  };

  for (InvertedIndexSearcher* inv_index_searcher : inv_index_searcher_vec_) {
    Scorer* scorer = query.NewScorer(inv_index_searcher, storage_reader_);
    while (scorer->Next() < Scorer::kDocExhausted) {
      if ((int)ans.size() > n) {
        std::pop_heap(ans.begin(), ans.end(), greater_score_doc);
        ans.pop_back();
      }
      ans.emplace_back(scorer->doc(), scorer->score());
      std::push_heap(ans.begin(), ans.end(), greater_score_doc);
    }
    delete scorer;
  }
  std::sort_heap(ans.begin(), ans.end(), greater_score_doc);
  return ans;
}

void IndexSearcher::Close() {
  for (InvertedIndexSearcher* inv_index_searcher : inv_index_searcher_vec_) {
    inv_index_searcher->Close();
  }
  storage_reader_->Close();
}

}  // namespace search
