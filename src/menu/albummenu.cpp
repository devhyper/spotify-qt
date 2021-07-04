#include "albummenu.hpp"
#include "mainwindow.hpp"

AlbumMenu::AlbumMenu(lib::spt::api &spotify, lib::cache &cache, const std::string &albumId,
	QWidget *parent)
	: parent(parent),
	albumId(albumId),
	spotify(spotify),
	QMenu(parent)
{
	trackCount = addAction("...");
	trackCount->setEnabled(false);

	tracksLoaded(cache.get_tracks(albumId));
	spotify.album(albumId, [this](const lib::spt::album &album)
	{
		this->spotify.album_tracks(album, [this](const std::vector<lib::spt::track> &items)
		{
			this->tracksLoaded(items);
		});
	});

	addSeparator();
	auto *playShuffle = addAction(Icon::get("media-playlist-shuffle"), "Shuffle play");
	QAction::connect(playShuffle, &QAction::triggered, this, &AlbumMenu::shuffle);

	auto *share = addMenu(Icon::get("document-share"), "Share");
	auto *sharePlaylist = share->addAction("Copy album link");
	QAction::connect(sharePlaylist, &QAction::triggered, this, &AlbumMenu::shareAlbum);

	auto *shareSongOpen = share->addAction("Open in Spotify");
	QAction::connect(shareSongOpen, &QAction::triggered, this, &AlbumMenu::shareOpen);
}

void AlbumMenu::shuffle(bool /*checked*/)
{
	if (tracks.empty())
	{
		auto *mainWindow = MainWindow::find(parentWidget());
		mainWindow->setStatus("No tracks found to shuffle", true);
		return;
	}

	auto initialIndex = lib::random().next_int(0, tracks.size());
	spotify.play_tracks(initialIndex, lib::spt::api::to_uri("album", albumId),
		[this](const std::string &status)
		{
			auto *mainWindow = MainWindow::find(this->parent);
			if (!status.empty())
			{
				mainWindow->status(status, true);
				return;
			}

			spotify.set_shuffle(true, [mainWindow](const std::string &status)
			{
				mainWindow->status(status, true);
			});
		});
}

void AlbumMenu::shareAlbum(bool /*checked*/)
{
	QApplication::clipboard()->setText(QString("https://open.spotify.com/album/%1")
		.arg(QString::fromStdString(albumId)));
	MainWindow::find(parentWidget())->setStatus("Link copied to clipboard");
}

void AlbumMenu::shareOpen(bool /*checked*/)
{
	UrlUtils::open(QString("https://open.spotify.com/album/%1")
		.arg(QString::fromStdString(albumId)), LinkType::Web, this->parent);
}

void AlbumMenu::tracksLoaded(const std::vector<lib::spt::track> &items)
{
	tracks = items;

	auto duration = 0;
	for (auto &track : tracks)
	{
		duration += track.duration;
	}

	constexpr int secInMin = 60;
	constexpr int msToMin = 1000 / secInMin;
	auto minutes = duration / msToMin;

	trackCount->setText(QString("%1 tracks, %2%3 m")
		.arg(tracks.size())
		.arg(minutes >= secInMin
			? QString("%1 h ").arg(minutes / secInMin)
			: QString())
		.arg(minutes % secInMin));
}
