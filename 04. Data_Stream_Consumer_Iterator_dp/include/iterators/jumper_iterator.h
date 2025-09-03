#pragma once
#include <memory>
#include <vector>
#include <entities/data.h>
#include <core/iiterator.h>

using namespace std;

class JumperIterator : public IIterator {
  shared_ptr<const vector<Data>> buf;
  int idx;
  int step;
public:
  JumperIterator(shared_ptr< vector<Data>> b, int s, int start = 0);
  bool hasNext() override;
  Data next() override;
  ~JumperIterator() override = default;
};