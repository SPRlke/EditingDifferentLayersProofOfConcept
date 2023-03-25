#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include "mainworkspace.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPushButton>
#include <QCheckBox>

QT_BEGIN_NAMESPACE
namespace Ui { class EditorView; }
QT_END_NAMESPACE

class EditorView : public QMainWindow
{
    Q_OBJECT

    QPushButton* currentLayer;
    QVector<QPushButton*> layerButtons;
    QVector<QCheckBox*> layerChecks;

public:
    EditorView(MainWorkspace& model, QWidget* parent = nullptr);
    ~EditorView();

    void setScene(QGraphicsScene* scene);

public slots:

    void drawScreen(QGraphicsScene* scene);
    void addLayer();
    void layerClicked();
    void checkBoxClicked();

signals:

    void created();
    void layerAdded();
    void layerSelected(int);
    void layerVisibility(int, bool);

private:
    Ui::EditorView *ui;
};
#endif // EDITORVIEW_H
