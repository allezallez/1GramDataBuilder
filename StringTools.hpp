#ifndef STRINGTOOLS_H_
#define STRINGTOOLS_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class StringTools {

private:

public:
  static vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
      elems.push_back(item); 
    }
    return elems;
  }

  static vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems; 
  }

  static string to_upper_case(string str) {
    for (int i = 0; i < str.length(); i++) {
      str[i] = toupper(str[i]);
    }
    return str;
  }

  static bool check_proper_word(string str) {
    for (int i = 0; i < str.length(); i++) {
      if ((str[i] < 'A') || (str[i] > 'Z')) {
        return false;
      }
    }
    return true;
  }

};

#endif // STRINGTOOLS_H_
