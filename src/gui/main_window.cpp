#include <gui/main_window.h>
#include <ui_main_window.h>

#include <gui/settings_dialog.h>

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
