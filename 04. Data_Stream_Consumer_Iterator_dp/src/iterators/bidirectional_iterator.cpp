#include <iterators/Bidirectional_Iterator.h>
#include <vector>
#include <memory>

using namespace std;

BidirectionalIterator::BidirectionalIterator(shared_ptr< vector<Data>> b, int start) : buf(b), idx(start) {}
  
bool BidirectionalIterator::hasNext() {
    return idx < buf->size();
  }
  Data BidirectionalIterator::next() {
    return (*buf)[idx++];
  }
  bool BidirectionalIterator::hasPrev() {
    return idx > 0;
  }
  Data BidirectionalIterator::prev() {
    return (*buf)[--idx];
  }