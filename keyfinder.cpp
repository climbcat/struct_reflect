#include <regex>
#include <vector>
#include <sstream>
using std::string;
using std::to_string;
using std::regex_search;
using std::smatch;
using std::regex;
using std::vector;

#include <iostream>
#include <string>
#include <algorithm>

void _trim(string& s, string what)
{
  // (via public domain)
  size_t start = s.find_first_not_of(what); // ltrim
  s = ((start == string::npos) ? "" : s.substr(start));
  size_t end = s.find_last_not_of(what); // rtrim
  s = (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

int find_int(string key, string rjsons) {
  string spat = "\"" + key + "\":\\s*([0-9]+)\\s*,?}?";
  regex pat {spat};
  smatch matches;
  regex_search(rjsons, matches, pat);
  return stoi(matches[1]);
}
double find_double(string key, string rjsons) {
  string spat = "\"" + key + "\":\\s*([0-9.]+)\\s*,?}?";
  regex pat {spat};
  smatch matches;
  regex_search(rjsons, matches, pat);
  return stod(matches[1]);
}
string find_string(string key, string rjsons) {
  string spat = "\"" + key + "\":\\s*\"(.*?)\",?}?";
  regex pat {spat};
  smatch matches;
  regex_search(rjsons, matches, pat);
  return matches[1];
}
string _find_list_any(string key, string rjsons) {
  string spat = "\"" + key + "\":\\s*\\[(.*?)\\],?}?";
  regex pat {spat};
  smatch matches;
  regex_search(rjsons, matches, pat);
  return matches[1];
}
vector<int> find_int_array(string key, string rjsons) {
  string list_content = _find_list_any(key, rjsons);
  std::istringstream iss(list_content);
  vector<int> vect;
  string token;
  while (std::getline(iss, token, ',')) vect.push_back(stoi(token));
  return vect;
}
vector<double> find_double_array(string key, string rjsons) {
  string list_content = _find_list_any(key, rjsons);
  std::istringstream iss(list_content);
  vector<double> vect;
  string token;
  while (std::getline(iss, token, ',')) vect.push_back(stod(token));
  return vect;
}
vector<string> find_string_array(string key, string rjsons) {
  string list_content = _find_list_any(key, rjsons);
  std::istringstream iss(list_content);
  vector<string> vect;
  string token;
  while (std::getline(iss, token, ',')) {
    _trim(token, " ");
    _trim(token, "\"");
    vect.push_back(token);
  }
  return vect;
}
string encode_double_list(vector<double> vect){
  string res = "[";
  for(int i = 0; i < vect.size(); i++) {
    res += to_string(vect[i]);
    if (i < vect.size()-1)
      res += ", ";
  }
  res += "]";
  return res;
}
string encode_int_list(vector<int> vect){
  string res = "[";
  for(int i = 0; i < vect.size(); i++) {
    res += to_string(vect[i]);
    if (i < vect.size()-1)
      res += ", ";
  }
  res += "]";
  return res;
}
string encode_string_list(vector<string> vect){
  string res = "[";
  for(int i = 0; i < vect.size(); i++) {
    res += "\"" + vect[i] + "\"";
    if (i < vect.size()-1)
      res += ", ";
  }
  res += "]";
  return res;
}
