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

  virtual void run_() = 0;

    
};