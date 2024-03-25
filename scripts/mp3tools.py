import eyed3
import pybind11


def get_mp3_info(filepath):
    """
    Function to get information from an MP3 file
    """
    # Open file
    mp3file = eyed3.load(filepath)

    # Get information
    info = {
        "title": mp3file.tag.title,
        "artist": mp3file.tag.artist,
        "album": mp3file.tag.album,
        "year": mp3file.tag.year,
        "genre": mp3file.tag.genre,
        "duration": mp3file.info.time_secs,
    }

    if mp3file.tag.images:
        info["cover"] = mp3file.tag.images[0].image_data

    # Get comments
    info["comments"] = [comment.text for comment in mp3file.tag.comments]

    return info


# Create Pybind11 module
module = pybind11.module("mp3_info_wrap")
