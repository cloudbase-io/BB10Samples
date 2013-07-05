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
#include "BB10Instagram.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/system/CardDoneMessage>
#include <bb/system/InvokeManager>
#include <bb/data/DataSource>
#include <bb/cascades/GroupDataModel>
#include <bb/data/JsonDataAccess>
#include <bb/cascades/ListView>
#include <bb/system/InvokeTargetReply>
#include <bb/cascades/pickers/FilePicker>
#include <bb/system/SystemDialog>


using namespace bb::system;
using namespace bb::cascades;
using namespace bb::cascades::pickers;
using namespace Cloudbase;

BB10Instagram::BB10Instagram(bb::cascades::Application *app)
: QObject(app)
{
	// Create the QSettings object to store the username locally
	QSettings settings("cloudbase.io", "com.coudbase.BB10Instagram");
	QString settingsUsername = settings.value("username", "").toString();

	// Create the User object in from the settings or set it to null if no username has
    // been stored yet
	if ( settingsUsername.compare("") == 0 ) {
		userObject = NULL;
	} else {
		userObject = new User(settingsUsername);
	}


    // create scene document from main.qml asset
    // set parent to created document to ensure it exists for the whole application lifetime
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

    // Send this object to the QML so its Q_INVOKABLE methods can be called
    qml->setContextProperty("app", this);

    // create root object for the UI
    root = qml->createRootObject<AbstractPane>();
    // set created root object as a scene
    app->setScene(root);

    // initialize the CBHelper
    // TODO: Place the unique keys for your application here
    helperClassRegistered = false;
    helper = new CBHelper("your-app-code", "app-unique-code");
    helper->debugMode = true;
    helper->setPassword("md5 of app password");

    // initialize the global PhotoLoader
    loader = new PhotoLoader(helper);

    // connect the SIGNAL from the PhotoLoader to the local method to add a photo
    // to the ListView
    qRegisterMetaType< Photo* >("Photo*");
    QObject::connect(loader, SIGNAL(receivedPhotos(QVariantList)), this, SLOT(receivedPhotos(QVariantList)));

    loader->loadPhotos();
}

Q_INVOKABLE void BB10Instagram::saveSettings(QString newUsername) {
	qDebug("checking user... %s", newUsername.toStdString().c_str());
	// if it's a new user
	if ( userObject == NULL || userObject->getUsername().compare(newUsername) != 0 ) {

		// save the user in the settings
		QSettings settings("cloudbase.io", "com.coudbase.BB10Instagram");
		settings.setValue("username", newUsername);

		// create a new User object
		userObject = new User(newUsername);
		// Search the users collection to see if a user with this name already exists
		// once this operation is completed it will call the parseResponse method on this object
		CBHelperSearchCondition *cond = new CBHelperSearchCondition("username", newUsername.toStdString(), Cloudbase::CBOperatorEqual);
		helper->searchDocument("users", cond, this);
	}
}

void BB10Instagram::parseResponse(Cloudbase::CBHelperResponseInfo resp) {
	// no other users were found with the same username, we can proceed with the insert
	if (resp.parsedMessage->getNumChildValues() == 0) {
		// create the user
		helper->insertDocument("users", dynamic_cast<Cloudbase::CBSerializable*>(userObject), NULL);
	} else {
		qDebug() << "user exists";
		// TODO: display an alert and ask to change the username
	}
}

void BB10Instagram::startPicture(QStringList list) {
	// check that the user is set
	if ( userObject == NULL || userObject->getUsername() == NULL ) {
		SystemDialog *dialog = new SystemDialog("OK");
		dialog->setTitle("Missing username");
		dialog->setBody("Setup a user for the application in the settings tab");
		dialog->show();
		return;
	}

	newPhoto = new Photo(QString(curTitle), QString(userObject->getUsername()), QString(curTags), QString(list[0]));
	QFile file(list[0]);
	if (file.exists()) {
		Cloudbase::CBHelperAttachment att;
		att.fileName = file.fileName().toStdString();
		att.filePath = list[0].toStdString();

		// TODO: here we might want to generate a thumbnail and attach it
		// to the record so we can load it from the preview screen
		std::vector<Cloudbase::CBHelperAttachment> atts;
		atts.insert(atts.begin(), att);

		PhotoUploadResponder *uploadResponder = new PhotoUploadResponder(newPhoto);

		QObject::connect(uploadResponder, SIGNAL(photoUploaded(Photo*)), this, SLOT(photoUploaded(Photo*)));
		QObject::connect(uploadResponder, SIGNAL(photoUploadFailed(Photo*, QString)), this, SLOT(photoUploadFailed(Photo*, QString)));

		helper->insertDocument("photos", dynamic_cast<Cloudbase::CBSerializable*>(newPhoto), atts, uploadResponder);
	} else {
		qDebug("file doesn't exist");
	}
}

Q_INVOKABLE void BB10Instagram::takePicture(QString title, QString tags) {
	curTitle = title;
	curTags = tags;

	FilePicker* filePicker = new FilePicker();
	filePicker->setType(FileType::Picture);
	filePicker->setTitle("Select Picture");
	filePicker->setMode(FilePickerMode::Picker);
	filePicker->open();

	// Connect the fileSelected() signal with the slot.
	QObject::connect(filePicker,
	    SIGNAL(fileSelected(const QStringList&)),
	    this,
	    SLOT(startPicture(const QStringList&)));
}

void BB10Instagram::photoUploaded(Photo* photo) {
	// we finished uploading the photo. add it to the list view
	// using the standard method
}

void BB10Instagram::photoUploadFailed(Photo* photo, QString error) {
	//qDebug("Error while uploading photo %s", error.toStdString().c_str());
}

void BB10Instagram::receivedPhotos(QVariantList photos) {
	// TODO: create the list item and add it to the list view
	// the pointer should be passed to the download responder
	// which will add the picture as soon as it's downloaded
	//populate the listview directly from here - lsale 20120528
	m_listView = bb::cascades::Application::instance()->findChild<ListView*>("photoListView");
	GroupDataModel *model = new GroupDataModel(QStringList() << "username");
	model->insertList(photos);
	m_listView->setDataModel(model);
}
