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
