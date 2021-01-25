#include <regex>
using std::string;
using std::to_string;
using std::regex_search;
using std::smatch;
using std::regex;

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
  string spat = "\"" + key + "\":\\s*\"(.*)\",?}?";
  regex pat {spat};
  smatch matches;
  regex_search(rjsons, matches, pat);
  return matches[1];
}
