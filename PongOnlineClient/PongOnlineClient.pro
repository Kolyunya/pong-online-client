TEMPLATE = app

TARGET = PongOnlineClient

QT += \
    core \
    widgets \
    network \
    multimedia \

QT -= \
    console \

CONFIG += \
    console \
    c++11 \

CONFIG -= \
    console \
    app_bundle \

debug:DESTDIR = Build/Debug
release:DESTDIR = Build/Release
OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.rcc
UI_DIR = $$DESTDIR/.ui

INCLUDEPATH += \
    Sources \
    ../PongOnlineCommon/Sources \

release:LIBS += -L../PongOnlineCommon/Build/Release
debug:LIBS += -L../PongOnlineCommon/Build/Debug
LIBS += -lPongOnlineCommon

HEADERS += \
    Sources/Client/Client.hpp \
    Sources/FieldView/FieldView.hpp \
    Sources/NetworkManager/NetworkManager.hpp \
    Sources/Pages/MainMenu/PageMainMenu.hpp \
    Sources/Pages/Game/PageGame.hpp \
    Sources/Windows/Main/WindowMain.hpp \
    Sources/Game/Game.hpp \
    Sources/Pages/Loading/Loading.hpp \
    Sources/InputManager/InputManager.hpp \
    Sources/ScoreView/ScoreView.hpp \
    Sources/SpriteView/SpriteView.hpp \
    Sources/StatusBar/StatusBarEasingCurve/StatusBarEasingCurve.hpp \
    Sources/StatusBar/StatusBarWidget/StatusBarWidget.hpp

SOURCES += \
    Sources/Main/Main.cpp \
    Sources/Client/Client.cpp \
    Sources/FieldView/FieldView.cpp \
    Sources/NetworkManager/NetworkManager.cpp \
    Sources/Pages/MainMenu/PageMainMenu.cpp \
    Sources/Pages/Game/PageGame.cpp \
    Sources/Windows/Main/WindowMain.cpp \
    Sources/Game/Game.cpp \
    Sources/Pages/Loading/Loading.cpp \
    Sources/InputManager/InputManager.cpp \
    Sources/ScoreView/ScoreView.cpp \
    Sources/SpriteView/SpriteView.cpp \
    Sources/StatusBar/StatusBarEasingCurve/StatusBarEasingCurve.cpp \
    Sources/StatusBar/StatusBarWidget/StatusBarWidget.cpp

FORMS += \
    Sources/Windows/Main/WindowMain.ui \
    Sources/Pages/MainMenu/PageMainMenu.ui \
    Sources/Pages/Game/PageGame.ui \
    Sources/Pages/Loading/Loading.ui

RESOURCES += \
    Resources/Main.qrc \
