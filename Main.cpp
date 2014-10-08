#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <thread>
#include <future>
#include "ngram_cleaner.cpp"

using namespace std;

int main(int argc, char* argv[]) {

  unordered_map<char, unordered_map<string, vector<string>>*> dictionaries;
  const string filename_prefix = "../data/1gramdata/googlebooks-eng-all-1gram-20120701-";

  thread letterThreads[26];

  for (char letter = 'a'; letter <= 'z'; letter++) {
    dictionaries[letter] = new unordered_map<string, vector<string>>();
    letterThreads[((int) letter) - ((int) 'a')] =
      thread(ngram_cleaner::condense_and_clean_1gram_data, 
             filename_prefix + letter, dictionaries[letter]);
  }

  for (int i = 0; i < 26; i++) {
    letterThreads[i].join();
  }

  for (auto letter_map_iter = dictionaries.begin(); letter_map_iter != dictionaries.end();
      letter_map_iter++) {
    for (auto string_map_iter = letter_map_iter->second->begin(); 
        string_map_iter != letter_map_iter->second->end();
        string_map_iter++) {
      for (string string_data: string_map_iter->second) {
        cout<<string_data<<"\t";
      }
      cout<<endl;
    }
    delete letter_map_iter->second;
  }
};
