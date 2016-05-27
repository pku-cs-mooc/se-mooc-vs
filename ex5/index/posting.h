#ifndef INDEX_POSTING_H_
#define INDEX_POSTING_H_

#include <iostream>
#include <string>

namespace search {

// Posting records a term-related document infomation.
class Posting {
 public:
  Posting(std::istream* in) { Load(in); }
  Posting(int doc_id) : Posting(doc_id, 0) {}
  Posting(int doc_id, int tf) : doc_id_(doc_id), tf_(tf) {}

  int doc_id() const { return doc_id_; }
  int tf() const { return tf_; }

  // Increments tf by one.
  void tf_increment() { ++tf_; }

  // Loads a posting from istream.
  void Load(std::istream* in) {
    in->read((char*)&doc_id_, sizeof(doc_id_));
    in->read((char*)&tf_, sizeof(tf_));
  }

  // Writes a posting to ostream.
  void Write(std::ostream* out) const {
    out->write((char*)&doc_id_, sizeof(doc_id_));
    out->write((char*)&tf_, sizeof(tf_));
  }

  bool operator==(const Posting& posting) const {
    return doc_id_ == posting.doc_id_ && tf_ == posting.tf_;
  }

  std::string DebugString() const {
    return "<" + std::to_string(doc_id_) + ":" + std::to_string(tf_) + ">";
  }

 private:
  int doc_id_;  // Document id.
  int tf_;      // Term frequency.
};

}  // namespace search

#endif  // INDEX_POSTING_H_
