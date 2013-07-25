/* Copyright (c) 2013 Cloudbase.io Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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

