/*
 * ImageFolderWatcher.cpp
 *
 *  Created on: 3 Jul 2013
 *      Author: darnold
 */

#include "ImageFolderWatcher.hpp"

ImageFolderWatcher::ImageFolderWatcher() {
	// TODO Auto-generated constructor stub
	connect(this, SIGNAL(imagePathUpdated(QString)), this, SLOT(onImagePathUpdated(QString)));
	connect(this, SIGNAL(imageFilenameUpdated(QString)), this, SLOT(onImageFilenameUpdated(QString)));

	setImagePath(QDir::homePath());
}

ImageFolderWatcher::~ImageFolderWatcher() {
	// TODO Auto-generated destructor stub
	disconnect(this, SIGNAL(imagePathUpdated(QString)), this, SLOT(onImagePathUpdated(QString)));
	disconnect(this, SIGNAL(imageFilenameUpdated(QString)), this, SLOT(onImageFilenameUpdated(QString)));

	if(_fileSystemWatcher)
	{
		disconnect(_fileSystemWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(onDirectoryChanged(QString)));
		delete _fileSystemWatcher;
	}
}

void ImageFolderWatcher::setImagePath(QString imagePath) {



	_imagePath = imagePath;
//	_imagePath = imagePath;
	emit imagePathUpdated(_imagePath);
}

QString ImageFolderWatcher::imagePath() {
	return _imagePath;
}

void ImageFolderWatcher::setImageFilename(QString imageFilename) {
	_imageFilename = imageFilename;
	emit imageFilenameUpdated(imageFilename);
}

QString ImageFolderWatcher::imageFilename() {
	return _imageFilename;
}

void ImageFolderWatcher::onImagePathUpdated(QString imagePath) {
	QStringList list(imagePath);
	if(_fileSystemWatcher)
	{
		disconnect(_fileSystemWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(onDirectoryChanged(QString)));
		delete _fileSystemWatcher;
	}
	_fileSystemWatcher = new QFileSystemWatcher(list);
	bool directoryChange = connect(_fileSystemWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(onDirectoryChanged(QString)));

	Q_ASSERT(directoryChange);

	checkImageExists();
}

void ImageFolderWatcher::onImageFilenameUpdated(QString imageFilename) {
	checkImageExists();
}

void ImageFolderWatcher::onDirectoryChanged(QString path){
	qDebug() << "onDirectoryChanged";

	checkImageExists();

}

void ImageFolderWatcher::checkImageExists() {
	if (imagePath().isNull() && imageFilename().isNull()) {
		return;
	}
	QString fullImageFilename(imageFilename());

	if (QFile::exists (fullImageFilename)) {
		qDebug() << "Emitting imageCreated for " << fullImageFilename;
		emit imageCreated(fullImageFilename);
	}
}

