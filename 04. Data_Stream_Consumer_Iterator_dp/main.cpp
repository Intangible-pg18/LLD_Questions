#include <vector>
#include <string>
#include "entities/datastream.h"
#include <iostream>
#include "factory/iterator_factory.h"
#include "processors/print_processor.h"
#include "consumers/consumer.h"
#include "factory/iterator_kind.h"
#include "core/ibatchprocessor.h"
#include "consumers/batch_consumer.h"
#include "processors/print_batch_processor.h"


int main() {
  vector<string> input{
    "one","two","three","four","five",
    "six","seven","eight","nine","ten"
  };

  DataStream ds(input);

  cout << "Single-item forward consumption:" << endl;
  unique_ptr<IIterator> it1 = IteratorFactory::create(&ds, IteratorKind::ITER_FORWARD);
  shared_ptr<IProcessor> proc1 = make_shared<PrintProcessor>();
  Consumer c1(move(it1), proc1);
  while (c1.consumeNext()) {}

  cout << endl << "Batch consumption (offset=3, limit=4):" << endl;
  unique_ptr<IBatchIterator> bi = IteratorFactory::createBatch(&ds, IteratorKind::ITER_FORWARD, 3);
  shared_ptr<IBatchProcessor> batchProc = make_shared<PrintBatchProcessor>();
  BatchConsumer bc(move(bi), batchProc);
  while (bc.consumeNextBatch(4)) {}

  cout << endl << "Jumper iterator (step=2):" << endl;
  unique_ptr<IIterator> itJump = IteratorFactory::create(&ds, IteratorKind::ITER_JUMPER, 2);
  Consumer cJump(move(itJump), proc1);
  while (cJump.consumeNext()) {}

  cout << endl << "Bidirectional sample:" << endl;
  unique_ptr<IIterator> itBidi = IteratorFactory::create(&ds, IteratorKind::ITER_BIDIRECTIONAL);
  IBidirectionalIterator* bidiRaw = dynamic_cast<IBidirectionalIterator*>(itBidi.get());
  if (bidiRaw) {
    if (bidiRaw->hasNext()) {
      Data d = bidiRaw->next();
      cout << d.payload << endl;
    }
    if (bidiRaw->hasNext()) {
      Data d = bidiRaw->next();
      cout << d.payload << endl;
    }
    if (bidiRaw->hasPrev()) {
      Data d = bidiRaw->prev();
      cout << d.payload << endl;
    }
  }

  return 0;
}