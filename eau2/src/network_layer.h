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
                if (vc->at(i)->get_kv().request_check) {
                    
                }
            }
        }
    }

    void tracking() {
        thread run_thread(request_check, &app_vec);

        run_thread.join();
    }
};