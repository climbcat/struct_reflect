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

string encode_examplepacket(ExamplePacket pack){
  return "{"
    + "count:" + to_string(pack.count)
    + "temp:" + to_string(pack.temp)
    + "info:" + pack.info
    + "t1:" + to_string(pack.t1)
    + "t2:" + to_string(pack.t2)
    + "t3:" + to_string(pack.t3)
    + "t4:" + to_string(pack.t4)
    + "t5:" + to_string(pack.t5)
    + "t6:" + to_string(pack.t6)
    + "t7:" + to_string(pack.t7);
};
ExamplePacket decode_examplepacket(string rjsons){
  ExamplePacket pack;
  pack.count = find_int("count");
  pack.temp = find_double("temp");
  pack.info = find_string("info");
  pack.t1 = find_double("t1");
  pack.t2 = find_double("t2");
  pack.t3 = find_double("t3");
  pack.t4 = find_double("t4");
  pack.t5 = find_double("t5");
  pack.t6 = find_double("t6");
  pack.t7 = find_double("t7");
  return pack;
}
