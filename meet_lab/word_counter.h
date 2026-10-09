#ifndef UNTITLED_WORD_COUNTER_H
#define UNTITLED_WORD_COUNTER_H

typedef struct list {
    char *word;
    int count;
    struct list *next;
} list;

class word_counter {
private:
    int bucket_count;
    list **buckets;
    int unique_word_count;
    int total_word_count;

    int calculate_hash(const char *word);

public:
    word_counter(int size);
    ~word_counter();

    void add_word(const char *word);
    int get_total_word_count() const;
    int get_unique_word_count() const;
};


#endif //UNTITLED_WORD_COUNTER_H
