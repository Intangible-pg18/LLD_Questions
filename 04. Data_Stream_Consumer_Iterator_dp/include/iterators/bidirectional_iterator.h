#pragma once
#include <core/IBidirectionalIterator.h>
#include <vector>
#include <memory>

using namespace std;

class BidirectionalIterator : public IBidirectionalIterator {
  shared_ptr< vector<Data>> buf;
  int idx;
public:
  BidirectionalIterator(shared_ptr< vector<Data>> b, int start = 0);
  bool hasNext() override;
  Data next() override;
  bool hasPrev() override;
  Data prev() override;
  ~BidirectionalIterator() override = default;
};