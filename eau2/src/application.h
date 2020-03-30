#pragma once
#include "dataframe.h"
#include "kvstore.h"
#include "object.h"

class Application : public Object {
protected:
  KVStore<DataFrame *> kv;

public:
  Application(size_t idx) {
    kv = KVStore<DataFrame *>(idx);
  }

  ~Application() {
  }

  virtual void run_() = 0;

  virtual size_t this_node() {};    
};