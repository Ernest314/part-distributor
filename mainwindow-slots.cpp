#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::update_disp_name(int index)
{
	int new_size = (disp_spinBoxes[index])->value();
	int old_size =
			((disp_rows[index])->widget()->findChildren<QLineEdit*>()).count();

	if (new_size > old_size) {
		for (int i=0; i < new_size-old_size; ++i) {
			(disp_rows[index])->widget()->layout()->addWidget(get_widget_name());
		}
	}
	if (new_size < old_size) {
		for (int i=old_size-1; i >= new_size; --i) {
			QLayoutItem* item = (disp_rows[index])->widget()->layout()->takeAt(i);
			delete item->widget();
		}
	}
}

void MainWindow::add_disp_row()
{
	QSpinBox* spinBox = get_spinBox_row();
	disp_spinBoxes.push_back(spinBox);

	QScrollArea* scrollArea = get_scrollArea_row();
	disp_rows.push_back(scrollArea);
	int last_row = disp_rows.size();

	QObject::connect(	spinBox,	&QSpinBox::editingFinished,
						[=]() { emit update_disp_name_signal(last_row-1); }	);

	QGridLayout* layout = ui->layout_disp;
	layout->addWidget(spinBox, last_row-1, 0);
	layout->addWidget(scrollArea, last_row-1, 1);

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

void MainWindow::update_names()
{
	QComboBox* comboBox = ui->comboBox_section_leader;
	QString sectionLeader_prev = comboBox->currentText();
	comboBox->clear();

	for (QScrollArea* scrollArea : disp_rows) {
		//recursive
		QList<QLineEdit*> lineEdits = scrollArea->widget()->findChildren<QLineEdit*>();
		for (QLineEdit* lineEdit : lineEdits) {
			comboBox->addItem(lineEdit->text());
			if (lineEdit->text() == sectionLeader_prev) {
				comboBox->setCurrentIndex(comboBox->findText(sectionLeader_prev));
			}
		}
	}
}

void MainWindow::update_sectionLeaderDisp()
{
	QString sectionLeader = ui->comboBox_section_leader->currentText();

	for (QScrollArea* scrollArea : disp_rows) {
		//recursive
		QList<QLineEdit*> lineEdits = scrollArea->widget()->findChildren<QLineEdit*>();
		for (QLineEdit* lineEdit : lineEdits) {
			QFont font = lineEdit->font();
			font.setBold(lineEdit->text() == sectionLeader);
			lineEdit->setFont(font);
		}
	}
}

void MainWindow::add_piece()
{
	QWidget* widget = get_widget_piece();
	ui->layout_pieces->insertWidget(1, widget);
}
