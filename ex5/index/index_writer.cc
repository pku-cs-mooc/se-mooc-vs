#include "index/index_writer.h"

#include <string>

#include "index/inverted_index_writer.h"

namespace search {

IndexWriter::~IndexWriter() {
  Close();
  delete storage_writer_;
}

void IndexWriter::AddDocument(Document* doc) {
  if (IsFull()) {
    CheckCloseInvertedIndexWriter();
  }
  CheckCreateInvertedIndexWriter();

  doc->set_doc_id(next_doc_id_++);
  inv_index_writer_->AddDocument(doc);

  storage_writer_->AddStorage(doc->stored());
}

void IndexWriter::Close() {
  CheckCloseInvertedIndexWriter();
  storage_writer_->Close();
}

void IndexWriter::CheckCloseInvertedIndexWriter() {
  if (inv_index_writer_ == nullptr) return;
  delete inv_index_writer_;  // It writes and closes when destructed.
  inv_index_writer_ = nullptr;
}

void IndexWriter::CheckCreateInvertedIndexWriter() {
  if (inv_index_writer_) return;
  inv_index_writer_ =
      new InvertedIndexWriter(analyzer_, io_, next_inv_index_id_++);
}

bool IndexWriter::IsFull() const {
  // NOTE: We keep it returning false at this moment, to make IndexWriter only
  // write one inverted index.
  return false;
}

}  // namespace search
