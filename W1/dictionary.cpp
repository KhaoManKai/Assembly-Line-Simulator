// Workshop 1
// Dictionary Module
// Revision History
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 30 Sep 2024   ID 132957234
// NBB  hllee13@myseneca.ca
/////////////////////////////////////////////////////////////////

#include "dictionary.h"
using namespace std;
namespace seneca {

Dictionary::Dictionary(const char* filename) : m_words(nullptr), m_currentNum(0) {
    if (filename) {
        loadFile(filename);
    } // loadfile function
}
void Dictionary::loadFile(const char* filename) {
    ifstream file(filename);
    if (!file) {
        throw runtime_error("Unable to open file: " + string(filename));
    }
    
    // vector method was I google it, not familiar with this method right now,
    // but vector make it more efficient
    // cuz when it's reading file, can resizing dynamically
    vector<Word> temp;
       string line;
       while (getline(file, line)) {
           //find the first two commas
           size_t pos1 = line.find(',');
           size_t pos2 = line.find(',', pos1 + 1);
           
           if (pos1 != string::npos && pos2 != string::npos) {
               string word = line.substr(0, pos1);
               string pos = line.substr(pos1 + 1, pos2 - pos1 - 1);
               string definition = line.substr(pos2 + 1);

               // remove whitespace
               word.erase(0, word.find_first_not_of(" \t"));
               word.erase(word.find_last_not_of(" \t") + 1);
               pos.erase(0, pos.find_first_not_of(" \t"));
               pos.erase(pos.find_last_not_of(" \t") + 1);
               definition.erase(0, definition.find_first_not_of(" \t"));
               definition.erase(definition.find_last_not_of(" \t") + 1);

               temp.push_back(Word{word, definition, stringToSpeech(pos)});
           }
       }

       m_currentNum = temp.size();
       delete[] m_words;
       m_words = new Word[m_currentNum];
       for (size_t i = 0; i < m_currentNum; ++i) {
           m_words[i] = temp[i];
       }

}
Dictionary::Dictionary(const Dictionary& other) : m_words(nullptr), m_currentNum(0) {
    if (other.m_currentNum > 0) {
        m_currentNum = other.m_currentNum;
        m_words = new Word[m_currentNum];
        for (size_t i = 0; i < m_currentNum; ++i) {
            m_words[i] = other.m_words[i];
        }
    }
}

Dictionary& Dictionary::operator=(const Dictionary& other) {
    if (this != &other) {
        delete[] m_words;
        m_currentNum = other.m_currentNum;
        if (m_currentNum > 0) {
            m_words = new Word[m_currentNum];
            for (size_t i = 0; i < m_currentNum; ++i) {
                m_words[i] = other.m_words[i];
            }
        } else {
            m_words = nullptr;
        }
    }
    return *this;
}
Dictionary::Dictionary(Dictionary&& other) noexcept: m_words(other.m_words), m_currentNum(other.m_currentNum) {
    other.m_words = nullptr;
    other.m_currentNum = 0;
}

Dictionary& Dictionary::operator=(Dictionary&& other) noexcept {
    if (this != &other) {
        delete[] m_words;
        m_words = other.m_words;
        m_currentNum = other.m_currentNum;
        other.m_words = nullptr;
        other.m_currentNum = 0;
    }
    return *this;
}

Dictionary::~Dictionary() {
    delete[] m_words;
}
void Dictionary::searchWord(const char* word) {
    bool found = false;
    for (size_t i = 0; i < m_currentNum; ++i) {
        if (strcmp(m_words[i].w_word.c_str(), word) == 0) {
            if (!found || g_settings.m_show_all) {
                if (found) {
                    cout << string(strlen(word), ' ');
                } else {
                    cout << m_words[i].w_word;
                }
                cout << " - ";
                if (g_settings.m_verbose && m_words[i].m_pos != PartOfSpeech::Unknown) {
                    cout << "(" << SpeechToString(m_words[i].m_pos) << ") ";
                }
                cout << m_words[i].m_definition << endl;
            }
            found = true;
            if (!g_settings.m_show_all) break;
        }
    }
    if (!found) {
        cout << "Word '" << word << "' was not found in the dictionary." << endl;
    }
}
PartOfSpeech Dictionary::stringToSpeech(const string& pos) const {
    if (pos == "n." || pos == "n. pl.") return PartOfSpeech::Noun;
    if (pos == "adv.") return PartOfSpeech::Adverb;
    if (pos == "a.") return PartOfSpeech::Adjective;
    if (pos == "v." || pos == "v. i." || pos == "v. t." || pos == "v. t. & i.") return PartOfSpeech::Verb;
    if (pos == "prep.") return PartOfSpeech::Preposition;
    if (pos == "pron.") return PartOfSpeech::Pronoun;
    if (pos == "conj.") return PartOfSpeech::Conjunction;
    if (pos == "interj.") return PartOfSpeech::Interjection;
    return PartOfSpeech::Unknown;
}

string Dictionary::SpeechToString(PartOfSpeech pos) const {
    switch (pos) {
        case PartOfSpeech::Noun: return "noun";
        case PartOfSpeech::Pronoun: return "pronoun";
        case PartOfSpeech::Adjective: return "adjective";
        case PartOfSpeech::Adverb: return "adverb";
        case PartOfSpeech::Verb: return "verb";
        case PartOfSpeech::Preposition: return "preposition";
        case PartOfSpeech::Conjunction: return "conjunction";
        case PartOfSpeech::Interjection: return "interjection";
        default: return "unknown";
    }
}
}
