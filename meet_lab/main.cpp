#include <cstdio>
#include "word_counter.h"
#include "text_reader.h"
#include "csv_writer.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        std::fprintf(stderr, "Usage: ./word_counter <input_file_name> <output_file_name>\n");
        return 1;
    }

    std::FILE *input = std::fopen(argv[1], "r");
    if (input == nullptr) {
        std::fprintf(stderr, "Could not open input file\n");
        return 1;
    }

    word_counter counter(100000);
    read_words(input, counter);
    std::fclose(input);

    std::FILE *output = std::fopen(argv[2], "w");
    if (output == nullptr) {
        std::fprintf(stderr, "Could not open output file\n");
        return 1;
    }

    write_csv(output, counter);
    std::fclose(output);
    return 0;
}