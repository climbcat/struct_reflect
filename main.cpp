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

  string example = "{\"count\": 17, \"temp\": 19.2, \"info\": \"fredag\", \"list_d3\": [12.3, 5.0, 666.1], \"list_i3\": [42, 99, 117], \"list_s3\": [\"oktober\", \"november\", \"december\"]}";
  std::cout << example << "\n";
  std::cout << "\n";

  //std::cout << find_int("count", example) << "\n";
  //std::cout << find_double("temp", example) << "\n";
  //std::cout << find_string("info", example) << "\n";

  auto vec = find_int_array("list_i3", example);
  for(int i=0; i < vec.size(); i++){
    std::cout << vec[i] << "\n";
  }
  std::cout << "\n";

  auto vec2 = find_double_array("list_d3", example);
  for(int i=0; i < vec2.size(); i++){
    std::cout << vec2[i] << "\n";
  }
  std::cout << "\n";

  auto vec3 = find_string_array("list_s3", example);
  for(int i=0; i < vec3.size(); i++){
    std::cout << vec3[i] << "\n";
  }
  std::cout << "\n";


  ExamplePacket pack;
  pack = decode_examplepacket(example);
  std::cout << pack.count << "\n";
  std::cout << pack.info << "\n";
  std::cout << pack.temp << "\n";

  std::cout << "\n";


  // encoder testing

  std::cout << encode_examplepacket(pack) << "\n";



  return 0;
}
