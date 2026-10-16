#include "csv_writer.h"
#include <algorithm>

bool has_higher_frequency(const list *left, const list *right) {
    return left->count > right->count;
}

void sort_by_frequency(std::vector<const list *> &entries) {
    std::sort(entries.begin(), entries.end(), has_higher_frequency);
}

void write_csv(std::FILE *output, const word_counter &counter) {
    std::vector<const list *> entries = counter.get_entries();
    sort_by_frequency(entries);

    int total = counter.get_total_word_count();

    std::fprintf(output, "Слово,Частота,Частота(%%)\n");

    for (const list *entry : entries) {
        int frequency_count = entry->count;
        float frequency_percent = static_cast<float>(frequency_count) / total * 100;
        std::fprintf(output,"%s,%d,%f%%\n", entry->word, frequency_count, frequency_percent);
    }
}