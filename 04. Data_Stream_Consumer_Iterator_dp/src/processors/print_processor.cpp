#include <core/iprocessor.h>
#include <processors/print_processor.h>
#include <iostream>

using namespace std;

  void PrintProcessor::process(Data& d) {
    cout << d.payload << endl;
  }