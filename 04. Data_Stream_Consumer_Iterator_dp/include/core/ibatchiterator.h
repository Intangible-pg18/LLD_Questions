#pragma once
#include <entities/data.h>
#include <vector>

class IBatchIterator {
public:
  virtual ~IBatchIterator() = default;
  virtual bool hasNextBatch() = 0;
  virtual vector<Data> nextBatch(int limit) = 0;
};