#include <processors/print_batch_processor.h>
#include <iostream>

using namespace std;

 void PrintBatchProcessor::process(vector<Data>& v) {
    for (auto& d : v) {
      cout << d.payload << endl;
    }
  }