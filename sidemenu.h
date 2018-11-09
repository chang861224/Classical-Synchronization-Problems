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
    QWidget* carControlWidget(int mode=0);
    QVBoxLayout *layout;

signals:
    void run();
    void freqChange(int);
    void speedChange(int);

public slots:
};

#endif // SIDEMENU_H
