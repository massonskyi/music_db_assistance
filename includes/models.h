#ifndef MUSIC_DB_MODELS_H
#define MUSIC_DB_MODELS_H

#include <string>
#include <cstdint>

namespace models{
    struct artist{
        int id;
        std::string name;
        std::string biography;
        std::string photo;
    };

    struct album{
        uint32_t id;
        uint32_t artist_id;

        std::string title;
        std::string release_date;
        std::string cover_art;
    };

    struct track{
        uint32_t id;
        std::string title;
        std::string duration;
        std::string audio_file;
        std::string bit_rate;
        std::string sample_freq;
    };

    struct genres{
        uint32_t id;
        std::string name;
    };

    struct track_genres{
        uint32_t track_id;
        uint32_t genres_id;
    };
}
#endif //MUSIC_DB_MODELS_H
