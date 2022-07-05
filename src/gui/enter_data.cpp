#include "gui/enter_data.h"
#include "ui_enter_data.h"
#include <QFileInfo>
#include <QFileDialog>
#include <QString>
#include <QLabel>
#include <QSpinBox>

EnterData::EnterData(QWidget *parent, const Data& data) :
    QDialog(parent),
    ui(new Ui::EnterData)
{
    ui->setupUi(this);
    ui->rectangles_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->rectangles_table->setColumnCount(2);
    ui->rectangles_table->setHorizontalHeaderLabels({tr("width"), tr("height")});
    set_data(data);
}

EnterData::~EnterData()
{
    delete ui;
}


Data EnterData::get_data()
{
    Data data;
    data.set_file_name(file_name_);
    data.set_tape_width(ui->width_edit->text().toInt());
    pair_vector rectangles_vector;
    for(int i = 0; i < ui->rectangles_table->rowCount(); i++)
    {
        rectangles_vector.emplace_back(
            dynamic_cast<QSpinBox*> (ui->rectangles_table->cellWidget(i, 0))->value(),
            dynamic_cast<QSpinBox*> (ui->rectangles_table->cellWidget(i, 1))->value()
        );
    }
    data.set_rectangles_info(rectangles_vector);
    return data;
}


void EnterData::set_data(const Data& data)
{
    file_name_ = data.get_file_name();
    ui->width_edit->setValue(data.get_tape_width());
    ui->rectangles_table->setRowCount(data.get_rectangles_info().size());
    for(size_t i = 0; i < data.get_rectangles_info().size(); i++)
    {
        QSpinBox *width_input = new QSpinBox;
        QSpinBox *height_input = new QSpinBox;
        width_input->setMinimum(1);
        width_input->setMaximum(1000000);
        height_input->setMinimum(1);
        height_input->setMaximum(1000000);

        width_input->setValue(data.get_rectangles_info()[i].first);
        height_input->setValue(data.get_rectangles_info()[i].second);

        ui->rectangles_table->setCellWidget(i, 0, width_input);
        ui->rectangles_table->setCellWidget(i, 1, height_input);
    }
    ui->open_file_button->setText(file_name_.isEmpty() ?
                                  tr("Open file") : QFileInfo(file_name_).fileName());
}


void EnterData::on_ok_button_clicked()
{
    accept();
}


void EnterData::on_cancel_button_clicked()
{
    reject();
}


void EnterData::on_open_file_button_clicked()
{
    file_name_ = QFileDialog::getOpenFileName(this, tr("Select file"));
    ui->open_file_button->setText(file_name_.isEmpty() ?
                                  tr("Open file") : QFileInfo(file_name_).fileName());
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
