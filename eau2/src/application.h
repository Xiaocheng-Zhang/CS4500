#pragma once
#include "dataframe.h"
#include "kvstore.h"
#include "object.h"

/**
 * Application class that followed the requirement from the given test.
 */
class Application : public Object {
protected:
  KVStore<DataFrame *> kv;
  size_t home_address;

public:
  Application(size_t idx) {
    kv = KVStore<DataFrame *>(idx);
    home_address = idx;
  }

  /**
   * Deconstructor
   */
  ~Application() {}

  /**
   * pure virtual method that require all subclasses follow the requirements
   * from custormer's example test.
   */
  virtual void run_() = 0;

  /**
   * get the node home address which saved in both Application and the KVStore.
   */
  virtual size_t this_node() { return home_address; };
};