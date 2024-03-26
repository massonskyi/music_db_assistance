import sqlite3
from models import artist, album, track, genres, track_genres


class SQLiteDB:
    def __init__(self, db_name):
        print("Начало подключения к базе данных")
        try:
            self.db = sqlite3.connect(db_name)
            print("База данных открыта")
        except sqlite3.Error as e:
            print("Не удалось открыть базу данных:", str(e))
            raise

    def __del__(self):
        if hasattr(self, 'db') and self.db is not None:
            print("База данных будет закрыта")
            self.db.close()

    def prepare_statement(self, sql):
        print("Вызов функции PrepareStatement класса SQLiteDB")
        try:
            return self.db.cursor().execute(sql)
        except sqlite3.Error as e:
            print("Ошибка подготовки SQL-запроса:", str(e))
            raise

    def get_artists(self):
        print("Вызов функции GetArtists класса SQLiteDB")
        try:
            cursor = self.prepare_statement("SELECT * FROM artists")
            return [artist(*row) for row in cursor.fetchall()]
        except sqlite3.Error as e:
            print("Ошибка при получении списка исполнителей:", str(e))
            raise

    def get_albums(self):
        print("Вызов функции GetAlbums класса SQLiteDB")
        try:
            cursor = self.prepare_statement("SELECT * FROM albums")
            return [album(*row) for row in cursor.fetchall()]
        except sqlite3.Error as e:
            print("Ошибка при получении списка альбомов:", str(e))
            raise

    def get_tracks(self):
        print("Вызов функции GetTracks класса SQLiteDB")
        try:
            cursor = self.prepare_statement("SELECT * FROM tracks")
            array_tracks = cursor.fetchall()
            tracks = []
            for row in array_tracks:
                tracks.append(track(row[3], row[1], row[2], row[4]))
            return tracks
        except sqlite3.Error as e:
            print("Ошибка при получении списка треков:", str(e))
            raise

    def get_genres(self):
        print("Вызов функции GetGenres класса SQLiteDB")
        try:
            cursor = self.prepare_statement("SELECT * FROM genres")
            return [genres(*row) for row in cursor.fetchall()]
        except sqlite3.Error as e:
            print("Ошибка при получении списка жанров:", str(e))
            raise

    def get_track_genres(self):
        print("Вызов функции GetTraskGenres класса SQLiteDB")
        try:
            cursor = self.prepare_statement("SELECT * FROM track_genres")
            return [track_genres(*row) for row in cursor.fetchall()]
        except sqlite3.Error as e:
            print("Ошибка при получении списка жанров треков:", str(e))
            raise

    def add_artist(self, artist):
        print("Вызов функции AddArtist класса SQLiteDB")
        try:
            self.prepare_statement(f"INSERT INTO artists (name, biography, photo) VALUES ({artist.name}, {artist.biography}, {artist.photo})")
            self.db.commit()
        except sqlite3.Error as e:
            print("Ошибка при добавлении исполнителя:", str(e))
            raise

    def add_album(self, album):
        print("Вызов функции AddAlbums класса SQLiteDB")
        try:
            self.prepare_statement(f"INSERT INTO albums (title, release_date, artist_id, cover_art) VALUES ({album.title}, {album.release_date}, {album.artist_id}, {album.cover_art})")
            self.db.commit()
        except sqlite3.Error as e:
            print("Ошибка при добавлении альбома:", str(e))
            raise

    def add_track(self, track):
        print("Вызов функции AddTrack класса SQLiteDB")
        try:
            self.prepare_statement(f"INSERT INTO tracks (title, release_date, album_id, genre_id) VALUES ({track.title},{track.release_date}, {track.album_id}, {track.genre_id})")
            self.db.commit()
        except sqlite3.Error as e:
            print("Ошибка при добавлении трека:", str(e))
            raise

    def add_genres(self, genres):
        print("Вызов функции AddGenres класса SQLiteDB")
        try:
            self.prepare_statement(f"INSERT INTO genres (name) VALUES ({genres.name})")
            self.db.commit()
        except sqlite3.Error as e:
            print("Ошибка при добавлении жанра:", str(e))
            raise

    def add_track_genres(self, track_genres):
        print("Вызов функции AddTrackGenres класса SQLiteDB")
        try:
            self.prepare_statement(f"INSERT INTO track_genres (track_id, genre_id) VALUES ({track_genres.track_id},{track_genres.genre_id})")
            self.db.commit()
        except sqlite3.Error as e:
            print("Ошибка при добавлении жанра трека:", str(e))
            raise

    def get_id_artist_from_name(self, artist_name):
        print("Вызов функции GetIdArtistFromName класса SQLiteDB")
        try:
            cursor = self.prepare_statement(f"SELECT id FROM artists WHERE name = {artist_name}")
            row = cursor.fetchone()
            return row[0] if row else None
        except sqlite3.Error as e:
            print("Ошибка при получении идентификатора исполнителя:", str(e))
            raise

    def get_id_album_from_title(self, album_title):
        print("Вызов функции GetIdAlbumFromTitle класса SQLiteDB")
        try:
            cursor = self.prepare_statement(f"SELECT id FROM albums WHERE title = {album_title}")
            row = cursor.fetchone()
            return row[0] if row else None
        except sqlite3.Error as e:
            print("Ошибка при получении идентификатора альбома:", str(e))
            raise
