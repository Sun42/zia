TEMPLATE = app
TARGET = ZiaPluginLoader
DEPENDPATH += . \
    headers \
    src \
    ui
INCLUDEPATH += . \
    headers \
    /usr/local/boost_1_39_0/
LIBS += -lboost_system-gcc43-mt \
    -lboost_thread-gcc43-mt

# Input
HEADERS += headers/NetworkThread.h \
    headers/Preferences.h \
    headers/ZiaPluginLoader.h \
    headers/Packet.h \
    headers/ParserLoader.h
FORMS += ui/Preferences.ui \
    ui/ZiaPluginLoader.ui
SOURCES += src/main.cpp \
    src/NetworkThread.cpp \
    src/Preferences.cpp \
    src/ZiaPluginLoader.cpp \
    src/Packet.cpp \
    src/ParserLoader.cpp
RESOURCES += Images.qrc

# Output
DESTDIR = .
OBJECTS_DIR = obj
MOC_DIR = moc
UI_SOURCES_DIR = ui
UI_HEADERS_DIR = headers
