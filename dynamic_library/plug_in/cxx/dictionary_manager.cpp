#include "dictionary_manager.h"

#include <dirent.h>
#include <dlfcn.h>

#include <string.h>
#include <iostream>

DictionaryManager& DictionaryManager::getInstance() {
    static DictionaryManager dictionaryManager; 
    return dictionaryManager;
}

std::vector<std::string> DictionaryManager::getDictionaryPaths() {
    std::vector<std::string> paths;

    DIR* dir_ptr;		/* the directory */
    struct dirent* direntp;		/* each entry	 */
    const std::string dirname = "dictionaries";
    std::string filename;
    if ((dir_ptr = opendir(dirname.c_str())) == NULL ) {
        std::cout << "cannot open " << dirname << ": " << strerror(errno) << std::endl;
        return paths;
    } else {
        while ((direntp = readdir(dir_ptr)) != NULL) {
            filename = direntp->d_name; 
            if (filename.length() > 3 && filename.substr(filename.length()-3) == ".so") {
                paths.push_back(dirname+"/"+filename);
            }
        }
        closedir(dir_ptr);
    }
    return paths;
}

IDictionary* DictionaryManager::loadDictionary(const std::string& path) {
    void* handle = dlopen(path.c_str(), RTLD_NOW);
    if (handle == NULL) {
        std::cout << "load " << path << " error: " << dlerror() << std::endl;
        return NULL;
    }

    typedef IDictionary* (*get_dictionary_func_ptr)();
    get_dictionary_func_ptr get_dictionary = (get_dictionary_func_ptr) dlsym(handle, "get_dictionary");
    if (get_dictionary == NULL) {
        std::cout << "get symbol get_dictionary error: " << dlerror() << std::endl;
        dlclose(handle);
        return NULL;
    }

    IDictionary* dictionary = get_dictionary();
    return dictionary;
}
