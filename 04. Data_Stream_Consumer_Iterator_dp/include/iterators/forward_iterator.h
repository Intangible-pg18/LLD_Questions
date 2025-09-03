#pragma once
#include <memory>
#include <vector>
#include <entities/data.h>
#include <core/iiterator.h>

using namespace std;

class ForwardIterator : public IIterator {
  shared_ptr<vector<Data>> buf;
  int idx;
public:
  ForwardIterator(shared_ptr<vector<Data>> b);
  bool hasNext() override;
  Data next() override;
  ~ForwardIterator() override = default;
};