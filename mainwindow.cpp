#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    RandomNumber::seed();

    m_ga = std::make_unique<GA>(m_params);

    QTimer * updateTimer = new QTimer();
    updateTimer->start(67);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateGui()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateGui() {
    if (m_ga) {
        if (m_ga->running()) {
            ui->mse_lbl->setText(QString::number(m_ga->best().cost()));
            ui->epochs_lbl->setText(QString::number(m_ga->epochs()));
        }
    }
}

void MainWindow::on_start_btn_pressed() {
    m_ga->process();
}

void MainWindow::on_stop_btn_pressed() {
    m_ga->interrupt();
}
