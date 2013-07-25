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
#include "PhotoLoader.hpp"

using namespace Cloudbase;

PhotoLoader::PhotoLoader(CBHelper *initializedHelper) {
	helper = initializedHelper;
}

void PhotoLoader::loadPhotos() {
	if ( helper != NULL ) {
		CBHelperSearchCondition *cond = new CBHelperSearchCondition();
		// sort descending based on photo_time
		cond->addSortField("photo_time", Cloudbase::CBSortDescending);
		helper->searchDocument("photos", cond, this);
	}
}

void PhotoLoader::loadPhotos(QString user) {
	if ( helper != NULL ) {
		CBHelperSearchCondition *cond = new CBHelperSearchCondition("username", user.toStdString(), Cloudbase::CBOperatorEqual);
		// sort descending based on photo_time
		cond->addSortField("photo_time", Cloudbase::CBSortDescending);
		helper->searchDocument("photos", cond, this);
	}
}

void PhotoLoader::parseResponse(Cloudbase::CBHelperResponseInfo resp) {

	if ( resp.function == "download" ) {
		qDebug() << "received file";
		QString oldName = QString::fromStdString(resp.downloadedFileName);
		QString newName = QString::fromStdString(resp.downloadedFileName+".jpg");
		QFile::rename(oldName, newName);
		qDebug() << QString::fromStdString(resp.downloadedFileName);
		return;
	}

	qDebug() << "error message: " << resp.errorMessage.c_str();
	if ( resp.postSuccess ) {
		if ( resp.parsedMessage->getType() == YAJLDom::Value::ARRAY ) {
			QVariantList photos;
			// loop over the array of objects from the photos collection
			for (int i = 0; i < resp.parsedMessage->getNumChildValues(); i++) {
				YAJLDom::Value* curPhoto = resp.parsedMessage->getValueByIndex(i);

				// get all the basic data for the current object
				QString title = QString::fromStdString(curPhoto->getValueForKey("title")->toString());
				QString username = QString::fromStdString(curPhoto->getValueForKey("username")->toString());
				QString tags = QString::fromStdString(curPhoto->getValueForKey("tags")->toString());
				QString photoTime = QString::fromStdString(curPhoto->getValueForKey("photo_time")->toString());
				QString filePath = "";

				Photo* newPhoto = new Photo(title, username, tags, "");

				// if we have files attached to the document
				if (!curPhoto->getValueForKey("cb_files")->isNull()) {
					YAJLDom::Value* photoFiles = curPhoto->getValueForKey("cb_files");
					// loop over the files - we may have multiple files as we could be creating
					// thumbnails as well as the full size picture. We assume the thumbnail images
					// contain "thumb" in the file name
					for (int y = 0; y < photoFiles->getNumChildValues(); y++) {
						qDebug() << "loop over files";
						YAJLDom::Value* curFile = photoFiles->getValueByIndex(y);

						qDebug() << "starting download";
						const QDir home = QDir::currentPath()+"/data/";
						QString fileIdString = QString::fromStdString(curFile->getValueForKey("file_id")->toString());
						filePath = home.absoluteFilePath(fileIdString);
						newPhoto->setThumbnailFileId(filePath);
						helper->downloadFile(curFile->getValueForKey("file_id")->toString(), this);

						qDebug() << "file path: " << filePath;
					}

					// send the photo back to the application using the SIGNAL
					//emit receivedPhoto(newPhoto);
				} else {
					qDebug() << "no files";
				}

				QVariantMap photoMap;
				qDebug() << "loaded photo: " << title;
				photoMap["title"] = title;
				photoMap["imageSource"] = filePath;
				photoMap["username"] = username;
				photoMap["tags"] = tags;
				photoMap["time"] = photoTime;

				//photos.append(photoMap);
				photos << photoMap;
			}
			qDebug() << "Emitting signal receivedPhotos";
			emit receivedPhotos(photos);
		}
	}

}
