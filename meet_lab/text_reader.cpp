#include "text_reader.h"
#include <string>
#include <cstring>

void read_words(std::FILE *input, word_counter &counter) {
    std::string current_word;
    int ch;

    const char *delimiters = ".,:;!?()[]{}<>\"'`~|^*+-\\/%*@#$&_ \t\n\r";

    while ((ch = std::fgetc(input)) != EOF) {
        if (std::strchr(delimiters, ch) != nullptr) {
            if (!current_word.empty()) {
                counter.add_word(current_word.c_str());
                current_word.clear();
            }
        } else {
            current_word.push_back(static_cast<char>(ch));
        }
    }

    if (!current_word.empty()) {
        counter.add_word(current_word.c_str());
    }
}
