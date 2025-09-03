#pragma once
#include <core/iiterator.h>
#include <core/iprocessor.h>
#include <memory>
using namespace std;

class Consumer {
  unique_ptr<IIterator> it;
  shared_ptr<IProcessor> proc;
public:
  Consumer(unique_ptr<IIterator> i, shared_ptr<IProcessor> p);
  bool consumeNext();
  IIterator* iterator();
  ~Consumer() = default;
};