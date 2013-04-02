import bb.cascades 1.0

Container {
    horizontalAlignment: HorizontalAlignment.Center
    Label {
        id: title
        text: ListItemData.title 
        horizontalAlignment: HorizontalAlignment.Center

    }

    ImageView {
        //TODO Placeholder: Replace this source with the actual image
        imageSource: "asset:///images/picture1.png"
        horizontalAlignment: HorizontalAlignment.Center

    }
    Label {
        id: tags
        text: "TAGS: " + ListItemData.tags
        textStyle.fontSize: FontSize.XSmall 
        horizontalAlignment: HorizontalAlignment.Center

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
