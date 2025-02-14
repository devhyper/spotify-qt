#include "view/context/expandedcontent.hpp"
#include "view/context/abstractcontent.hpp"

Context::ExpandedContent::ExpandedContent(lib::spt::api &spotify, spt::Current &current,
	const lib::cache &cache, QWidget *parent)
	: AbstractContent(spotify, current, cache, parent)
{
	auto *layout = AbstractContent::layout<QGridLayout>();

	album = new QLabel(this);
	album->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	layout->addWidget(album, 0, 0, Qt::AlignBottom);

	// TODO: Add background to text
	nowPlaying = new Context::NowPlaying(this);
	layout->addWidget(nowPlaying, 0, 0, Qt::AlignBottom);

	setFixedHeight(width());
	reset();
}

void Context::ExpandedContent::resizeEvent(QResizeEvent *event)
{
	AbstractContent::resizeEvent(event);
	setFixedHeight(width());
}
