#include <memory>
#include <vector>
#include <entities/data.h>
#include <iterators/jumper_iterator.h>


JumperIterator::JumperIterator(shared_ptr< vector<Data>> b, int s, int start) : buf(b), idx(start), step(s ? s : 1) {}

  bool JumperIterator::hasNext() {
    return idx < buf->size();
  }

  Data JumperIterator::next() {
    Data d = (*buf)[idx];
    idx += step;
    return d;
  }