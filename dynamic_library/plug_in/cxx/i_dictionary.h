#pragma once

class IDictionary {
public:
    virtual const char *getTranslation(const char *word) = 0;
    virtual const char *getLanguage() = 0;
};

extern "C" {
    IDictionary *get_dictionary();
}

