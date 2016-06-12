#ifndef UTIL_MEM_IO_H_
#define UTIL_MEM_IO_H_

#include <sstream>
#include <string>

#include "util/io.h"
#include "util/logging.h"

namespace search {
  namespace util {

    // IO for memory.
    class MemIO : public IO {
    public:
      MemIO() = default;
      MemIO(int term_size) : IO(term_size) {}

      // Term.
      std::istream* NewTermIn(int id) const override {
        return HasIdForIn(id) ? new std::istringstream(term_) : nullptr;
      }

      void CloseAndDeleteTermIn(std::istream* in) const override { delete in; }

      std::ostream* NewTermOut(int id) const override {
        CheckIdForOut(id);
        return new std::ostringstream();
      }

      void CloseAndDeleteTermOut(std::ostream* out) override {
        if (std::ostringstream* sout = dynamic_cast<std::ostringstream*>(out)) {
          term_ = sout->str();
        }
        delete out;
      }

      // Posting.
      std::istream* NewPostingIn(int id) const override {
        return HasIdForIn(id) ? new std::istringstream(posting_) : nullptr;
      }

      void CloseAndDeletePostingIn(std::istream* in) const override { delete in; }

      std::ostream* NewPostingOut(int id) const override {
        CheckIdForOut(id);
        return new std::ostringstream();
      }

      void CloseAndDeletePostingOut(std::ostream* out) override {
        if (std::ostringstream* sout = dynamic_cast<std::ostringstream*>(out)) {
          posting_ = sout->str();
        }
        delete out;
      }

      // Storage Index.
      std::istream* NewStorageIndexIn() const override {
        return new std::istringstream(storage_index_);
      }

      void CloseAndDeleteStorageIndexIn(std::istream* in) const override {
        delete in;
      }

      std::ostream* NewStorageIndexOut() const override {
        return new std::ostringstream();
      }

      void CloseAndDeleteStorageIndexOut(std::ostream* out) override {
        if (std::ostringstream* sout = dynamic_cast<std::ostringstream*>(out)) {
          storage_index_ = sout->str();
        }
        delete out;
      }

      // Storage.
      std::istream* NewStorageIn() const override {
        return new std::istringstream(storage_);
      }

      void CloseAndDeleteStorageIn(std::istream* in) const override { delete in; }

      std::ostream* NewStorageOut() const override {
        return new std::ostringstream();
      }

      void CloseAndDeleteStorageOut(std::ostream* out) override {
        if (std::ostringstream* sout = dynamic_cast<std::ostringstream*>(out)) {
          storage_ = sout->str();
        }
        delete out;
      }

      bool HasIdForIn(int id) const override { return id == 0; }

      // Data.
      const std::string& term() const { return term_; }
      const std::string& posting() const { return posting_; }
      const std::string& storage_index() const { return storage_index_; }
      const std::string& storage() const { return storage_; }

    private:
      void CheckIdForOut(int id) const {
        CHECK(id == 0) << "Unimplement for id != 0.";
      }

    private:
      std::string term_;
      std::string posting_;
      std::string storage_index_;
      std::string storage_;
    };

  }  // namespace util
}  // namespace search

#endif  // UTIL_IO_H_