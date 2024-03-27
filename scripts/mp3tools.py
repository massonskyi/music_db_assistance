import io

import eyed3

import shutil
import base64
import os
from PIL import Image
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
script_dir = os.path.dirname(os.path.realpath(__file__))
project_dir = os.path.abspath(os.path.join(script_dir, ".."))

print("Script directory:", script_dir)
print("Project directory:", project_dir)


def get_metadata_from_file(filepath):
    """
    Function to get information from an MP3 file
    """
    print(filepath)
    name = os.path.basename(filepath).split(".")[0]
    mp3file = eyed3.load(filepath)
    try:
        info = {
            "filename": filepath,
            "title": mp3file.tag.title if mp3file.tag.title is not None else " ",
            "artist": mp3file.tag.artist if mp3file.tag.artist is not None else "nullptr",
            "album": mp3file.tag.album if mp3file.tag.album is not None else "nullptr",
            "release_date": mp3file.tag.release_date if mp3file.tag.release_date is not None else "nullptr",
            "genre": mp3file.tag.genre.name if mp3file.tag.genre is not None else "nullptr",
            "duration": str(mp3file.info.time_secs) if mp3file.info.time_secs is not None else "nullptr",
            "track_number": str(mp3file.tag.track_num.count) if mp3file.tag.track_num is not None else "nullptr",
            "album_artist": mp3file.tag.album_artist if mp3file.tag.album_artist is not None else "nullptr",
            "bitrate": mp3file.info.bit_rate_str if mp3file.info.bit_rate_str is not None else "nullptr",
            "sample_rate": str(mp3file.info.sample_freq) if mp3file.info.sample_freq is not None else "nullptr",
        }
        if mp3file.tag.images:
            filepath = f"{project_dir}/res/{name}.jpg"
            image_data = mp3file.tag.images[0].image_data
            image = Image.open(io.BytesIO(image_data))
            image.save(filepath)
            info["cover"] = filepath

        info["comments"] = [comment.text for comment in mp3file.tag.comments]

    except Exception as e:
        return e
    return info


def copy_file_to_buffer(filepath):
    with open(filepath, "rb") as f:
        file_buffer = base64.b64encode(f.read()).decode()
    return file_buffer


def move_file_from_buffer(file_buffer, filename):
    try:
        print(os.path.basename(filename))
        filename = os.path.basename(filename)
        dest_dir = f"{project_dir}/res"
        file_buffer = base64.b64decode(file_buffer)
        os.makedirs(dest_dir, exist_ok=True)

        dest_filepath = os.path.join(dest_dir, filename)

        with open(dest_filepath, "wb") as f:
            f.write(file_buffer)

        return dest_filepath
    except Exception as e:
        print(f"Error: {e}")


def move_file_to_directory(filepath, dest_dir="/res"):
    filename = os.path.basename(filepath)
    dest_filepath = os.path.join(dest_dir, filename)
    shutil.copy(filepath, dest_filepath)
    return dest_filepath

print(get_metadata_from_file("/home/user064/Downloads/Молчат судна.mp3"))
