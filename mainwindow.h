#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	QScrollArea* get_scrollArea_row();
	QSpinBox* get_spinBox_row();
	QWidget* get_widget_name();
};

#endif // MAINWINDOW_H
