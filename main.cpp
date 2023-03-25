#include "editorview.h"
#include "mainworkspace.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWorkspace canvas;
    EditorView w(canvas);
    w.show();
    return a.exec();
}
