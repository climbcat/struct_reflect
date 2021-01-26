#include <iostream>
#include <thread>
#include <mutex>
#include <cstring>
#include <fstream>
#include <string>

#include "packet.cpp"

using std::string;

int main (int argc, char **argv) {
  // decoder testing
  std::cout << "--- decoder test:" << "\n";

  string example = "{\"count\": 17, \"temp\": 19.2, \"info\": \"fredag\", \"list_d3\": [12.3, 5.0, 666.1], \"list_i3\": [42, 99, 117], \"list_s3\": [\"oktober\", \"november\", \"december\"]}";
  std::cout << example << "\n";
  std::cout << "\n";

  ExamplePacket pack = decode_examplepacket(example);
  std::cout << pack.count << "\n";
  std::cout << pack.info << "\n";
  std::cout << pack.temp << "\n";
  std::cout << "\n";
  std::cout << "list_d3:\n";
  for(int i=0; i < pack.list_d3.size(); i++){
    std::cout << pack.list_d3[i] << "\n";
  }
  std::cout << "\n";
  std::cout << "list_i3:\n";
  for(int i=0; i < pack.list_i3.size(); i++){
    std::cout << pack.list_i3[i] << "\n";
  }
  std::cout << "\n";
  std::cout << "list_s3:\n";
  for(int i=0; i < pack.list_s3.size(); i++){
    std::cout << pack.list_s3[i] << "\n";
  }
  std::cout << "\n";

  // encoder testing
  std::cout << "--- encoder test:" << "\n";
  std::cout << encode_examplepacket(pack) << "\n";

  std::cout << "\nNOTE: ordering of temp and info from json as compared to encoder output\n";

  return 0;
}
