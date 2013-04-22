/*
 * User.hpp
 *
 *  Created on: Mar 24, 2013
 *      Author: stef
 */

#ifndef PHOTO_HPP_
#define PHOTO_HPP_

 #include <QDateTime>

#include "CBSerializable.h"

class Photo : public Cloudbase::CBSerializable {
public:
	//Photo() {};
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
