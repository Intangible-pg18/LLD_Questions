#pragma once
#include <core/iiterator.h>

class IBidirectionalIterator : public IIterator {
public:
  virtual ~IBidirectionalIterator() = default;
  virtual bool hasPrev() = 0;
  virtual Data prev() = 0;
};