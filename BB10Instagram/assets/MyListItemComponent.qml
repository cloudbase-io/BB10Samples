/* Copyright (C) 2012 cloudbase.io
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 2, as published by
 * the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to the Free
 * Software Foundation, 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */
import bb.cascades 1.0
import imagewatcher 1.0

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
        preferredHeight: 300;
        scalingMethod: ScalingMethod.AspectFit
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
    attachedObjects: [
        ImageFolderWatcher {
            id:imageFolderWatcher
            imageFilename: ListItemData.imageSource+'.jpg'
            onImageCreated: {
                myImage.setImageSource(fullImageFilename);
            }
        }
    
    ]
}
