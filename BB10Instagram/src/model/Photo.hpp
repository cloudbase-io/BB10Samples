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
		out += "\"title\" : \"" + title_.toStdString() + "\", ";
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
