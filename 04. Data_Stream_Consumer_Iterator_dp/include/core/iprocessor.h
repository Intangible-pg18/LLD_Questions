#pragma once
#include <entities/data.h>

class IProcessor {
public:
  virtual ~IProcessor() = default;
  virtual void process(Data&) = 0;
};