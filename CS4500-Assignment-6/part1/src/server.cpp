#include "network.h"

int main(void) {
  Server *s = new Server(4);
  s->start();
}