#ifndef UTIL_FILE_IO_H_
#define UTIL_FILE_IO_H_

#include <fstream>
#include <iostream>
#include <string>

#include "util/io.h"

#ifdef _WIN32
#define pathDeli '\\'
#else
#define pathDeli '/'
#endif


namespace search {
namespace util {

// IO for file.
class FileIO : public IO {
 public:
  FileIO(const std::string& root_path)
      : FileIO(root_path, IO::kDefaultTermSize) {}

  FileIO(const std::string& root_path, int term_size) : IO(term_size) {
    if (root_path.empty() || root_path.back() == pathDeli) {
      root_path_ = root_path;
    } else {
      root_path_ = root_path + pathDeli;
    }
  }

  // Term.
  std::istream* NewTermIn(int id) const override {
    return HasIdForIn(id) ? new std::ifstream(GetTermPath(id), std::ios::binary)
                          : nullptr;
  }

  void CloseAndDeleteTermIn(std::istream* in) const override {
    CloseAndDeleteIn(in);
  }

  std::ostream* NewTermOut(int id) const override {
    return new std::ofstream(GetTermPath(id), std::ios::binary);
  }

   void CloseAndDeleteTermOut(std::ostream* out) override {
    CloseAndDeleteOut(out);
  }

  // Posting.
  std::istream* NewPostingIn(int id) const override {
    return HasIdForIn(id)
               ? new std::ifstream(GetPostingPath(id), std::ios::binary)
               : nullptr;
  }

  void CloseAndDeletePostingIn(std::istream* in) const override {
    CloseAndDeleteIn(in);
  }

  std::ostream* NewPostingOut(int id) const override {
    return new std::ofstream(GetPostingPath(id), std::ios::binary);
  }

  void CloseAndDeletePostingOut(std::ostream* out) override {
    CloseAndDeleteOut(out);
  }


  // Storage Index.
  std::istream* NewStorageIndexIn() const override {
    return new std::ifstream(GetStorageIndexPath(), std::ios::binary);
  }

   void CloseAndDeleteStorageIndexIn(std::istream* in) const override {
    CloseAndDeleteIn(in);
  }

  std::ostream* NewStorageIndexOut() const override {
    return new std::ofstream(GetStorageIndexPath(), std::ios::binary);
  }

  void CloseAndDeleteStorageIndexOut(std::ostream* out) override {
    CloseAndDeleteOut(out);
  }

  // Storage.
  std::istream* NewStorageIn() const override {
    return new std::ifstream(GetStoragePath(), std::ios::binary);
  }

  void CloseAndDeleteStorageIn(std::istream* in) const override {
    CloseAndDeleteIn(in);
  }

  std::ostream* NewStorageOut() const override {
    return new std::ofstream(GetStoragePath(), std::ios::binary);
  }

  void CloseAndDeleteStorageOut(std::ostream* out) override {
    CloseAndDeleteOut(out);
  }

  bool HasIdForIn(int id) const override {
    return std::ifstream(GetTermPath(id), std::ios::binary) &&
           std::ifstream(GetPostingPath(id), std::ios::binary);
  }

  // Paths.
  std::string GetTermPath(int id) const {
    return root_path_ + "invidx." + std::to_string(id) + ".term";
  }

  std::string GetPostingPath(int id) const {
    return root_path_ + "invidx." + std::to_string(id) + ".posting";
  }

  std::string GetStorageIndexPath() const {
    return root_path_ + "storage.index";
  }

  std::string GetStoragePath() const { return root_path_ + "storage.content"; }

 private:
  void CloseAndDeleteIn(std::istream* in) const {
    if (std::ifstream* fin = dynamic_cast<std::ifstream*>(in)) {
      fin->close();
    }
    delete in;
  }

  void CloseAndDeleteOut(std::ostream* out) const {
    if (std::ofstream* fout = dynamic_cast<std::ofstream*>(out)) {
      fout->close();
    }
    delete out;
  }

 private:
  // Unless root_path_ is empty, it ends up with "/".
  std::string root_path_;  // ASSIGNED ONCE
};

}  // namespace util
}  // namespace search

#endif  // UTIL_FILE_IO_H_