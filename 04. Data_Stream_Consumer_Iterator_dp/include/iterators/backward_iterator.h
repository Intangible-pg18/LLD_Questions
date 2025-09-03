#pragma once
#include <memory>
#include <vector>
#include <entities/data.h>
#include <core/iiterator.h>

class BackwardIterator : public IIterator {
  shared_ptr<vector<Data>> buf;
  long idx;
public:
  BackwardIterator(shared_ptr<vector<Data>> b);
  bool hasNext() override;
  Data next() override;
  ~BackwardIterator() override = default;
};