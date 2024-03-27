#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include <QLabel>
#include <QtWidgets>
#include <QMessageBox>
#include "../includes/hpp/out.hpp"
#include "../includes/IMusic.h"
using namespace album_controller;
using namespace artist_controller;
using namespace track_controller;
using namespace genres_controller;
using namespace track_genres_controller;

IMusic::IMusic(QWidget *parent)
: QWidget(parent), db_(cst::kDatabaseFilename)
{
    out::print("Начало инициализации проекта");
    int r = this->initializeWindow();
    if(!r){
        throw std::runtime_error("Не удалось инициализировать окно");
    }
    r = this->loadDataFromDatabase();
    if(!r){
        throw std::runtime_error("Не удалось загрузить данные из БД");
    }
    r = this->createArtistInputSection();
    if(!r){
        throw std::runtime_error("Не создать окно для ввода артиста");
    }
    r = this->createAlbumInputSection();
    if(!r){
        throw std::runtime_error("Не создать окно для ввода альбома");
    }
    r = this->createTrackInputSection();
    if(!r){
        throw std::runtime_error("Не создать окно для ввода трека");
    }

    r = this->createTabWidget();
    if(!r){
        throw std::runtime_error("Не создать виджет для ввода данных");
    }
    this->dropTargetLabel->setAcceptDrops(true);
    out::print("Конец инициализации");
}
bool IMusic::initializeWindow(){
    try {
        this->setMinimumWidth(settings::min_width);
        this->setMinimumHeight(settings::min_height);
        this->setMaximumWidth(settings::max_width);
        this->setMaximumHeight(settings::max_height);
        this->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);

        this->setAcceptDrops(true);
        return true;
    }catch(...){
        return false;
    }
}
bool IMusic::createArtistInputSection(){
    try {
        this->artistWidget = new QWidget(this);
        this->artistWidget->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);

        auto *artistsTableView = new QTableView(this);
        auto *artistNameLabel = new QLabel("Имя исполнителя:");
        auto *artistNameLineEdit = new QLineEdit(this);
        auto *artistBiographyLabel = new QLabel("Биография:");
        auto *artistBiographyLineEdit = new QLineEdit(this);
        auto *artistPhotoPathLabel = new QLabel("Фотография:");
        auto *artistPhotoPathLineEdit = new QLineEdit(this);
        auto *addArtistButton = new QPushButton("Добавить исполнителя", this);

        this->artistInputLayout = new QVBoxLayout();
        this->artistInputLayout->addWidget(artistNameLabel);
        this->artistInputLayout->addWidget(artistNameLineEdit);
        this->artistInputLayout->addWidget(artistBiographyLabel);
        this->artistInputLayout->addWidget(artistBiographyLineEdit);
        this->artistInputLayout->addWidget(artistPhotoPathLabel);
        this->artistInputLayout->addWidget(artistPhotoPathLineEdit);
        this->artistInputLayout->addWidget(addArtistButton);
        this->artistInputLayout->addWidget(artistsTableView);
        this->artistWidget->setLayout(this->artistInputLayout);

        connect(addArtistButton, &QPushButton::clicked, this,
                [this, artistNameLineEdit, artistBiographyLineEdit, artistPhotoPathLineEdit]() {
                    models::artist artist;
                    artist.name = artistNameLineEdit->text().toStdString();
                    artist.biography = artistBiographyLineEdit->text().toStdString();
                    artist.photo = artistPhotoPathLineEdit->text().toStdString();
                    this->AddArtist(artist);
                });

        artistsTableView->setModel(this->artists_model_);
        artistsTableView->horizontalHeader()->setStretchLastSection(true);
        return true;
    }catch(...){
        return false;
    }
}
bool IMusic::createAlbumInputSection(){
    try{
        this->albumWidget = new QWidget(this);
        this->albumWidget->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);


        auto* albumTableView = new QTableView(this);
        auto* albumTitleLabel = new QLabel("Название альбома:");
        auto* albumTitleLineEdit = new QLineEdit(this);
        auto* albumReleaseDateLabel = new QLabel("Дата выхода:");
        auto* albumReleaseDateLineEdit = new QLineEdit(this);
        auto* albumCoverArtLabel = new QLabel("Обложка:");
        auto* albumCoverArtLineEdit = new QLineEdit(this);
        auto* addAlbumButton = new QPushButton("Добавить альбом", albumWidget);

        this->albumInputLayout = new QVBoxLayout();
        this->albumInputLayout->addWidget(albumTitleLabel);
        this->albumInputLayout->addWidget(albumTitleLineEdit);
        this->albumInputLayout->addWidget(albumReleaseDateLabel);
        this->albumInputLayout->addWidget(albumReleaseDateLineEdit);
        this->albumInputLayout->addWidget(albumCoverArtLabel);
        this->albumInputLayout->addWidget(albumCoverArtLineEdit);
        this->albumInputLayout->addWidget(addAlbumButton);
        this->albumInputLayout->addWidget(albumTableView);
        this->albumWidget->setLayout(this->albumInputLayout);

        connect(addAlbumButton,&QPushButton::clicked,this,
                [this, albumTitleLineEdit, albumReleaseDateLineEdit, albumCoverArtLineEdit]() {
                    models::album album;
                    album.title = albumTitleLineEdit->text().toStdString();
                    album.release_date = albumReleaseDateLineEdit->text().toStdString();
                    album.cover_art = albumCoverArtLineEdit->text().toStdString();
                    this->AddAlbum(album);
                });

        albumTableView->setModel(this->albums_model_);
        albumTableView->horizontalHeader()->setStretchLastSection(true);
        return true;
    }catch(...){
        return false;
    }
}
bool IMusic::createTrackInputSection() {
    try {
        this->trackWidget = new QWidget(this);
        this->trackWidget->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);

        auto *trackTableView = new QTableView(this);
        auto *trackTitleLabel = new QLabel("Название трека:");
        auto *trackTitleLineEdit = new QLineEdit(this);
        auto *trackDurationLabel = new QLabel("Продолжительность:");
        auto *trackDurationLineEdit = new QLineEdit(this);
        auto *trackAudioFileLabel = new QLabel("Аудиофайл:");
        auto *trackAudioFileLineEdit = new QLineEdit(this);
        auto *addTrackButton = new QPushButton("Добавить трек", trackWidget);

        dropTargetLabel = new QLabel(this);
        dropTargetLabel->setText("Drag and drop MP3 files here");
        dropTargetLabel->setAlignment(Qt::AlignCenter);
        dropTargetLabel->setMinimumHeight(120);

        this->trackInputLayout = new QVBoxLayout();
        this->trackInputLayout->addWidget(trackTitleLabel);
        this->trackInputLayout->addWidget(trackTitleLineEdit);
        this->trackInputLayout->addWidget(trackDurationLabel);
        this->trackInputLayout->addWidget(trackDurationLineEdit);
        this->trackInputLayout->addWidget(trackAudioFileLabel);
        this->trackInputLayout->addWidget(trackAudioFileLineEdit);
        this->trackInputLayout->addWidget(addTrackButton);
        this->trackInputLayout->addWidget(trackTableView);
        this->trackInputLayout->addWidget(dropTargetLabel);
        this->trackWidget->setLayout(this->trackInputLayout);

        connect(addTrackButton, &QPushButton::clicked, this,
                [this, trackTitleLineEdit, trackDurationLineEdit, trackAudioFileLineEdit]() {
                    models::track track;
                    track.title = trackTitleLineEdit->text().toStdString();
                    track.duration = trackDurationLineEdit->text().toStdString();
                    track.audio_file = trackAudioFileLineEdit->text().toStdString();
                    this->AddTrack(track);
                });

        trackTableView->setModel(this->tracks_model_);
        trackTableView->horizontalHeader()->setStretchLastSection(true);
        return true;
    }catch(...){
        return false;
    }
}

