APP_NAME = BB10Instagram

CONFIG += qt warn_on cascades10

LIBS += -lbbdevice -lbbnetwork -lbbsystem -lcurl -lQtLocationSubset -lCBHelper -lbbdata

include(config.pri)

device {
    CONFIG(debug, debug|release) {
        # Device-Debug custom configuration
    }

    CONFIG(release, debug|release) {
        # Device-Release custom configuration
    }
}

simulator {
    CONFIG(debug, debug|release) {
        # Simulator-Debug custom configuration
    }
}
