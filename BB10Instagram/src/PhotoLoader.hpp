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
#include "CBHelper.h"

#include "model/Photo.hpp"

#ifndef PHOTOLOADER_HPP_
#define PHOTOLOADER_HPP_

class PhotoLoader : public QObject, Cloudbase::CBHelperResponder
{
    Q_OBJECT
public:
    PhotoLoader(Cloudbase::CBHelper *initializedHelper);
    //~PhotoLoader();

    void loadPhotos();
    void loadPhotos(QString user);

    virtual void parseResponse(Cloudbase::CBHelperResponseInfo resp);
private:
    Cloudbase::CBHelper *helper;

signals:
	void receivedPhoto(Photo* photo);
};

#endif /* PHOTOLOADER_HPP_ */
