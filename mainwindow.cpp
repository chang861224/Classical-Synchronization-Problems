#include "mainwindow.h"
#include "sidemenu.h"
#include "canvas.h"
#include "Single-Lane-Bridge/singlelanebridge.h"
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGuiApplication>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create a QWidget as a central widget.
    QWidget* win = new QWidget;
    setCentralWidget(win);

    // Initialize window
    QRect desktop =  QGuiApplication::primaryScreen() -> geometry();
    int win_height = desktop.height() / 2;
    int win_width = desktop.width() / 2;
    setGeometry(desktop.width()/4, desktop.height()/4, win_width, win_height);
    setWindowTitle(tr("Single Lane Bridge Problem"));
    setMinimumSize(win_width/2, win_height/2);
    setFont(QFont("Helvetica [Cronyx]", 14));
    setPalette(QColor(180, 180, 180));
    setAutoFillBackground(true);

    // Widgets
    SideMenu *sidemenu = new SideMenu();
    Canvas *canvas = new Canvas();

    // Problem
    SingleLaneBridge *problem = new SingleLaneBridge;
    connect(canvas, SIGNAL(carWidthChange(int)), problem, SLOT(setCarWidth(int)));
    connect(sidemenu, SIGNAL(run()), problem, SLOT(init()));
    connect(sidemenu, SIGNAL(freqChange(int)), problem, SLOT(setCreateFreq(int)));
    connect(problem, SIGNAL(carChanged(int,int)), canvas, SLOT(setObjects(int,int)));
    connect(problem, SIGNAL(deleteCar(int)), canvas, SLOT(deleteObject(int)));

    // Layout
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout -> addWidget(canvas, 0, 0);
    mainLayout -> setRowStretch(0, 5);
    mainLayout -> addWidget(sidemenu, 1, 0);
    mainLayout -> setRowStretch(1, 1);

    //Set layout
    win -> setLayout(mainLayout);
}

MainWindow::~MainWindow()
{

}
