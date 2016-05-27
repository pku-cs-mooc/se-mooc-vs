#ifndef INDEX_SCORE_DOC_H_
#define INDEX_SCORE_DOC_H_

#include <string>

// ScoreDoc records a document's id and its score.
class ScoreDoc {
 public:
  ScoreDoc(int doc, float score) : doc_(doc), score_(score) {}

  void set_doc(int doc) { doc_ = doc; }
  int doc() const { return doc_; }

  void set_score_(int score) { score_ = score; }
  float score() const { return score_; }

  std::string DebugString() const {
    return "<" + std::to_string(doc_) + ":" + std::to_string(score_) + ">";
  }

 private:
  int doc_;
  float score_;
};

#endif  // INDEX_SCORE_DOC_H_
