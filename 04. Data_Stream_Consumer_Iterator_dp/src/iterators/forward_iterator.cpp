#include <iterators/forward_iterator.h>
#include <memory>

ForwardIterator::ForwardIterator(shared_ptr<vector<Data>> b) : buf(b), idx(0) {}

bool ForwardIterator::hasNext() {
    return idx < buf->size();
}

Data ForwardIterator::next() {
    return (*buf)[idx++];
}