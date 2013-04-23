/* Copyright (C) 2012 cloudbase.io

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU General Public License, version 2, as published by
 the Free Software Foundation.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 for more details.

 You should have received a copy of the GNU General Public License
 along with this program; see the file COPYING.  If not, write to the Free
 Software Foundation, 59 Temple Place - Suite 330, Boston, MA
 02111-1307, USA.
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

				Photo* newPhoto = new Photo(title, username, tags, "");

				// if we have files attached to the document
				if (!curPhoto->getValueForKey("cb_files")->isNull()) {
					YAJLDom::Value* photoFiles = curPhoto->getValueForKey("cb_files");
					// loop over the files - we may have multiple files as we could be creating
					// thumbnails as well as the full size picture. We assume the thumbnail images
					// contain "thumb" in the file name
					for (int y = 0; y < photoFiles->getNumChildValues(); y++) {
						YAJLDom::Value* curFile = photoFiles->getValueByIndex(y);

						if (std::string::npos == curFile->getValueForKey("file_name")->toString().find("thumb")) {
							newPhoto->setFileId(QString::fromStdString(curFile->getValueForKey("file_id")->toString()));
						} else {
							newPhoto->setThumbnailFileId(QString::fromStdString(curFile->getValueForKey("file_id")->toString()));
						}
					}

					// send the photo back to the application using the SIGNAL
					//emit receivedPhoto(newPhoto);
				}

				QVariantMap photoMap;

				photoMap["title"] = title;
				photoMap["username"] = username;
				photoMap["tags"] = tags;
				photoMap["time"] = photoTime;

				//photos.append(photoMap);
				photos << photoMap;
			}

			emit receivedPhotos(photos);
		}
	}
}
