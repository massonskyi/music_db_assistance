//
// Created by user064 on 25.03.24.
//

#ifndef MUSIC_DB_SQLITEDB_H
#define MUSIC_DB_SQLITEDB_H
#include <sqlite3.h>
#include <string>
#include <vector>


#include "models.h"
#include "functiontools.h"

class SQLiteDB {
public:
    explicit SQLiteDB(const std::string&);
    ~SQLiteDB();

    std::vector<models::artist> GetArtists();
    std::vector<models::album> GetAlbums();
    std::vector<models::track> GetTracks();
    std::vector<models::genres> GetGenres();
    std::vector<models::track_genres> GetTraskGenres();


    void AddArtist(const models::artist&);
    void AddAlbums(const models::album&);
    void AddTrack(const models::track&);
    void AddGenres(const models::genres&);
    void AddTrackGenres(const models::track_genres&);
protected:
    sqlite3_stmt* PrepareStatement(const std::string&);

private:
    ft::print_info print;
    sqlite3* db;
};


#endif //MUSIC_DB_SQLITEDB_H
