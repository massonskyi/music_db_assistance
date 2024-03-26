#ifndef MUSIC_DB_IMUSIC_H
#define MUSIC_DB_IMUSIC_H
#include <memory>
#include <vector>

#include <QWidget>

#include "SQLiteDB.h"
#include "models.h"
#include "consts.h"
#include "controllers.h"
#include "functiontools.h"
#include "hpp/out.hpp"
class QVBoxLayout;
class QTabWidget;
class QLabel;

class IMusic : public QWidget{
    Q_OBJECT

public:
    explicit IMusic(QWidget* parent = nullptr);

    std::vector<models::artist> GetArtists();
    std::vector<models::album> GetAlbum();
    std::vector<models::track> GetTrack();
    std::vector<models::genres> GetGenres();
    std::vector<models::track_genres> GetTrackGenres();

    void AddArtist(const models::artist&);
    void AddAlbum(const models::album&);
    void AddTrack(const models::track&);
    void AddGenres(const models::genres&);
    void AddTrackGenres(const models::track_genres& );
protected:
    void dropEvent(QDropEvent*) override;
    void dragEnterEvent(QDragEnterEvent*) override;
private:
    bool initializeWindow();
    bool createArtistInputSection();
    bool createAlbumInputSection();
    bool createTrackInputSection();
    bool createTabWidget();
    bool initializeDatabase();
    bool loadDataFromDatabase();
    QWidget* artistWidget{};
    QWidget* albumWidget{};
    QWidget* trackWidget{};
    QVBoxLayout* artistInputLayout{};
    QVBoxLayout* albumInputLayout{};
    QVBoxLayout* trackInputLayout{};
    QTabWidget* tabWidget{};
    QLabel* dropTargetLabel{};
    SQLiteDB db_;
    std::vector<models::artist> artists_;
    std::vector<models::album> albums_;
    std::vector<models::track> tracks_;
    std::vector<models::genres> genres_;
    std::vector<models::track_genres> track_genres_;
    artist_controller::ArtistModel* artists_model_{};
    album_controller::AlbumModel* albums_model_{};
    track_controller::TrackModel* tracks_model_{};
    genres_controller::GenresModel* genres_model_{};
    track_genres_controller::TrackGendersModel* track_genres_model_{};
};
#endif //MUSIC_DB_IMUSIC_H
