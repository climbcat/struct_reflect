#include "keyfinder.cpp"
#include <string>
#include <vector>
using std::string;
struct ExamplePacket {
  int count;
  string info;
  double temp;
  vector<double> list_d3;
  vector<int> list_i3;
  vector<string> list_s3;
};
string encode_examplepacket(ExamplePacket pack){
  string res = "{";

  res += "\"count\":" + to_string(pack.count) + ", ";
  res += "\"info\":" + pack.info + ", ";
  res += "\"temp\":" + to_string(pack.temp) + ", ";
  res += "\"list_d3\":" + ecode_double_list(pack.list_d3);

  res += "}";
  return res;
};
ExamplePacket decode_examplepacket(string rjsons){
  ExamplePacket pack;
  pack.count = find_int("count", rjsons);
  pack.info = find_string("info", rjsons);
  pack.temp = find_double("temp", rjsons);
  pack.list_d3 = find_double_array("list_d3", rjsons);
  return pack;
}
