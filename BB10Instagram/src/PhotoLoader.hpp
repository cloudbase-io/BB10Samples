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
#include "CBHelper.h"
#include <QVariant>
#include <QDataStream>

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
	void receivedPhotos(QVariantList photos);
};

#endif /* PHOTOLOADER_HPP_ */
