#include <gui/main_window.h>
#include <ui_main_window.h>

#include <gui/settings_dialog.h>
#include <logger/log.h>

#include <logger/console_logger.h>
#include <logger/file_logger.h>
#include <logger/tab_logger.h>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent), ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui_;
}


void MainWindow::on_action_settings_triggered()
{
    SettingsDialog dialog(nullptr, algo_settings_);
    if (dialog.exec() == QDialog::Accepted)
    {
        algo_settings_ = dialog.get_settings();
    }
}


void MainWindow::on_action_enter_data_triggered()
{
    EnterData dialog(nullptr, data_);
    if (dialog.exec() == QDialog::Accepted)
    {
        data_ = dialog.get_data();
    }
}
