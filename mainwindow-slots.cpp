#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::add_disp_row()
{
	QSpinBox* spinBox = get_spinBox_row();
	disp_spinBoxes.push_back(spinBox);

	QScrollArea* scrollArea = get_scrollArea_row();
	disp_rows.push_back(scrollArea);

	QGridLayout* layout = ui->layout_disp;
	int last_row = layout->rowCount();
	layout->addWidget(spinBox, last_row, 0);
	layout->addWidget(scrollArea, last_row, 1);

	ui->button_rows_remove->setEnabled(true);
}

void MainWindow::remove_disp_row()
{
	QGridLayout* layout = ui->layout_disp;
	int rows = disp_rows.size();
	if (rows > 1) {
		layout->removeWidget(disp_rows[rows-1]);
		layout->removeWidget(disp_spinBoxes[rows-1]);
		delete disp_rows[rows-1];
		delete disp_spinBoxes[rows-1];
		disp_rows.pop_back();
		disp_spinBoxes.pop_back();
	}
	ui->button_rows_remove->setEnabled(disp_rows.size() > 1);
}
