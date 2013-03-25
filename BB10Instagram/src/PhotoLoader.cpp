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
			for (int i = 0; i < resp.parsedMessage->getNumChildValues(); i++) {
				YAJLDom::Value* curPhoto = resp.parsedMessage->getValueByIndex(i);

				QString title = QString::fromStdString(curPhoto->getValueForKey("title")->toString());
				QString username = QString::fromStdString(curPhoto->getValueForKey("username")->toString());
				QString tags = QString::fromStdString(curPhoto->getValueForKey("tags")->toString());
				QString photoTime = QString::fromStdString(curPhoto->getValueForKey("photo_time")->toString());

				Photo* newPhoto = new Photo(title, username, tags, "");

				YAJLDom::Value* photoFiles = curPhoto->getValueForKey("cb_files");
				// loop over the files and initiate the download
				for (int y = 0; y < photoFiles->getNumChildValues(); y++) {
					YAJLDom::Value* curFile = photoFiles->getValueByIndex(y);

					if (std::string::npos == curFile->getValueForKey("file_name")->toString().find("thumb")) {
						newPhoto->setFileId(QString::fromStdString(curFile->getValueForKey("file_id")->toString()));
					} else {
						newPhoto->setThumbnailFileId(QString::fromStdString(curFile->getValueForKey("file_id")->toString()));
					}
				}

				emit receivedPhoto(newPhoto);
			}
		}
	}
}
