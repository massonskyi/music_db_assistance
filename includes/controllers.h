#ifndef MUSIC_DB_CONTROLLERS_H
#define MUSIC_DB_CONTROLLERS_H

#include <QAbstractTableModel>
#include "models.h"

namespace artist_controller{

    class ArtistModel : public QAbstractTableModel {
    public:

        explicit ArtistModel(const std::vector<models::artist>& artists);
        [[nodiscard]] int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        [[nodiscard]] int columnCount(const QModelIndex& parent = QModelIndex()) const override;
        [[nodiscard]] QVariant data(const QModelIndex& index, int role) const override;
        [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    public slots:
        void update();
    private:
        std::vector<models::artist> artists_;
    };

}

namespace album_controller{

    class AlbumModel : public QAbstractTableModel {

    public:
        explicit AlbumModel(const std::vector<models::album>& albums);

        [[nodiscard]] int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        [[nodiscard]] int columnCount(const QModelIndex& parent = QModelIndex()) const override;

        [[nodiscard]] QVariant data(const QModelIndex& index, int role) const override;

        [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    public slots:
        void update();
    private:
        std::vector<models::album> albums_;
    };

}

namespace track_controller{

    class TrackModel : public QAbstractTableModel{
    public:
        explicit TrackModel(const std::vector<models::track>& track);

        [[nodiscard]] int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        [[nodiscard]] int columnCount(const QModelIndex& parent = QModelIndex()) const override;

        [[nodiscard]] QVariant data(const QModelIndex& index, int role) const override;

        [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    public slots:
        void update();
    private:
        std::vector<models::track> tracks_;
    };

}

namespace genres_controller{

    class GenresModel : public QAbstractTableModel{
    public:
        explicit GenresModel(const std::vector<models::genres>& genres);

        [[nodiscard]] int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        [[nodiscard]] int columnCount(const QModelIndex& parent = QModelIndex()) const override;

        [[nodiscard]] QVariant data(const QModelIndex& index, int role) const override;

        [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    public slots:
        void update();
    private:
        std::vector<models::genres> genres_;
    };

}

namespace track_genres_controller{
    class TrackGendersModel : public QAbstractTableModel{
    public:
        explicit TrackGendersModel(const std::vector<models::track_genres>& track_genres);

        [[nodiscard]] int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        [[nodiscard]] int columnCount(const QModelIndex& parent = QModelIndex()) const override;

        [[nodiscard]] QVariant data(const QModelIndex& index, int role) const override;

        [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    public slots:
        void update();
    private:
        std::vector<models::track_genres> track_genres_;
    };
}
#endif //MUSIC_DB_CONTROLLERS_H
