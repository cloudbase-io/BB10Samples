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
