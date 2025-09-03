#pragma once
#include <vector>
#include <entities/data.h>
#include <memory>

class IBatchProcessor {
public:
  virtual ~IBatchProcessor() = default;
  virtual void process(vector<Data>&) = 0;
};