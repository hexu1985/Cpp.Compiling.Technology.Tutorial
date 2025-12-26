#ifndef __german_english_dictionary_h
#define __german_english_dictionary_h

#include <map>
#include <string>
#include "i_dictionary.h"

class GermanFrenchDictionary: public IDictionary {
private:
    static std::map<std::string, std::string> wordsList;

public:
    const char* getTranslation(const char* word) override;

    const char* getLanguage() override;
};

std::map<std::string, std::string> GermanFrenchDictionary::wordsList = {{"Hallo", "Salut"}, {"Auf Wiedersehen", "Au revoir"}};

const char* GermanFrenchDictionary::getTranslation(const char* word) {
    return wordsList[word].c_str();
}

const char* GermanFrenchDictionary::getLanguage() {
    return "German-French";
}

extern "C" {

IDictionary* get_dictionary() {
    static GermanFrenchDictionary dictionary;
    return &dictionary;
}

}

#endif

