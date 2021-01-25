#include "keyfinder.cpp"
#include <string>
using std::string;
struct ExamplePacket {
  int count;
  string info;
  double temp;
};
string encode_examplepacket(ExamplePacket pack){
  string res = "{";
  res += "count:" + to_string(pack.count);
  res += "info:" + pack.info;
  res += "temp:" + to_string(pack.temp);
  return res;
};
ExamplePacket decode_examplepacket(string rjsons){
  ExamplePacket pack;
  pack.count = find_int("count", rjsons);
  pack.info = find_string("info", rjsons);
  pack.temp = find_double("temp", rjsons);
  return pack;
}
