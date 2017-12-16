#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>

#include <vector>
#include <memory>

#include "GA/ga.h"
#include "randomnumber.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void updateGui();
    void on_start_btn_pressed();
    void on_stop_btn_pressed();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<GA> m_ga;
    GA::GA_Params m_params;
};

#endif // MAINWINDOW_H
