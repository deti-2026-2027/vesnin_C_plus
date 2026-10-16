#ifndef UNTITLED_CSV_WRITER_H
#define UNTITLED_CSV_WRITER_H

#include <cstdio>
#include "word_counter.h"

void write_csv(std::FILE *output, const word_counter &counter);



#endif //UNTITLED_CSV_WRITER_H