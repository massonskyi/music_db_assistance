#include "../includes/controllers.h"

namespace artist_controller{
    ArtistModel::ArtistModel(const std::vector<models::artist> &artists): artists_(artists) {}

    [[nodiscard]] int ArtistModel::rowCount(const QModelIndex &parent) const {
        return artists_.size();
    }

    [[nodiscard]] int ArtistModel::columnCount(const QModelIndex &parent) const {
        return 4;
    }

    [[nodiscard]] QVariant ArtistModel::data(const QModelIndex &index, int role) const {
        if (role == Qt::DisplayRole) {
            switch (index.column()) {
                case 0: return artists_[index.row()].id;
                case 1: return artists_[index.row()].name.c_str();
                case 2: return artists_[index.row()].biography.c_str();
                case 3: return artists_[index.row()].photo.c_str();
            }
        }
        return {};
    }

    [[nodiscard]] QVariant ArtistModel::headerData(int section, Qt::Orientation orientation, int role) const {
        if (role == Qt::DisplayRole) {
            if (orientation == Qt::Horizontal) {
                switch (section) {
                    case 0: return "ID";
                    case 1: return "Имя";
                    case 2: return "Биография";
                    case 3: return "Фото";
                }
            }
        }
        return {};
    }

    void ArtistModel::update() {
        emit dataChanged(QModelIndex(), QModelIndex());
    }



}
namespace album_controller{

    AlbumModel::AlbumModel(const std::vector<models::album> &albums):albums_(albums) {}

    [[nodiscard]] int AlbumModel::rowCount(const QModelIndex &parent) const {
        return albums_.size();
    }

    [[nodiscard]] int AlbumModel::columnCount(const QModelIndex &parent) const {
        return 5;
    }

    [[nodiscard]] QVariant AlbumModel::data(const QModelIndex &index, int role) const {
        if (role == Qt::DisplayRole) {
            switch (index.column()) {
                case 0: return albums_[index.row()].id;
                case 1: return albums_[index.row()].title.c_str();
                case 2: return albums_[index.row()].release_date.c_str();
                case 3: return albums_[index.row()].artist_id;
                case 4: return albums_[index.row()].cover_art.c_str();
            }
        }
        return {};
    }

    [[nodiscard]] QVariant AlbumModel::headerData(int section, Qt::Orientation orientation, int role) const {
        if (role == Qt::DisplayRole) {
            if (orientation == Qt::Horizontal) {
                switch (section) {
                    case 0: return "ID";
                    case 1: return "Название";
                    case 2: return "Дата Релиза";
                    case 3: return "Автор";
                    case 4: return "Фото";
                }
            }
        }
        return {};
    }
    void AlbumModel::update() {
        emit dataChanged(QModelIndex(), QModelIndex());
    }

}

namespace track_controller{

    TrackModel::TrackModel(const std::vector<models::track>& track): tracks_(track) {}

    [[nodiscard]] int TrackModel::rowCount(const QModelIndex &parent) const {
        return tracks_.size();
    }

    [[nodiscard]] int TrackModel::columnCount(const QModelIndex &parent) const {
        return 5;
    }

    [[nodiscard]] QVariant TrackModel::data(const QModelIndex &index, int role) const {
        if (role == Qt::DisplayRole) {
            switch (index.column()) {
                case 0: return tracks_[index.row()].id;
                case 1: return tracks_[index.row()].title.c_str();
                case 2: return tracks_[index.row()].duration.c_str();
                case 3: return tracks_[index.row()].album_id;
                case 4: return tracks_[index.row()].audio_file.c_str();
            }
        }
        return {};
    }

    [[nodiscard]] QVariant TrackModel::headerData(int section, Qt::Orientation orientation, int role) const {
        if (role == Qt::DisplayRole) {
            if (orientation == Qt::Horizontal) {
                switch (section) {
                    case 0: return "ID";
                    case 1: return "Название";
                    case 2: return "Продолжительность";
                    case 3: return "Альбом";
                    case 4: return "Путь к файлу";
                }
            }
        }
        return {};
    }
    void TrackModel::update() {
        emit dataChanged(QModelIndex(), QModelIndex());
    }
};

namespace genres_controller{

    GenresModel::GenresModel(const std::vector<models::genres>& genres) : genres_(genres) {}

    [[nodiscard]] int GenresModel::rowCount(const QModelIndex &parent) const {
        return genres_.size();
    }

    [[nodiscard]] int GenresModel::columnCount(const QModelIndex &parent) const {
        return 2;
    }

    [[nodiscard]] QVariant GenresModel::data(const QModelIndex &index, int role) const {
        if (role == Qt::DisplayRole) {
            switch (index.column()) {
                case 0: return genres_[index.row()].id;
                case 1: return genres_[index.row()].name.c_str();
            }
        }
        return {};
    }

    [[nodiscard]] QVariant GenresModel::headerData(int section, Qt::Orientation orientation, int role) const {
        if (role == Qt::DisplayRole) {
            if (orientation == Qt::Horizontal) {
                switch (section) {
                    case 0: return "ID";
                    case 1: return "Название";
                }
            }
        }
        return {};
    }
    void GenresModel::update() {
        emit dataChanged(QModelIndex(), QModelIndex());
    }
}
namespace track_genres_controller{

    TrackGendersModel::TrackGendersModel(const std::vector<models::track_genres> &track_genres): track_genres_(track_genres) {}

    [[nodiscard]] int TrackGendersModel::rowCount(const QModelIndex &parent) const {
        return track_genres_.size();
    }

    [[nodiscard]] int TrackGendersModel::columnCount(const QModelIndex &parent) const {
        return 2;
    }

    [[nodiscard]] QVariant TrackGendersModel::data(const QModelIndex &index, int role) const {
        if (role == Qt::DisplayRole) {
            switch (index.column()) {
                case 0: return track_genres_[index.row()].track_id;
                case 1: return track_genres_[index.row()].genres_id;
            }
        }
        return {};
    }

    [[nodiscard]] QVariant TrackGendersModel::headerData(int section, Qt::Orientation orientation, int role) const {
        if (role == Qt::DisplayRole) {
            if (orientation == Qt::Horizontal) {
                switch (section) {
                    case 0: return "TRACK_ID";
                    case 1: return "GENRES_ID";
                }
            }
        }
        return {};
    }
    void TrackGendersModel::update() {
        emit dataChanged(QModelIndex(), QModelIndex());
    }
}