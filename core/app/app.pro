QT += core gui qml quick widgets

TARGET = board
TEMPLATE = app
LIBS += -lz
DESTDIR =  ../../bin
LIBSDIR = ../../bin
DEPENDENCY_LIBRARIES = board-common

include(../../main.pri)
include(../../third-party/quazip-0.5.1/quazip/quazip.pri)

SOURCES += \
    src/brd/brdnetworkaccessmanager.cpp \
    src/brd/brdnetworkaccessmanagerfactory.cpp \
    src/brd/brdreply.cpp \
    src/brd/brdstore.cpp \
    src/core.cpp \
    src/main.cpp \
    src/paint/circlegen.cpp \
    src/paint/ellipse.cpp \
    src/paint/ellipsegen.cpp \
    src/paint/erasergen.cpp \
    src/paint/imagegen.cpp \
    src/paint/imagewrapper.cpp \
    src/paint/line.cpp \
    src/paint/linegen.cpp \
    src/paint/magicpengen.cpp \
    src/paint/movegen.cpp \
    src/paint/paint.cpp \
    src/paint/paintutils.cpp \
    src/paint/pathprocessor/ellipse_pp.cpp \
    src/paint/pathprocessor/pathprocessor.cpp \
    src/paint/pathprocessor/polygon.cpp \
    src/paint/pathprocessor/shapehunter.cpp \
    src/paint/pathprocessor/utils.cpp \
    src/paint/pen.cpp \
    src/paint/pengen.cpp \
    src/paint/rectangle.cpp \
    src/paint/rectanglegen.cpp \
    src/paint/selectgen.cpp \
    src/paint/sheet.cpp \
    src/paint/sheetcanvas.cpp \
    src/paint/textgen.cpp \
    src/paint/textwrapper.cpp \
    src/paint/videogen.cpp \
    src/paint/videoplayer.cpp \
    src/str_stack/strstack.cpp \
    src/style.cpp

HEADERS += \
    src/brd/brdnetworkaccessmanager.h \
    src/brd/brdnetworkaccessmanagerfactory.h \
    src/brd/brdreply.h \
    src/brd/brdstore.h \
    src/core.h \
    src/paint/circlegen.h \
    src/paint/ellipse.h \
    src/paint/ellipsegen.h \
    src/paint/erasergen.h \
    src/paint/imagegen.h \
    src/paint/imagewrapper.h \
    src/paint/line.h \
    src/paint/linegen.h \
    src/paint/magicpengen.h \
    src/paint/movegen.h \
    src/paint/paint.h \
    src/paint/paintutils.h \
    src/paint/pathprocessor/ellipse.h \
    src/paint/pathprocessor/pathprocessor.h \
    src/paint/pathprocessor/points.h \
    src/paint/pathprocessor/polygon.h \
    src/paint/pathprocessor/shape.h \
    src/paint/pathprocessor/shapehunter.h \
    src/paint/pathprocessor/utils.h \
    src/paint/pen.h \
    src/paint/pengen.h \
    src/paint/rectangle.h \
    src/paint/rectanglegen.h \
    src/paint/selectgen.h \
    src/paint/sheet.h \
    src/paint/sheetcanvas.h \
    src/paint/textgen.h \
    src/paint/textwrapper.h \
    src/paint/videogen.h \
    src/paint/videoplayer.h \
    src/str_stack/strstack.h \
    src/style.h

OTHER_FILES += \
    qml/Board.qml \
    qml/CloseCaution.qml\
    qml/ColorGrid.qml \
    qml/ErrorMessageBox.qml \
    qml/ImageWrapper.qml \
    qml/keyboard.js \
    qml/Keyboard.qml \
    qml/ModeBar.qml \
    qml/PopupMenu.qml \
    qml/ScrollBar.qml \
    qml/ScrollButton.qml \
    qml/sheet.js \
    qml/SpinBoxEx.qml \
    qml/Sheet.qml \
    qml/StyleQml.qml \
    qml/TextWrapper.qml \
    qml/ToolBar.qml \
    qml/VideoPlayer.qml \
    res/backspace.svg \
    res/back.svg \
    res/circle.svg \
    res/close.svg \
    res/delete.svg \
    res/desktop.svg \
    res/down_arrow.svg \
    res/duplicate.svg \
    res/ellipse.svg \
    res/enter.svg \
    res/eraser.png \
    res/font_size.svg \
    res/help \
    res/image.svg \
    res/left_arrow.svg \
    res/line.svg \
    res/magic_pen.svg \
    res/minimize.svg \
    res/move.svg \
    res/open.svg \
    res/pause.svg \
    res/pen.svg \
    res/play.svg \
    res/rectangle.svg \
    res/redo.svg \
    res/right_arrow.svg \
    res/save.svg \
    res/select.svg \
    res/stop.svg \
    res/text.svg \
    res/thickness.svg \
    res/to_front.svg \
    res/to_back.svg \
    res/undo.svg \
    res/up_arrow.svg \
    res/video.svg \
    board.desktop

RESOURCES += app.qrc

target.path=$$PREFIX/bin
shortcut.path=$$PREFIX/share/applications
shortcut.files=board.desktop
INSTALLS += target shortcut
