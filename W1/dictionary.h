// Workshop 1
// Dictionary Module
// Revision History
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 30 Sep 2024   ID 132957234
// NBB  hllee13@myseneca.ca
/////////////////////////////////////////////////////////////////

// the dictionary module manages a dynamically allocated collection
// of objects of type Word in the form of an array.
#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cstddef>
#include <stdexcept>
#include "settings.h"
using namespace std;
namespace seneca {
enum class PartOfSpeech
{
  Unknown,
  Noun,
  Pronoun,
  Adjective,
  Adverb,
  Verb,
  Preposition,
  Conjunction,
  Interjection,
};
struct Word
{
  string w_word{};
  string m_definition{};
  PartOfSpeech m_pos = PartOfSpeech::Unknown;
};

class Dictionary{
private:
    Word* m_words;
    size_t m_currentNum;
    
    void loadFile(const char* filename);
    PartOfSpeech stringToSpeech(const string& pos) const;
    string SpeechToString(PartOfSpeech pos) const;
public:
    //defult constructor
    Dictionary(): m_words(nullptr), m_currentNum(0){};
    // the rule of five
    Dictionary(const Dictionary&);
    Dictionary& operator=(const Dictionary&);
    ~Dictionary();
    Dictionary(Dictionary&& other)noexcept;
    Dictionary& operator=(Dictionary&& other)noexcept;
    
    Dictionary(const char* filename);
    void searchWord(const char* word);
};
}
#endif /* dictionary_hpp */
