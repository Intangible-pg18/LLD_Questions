#pragma once
#include <core/IIterator.h>
#include <core/IBatchIterator.h>
#include <memory>
using namespace std;

class BatchIteratorAdapter : public IBatchIterator {
  unique_ptr<IIterator> inner;
public:
  BatchIteratorAdapter(unique_ptr<IIterator> i);
  bool hasNextBatch() override;
  vector<Data> nextBatch(int limit) override;
  ~BatchIteratorAdapter() override = default;
};