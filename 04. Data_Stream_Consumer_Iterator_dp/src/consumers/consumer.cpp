#include <core/iprocessor.h>
#include <consumers/consumer.h>
#include <memory>
using namespace std;

  Consumer::Consumer(unique_ptr<IIterator> i, shared_ptr<IProcessor> p) : it(move(i)), proc(p) {}
  
  bool Consumer::consumeNext() {
    if (!it->hasNext()) return false;
    Data d = it->next();
    proc->process(d);
    return true;
  }
  
  IIterator* Consumer::iterator() {
    return it.get();
  }