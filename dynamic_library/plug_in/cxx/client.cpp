#include <iostream>
#include "dictionary_set.h"

int main(int argc, char *argv[])
{
    DictionarySet dictionarySet;

    std::cout << "All existing ones Dictionaries:\n";
    auto allDictionaries = dictionarySet.getAllDictionaries();
    for (auto& currentDictionary : allDictionaries) {
        std::cout << currentDictionary << "\n";
    } 
    std::cout << "\n";

    std::string word = "Hallo";
    std::cout << "It will be the Word \"" << word << "\" translate:\n";

    std::string language = "German-English";
    std::string ret = dictionarySet.translate(word, language);
    std::cout << word << ": " << ret << "\n";

    language = "German-French";
    ret = dictionarySet.translate(word, language);
    std::cout << word << ": " << ret << "\n\n";

    word = "Auf Wiedersehen";
    std::cout << "It will be the Word \"" << word << "\" translate:\n";

    language = "German-English";
    ret = dictionarySet.translate(word, language);
    std::cout << word << ": " << ret << "\n";

    language = "German-French";
    ret = dictionarySet.translate(word, language);
    std::cout << word << ": " << ret << "\n\n";

    return 0;
}

