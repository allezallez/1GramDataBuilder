#ifndef NGRAM_CLEANER_H_
#define NGRAM_CLEANER_H_

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include "StringTools.hpp"

using namespace std;

class ngram_cleaner {
  public:
    static void condense_and_clean_1gram_data(string filename, 
        unordered_map<string, vector<string>> * all_the_words);

  private:
    static const int EARLIEST_YEAR;
    static const int MINIMUM_WORD_OCCURENCES;
    static const unordered_set<string> parts_of_speech;
};

#endif // NGRAM_CLEANER_H_
