#pragma once

#include "lib/spotify/api.hpp"
#include "lib/cache.hpp"

#include <QApplication>
#include <QDesktopServices>
#include <QMenu>

class AlbumMenu: public QMenu
{
Q_OBJECT

public:
	AlbumMenu(lib::spt::api &spotify, lib::cache &cache, const std::string &albumId,
		QWidget *parent);

private:
	QWidget *parent = nullptr;
	std::vector<lib::spt::track> tracks;
	std::string albumId;
	lib::spt::api &spotify;
	QAction *trackCount = nullptr;

	void tracksLoaded(const std::vector<lib::spt::track> &items);

	void shuffle(bool checked);
	void shareAlbum(bool checked);
	void shareOpen(bool checked);
};
