#include "sidemenu.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>

SideMenu::SideMenu(QWidget *parent) : QWidget(parent)
{
    // Layout configuration
    layout = new QVBoxLayout();
    setLayout(layout);

    layout -> addWidget(createControlWidgets());
}

QWidget*
SideMenu::createControlWidgets()
{
    // Layout
    QGridLayout *carLayout = new QGridLayout();

    // Widgets
    QLabel *carLabel = new QLabel(tr("Control"));
    carLabel -> setAlignment(Qt::AlignCenter);
    QPushButton *startBtn = new QPushButton(tr("Start"));
    QPushButton *addCarBtn = new QPushButton(tr("Add (+1)"));
    QPushButton *autoCreateCarBtn = new QPushButton(tr("Auto"));
    QWidget *carFreq = carControlWidget(0);
    QWidget *carSpeed = carControlWidget(1);

    // Layout
    carLayout -> addWidget(carLabel, 0, 0, 1, 3);
    carLayout -> addWidget(startBtn, 1, 1);
    carLayout -> addWidget(addCarBtn, 1, 0);
    carLayout -> addWidget(autoCreateCarBtn, 1, 2);
    carLayout -> addWidget(carFreq, 2, 0, 1, 3);
    carLayout -> addWidget(carSpeed, 3, 0, 1, 3);

    // Behavior
    connect(startBtn, SIGNAL(clicked()), this, SIGNAL(run()));

    // Pack as a widget
    QWidget *carMenu = new QWidget;
    carMenu -> setLayout(carLayout);

    return carMenu;
}

QWidget*
SideMenu::carControlWidget(int mode)
{
    // Widgets
    QLabel *labelTitle = new QLabel();
    switch(mode){
    case 0: labelTitle -> setText(tr("Frequence: ")); break;
    case 1: labelTitle -> setText(tr("Speed: ")); break;
    }
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider -> setRange(100, 1500);
    slider -> setValue(800);
    QLabel *labelValue = new QLabel();
    labelValue -> setText(QString::number(slider -> value()));

    // Behavior
    connect(slider, SIGNAL(valueChanged(int)), labelValue, SLOT(setNum(int)));
    switch(mode){
    case 0: connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(freqChange(int))); break;
    case 1: connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(speedChange(int))); break;
    }

    // Layout
    QHBoxLayout *carFreqLayout = new QHBoxLayout();
    carFreqLayout -> addWidget(labelTitle);
    carFreqLayout -> addWidget(slider);
    carFreqLayout -> addWidget(labelValue);
    carFreqLayout -> addWidget(new QLabel(tr("ms")));

    // Pack as a widget
    QWidget *carFreqWidget = new QWidget;
    carFreqWidget -> setLayout(carFreqLayout);

    return carFreqWidget;
}
