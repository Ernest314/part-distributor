#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>

#include <QLineEdit>
#include <QPushButton>
#include <QScrollBar>
#include <QSpinBox>
#include <QWidget>

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
	QSpinBox* get_spinBox_rowNum();
	QWidget* get_widget_dispName();
};

#endif // MAINWINDOW_H
