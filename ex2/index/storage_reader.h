#ifndef INDEX_STORAGE_READER_H_
#define INDEX_STORAGE_READER_H_

#include <string>
// TODO: Add headers you need.

#include "util/io.h"

namespace search {

	// StorageReader reads storage data.
	class StorageReader {
	public:
		// Constructor.
		//
		// - io manages istreams, and should keep alive in this class.
		StorageReader(util::IO* io);

		// Closes and deletes istreams.
		virtual ~StorageReader();

		// Closes istreams.
		//
		// This function can be both called and never called, as the destructor will
		// call it. Should not do further operations, after this function is called.
		void Close();

		// Gets the stored data the document whose id is 'doc'.
		//
		// If doc is out of range, it crashes.
		std::string Stored(int doc);

		// Number of documents.
		virtual int num_docs() const {
			// TODO: Implement this function.
			return 0;
		}

	private:
		// TODO: Add members you need.
	};

}  // namespace search

#endif  // INDEX_STORAGE_READER_H_
