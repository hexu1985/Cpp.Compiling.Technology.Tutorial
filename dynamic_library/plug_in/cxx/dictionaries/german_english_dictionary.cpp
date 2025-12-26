#ifndef __german_english_dictionary_h
#define __german_english_dictionary_h

#include <map>
#include <string>
#include "i_dictionary.h"

class GermanEnglishDictionary: public IDictionary {
private:
    static std::map<std::string, std::string> wordsList;

public:
    const char* getTranslation(const char* word) override;

    const char* getLanguage() override;
};

std::map<std::string, std::string> GermanEnglishDictionary::wordsList = {{"Hallo", "Hello"}, {"Auf Wiedersehen", "Goodbye"}};

const char* GermanEnglishDictionary::getTranslation(const char* word) {
    return wordsList[word].c_str();
}

const char* GermanEnglishDictionary::getLanguage() {
    return "German-English";
}

extern "C" {

IDictionary* get_dictionary() {
    static GermanEnglishDictionary dictionary;
    return &dictionary;
}

}

#endif

