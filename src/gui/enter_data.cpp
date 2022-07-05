#include "gui/enter_data.h"
#include "ui_enter_data.h"
#include <QFileDialog>
#include <QString>
#include <QLabel>
#include <QLineEdit>

EnterData::EnterData(QWidget *parent, const Data& data) :
    QDialog(parent),
    ui(new Ui::EnterData)
{
    ui->setupUi(this);
    ui->rectangles_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->rectangles_table->setColumnCount(2);
    ui->rectangles_table->setHorizontalHeaderLabels({"width", "height"});
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
            dynamic_cast<QLineEdit*> (ui->rectangles_table->cellWidget(i, 0))->text().toInt(),
            dynamic_cast<QLineEdit*> (ui->rectangles_table->cellWidget(i, 1))->text().toInt()
        );
    }
    data.set_rectangles_info(rectangles_vector);
    return data;
}


void EnterData::set_data(const Data& data)
{
    file_name_ = data.get_file_name();
    ui->width_edit->setText(QString::number(data.get_tape_width()));
    ui->rectangles_table->setRowCount(data.get_rectangles_info().size());
    for(size_t i = 0; i < data.get_rectangles_info().size(); i++)
    {
        ui->rectangles_table->setCellWidget(i, 0, new QLineEdit(
            QString::number(data.get_rectangles_info().at(i).first)
        ));
        ui->rectangles_table->setCellWidget(i, 1, new QLineEdit(
            QString::number(data.get_rectangles_info().at(i).second)
        ));
    }
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
    file_name_ = QFileDialog::getOpenFileName(this, "Select file");
}


void EnterData::on_add_rectangle_button_clicked()
{
    ui->rectangles_table->setRowCount(ui->rectangles_table->rowCount() + 1);
    ui->rectangles_table->setCellWidget(ui->rectangles_table->rowCount() - 1, 0, new QLineEdit);
    ui->rectangles_table->setCellWidget(ui->rectangles_table->rowCount() - 1, 1, new QLineEdit);
}


void EnterData::on_delete_rectangle_button_clicked()
{
    ui->rectangles_table->removeRow(ui->rectangles_table->currentRow());
}
