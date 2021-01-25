#include <iostream>
#include <thread>
#include <mutex>
#include <cstring>
#include <fstream>
#include <string>

#include "packet.cpp"

using std::string;

int main (int argc, char **argv) {
  string example = "{\"count\": 17, \"temp\": 19.2, \"info\": \"fredag\"}";

  std::cout << example << "\n";

  std::cout << find_int("count", example) << "\n";
  std::cout << find_double("temp", example) << "\n";
  std::cout << find_string("info", example) << "\n";

  return 0;
}
