#include <core/IIterator.h>
#include <core/IBatchIterator.h>
#include <iterators/Batch_Iterator_adapter.h>
#include <core/IIterator.h>
#include <memory>


  BatchIteratorAdapter::BatchIteratorAdapter(unique_ptr<IIterator> i) : inner(move(i)) {}
  
  bool BatchIteratorAdapter::hasNextBatch() {
    return inner->hasNext();
  }

  vector<Data> BatchIteratorAdapter::nextBatch(int limit) {
    vector<Data> batch;
    while(limit-- && inner->hasNext()) {
        batch.push_back(inner->next());
    }
    return batch;
  }