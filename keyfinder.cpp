#include <regex>
#include <vector>
#include <sstream>
using std::string;
using std::to_string;
using std::regex_search;
using std::smatch;
using std::regex;
using std::vector;

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
    // TODO: remove the quotations
    vect.push_back(token);
  }
  return vect;
}
