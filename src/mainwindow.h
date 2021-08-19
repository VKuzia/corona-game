#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void SetStarted(bool started);

public slots:
    void resizeEvent(QResizeEvent* event) override;
    void ChangeScore();
    void Pause();
    void Retry();
    void LosableChanged();
    void DifficultyChanged();
    void SpeedChanged();

private:
    Ui::MainWindow *ui;
    bool started_;
};

#endif // MAINWINDOW_H
