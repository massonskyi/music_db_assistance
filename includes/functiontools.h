#ifndef MUSIC_DB_FUNCTIONTOOLS_H
#define MUSIC_DB_FUNCTIONTOOLS_H

#include <string>

namespace ft{
    std::string move_file_to_directory_python(const std::string& filepath, const std::string& dest_dir);
    std::string copy_file_to_buffer_python(const std::string& filepath);
    std::string move_file_from_buffer_to_directory_python(const std::string& file_buffer,const std::string& filename);
    std::vector<std::pair<const char *, const char *>> get_metadata_from_mp3(const std::string& filepath);
}
#endif //MUSIC_DB_FUNCTIONTOOLS_H
