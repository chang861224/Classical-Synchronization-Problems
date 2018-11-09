#ifndef SIDEMENU_H
#define SIDEMENU_H

#include <QWidget>
class QVBoxLayout;

class SideMenu : public QWidget
{
    Q_OBJECT
public:
    explicit SideMenu(QWidget *parent = nullptr);

private:
    QWidget* createControlWidgets();
    QWidget* createCarFreqWidget();
    QVBoxLayout *layout;

signals:
    void run();

public slots:
};

#endif // SIDEMENU_H
