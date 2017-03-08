#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
  void on_pushButton_released();
  void on_actionQuit_triggered();

  void loadSettings();
  void saveSettings();

private:
    Ui::MainWindow *ui;
    QString acctUsername, acctPassword, displayName;
    QSettings settings;
};

#endif // MAINWINDOW_HPP
