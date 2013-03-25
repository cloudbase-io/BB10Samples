// Tabbed Pane project template
import bb.cascades 1.0

TabbedPane {
    showTabsOnActionBar: true
    Tab {
        id: browseTab

        title: qsTr("Browse")
        NavigationPane {
            Page {
                ListView {
                    id: photosListView
                    leadingVisual: photosListView

                }

            }

        }

    }
    Tab {
        id: takePhotoTab
        title: qsTr("New Photo")
        imageSource: "asset:///images/camera.png"
        Page {
            id: tab2
            actions: [
                // define the actions for tab here
                ActionItem {

                    title: qsTr("Raise")
                    onTriggered: {
                        // run the image animation
                        raiseAnimation.play();
                    }
                }
            ]
            Container {
                // define tab content here
                Label {
                    text: qsTr("Take photo")
                    horizontalAlignment: HorizontalAlignment.Center
                    textStyle {
                        base: SystemDefaults.TextStyles.TitleText
                    }
                }
                TextField {
                    id: photoTitleField
                    hintText: "Title"
                }
                TextField {
                    id: photoTagsField
                    hintText: "Tags (Comma separated)"

                }
                Button {
                    text: "Start"
                    onClicked: {
                        app.startPicture(photoTitleField.text, photoTagsField.text);
                    }
                }

            }
        }
    }
    Tab {
        id: settingsTab
        title: qsTr("Settings")
        Page {
            id: tab3
            Container {
                // define tab content here
                Label {
                    text: qsTr("Settings")
                    horizontalAlignment: HorizontalAlignment.Center
                    textStyle {
                        base: SystemDefaults.TextStyles.TitleText
                    }
                }
                Container {

                    verticalAlignment: VerticalAlignment.Fill
                    horizontalAlignment: HorizontalAlignment.Fill
                    TextField {
                        id: userNameField
                        hintText: "Username"

                    }
                    Button {
                        text: "Save"
                        onClicked: {
                            app.saveSettings(userNameField.text);
                        }
                    }
                    ActivityIndicator {
                        id: settingsActivityIndicator
                        visible: false
                        verticalAlignment: VerticalAlignment.Center
                        horizontalAlignment: HorizontalAlignment.Center

                    }

                }
            }
        }
    }
    onCreationCompleted: {
        // this slot is called when declarative scene is created
        // write post creation initialization here
        console.log("TabbedPane - onCreationCompleted()")

        // enable layout to adapt to the device rotation
        // don't forget to enable screen rotation in bar-bescriptor.xml (Application->Orientation->Auto-orient)
        OrientationSupport.supportedDisplayOrientation = SupportedDisplayOrientation.All;
    }
}
