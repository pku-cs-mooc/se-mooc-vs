#ifndef INDEX_INDEX_WRITER_H_
#define INDEX_INDEX_WRITER_H_

#include <string>

#include "analysis/analyzer.h"
#include "index/inverted_index_writer.h"
#include "index/storage_writer.h"
#include "util/io.h"

namespace search {

// IndexWriter coordinates to write several inverted indices and storage index.
class IndexWriter {
 public:
  // Constructor.
  //
  // - analyzer specifies how does it tokenize text.
  // - io manages ostreams in writers.
  //
  // analyzer and io should keep alive in this class.
  IndexWriter(const Analyzer& analyzer, util::IO* io)
      : analyzer_(analyzer), io_(io), storage_writer_(new StorageWriter(io)) {}

  // Closes and deletes inverted index writer and storage writer.
  ~IndexWriter();

  // Adds document to inverted index and storage index.
  //
  // This function should only be called once for each doc. It assigns each
  // document with an id which is increasing by one.
  //
  // If doc contains no text, it crashes.
  //
  // Everytime when the memory inverted index is full, saves the inverted index.
  // In this case, it will create a new memory inverted index to write at the
  // beginning of next call.
  void AddDocument(Document* doc);

  // Closes inverted index writer and stroage writer.
  //
  // This function can be both called and never called, as the destructor will
  // call it. Should not add any document, after this function is called.
  void Close();

 private:
  // If available, closes and deletes the inverted index writer.
  void CheckCloseInvertedIndexWriter();

  // If necessary, creates new inverted index writer.
  //
  // The new inverted index id will be bigger by one.
  void CheckCreateInvertedIndexWriter();

  // Judges whether inverted index writer is full now.
  bool IsFull() const;

 private:
  const Analyzer& analyzer_;
  util::IO* const io_;
  int next_inv_index_id_ = 0;  // Next inverted index id.

  // inv_index_writer_ writes and indexes pieces of posting data.
  InvertedIndexWriter* inv_index_writer_ = nullptr;  // OWNED

  // Next document id, which will be assigned to the next added document.
  int next_doc_id_ = 0;

  // storage_writer_ writes and indexes storage data.
  StorageWriter* const storage_writer_;  // OWNED
};

}  // namespace search

#endif  // INDEX_INDEX_WRITER_H_
