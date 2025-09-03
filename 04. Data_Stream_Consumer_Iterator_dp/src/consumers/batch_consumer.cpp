#include <core/ibatchiterator.h>
#include <core/ibatchprocessor.h>
#include <consumers/batch_consumer.h>
#include <memory>
using namespace std;

 BatchConsumer::BatchConsumer(unique_ptr<IBatchIterator> i, shared_ptr<IBatchProcessor> p)
    : it(move(i)), proc(p) {}

  bool BatchConsumer::consumeNextBatch(size_t limit) {
    if (!it->hasNextBatch()) return false;
    vector<Data> v = it->nextBatch(limit);
    proc->process(v);
    return v.size() > 0;
  }
  IBatchIterator* BatchConsumer::iterator() {
    return it.get();
  }