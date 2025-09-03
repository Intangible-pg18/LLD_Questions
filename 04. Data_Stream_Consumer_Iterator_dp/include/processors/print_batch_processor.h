#pragma once
#include <entities/data.h>
#include <core/ibatchprocessor.h>
#include <vector>

using namespace std;

class PrintBatchProcessor : public IBatchProcessor {
public:
  void process(vector<Data>& v) override;
  ~PrintBatchProcessor() override = default;
};