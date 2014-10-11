#include "ngram_cleaner.hpp"

using namespace std;

const int ngram_cleaner::EARLIEST_YEAR = 1885;
const int ngram_cleaner::MINIMUM_WORD_OCCURENCES = 65;
const unordered_set<string> ngram_cleaner::parts_of_speech {"NOUN", "VERB", "ADJ", "ADV", 
  "PRON", "DET", "ADP", "NUM", "CONJ", "PART", ".", "X"};

void ngram_cleaner::condense_and_clean_1gram_data(string filename, 
    unordered_map<string, vector<string>> * all_the_words) {
  // temp variables
  vector<string> this_split_line;
  string current_part_of_speech;
  string current_actual_word;
  string this_line;
  
  ifstream dictionary_reader(filename);
  while (getline(dictionary_reader, this_line)) {
    // google separates ngram data with tabs
    this_split_line = StringTools::split(this_line, '\t');
    // check for year and occurences thresholds
    if (stoi(this_split_line.at(1)) > EARLIEST_YEAR 
        && stoi(this_split_line.at(2)) > MINIMUM_WORD_OCCURENCES ) {
      // google separates parts of speech (noun, verb etc) with _ characters
      vector<string> possible_part_of_speech_split = StringTools::split(this_split_line.at(0), '_');
      current_actual_word = StringTools::to_upper_case(possible_part_of_speech_split.at(0));
      // check for bad word (there are many)
      if (StringTools::check_proper_word(current_actual_word)) {
        // check if this word is classified
        if (possible_part_of_speech_split.size() > 1) {
          if (parts_of_speech.count(possible_part_of_speech_split.at(1)) != 0) {
            current_part_of_speech = possible_part_of_speech_split.at(1);
          } else {
            // this implies _ in word itself, but have already checked for this above
            current_part_of_speech = "UNKNOWN";
          }
        } else {
          // no part of speech classification in this 1-gram
          current_part_of_speech = "UNKNOWN";
        }
        // have not seen this word at all before
        if (all_the_words->count(current_actual_word) == 0) {
          vector<string> new_word_data;
          new_word_data.push_back(current_actual_word);
          new_word_data.push_back(current_part_of_speech);
          new_word_data.push_back(this_split_line.at(2));
          (*all_the_words)[current_actual_word] = new_word_data;
        // have seen this word before
        } else {
          vector<string> * this_vector = &(*all_the_words)[current_actual_word];
          vector<string>::iterator part_of_speech_searcher = 
              find(++this_vector->begin(), this_vector->end(), current_part_of_speech);
          // no longer using cumulative counting:
          // this_vector->at(1) = to_string(stoi(this_vector->at(1)) + stoi(this_split_line[2]));
          
          // haven't seen this part of speech before
          if( part_of_speech_searcher == this_vector->end()) {
            this_vector->push_back(current_part_of_speech);
            this_vector->push_back(this_split_line[2]);
          // have seen this part of speech before
          } else {
            part_of_speech_searcher++;
            *part_of_speech_searcher = to_string(stoi(*part_of_speech_searcher) + stoi(this_split_line[2]));
          }
        }
      }
    }
  }
}
