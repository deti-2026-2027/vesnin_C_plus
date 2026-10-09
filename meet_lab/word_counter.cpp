#include "word_counter.h"
#include <cstring>

word_counter::word_counter(int size): bucket_count(size), buckets(new list *[size]{}), total_word_count(0), unique_word_count(0) {}

word_counter::~word_counter()
{
    for (int i = 0; i < bucket_count; i++) {
        list * current_node = buckets[i];
        list * next_node;
        while (current_node != nullptr) {
            next_node = current_node->next;
            delete[] current_node->word;
            delete current_node;
            current_node = next_node;
        }
    }
    delete[] buckets;
}

int word_counter::calculate_hash(const char *word) {
    const char * ch = word;
    unsigned int hash_sum = 0;
    while(*ch != '\0') {
        hash_sum += static_cast<unsigned char>(*ch);
        ch++;
    }
    return hash_sum % bucket_count;
}

void word_counter::add_word(const char *word) {
    int hash_table_index = calculate_hash(word);
    list * current_node = buckets[hash_table_index];
    while (current_node != nullptr) {
        if (std::strcmp(word, current_node->word) == 0) {
            current_node->count++;
            total_word_count++;
            return;
        }
        current_node = current_node->next;
    }
    list * new_node = new list{};
    new_node->word = new char [std::strlen(word) + 1]{};
    std::strcpy(new_node->word, word);
    new_node->count = 1;
    new_node->next = buckets[hash_table_index];
    buckets[hash_table_index] = new_node;
    total_word_count++;
    unique_word_count++;
}

int word_counter::get_total_word_count() const {
    return total_word_count;
}

int word_counter::get_unique_word_count() const {
    return unique_word_count;
}