bool IMusic::createTabWidget(){
    try {

        this->tabWidget = new QTabWidget(this);
        this->tabWidget->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);

        this->tabWidget->addTab(this->artistWidget, "Исполнитель");
        this->tabWidget->addTab(this->albumWidget, "Альбом");
        this->tabWidget->addTab(this->trackWidget, "Трек");

        auto *layout = new QVBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(this->tabWidget);
        return true;
    }catch(...){
        return false;
    }
}

bool IMusic::loadDataFromDatabase(){
    try {
        this->artists_ = GetArtists();
        this->artists_model_ = new ArtistModel(this->artists_, this->db_);
        this->albums_ = GetAlbum();
        this->albums_model_ = new AlbumModel(this->albums_,this->db_);
        this->tracks_ = GetTrack();
        this->tracks_model_ = new TrackModel(this->tracks_,this->db_);

        this->genres_ = GetGenres();
        this->genres_model_ = new GenresModel(this->genres_,this->db_);

        this->track_genres_ = GetTrackGenres();
        this->track_genres_model_ = new TrackGendersModel(this->track_genres_,this->db_);
        return true;
    }catch(...){
        return false;
    }
}

void IMusic::dragEnterEvent(QDragEnterEvent* event){
    if (event->mimeData()->hasUrls()) {
        auto urls = event->mimeData()->urls();
        bool hasMp3 = false;
        for (const QUrl& url : urls) {
            if (url.fileName().endsWith(".mp3", Qt::CaseInsensitive)) {
                hasMp3 = true;
                break;
            }
        }
        if (hasMp3) {
            event->acceptProposedAction();  // Accept the drop if MP3 is found
            dropTargetLabel->setStyleSheet("background-color: lightblue;");  // Optional visual cue
        } else {
            event->ignore();  // Ignore the drop if not MP3
            dropTargetLabel->setStyleSheet("");  // Reset background color (optional)
        }
    } else {
        event->ignore();  // Ignore non-URL data
    }
}

