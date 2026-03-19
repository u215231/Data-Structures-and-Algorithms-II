#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary_utils.h"
#include "search_utils.h"
#include "network_data_control.h"
#include "print_utils.h"

void addValue(int value, char* key, Dict* dictionary) {

    // Diccionari ple.
    if(dictionary->current_elements == MAX_DICTIONARY_ELEMENTS) {
        printf("Dictionary is full");
        return;
    }

    // Diccionari no buit amb clau existent.
    int i = SET_ZERO;
    while ((i < MAX_DICTIONARY_ELEMENTS) && (dictionary->current_elements != EQUAL)) {
        if (strcmp(key, dictionary->element[i].key) == EQUAL) {
            // Substituïm el nou valor pel valor vell
            dictionary->element[i].value = value;
            return;
        }
        i++;
    }

    // Si arriba a aquesta part, vol dir que la clau no existeix i el diccionari no està ple
    dictionary->element[dictionary->current_elements].key = copyString(key);
    dictionary->element[dictionary->current_elements].value = value;
    dictionary->current_elements += INCREMENT_SIZE;
}

int searchIndexWithKey (char* key, Dict* dictionary) {

    // Donada una clau, retorna l'índex on està situada fent una cerca lineal.
    for (int idx = SET_ZERO; idx < dictionary->current_elements; idx++) {
        if (strcmp(key, dictionary->element[idx].key) == EQUAL) {
            return idx;
        }
    }
    // En cas contrari, retornem un error.
    return KEY_NOT_FOUND;
}

int getValue (char* key, Dict* dictionary) {
    // Aprofitar la funció definida abans
    int idx = searchIndexWithKey (key, dictionary);

    if (idx == KEY_NOT_FOUND) {
        return VALUE_NOT_FOUND;
    }
    return dictionary->element[idx].value;
}

int maxWordlength (Dict* dictionary) {
    int idx = SET_ZERO;
    int max = SET_ZERO;
    int length;

    while (idx<MAX_DICTIONARY_ELEMENTS && dictionary->current_elements >= MAX_DICTIONARY_ELEMENTS ||
    idx < dictionary->current_elements && dictionary->current_elements < MAX_DICTIONARY_ELEMENTS) {

        length = strlen(dictionary->element[idx].key);
        if(max < length) {
            max = length;
        }
        idx++;
    }
    return max;
}

void printDictionaryElements (Dict* dictionary) {
    int idx = SET_ZERO;
    printf("\n");

    while (idx<MAX_DICTIONARY_ELEMENTS && dictionary->current_elements >= MAX_DICTIONARY_ELEMENTS ||
    idx < dictionary->current_elements && dictionary->current_elements < MAX_DICTIONARY_ELEMENTS) {

        if (getValue(dictionary->element[idx].key, dictionary) != EQUAL) {
            printf("WORD:%s ", dictionary->element[idx].key);
            printSpaces(dictionary->element[idx].key, maxWordlength(dictionary));
            printf("USED:%d\n", dictionary->element[idx].value);
        }
        idx++;
    }
}

void countWords (Dict* dictionary, char* post) {

    int value;
    if (getValue(post, dictionary) == VALUE_NOT_FOUND) {
        addValue(1, post, dictionary);
    }
    else {
        value = getValue(post, dictionary);
        addValue(value + 1, post, dictionary);
    }
}

void readWords (Dict *dictionary, char* post) {
    int idx = 0;
    size_t post_length = strlen(post);
    char* buffer = malloc(BUFFER_SIZE*sizeof(char));
    countWords (dictionary, "");
    for(int i = 0; (size_t)i < post_length; i++) {
        if(post[i] != ' ' && post[i] != '!' && post[i] != '?' && post[i] != '.' &&
           post[i] != ',' && post[i] != ':' && post[i] != ';' && (size_t)i != post_length-1) {
            buffer[idx] = tolower(post[i]);
            idx++;
        }
        else if(post[i] == ' ' || post[i] == '!' || post[i] == '?' || post[i] == '.' ||
                post[i] == ',' || post[i] == ':' || post[i] == ';') {
            buffer[idx] = '\0';
            countWords(dictionary, buffer);
            buffer = NULL;
            buffer = malloc(BUFFER_SIZE*sizeof(char));
            idx = 0;
        }
        else if((size_t)i == post_length-1) {
            if (post[i] != ' ' && post[i] != '!' && post[i] != '?' && post[i] != '.' ||
                post[i] != ',' && post[i] != ':' && post[i] != ';'){
                buffer[idx] = tolower(post[i]);
                buffer[idx+1] = '\0';
            }
            countWords(dictionary, buffer);
        }
    }
}