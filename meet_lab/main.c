#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct list {
    char * word;
    int count;
    struct list * next;
}list;

list ** arr_hash; 
int diff_words = 0;
int count_words = 0;

int hash_function(char * name, int m) {
    char * s = name;
    int h, sum = 0;
    while(*s != '\0') {
        sum += *s; 
        s++;
    }
    h = sum % m; 
    return h;
}

void hash_push(char * word, int hash_table_size) {
    int index = hash_function(word, hash_table_size);

    list * t = arr_hash[index];
    while (t != NULL) {
        if (strcmp(word, t->word) == 0) {
            t->count++;
            return;
        }
        t = t->next;
    }

    list * p = (list*)malloc(sizeof(list));
    p->word = (char*)malloc(strlen(word) + 1);
    strcpy(p->word, word);
    p->count = 1;
    p->next = arr_hash[index];
    arr_hash[index] = p;
    diff_words++;
}

void ins_sort(list ** arr, int n) {
    for (int i = 1; i < n; i++) {
        list * r = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j]->count < r->count) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = r;
    }
}

void free_memory_list(list ** arr, int N) { 
    for (int i = 0; i < N; i++) { 
        list * p = arr[i];
        list * t;
        while(p != NULL) {
            t = p;
            p = p->next;
            free(t->word);
            free(t);
        }
    }

    free(arr_hash);
}

int main(int argc, char ** argv) {
    SetConsoleOutputCP(CP_UTF8); 
    SetConsoleCP(CP_UTF8);
    FILE * fin = fopen(argv[1], "r");
    if (fin == NULL) {
        fprintf(stderr, "Не удалось открыть файл %s", argv[1]);
        return 1;
    }

    FILE * fout = fopen(argv[2], "w");
    if (fout == NULL) {
        fprintf(stderr, "Не удалось создать файл %s", argv[2]);
        return 1;
    }

    int hash_table_size = 100000;
    arr_hash = (list**)calloc(hash_table_size, sizeof(list*)); 

    int ch;
    char * s = (char*)malloc(1000 * sizeof(char));
    char * current = s;
    while ((ch = fgetc(fin)) != EOF) {
        if (strchr(".,:;!?()[]{}<>\"'`~|^*+-\\/%*@#$&_ \t\n", ch) != NULL) {
            if (current != s) {
                *current = '\0';
                hash_push(s, hash_table_size);
                current = s;
                count_words++;
            }    
        }
        else {
            *current = ch;
            current++;
        }
    }
    if (current != s) {
        *current = '\0';
        hash_push(s, hash_table_size);
        count_words++;
    }

    list ** freq_arr = (list**)malloc(sizeof(list*) * diff_words);
    int pos_freq_arr = 0;
    for (int i = 0; i < hash_table_size; i++) {
        list * p = arr_hash[i];
        while (p != NULL) { 
            freq_arr[pos_freq_arr++] = p;
            p = p->next;
        }
    }

    ins_sort(freq_arr, diff_words);

    fprintf(fout, "Слово,Частота,Частота(%%)\n");
    for (int i = 0; i < diff_words; i++) {
        int freq_digit = freq_arr[i]->count;
        float freq_percent = ((float)freq_arr[i]->count / count_words) * 100;
        fprintf(fout, "%s,%d,%f%%\n", freq_arr[i]->word, freq_digit, freq_percent);
    }

    free_memory_list(arr_hash, hash_table_size);
    free(freq_arr);
    fclose(fin);
    fclose(fout);
    return 0;
}