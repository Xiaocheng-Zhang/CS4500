#pragma once
#include "application.h"
#include "object.h"
#include <iostream>
#include <vector>
#include <thread>

using namespace std;
/**
 * A fake network layer that simulate the net work connection has been build.
 */
class NetworkLayer : public Object {
private: 
  vector<Application *> app_vec;
public:
    NetworkLayer() : Object() {}

    ~NetworkLayer() {}

    void add(Application *app) {
        app_vec.push_back(app);
    }

    static void request_check(vector<Application*> *vc) {
        while(1) {
            for (size_t i = 0; i < vc->size(); i++) {
                KVStore tmp = vc->at(i)->get_kv();
                if (tmp.request_check) {
                    Key request_key = tmp.request_key;
                    for (size_t j = 0; j < vc->size(); j++) {
                        if (request_key.get_home_address() == vc->at(j)->this_node()) {
                            // haven't finish yet
                        }
                    }
                }
            }
        }
    }

    void tracking() {
        thread run_thread(request_check, &app_vec);

        run_thread.join();
    }
};