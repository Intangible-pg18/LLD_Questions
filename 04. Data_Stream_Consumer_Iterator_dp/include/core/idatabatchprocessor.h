#include <entities/data.h>
#include <vector>

class IDataBatchProcessor {
public:
  virtual ~IDataBatchProcessor() = default;
  virtual void process(vector<Data>&) = 0;
};