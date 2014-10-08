#include "ngram_cleaner.hpp"

using namespace std;

const int ngram_cleaner::EARLIEST_YEAR = 1885;
const int ngram_cleaner::MINIMUM_WORD_OCCURENCES = 65;
const unordered_set<string> ngram_cleaner::parts_of_speech {"NOUN", "VERB", "ADJ", "ADV", 
  "PRON", "DET", "ADP", "NUM", "CONJ", "PART", ".", "X"};

void ngram_cleaner::condense_and_clean_1gram_data(string filename, 
    unordered_map<string, vector<string>> * all_the_words) {


  vector<string> this_split_line;
  string current_part_of_speech;
  string current_actual_word;
  string this_line;
  ifstream dictionary_reader(filename);
  while (getline(dictionary_reader, this_line)) {
    this_split_line = StringTools::split(this_line, '\t');
    if (stoi(this_split_line.at(1)) > EARLIEST_YEAR 
        && stoi(this_split_line.at(2)) > MINIMUM_WORD_OCCURENCES ) {
      vector<string> possible_part_of_speech_split = StringTools::split(this_split_line.at(0), '_');
      current_actual_word = StringTools::to_upper_case(possible_part_of_speech_split.at(0));
      if (StringTools::check_proper_word(current_actual_word)) {
        if (possible_part_of_speech_split.size() > 1) {
          if (parts_of_speech.count(possible_part_of_speech_split.at(1)) != 0) {
            current_part_of_speech = possible_part_of_speech_split.at(1);
          } else {
            current_part_of_speech = "UNKNOWN";
          }
        } else {
          current_part_of_speech = "UNKNOWN";
        }
        if (all_the_words->count(current_actual_word) == 0) {
          vector<string> new_word_data;
          new_word_data.push_back(current_actual_word);
          new_word_data.push_back(this_split_line.at(2));
          new_word_data.push_back(this_split_line.at(3));
          new_word_data.push_back(current_part_of_speech);
          (*all_the_words)[current_actual_word] = new_word_data;
        } else {
          vector<string> * this_vector = &(*all_the_words)[current_actual_word];
          this_vector->at(1) = to_string(stoi(this_vector->at(1)) + stoi(this_split_line[2]));
          this_vector->at(2) = to_string(stoi(this_vector->at(2)) + stoi(this_split_line[3]));
          if(find(++this_vector->begin(), this_vector->end(), current_part_of_speech)
              == this_vector->end()) {
            this_vector->push_back(current_part_of_speech);
          }
        }
      }
    }
  }
}
