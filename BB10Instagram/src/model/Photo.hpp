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
#ifndef PHOTO_HPP_
#define PHOTO_HPP_

 #include <QDateTime>

#include "CBSerializable.h"

class Photo : public Cloudbase::CBSerializable {
public:
	Photo(QString title, QString username, QString tags, QString fileName) :
		title_(title), username_(username), tags_(tags), fileName_(fileName), dateCreated_(QDateTime().toMSecsSinceEpoch()) {};

	std::string serialize() {
		std::string out = "[ { ";
		out += "\"username\" : \"" + username_.toStdString() + "\", ";
		out += "\"title\" : \"";
		out += title_.toUtf8().constData();
		out += "\", ";
		out += "\"tags\" : \"" + tags_.toStdString() + "\", ";
		out += "\"photo_time\" : \"1938474\"";
		//out += dateCreated_;
		out += " } ]";

		return out;
	}

	void setFileId(QString fileId) { fileId_ = fileId; };
	QString getFileId() { return fileId_; };
	void setThumbnailFileId(QString thumbFileId) { thumbFileId_ = thumbFileId; };
	QString getThumbnailFileId() { return thumbFileId_; };

	QString getUsername() { return username_; };
private:
	QString title_;
	QString username_;
	QString tags_;
	QString fileName_;
	qint64 dateCreated_;

	QString fileId_;
	QString thumbFileId_;
};


#endif /* PHOTO_HPP_ */
