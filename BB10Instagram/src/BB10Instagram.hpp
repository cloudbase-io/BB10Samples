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
#ifndef BB10Instagram_HPP_
#define BB10Instagram_HPP_

#include <QObject>
#include <QtCore>
#include <QFile>
#include <QFileInfo>
#include <QVariant>

#include <bb/cascades/AbstractPane>
#include <bb/cascades/ActivityIndicator>
#include <bb/data/JsonDataAccess>
#include <bb/data/DataSource>
#include <bb/cascades/ListView>
#include <bb/system/InvokeManager>

#include "CBHelper.h"

#include "PhotoLoader.hpp"
#include "model/User.hpp"
#include "model/Photo.hpp"
#include "responder/PhotoUploadResponder.hpp"
#include "responder/PhotoDownloadResponder.hpp"

namespace bb { namespace cascades { class Application; }}

/*!
 * @brief BlackBerry 10 Instagram demo
 *
 * This object initializes the app UI and the cloudbase.io helper class to send and receive data
 */
class BB10Instagram : public QObject, Cloudbase::CBHelperResponder
{
    Q_OBJECT
public:
    BB10Instagram(bb::cascades::Application *app);
    virtual ~BB10Instagram() {};

    /**
     * Receives data from the cloudbase.io APIs. This method in the main object is only used
     * to save the user in the settings tab
     *
     * @param resp The response object from cloudbase.io
     */
    virtual void parseResponse(Cloudbase::CBHelperResponseInfo resp);

    /**
     * Called when the save button is pressed in the settings tab
     */
    Q_INVOKABLE void saveSettings(QString newUsername);

    //Added by lsale
    Q_INVOKABLE void takePicture(QString title, QString tags);

private:
    // The user created by the settings tab when a username is sent to cloudbase.io
    User *userObject;
    // A Photo object to store a new picture being taken while it's uploaded to cloudbase.io
    Photo *newPhoto;

    QString curTitle;
    QString curTags;
    bb::cascades::ListView *m_listView;

    // The global cloudbase.io helper class object
    Cloudbase::CBHelper *helper;
    bb::cascades::AbstractPane *root;
    // Global photoloader object to receive data from cloudbase.io
    PhotoLoader *loader;

    bb::system::InvokeManager *invokeManager;

    // tells us whether the helper class has registered with the cloudbase.io servers yet
    bool helperClassRegistered;
signals:
	void photosLoaded(QString filePath);
public slots:
	/**
	 * Called once a picture is taken and is ready to be uploaded the with picture details
	 */
	void startPicture(QStringList list);

	// These are used by the uploader object to communicate with the main app when
	// photos are being uplaoded
	void photoUploaded(Photo* photo);
	void photoUploadFailed(Photo* photo, QString error);

	// This SLOT is called by the PhotoLoader object every time it receives a new photo
	// from cloudbase.io
	void receivedPhotos(QVariantList photos);
};

#endif /* ApplicationUI_HPP_ */
