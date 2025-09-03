#include <entities/data.h>

class IDataProcessor {
public:
  virtual ~IDataProcessor() = default;
  virtual void process(Data&) = 0;
};