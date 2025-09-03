#pragma once
#include <core/ibatchiterator.h>
#include <core/ibatchprocessor.h>
#include <memory>
using namespace std;

class BatchConsumer {
  unique_ptr<IBatchIterator> it;
  shared_ptr<IBatchProcessor> proc;
public:
  BatchConsumer(unique_ptr<IBatchIterator> i, shared_ptr<IBatchProcessor> p);
  bool consumeNextBatch(size_t limit);
  IBatchIterator* iterator();
  ~BatchConsumer() = default;
};