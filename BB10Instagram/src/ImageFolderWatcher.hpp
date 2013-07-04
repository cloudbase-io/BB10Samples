/*
 * ImageFolderWatcher.hpp
 *
 *  Created on: 3 Jul 2013
 *      Author: darnold
 */

#ifndef IMAGEFOLDERWATCHER_HPP_
#define IMAGEFOLDERWATCHER_HPP_

#include <QOBject>
#include <QString>
#include <QFile>
#include <QFileSystemWatcher>
#include <QStringList>
#include <QDebug>
#include <QDir>

class ImageFolderWatcher : public QObject {

	Q_OBJECT

	Q_PROPERTY(QString imagePath READ imagePath WRITE setImagePath NOTIFY imagePathUpdated)
	Q_PROPERTY(QString imageFilename READ imageFilename WRITE setImageFilename NOTIFY imageFilenameUpdated)

public:
	ImageFolderWatcher();
	virtual ~ImageFolderWatcher();

	void checkImageExists();

	Q_SIGNAL void imagePathUpdated(QString imagePath);

	void setImagePath(QString imagePath);
	QString imagePath();

	Q_SLOT void onImagePathUpdated(QString imagePath);



	Q_SIGNAL void imageFilenameUpdated(QString imageFilename);

	void setImageFilename(QString imageFilename);
	QString imageFilename();

	Q_SLOT void onImageFilenameUpdated(QString imageFilename);



	Q_SLOT void onDirectoryChanged(QString path);



	Q_SIGNAL void imageCreated(QString fullImageFilename);

private:
	QString _imagePath;
	QString _imageFilename;
	QFileSystemWatcher *_fileSystemWatcher;
};

#endif /* IMAGEFOLDERWATCHER_HPP_ */
