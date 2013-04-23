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

    // The global cloudbase.io helper class object
    Cloudbase::CBHelper *helper;
    bb::cascades::AbstractPane *root;
    // Global photoloader object to receive data from cloudbase.io
    PhotoLoader *loader;

    bb::system::InvokeManager *invokeManager;
signals:
	void photosLoaded(QString filePath);
public slots:
	void childCardDone(const bb::system::CardDoneMessage &message);

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

	// These slots are called by the downloader every time a download completes or fails.
	// the main UI is updated directly by the PhotoDownloader object using the VisualNode
	// it receives in its constructor - These are used only as debug methods here to monitor
	// the activity of the downloader.
	void photoDownloaded(Photo* photo);
	void photoDownloadFailed(Photo* photo, QString error);
};

#endif /* ApplicationUI_HPP_ */
