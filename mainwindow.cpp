#include "mainwindow.h"
#include "sidemenu.h"
#include <QVBoxLayout>
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
    int win_height = 540;
    int win_width = 960;
    setGeometry(desktop.width()/4, desktop.height()/4, win_width, win_height);
    setWindowTitle(tr("Single Lane Bridge Problem"));
    setMinimumSize(win_width/2, win_height/2);
    setFont(QFont("Helvetica [Cronyx]", 14));
    setPalette(QColor(180, 180, 180));
    setAutoFillBackground(true);

    // Widgets
    SideMenu *sidemenu = new SideMenu();

    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout -> addWidget(sidemenu);

    //Set layout
    win -> setLayout(mainLayout);
}

MainWindow::~MainWindow()
{

}
