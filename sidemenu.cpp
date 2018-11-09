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

    layout -> addWidget(createCarWidgets());
}

QWidget*
SideMenu::createCarWidgets()
{
    // Layout
    QGridLayout *carLayout = new QGridLayout();

    // Widgets
    QLabel *carLabel = new QLabel(tr("Car"));
    carLabel -> setAlignment(Qt::AlignCenter);
    carLayout -> addWidget(carLabel, 0, 0, 1, 3);
    QPushButton *startBtn = new QPushButton(tr("Start"));
    carLayout -> addWidget(startBtn, 1, 1);
    connect(startBtn, SIGNAL(clicked()), this, SIGNAL(run()));
    QPushButton *addCarBtn = new QPushButton(tr("Add (+1)"));
    carLayout -> addWidget(addCarBtn, 1, 0);
    QPushButton *autoCreateCarBtn = new QPushButton(tr("Auto"));
    carLayout -> addWidget(autoCreateCarBtn, 1, 2);
    carLayout -> addWidget(createCarFreqWidget(), 2, 0, 1, 3);

    // Pack as a widget
    QWidget *carMenu = new QWidget;
    carMenu -> setLayout(carLayout);

    return carMenu;
}

QWidget*
SideMenu::createCarFreqWidget()
{
    // Widgets
    QSlider *carFreqSlider = new QSlider(Qt::Horizontal);
    carFreqSlider -> setRange(10, 500);
    carFreqSlider -> setValue(100);
    QLabel *carFreqLabel = new QLabel();
    carFreqLabel -> setText(QString::number(carFreqSlider -> value()));

    // Behavior
    connect(carFreqSlider, SIGNAL(valueChanged(int)), carFreqLabel, SLOT(setNum(int)));

    // Layout
    QHBoxLayout *carFreqLayout = new QHBoxLayout();
    carFreqLayout -> addWidget(carFreqSlider);
    carFreqLayout -> addWidget(carFreqLabel);
    carFreqLayout -> addWidget(new QLabel(tr("ms")));

    // Pack as a widget
    QWidget *carFreqWidget = new QWidget;
    carFreqWidget -> setLayout(carFreqLayout);

    return carFreqWidget;
}
