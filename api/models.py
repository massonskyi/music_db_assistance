class artist:
    def __init__(self, name, biography, photo):
        self.name = name
        self.biography = biography
        self.photo = photo


class album:
    def __init__(self, artist_id, title, release_date, cover_art):
        self.artist_id = artist_id
        self.title = title
        self.release_date = release_date
        self.cover_art = cover_art


class track:
    def __init__(self, album_id, title, duration, audio_file):
        self.album_id = album_id
        self.title = title
        self.duration = duration
        self.audio_file = audio_file


class genres:
    def __init__(self, name):
        self.name = name


class track_genres:
    def __init__(self, track_id, genres_id):
        self.track_id = track_id
        self.genres_id = genres_id
