#include "gui/enter_data.h"
#include "ui_enter_data.h"
#include <QFileInfo>
#include <QFileDialog>
#include <QString>
#include <QLabel>
#include <QSpinBox>
#include <QMessageBox>

#include <logger/log.h>

EnterData::EnterData(QWidget *parent, const Data& data) :
    QDialog(parent), data_(data), ui(new Ui::EnterData)
{
    ui->setupUi(this);
    ui->rectangles_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->rectangles_table->setColumnCount(2);
    ui->rectangles_table->setHorizontalHeaderLabels({tr("width"), tr("height")});
    display_data();
}

EnterData::~EnterData()
{
    delete ui;
}


const Data& EnterData::get_data()
{
    return data_;
}


void EnterData::display_data()
{
    ui->width_edit->setValue(data_.get_tape_width());
    ui->rectangles_table->setRowCount(data_.get_rectangles_info().size());
    for(size_t i = 0; i < data_.get_rectangles_info().size(); i++)
    {
        QSpinBox *width_input = new QSpinBox;
        QSpinBox *height_input = new QSpinBox;
        width_input->setMinimum(1);
        width_input->setMaximum(1000000);
        height_input->setMinimum(1);
        height_input->setMaximum(1000000);

        width_input->setValue(data_.get_rectangles_info()[i].first);
        height_input->setValue(data_.get_rectangles_info()[i].second);

        ui->rectangles_table->setCellWidget(i, 0, width_input);
        ui->rectangles_table->setCellWidget(i, 1, height_input);
    }
    ui->open_file_button->setText(data_.get_file_name().isEmpty() ?
                                  tr("Open file") : QFileInfo(data_.get_file_name()).fileName());
}


void EnterData::on_ok_button_clicked()
{
    data_.set_tape_width(ui->width_edit->text().toInt());
    pair_vector rectangles_vector;
    for(int i = 0; i < ui->rectangles_table->rowCount(); i++)
    {
        rectangles_vector.emplace_back(
            dynamic_cast<QSpinBox*> (ui->rectangles_table->cellWidget(i, 0))->value(),
            dynamic_cast<QSpinBox*> (ui->rectangles_table->cellWidget(i, 1))->value()
        );
    }
    data_.set_rectangles_info(rectangles_vector);
    accept();
}


void EnterData::on_cancel_button_clicked()
{
    reject();
}


void EnterData::on_open_file_button_clicked()
{
    try
    {
        QString filename = QFileDialog::getOpenFileName(this, tr("Select file"));
        if (filename.isEmpty())
        {
            return;
        }
        data_.set_file_name(filename);
        data_.read_from_file();
        display_data();
    }
    catch (const std::runtime_error& e)
    {
        ui->open_file_button->setText(tr("Open file"));
        data_.set_file_name("");
        QMessageBox msg;
        msg.critical(nullptr, tr("Error"), e.what());
        Log::get_log().critical(e.what());
    }
}


void EnterData::on_add_rectangle_button_clicked()
{
    QSpinBox *width_input = new QSpinBox;
    QSpinBox *height_input = new QSpinBox;
    width_input->setMinimum(1);
    width_input->setMaximum(1000000);
    height_input->setMinimum(1);
    height_input->setMaximum(1000000);

    ui->rectangles_table->setRowCount(ui->rectangles_table->rowCount() + 1);
    ui->rectangles_table->setCellWidget(ui->rectangles_table->rowCount() - 1, 0, width_input);
    ui->rectangles_table->setCellWidget(ui->rectangles_table->rowCount() - 1, 1, height_input);
}


void EnterData::on_delete_rectangle_button_clicked()
{
    ui->rectangles_table->removeRow(ui->rectangles_table->currentRow());
}
