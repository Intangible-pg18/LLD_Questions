#pragma once
#include <core/IIterable.h>
#include <core/IBatchIterator.h>
#include <entities/datastream.h>
#include <iterators/Forward_Iterator.h>
#include <iterators/Backward_Iterator.h>
#include <iterators/Bidirectional_Iterator.h>
#include <iterators/Jumper_Iterator.h>
#include <iterators/Batch_Iterator_Adapter.h>
#include <factory/iterator_kind.h>

using namespace std;

class IteratorFactory {
public:
  static unique_ptr<IIterator> create(IIterable* src, IteratorKind k, int step = 1);
  static unique_ptr<IBatchIterator> createBatch(IIterable* src, IteratorKind k, int offset = 0, int step = 1);
};