void IMusic::dropEvent(QDropEvent* event) {
    if (event->mimeData()->hasUrls()) {
        QList<QUrl> urls = event->mimeData()->urls();
        for (const QUrl& url : urls) {
            QString filePath = url.toLocalFile();
            if (filePath.endsWith(".mp3", Qt::CaseInsensitive)) {
                out::print(std::format("Dropped MP3 file: {}",filePath.toStdString()));
                std::string buffer = ft::copy_file_to_buffer_python(filePath.toStdString());
                std::string new_path = ft::move_file_from_buffer_to_directory_python(buffer,filePath.toStdString());
                std::vector<std::pair<const char*, const char*>> metadata = ft::get_metadata_from_mp3(new_path);
                if(!metadata.empty()){
                    /*
                    models::artist artist;
                    artist.name = metadata[2].second;
                    artist.biography = "undefined";
                    artist.photo = "undefined";
                    this->AddArtist(artist);
                    models::album album;
                    if(metadata[3].second == NULL || strcmp(metadata[3].second, "nullptr") == 0){
                        album.title = "undefined";
                    }else{
                        album.title = metadata[3].second;
                    }
                    if(metadata[4].second == NULL || strcmp(metadata[4].second, "nullptr") == 0){
                        album.release_date = "undefined";
                    }else{
                        album.release_date = metadata[4].second;
                    }
                    album.artist_id = this->db_.GetIdArtistFromName(artist.name);

                    if(metadata[11].second == NULL || strcmp(metadata[11].second, "nullptr") == 0) {
                        album.cover_art = "undefined";
                    }else{
                        album.cover_art = metadata[11].second;
                    }
                    this->AddAlbum(album);
                     */
                    models::track track;
                    if(metadata[1].second == NULL || strcmp(metadata[1].second, "nullptr") == 0 || strcmp(metadata[1].second, " ") == 0) {
                        track.title = "undefined";
                    }else{
                        track.title = std::string(metadata[1].second);
                    }
                    if(metadata[6].second == NULL || strcmp(metadata[6].second, "nullptr") == 0) {
                        track.duration = "undefined";
                    }else{
                        track.duration = metadata[6].second;
                    }
                    track.audio_file = metadata[0].second;
                    track.bit_rate = metadata[9].second;
                    track.sample_freq = metadata[10].second;
                    this->AddTrack(track);
                    models::genres genre;
                    genre.name = metadata[5].second;
                    this->AddGenres(genre);

                }
            }
        }
    }
    event->acceptProposedAction();  // Accept the drop
    dropTargetLabel->setStyleSheet("");  // Reset background color (optional)
}
std::vector<models::artist> IMusic::GetArtists() {
    out::print("Вызов функции GetArtists класса IMusic");
    return this->db_.GetArtists();
}

std::vector<models::album> IMusic::GetAlbum() {
    out::print("Вызов функции GetAlbums класса IMusic");
    return this->db_.GetAlbums();
}

std::vector<models::track> IMusic::GetTrack() {
    out::print("Вызов функции GetTracks класса IMusic");
    return this->db_.GetTracks();
}

std::vector<models::genres> IMusic::GetGenres() {
    out::print("Вызов функции GetGenres класса IMusic");
    return this->db_.GetGenres();
}

std::vector<models::track_genres> IMusic::GetTrackGenres() {
    out::print("Вызов функции GetTraskGenres класса IMusic");
    return this->db_.GetTrackGenres();
}

void IMusic::AddArtist(const models::artist &artist) {
    out::print("Вызов функции AddArtist класса IMusic");
    this->db_.AddArtist(artist);
    out::print("Вызов функции GetArtists класса IMusic");
    this->artists_ = GetArtists();
    out::print("Вызов функции update класса ArtistModel");
    this->artists_model_->update();
}

void IMusic::AddAlbum(const models::album& album) {
    out::print("Вызов функции AddAlbums класса IMusic");
    this->db_.AddAlbums(album);
    out::print("Вызов функции GetAlbum класса IMusic");
    this->albums_ = GetAlbum();
    out::print("Вызов функции update класса AlbumModel");
    this->albums_model_->update();
}

void IMusic::AddTrack(const models::track& track) {
    out::print("Вызов функции AddTrack класса IMusic");
    this->db_.AddTrack(track);
    out::print("Вызов функции GetTrack класса IMusic");
    this->tracks_ = GetTrack();
    out::print("Вызов функции update класса TrackModel");
    this->tracks_model_->update();
}

void IMusic::AddGenres(const models::genres& genres) {
    out::print("Вызов функции AddGenres класса IMusic");
    this->db_.AddGenres(genres);
    out::print("Вызов функции GetGenres класса IMusic");
    this->genres_ = GetGenres();
    out::print("Вызов функции update класса GenresModel");
    this->genres_model_->update();
}

void IMusic::AddTrackGenres(const models::track_genres& track_genres) {
    out::print("Вызов функции AddTrackGenres класса IMusic");
    this->db_.AddTrackGenres(track_genres);
    out::print("Вызов функции GetTrackGenres класса IMusic");
    this->track_genres_ = GetTrackGenres();
    out::print("Вызов функции update класса TrackGendersModel");
    this->track_genres_model_->update();
}
