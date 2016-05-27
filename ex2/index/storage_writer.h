#ifndef INDEX_STORAGE_WRITER_H_
#define INDEX_STORAGE_WRITER_H_

#include <string>
// TODO: Add headers you need.

#include "util/io.h"

namespace search {

	// StorageWriter writes and indexes storage data.
	class StorageWriter {
	public:
		// Constructor.
		//
		// - io manages ostreams, and should keep alive in this class.
		StorageWriter(util::IO* io) {
			// TODO: Implement constructor.
		}

		// Closes and deletes ostreams.
		~StorageWriter();

		// Closes ostreams.
		//
		// This function can be both called and never called, as the destructor will
		// call it. Should not add any document, after this function is called.
		void Close();

		// Adds stored data into the storage ostreams.
		void AddStorage(const std::string& stored);

	private:
		// TODO: Add member you need.
	};

}  // namespace search

#endif  // INDEX_STORAGE_WRITER_H_
