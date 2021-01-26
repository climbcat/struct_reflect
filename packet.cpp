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
  res += "\"count\":" + to_string(pack.count) + ",";
  res += "\"info\":\"" + pack.info + "\"" + ",";
  res += "\"temp\":" + to_string(pack.temp) + ",";
  res += "\"list_d3\":" + encode_double_list(pack.list_d3) + ",";
  res += "\"list_i3\":" + encode_int_list(pack.list_i3) + ",";
  res += "\"list_s3\":" + encode_string_list(pack.list_s3);
  res += "}";
  return res;
};
ExamplePacket decode_examplepacket(string rjsons){
  ExamplePacket pack;
  pack.count = find_int("count", rjsons);
  pack.info = find_string("info", rjsons);
  pack.temp = find_double("temp", rjsons);
  pack.list_d3 = find_double_array("list_d3", rjsons);
  pack.list_i3 = find_int_array("list_i3", rjsons);
  pack.list_s3 = find_string_array("list_s3", rjsons);
  return pack;
}
