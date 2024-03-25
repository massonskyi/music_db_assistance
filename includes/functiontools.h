#ifndef MUSIC_DB_FUNCTIONTOOLS_H
#define MUSIC_DB_FUNCTIONTOOLS_H
#include <python3.11/Python.h>  // Include Python header


namespace ft{
    struct print_info {
        void operator()(const std::string& info);
    };
    int get_mp3_info_py(const std::string& filepath) ;

}
#endif //MUSIC_DB_FUNCTIONTOOLS_H
