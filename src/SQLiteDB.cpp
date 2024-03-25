#include <iostream>
#include <format>

#include "../includes/SQLiteDB.h"

SQLiteDB::SQLiteDB(const std::string &db_name) {
    print("Начало подлючения к базе данных");
    if (sqlite3_open(db_name.c_str(), &db)) {
        std::cerr << "Не удалось открыть базу данных: " << sqlite3_errmsg(db) << std::endl;
        throw std::runtime_error("Failed to open database");
    }
    print(std::format("База данных открыта {}",sqlite3_errmsg(this->db)));
}

SQLiteDB::~SQLiteDB() {
    if(sqlite3_errcode(this->db) == SQLITE_OK) {
        print("База данных будет закрыта");
        sqlite3_close(this->db);
    } else {
        print("База данных не открыта");
    }
}

sqlite3_stmt *SQLiteDB::PrepareStatement(const std::string &sql) {
    print("Вызов функции PrepareStatement класса SQLiteDB");
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(this->db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        print(std::format("Ошибка подготовки SQL-запроса:{}",sqlite3_errmsg(this->db)));
        exit(1);
    }
    return stmt;
}

std::vector<models::artist> SQLiteDB::GetArtists() {
    print("Вызов функции GetArtists класса SQLiteDB");
    std::vector<models::artist> artists;

    sqlite3_stmt* stmt = PrepareStatement(
            "SELECT * FROM artists"
    );

    while(sqlite3_step(stmt) == SQLITE_ROW){
        models::artist artist;

        artist.id = sqlite3_column_int(stmt, 0);
        artist.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        artist.biography = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        artist.photo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

        artists.push_back(artist);
    }
    sqlite3_finalize(stmt);

    return artists;
}

std::vector<models::album> SQLiteDB::GetAlbums() {
    print("Вызов функции GetAlbums класса SQLiteDB");
    std::vector<models::album> albums;

    sqlite3_stmt* stmt = PrepareStatement(
            "SELECT * FROM albums"
    );

    while(sqlite3_step(stmt) == SQLITE_ROW){
        models::album album;

        album.id = sqlite3_column_int(stmt, 0);
        album.title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        album.release_date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        album.artist_id = sqlite3_column_int(stmt, 3);
        album.cover_art = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

        albums.push_back(album);
    }
    sqlite3_finalize(stmt);

    return albums;
}

std::vector<models::track> SQLiteDB::GetTracks() {
    print("Вызов функции GetTracks класса SQLiteDB");
    std::vector<models::track> tracks;

    sqlite3_stmt* stmt = PrepareStatement(
            "SELECT * FROM tracks"
    );

    while(sqlite3_step(stmt) == SQLITE_ROW){
        models::track track;

        track.id = sqlite3_column_int(stmt, 0);
        track.title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        track.duration = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        track.album_id = sqlite3_column_int(stmt, 3);
        track.audio_file = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

        tracks.push_back(track);
    }
    sqlite3_finalize(stmt);

    return tracks;
}

std::vector<models::genres> SQLiteDB::GetGenres() {
    print("Вызов функции GetGenres класса SQLiteDB");
    std::vector<models::genres> genres;

    sqlite3_stmt* stmt = PrepareStatement(
            "SELECT * FROM genres"
    );

    while(sqlite3_step(stmt) == SQLITE_ROW){
        models::genres gen;

        gen.id = sqlite3_column_int(stmt, 0);
        gen.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

        genres.push_back(gen);
    }
    sqlite3_finalize(stmt);

    return genres;
}

std::vector<models::track_genres> SQLiteDB::GetTraskGenres() {
    print("Вызов функции GetTraskGenres класса SQLiteDB");
    std::vector<models::track_genres> tracks_genres;

    sqlite3_stmt* stmt = PrepareStatement(
            "SELECT * FROM track_genres"
    );

    while(sqlite3_step(stmt) == SQLITE_ROW){
        models::track_genres track_gen;

        track_gen.track_id = sqlite3_column_int(stmt, 0);
        track_gen.genres_id = sqlite3_column_int(stmt, 1);

        tracks_genres.push_back(track_gen);
    }
    sqlite3_finalize(stmt);

    return tracks_genres;
}

void SQLiteDB::AddArtist(const models::artist& artist) {
    print("Вызов функции AddArtist класса SQLiteDB");

    sqlite3_stmt* stmt = PrepareStatement(
            "INSERT INTO artists (name, biography, photo) VALUES (?, ?, ?)"
    );

    sqlite3_bind_text(stmt, 1, artist.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, artist.biography.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, artist.photo.c_str(), -1, SQLITE_TRANSIENT);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void SQLiteDB::AddAlbums(const models::album& album) {
    print("Вызов функции AddAlbums класса SQLiteDB");
    sqlite3_stmt* stmt = PrepareStatement(
            "INSERT INTO albums (title, release_date, artist_id, cover_art) VALUES (?, ?, ?, ?)"
    );

    sqlite3_bind_text(stmt, 1, album.title.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, album.release_date.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, (int)album.artist_id);
    sqlite3_bind_text(stmt, 4, album.cover_art.c_str(), -1, SQLITE_TRANSIENT);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void SQLiteDB::AddTrack(const models::track& track) {
    print("Вызов функции AddTrack класса SQLiteDB");
    sqlite3_stmt* stmt = PrepareStatement(
            "INSERT INTO tracks (title, duration, album_id, audiofile) VALUES (?, ?, ?, ?)"
    );

    sqlite3_bind_text(stmt, 1, track.title.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, track.duration.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, (int)track.album_id);
    sqlite3_bind_text(stmt, 4, track.audio_file.c_str(), -1, SQLITE_TRANSIENT);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void SQLiteDB::AddGenres(const models::genres& genres) {
    print("Вызов функции AddGenres класса SQLiteDB");
    sqlite3_stmt* stmt = PrepareStatement(
            "INSERT INTO genres (name) VALUES (?)"
    );

    sqlite3_bind_text(stmt, 1, genres.name.c_str(), -1, SQLITE_TRANSIENT);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void SQLiteDB::AddTrackGenres(const models::track_genres& track_genres) {
    print("Вызов функции AddTrackGenres класса SQLiteDB");
    sqlite3_stmt* stmt = PrepareStatement(
            "INSERT INTO track_genres (track_id, genres_id) VALUES (?, ?)"
    );

    sqlite3_bind_int(stmt, 1, (int)track_genres.track_id);
    sqlite3_bind_int(stmt, 2, (int)track_genres.genres_id);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

