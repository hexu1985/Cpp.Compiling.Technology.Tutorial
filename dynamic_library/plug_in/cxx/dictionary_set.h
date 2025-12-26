#pragma once

#include <vector>
#include <string>
#include "dictionary_manager.h"

class DictionarySet {
private:
    DictionaryManager* dm;

public:
    DictionarySet() {
        dm = &DictionaryManager::getInstance();
        dm->loadExistingDictionaries();
    }

    std::string translate(const std::string& word, const std::string& language) {
        std::string translatedWord = dm->getTranslation(language, word);
        if (!verifyWord(translatedWord)) {
            return "Error, Word not in Dictionary available!";
        } 
        return translatedWord;
    }

    const std::vector<std::string> getAllDictionaries() {
        return dm->getAllDictionaries();
    }

    bool verifyWord(const std::string& word) {
        bool contain = true;

        if (word.empty()) {
            contain = false;
        }
        return contain;
    }
};
