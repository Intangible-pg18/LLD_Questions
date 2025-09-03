#include <iterators/backward_iterator.h>
#include <memory>

BackwardIterator::BackwardIterator(shared_ptr<vector<Data>> b) : buf(b), idx(static_cast<long>(b->size()) - 1) {}

bool BackwardIterator::hasNext() {
    return idx >= 0 && buf->size() > 0;
}

Data BackwardIterator::next() {
    return (*buf)[idx--];
}