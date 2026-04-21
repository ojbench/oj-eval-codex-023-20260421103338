#include "deque.hpp"
#include <iostream>

int main() {
  // Minimal sanity use of sjtu::deque to keep runtime tiny
  sjtu::deque<int> d;
  for (int i = 0; i < 1000; ++i) d.push_back(i);
  for (int i = 0; i < 500; ++i) d.pop_front();
  if (d.size() != 500) return 1;
  // Print nothing; exit quickly
  return 0;
}

