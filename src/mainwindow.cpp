#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    started_(false)
{
    ui->setupUi(this);
    connect(ui->_graphics_view, SIGNAL(Scored()), this, SLOT(ChangeScore()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetStarted(bool started)
{
    started_ = started;
}

void MainWindow::Pause()
{
    ui->_graphics_view->setFocus();
    ui->_graphics_view->Pause();
}

void MainWindow::Retry()
{
    ui->_score_label->setText("0");
    ui->_graphics_view->setFocus();
    ui->_graphics_view->Retry();
}

void MainWindow::LosableChanged()
{
    ui->_graphics_view->setFocus();
    ui->_graphics_view->setIs_losable(ui->_check_box->isChecked());
}

void MainWindow::DifficultyChanged()
{
    ui->_graphics_view->setFocus();
    ui->_graphics_view->DifficultyChanged(ui->_mob_slider->value());
}

void MainWindow::SpeedChanged()
{
    ui->_graphics_view->setFocus();
    ui->_graphics_view->SpeedChanged(ui->_speed_slider->value());
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    if (started_) {
        ui->_graphics_view->Resized();
    }
}

void MainWindow::ChangeScore()
{
    ui->_score_label->setText(QString::number(ui->_graphics_view->GetScore()));
}

