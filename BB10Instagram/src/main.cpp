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
#include "BB10Instagram.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/ListView>
#include <bb/data/DataSource>

#include <QLocale>
#include <QTranslator>

// include JS Debugger / CS Profiler enabler
// this feature is enabled by default in the debug build only
#include <Qt/qdeclarativedebug.h>
#include <ImageFolderWatcher.hpp>


using namespace bb::cascades;

void myMessageOutput(QtMsgType type, const char* msg){
                fprintf(stdout, "%s\n", msg);
                fflush(stdout);
}

Q_DECL_EXPORT int main(int argc, char **argv)
{
	// register the qml type for the listview
	qmlRegisterType<ListView>("bb.cascades", 1, 0, "ListView");
	qmlRegisterType<ImageFolderWatcher>("imagewatcher",1,0,"ImageFolderWatcher");
	bb::data::DataSource::registerQmlTypes();
    // this is where the server is started etc
    Application app(argc, argv);
    qInstallMsgHandler(myMessageOutput);

    // localization support
    QTranslator translator;
    QString locale_string = QLocale().name();
    QString filename = QString( "BB10Instagram_%1" ).arg( locale_string );
    if (translator.load(filename, "app/native/qm")) {
        app.installTranslator( &translator );
    }

    // create the application pane object to init UI etc.
    new BB10Instagram(&app);

    // we complete the transaction started in the app constructor and start the client event loop here
    return Application::exec();
    // when loop is exited the Application deletes the scene which deletes all its children (per qt rules for children)
}
