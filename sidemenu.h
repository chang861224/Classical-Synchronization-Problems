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
    QWidget* createCarWidgets();
    QWidget* createCarFreqWidget();
    QVBoxLayout *layout;

signals:

public slots:
};

#endif // SIDEMENU_H
