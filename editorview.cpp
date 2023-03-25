#include "editorview.h"
#include "ui_editorview.h"
#include "drawingcanvas.h"

EditorView::EditorView(MainWorkspace& model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EditorView)
{
    ui->setupUi(this);

    currentLayer = ui->layer0;
    currentLayer->toggle();
    layerButtons.append(ui->layer0);
    ui->checkBox->toggle();
    layerChecks.append(ui->checkBox);
    connect(ui->layer0, &QPushButton::clicked, this, &EditorView::layerClicked);
    connect(ui->addLayer, &QPushButton::clicked, this, &EditorView::addLayer);
    connect(this, &EditorView::layerAdded, &model, &MainWorkspace::addLayer);
    connect(this, &EditorView::layerSelected, &model, &MainWorkspace::changeLayer);
    connect(ui->checkBox, &QCheckBox::clicked, this, &EditorView::checkBoxClicked);
    connect(this, &EditorView::layerVisibility, &model, &MainWorkspace::setVisibility);
    connect(&model, &MainWorkspace::displayScene, this, &EditorView::setScene);
    connect(ui->Canvas, &DrawingCanvas::mousePressed, &model, &MainWorkspace::drawPixel);
    connect(&model, &MainWorkspace::imageChanged, this, &EditorView::drawScreen);
    connect(this, &EditorView::created, &model, &MainWorkspace::firstCall);

    //Emit to substitute for the creation of the canvas.
    emit created();
}

EditorView::~EditorView()
{
    delete ui;
    delete currentLayer;
}

void EditorView::setScene(QGraphicsScene* scene)
{
    //Set the canvas to display the scene, then scale the scene to match the canvas
    ui->Canvas->setScene(scene);
    ui->Canvas->scale(400/(scene->height()),400/(scene->width()));
}

void EditorView::drawScreen(QGraphicsScene* scene)
{
    ui->Canvas->setScene(scene);
}

void EditorView::addLayer()
{
    //Create a new push button and add a connection to the layerClicked method
    QPushButton* newLayer = new QPushButton("Layer_" + QString::number(ui->gridLayout->count()/2));
    newLayer->connect(newLayer, &QPushButton::clicked, this, &EditorView::layerClicked);
    newLayer->setCheckable(true);

    //Add the new push button to the vector and ui, then tell the model a layer has been added
    layerButtons.append(newLayer);
    ui->gridLayout->addWidget(newLayer);
    emit layerAdded();

    //Create a new check box and add a connection to the checkBoxClicked method
    QCheckBox* newCheckBox = new QCheckBox();
    newCheckBox->toggle();
    newCheckBox->connect(newCheckBox, &QCheckBox::clicked, this, &EditorView::checkBoxClicked);

    //Add the checkbox to the ui and the vector. (Checkbox Vector is temporary for testing)
    layerChecks.append(newCheckBox);
    ui->gridLayout->addWidget(newCheckBox);
}

void EditorView::layerClicked()
{
    //Turn off the previous layer
    currentLayer->toggle();

    //loop through all layers (Making a custom PushButton would likely be better)
    for(unsigned int i = 0; i<layerButtons.count(); i++)
    {
        //Check if the button has been clicked
        if(layerButtons[i]->isChecked())
        {
            //Change the selected layer and tell the model the new selected layers positions.
            currentLayer = layerButtons[i];
            emit layerSelected(i);
        }
    }
}

void EditorView::checkBoxClicked()
{
    //Making Custom Check Boxes would help this

    //loop through all check boxes
    for(unsigned int i = 0; i<layerChecks.count(); i++)
    {
        //Check if they are clicked
        if(!layerChecks[i]->isChecked())
        {
            //Tell the model to disable the visibility
            emit layerVisibility(i, false);
        }
        else
        {
            //Tell the model to enable the visibility
            emit layerVisibility(i, true);
        }
    }
}


