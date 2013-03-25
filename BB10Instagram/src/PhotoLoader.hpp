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

/**
 * Loads the contents of the photos collection on the cloudbase.io Cloud Database
 * Once a picture is loaded into a Photo object the receivedPhoto SIGNAL is emitted
 */
class PhotoLoader : public QObject, Cloudbase::CBHelperResponder
{
    Q_OBJECT
public:
    /**
     * Creates a new PhotoLoader object
     *
     * @param initializedHelper An initialized CBHelper object
     */
    PhotoLoader(Cloudbase::CBHelper *initializedHelper);

    /**
     * Loads all of the photos available in the collection
     */
    void loadPhotos();
    /**
     * Loads all of the photos for a specific user from the photos collection
     *
     * @param user The username to look for
     */
    void loadPhotos(QString user);

    /**
     * Receives the data from the CBHelper object and creates Photo objects. Once a photo
     * object is populated the receivedPhoto SIGNAL is emitted
     */
    virtual void parseResponse(Cloudbase::CBHelperResponseInfo resp);
private:
    Cloudbase::CBHelper *helper; // the initialized helper class

signals:
	void receivedPhoto(Photo* photo);
};

#endif /* PHOTOLOADER_HPP_ */
