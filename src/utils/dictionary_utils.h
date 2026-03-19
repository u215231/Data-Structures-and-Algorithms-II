//
// Created by yjian on 05/06/2023.
//

#ifndef XARXA_SOCIAL_DICTIONARY_UTILS_H
#define XARXA_SOCIAL_DICTIONARY_UTILS_H

#define KEY_NOT_FOUND (-1)
#define VALUE_NOT_FOUND (-1)

typedef struct Dict Dict;
void addValue(int value, char* key, Dict* dictionary);
int getValue(char* key, Dict* dictionary);
void printDictionaryElements(Dict* dictionary);
void countWords(Dict* dictionary, char* post);
void readWords(Dict* dictionary, char* post);

#endif //XARXA_SOCIAL_DICTIONARY_UTILS_H
