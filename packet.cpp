#include <string>
using std::string;
using std::to_string;

struct ExamplePacket {
  int count;
  double temp;
  string info;
  double t1;
  double t2;
  double t3;
  double t4;
  double t5;
  double t6;
  double t7;
};

int find_int(string key, string rjsons) {
  return 0;
}
double find_double(string key, string rjsons) {
  return 0.0;
}
string find_string(string key, string rjsons) {
  return "";
}

string encode_examplepacket(ExamplePacket pack){
  string res = "{";
  res += "count:" + to_string(pack.count);
  res += "temp:" + to_string(pack.temp);
  res += "info:" + pack.info;
  res += "t1:" + to_string(pack.t1);
  res += "t2:" + to_string(pack.t2);
  res += "t3:" + to_string(pack.t3);
  res += "t4:" + to_string(pack.t4);
  res += "t5:" + to_string(pack.t5);
  res += "t6:" + to_string(pack.t6);
  res += "t7:" + to_string(pack.t7);
  return res;
};
ExamplePacket decode_examplepacket(string rjsons){
  ExamplePacket pack;
  pack.count = find_int("count", rjsons);
  pack.temp = find_double("temp", rjsons);
  pack.info = find_string("info", rjsons);
  pack.t1 = find_double("t1", rjsons);
  pack.t2 = find_double("t2", rjsons);
  pack.t3 = find_double("t3", rjsons);
  pack.t4 = find_double("t4", rjsons);
  pack.t5 = find_double("t5", rjsons);
  pack.t6 = find_double("t6", rjsons);
  pack.t7 = find_double("t7", rjsons);
  return pack;
}
