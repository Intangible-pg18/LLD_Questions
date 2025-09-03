#include <core/IIterable.h>
#include <core/IBatchIterator.h>
#include <entities/datastream.h>
#include <iterators/Forward_Iterator.h>
#include <iterators/Backward_Iterator.h>
#include <iterators/Bidirectional_Iterator.h>
#include <iterators/Jumper_Iterator.h>
#include <iterators/Batch_Iterator_Adapter.h>
#include <factory/Iterator_Factory.h>
#include <factory/Iterator_kind.h>

using namespace std;

  unique_ptr<IIterator> IteratorFactory::create(IIterable* src, IteratorKind k, int step) {
    DataStream* ds = dynamic_cast<DataStream*>(src);
    if (!ds) return src->createIterator();
    shared_ptr<vector<Data>> v = ds->getDataShared();
    switch (k) {
      case IteratorKind::ITER_FORWARD:
        return make_unique<ForwardIterator>(v);
      case IteratorKind::ITER_BACKWARD:
        return make_unique<BackwardIterator>(v);
      case IteratorKind::ITER_BIDIRECTIONAL:
        return make_unique<BidirectionalIterator>(v);
      case IteratorKind::ITER_JUMPER:
        return make_unique<JumperIterator>(v, step);
      default:
        return make_unique<ForwardIterator>(v);
    }
  }
  unique_ptr<IBatchIterator> IteratorFactory::createBatch(IIterable* src, IteratorKind k, int offset, int step) {
    unique_ptr<IIterator> it = create(src, k, step);
    while (offset > 0 && it->hasNext()) {
      it->next();
      --offset;
    }
    return make_unique<BatchIteratorAdapter>(move(it));
  }