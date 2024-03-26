from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
from sqlite3 import Error

from api.SQLiteBD import SQLiteDB
from models import artist, album, track, genres, track_genres

app = FastAPI()

# Initialize SQLiteDB instance
db = SQLiteDB("/home/user064/CLionProjects/music_db/data/music_database.db")  # Replace "your_database.db" with your actual database file


# Define Pydantic models for request and response bodies
class Artist(BaseModel):
    name: str
    biography: str
    photo: str


class Album(BaseModel):
    artist_id: int
    title: str
    release_date: str
    cover_art: str


class Track(BaseModel):
    album_id: int
    title: str
    duration: str
    audio_file: str


class Genres(BaseModel):
    name: str


class TrackGenres(BaseModel):
    track_id: int
    genres_id: int


# Define endpoints for CRUD operations
@app.get("/artists/")
async def get_artists():
    return db.get_artists()


@app.post("/artists/")
async def add_artist(artist: Artist):
    try:
        db.add_artist(artist)
        return {"message": "Artist added successfully"}
    except Error as e:
        raise HTTPException(status_code=500, detail=f"Error adding artist: {str(e)}")


if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)