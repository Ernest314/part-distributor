#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>

#include <QDebug>
#include <QFont>
#include <QList>
#include <QObject>
#include <QString>

#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QSpinBox>
#include <QWidget>

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	Ui::MainWindow *ui;

	std::vector<QSpinBox*> disp_spinBoxes;
	std::vector<QScrollArea*> disp_rows;

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

signals:
	void update_disp_name_signal(int index);

private slots:
	void update_disp_name(int index);
	void add_disp_row();
	void remove_disp_row();
	void update_names();
	void update_sectionLeaderDisp();

private:
	QScrollArea* get_scrollArea_row();
	QSpinBox* get_spinBox_row();
	QWidget* get_widget_name();
};

#endif // MAINWINDOW_H
