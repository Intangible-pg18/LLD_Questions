#pragma once
#include <entities/data.h>

class IIterator {
public:
  virtual ~IIterator() = default;
  virtual bool hasNext() = 0;
  virtual Data next() = 0;
};