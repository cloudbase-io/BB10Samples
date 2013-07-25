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
#include <bb/cascades/VisualNode>

#include "CBHelper.h"

#include "../model/Photo.hpp"

#ifndef PHOTODOWNLOADRESPONDER_HPP_
#define PHOTODOWNLOADRESPONDER_HPP_

class PhotoDownloadResponder : public QObject, Cloudbase::CBHelperResponder {
	Q_OBJECT
public:
	PhotoDownloadResponder(Photo* photo, bb::cascades::VisualNode *listItem) : photo_(photo), listItem_(listItem) {};

	virtual void parseResponse(Cloudbase::CBHelperResponseInfo resp);
private:
	Photo* photo_;
	bb::cascades::VisualNode *listItem_;
signals:
	void photoDownloaded(Photo* photo);
	void photoDownloadFailed(Photo* photo, QString error);
};

#endif /* PHOTODOWNLOADRESPONDER_HPP_ */
