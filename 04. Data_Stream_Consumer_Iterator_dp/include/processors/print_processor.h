#pragma once
#include <core/iprocessor.h>
#include <iostream>

using namespace std;

class PrintProcessor : public IProcessor {
public:
  void process(Data& d) override;
  ~PrintProcessor() override = default;
};