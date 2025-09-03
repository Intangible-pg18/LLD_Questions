#pragma once
#include <core/IIterable.h>
#include <iterators/Forward_Iterator.h>
#include <factory/iterator_kind.h>
#include <factory/iterator_factory.h>
#include <vector>
#include <string>
#include <memory>


using namespace std;

class DataStream : public IIterable {
  shared_ptr<vector<Data>> buf;
public:
  DataStream( vector<string>& in) : buf(make_shared<vector<Data>>()) {
    for (auto& s : in) {
      buf->push_back(Data{s});
    }
  }
  void append( string& s) {
    buf->push_back(Data{s});
  }
  unique_ptr<IIterator> createIterator(IteratorKind k = IteratorKind::ITER_FORWARD) override {
    return IteratorFactory::create(this, k);
  }
  shared_ptr< vector<Data>> getDataShared()  {
    return buf;
  }
  ~DataStream() = default;
};