import bb.cascades 1.0

Container {
    id: mainContainer
    horizontalAlignment: HorizontalAlignment.Center
    Label {
        id: title
        text: ListItemData.title 
        horizontalAlignment: HorizontalAlignment.Center

    }

    ImageView {      
        //TODO Placeholder: Replace this source with the actual image
        id: myImage
        imageSource: "asset:///images/picture1br.png"
        horizontalAlignment: HorizontalAlignment.Center
        enabled: mainContainer.ListItem.view.photoLoaded
        onCreationCompleted:{
            console.log("Created element with photo: "+imageSource);
        }
    }
    Label {
        id: tags
        text: "TAGS: " + ListItemData.tags
        textStyle.fontSize: FontSize.XSmall 
        horizontalAlignment: HorizontalAlignment.Center
        onTouch: {
            if(event.isDown()){
                myImage.imageSource = ListItemData.imageSource
                console.log("Image is"+myImage.imageSource)
            }
        }
    }
    Label {
        id: user
        text: "by " + ListItemData.username
        textStyle.fontSize: FontSize.XSmall
        horizontalAlignment: HorizontalAlignment.Center
    }
    Divider {

    }

}
