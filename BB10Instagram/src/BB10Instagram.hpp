// Tabbed pane project template
#ifndef BB10Instagram_HPP_
#define BB10Instagram_HPP_

#include <QObject>

#include <bb/cascades/AbstractPane>
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
#include <bb/cascades/ActivityIndicator>

#include "CBHelper.h"

#include "PhotoLoader.hpp"
#include "model/User.hpp"
#include "model/Photo.hpp"
#include "responder/PhotoUploadResponder.hpp"
#include "responder/PhotoDownloadResponder.hpp"

namespace bb { namespace cascades { class Application; }}

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class BB10Instagram : public QObject, Cloudbase::CBHelperResponder
{
    Q_OBJECT
public:
    BB10Instagram(bb::cascades::Application *app);
    virtual ~BB10Instagram() {};

    virtual void parseResponse(Cloudbase::CBHelperResponseInfo resp);

    Q_INVOKABLE void saveSettings(QString newUsername);
    Q_INVOKABLE void startPicture(QString title, QString tags);

private:
    User *userObject;
    Photo *newPhoto;

    Cloudbase::CBHelper *helper;
    bb::cascades::AbstractPane *root;
    PhotoLoader *loader;

public Q_SLOTS:
	void photoSaved (const QString &fileName, quint64 length );

	void photoUploaded(Photo* photo);
	void photoUploadFailed(Photo* photo, QString error);

	void receivedPhoto(Photo* photo);

	void photoDownloaded(Photo* photo);
	void photoDownloadFailed(Photo* photo, QString error);
};

#endif /* ApplicationUI_HPP_ */
