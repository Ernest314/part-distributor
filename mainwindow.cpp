#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

QScrollArea* MainWindow::get_scrollArea_row()
{
	QScrollArea* scrollArea = new QScrollArea(this);
	scrollArea->setFrameShape(QFrame::NoFrame);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setWidgetResizable(true);
		QWidget* widget = new QWidget(scrollArea);

			QHBoxLayout* layout = new QHBoxLayout(widget);
			layout->setContentsMargins(0, 0, 0, 0);
			layout->setSpacing(12);

		widget->setLayout(layout);	// TODO: remove?
	scrollArea->setWidget(widget);	// TODO: remove?

	return scrollArea;
}

QSpinBox* MainWindow::get_spinBox_row()
{
	QSpinBox* spinBox = new QSpinBox(this);
	spinBox->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	spinBox->setMinimum(1);
	spinBox->setValue(1);
	return spinBox;
}

QWidget* MainWindow::get_widget_name()
{
	QWidget* widget = new QWidget(this);
	widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	widget->setMinimumSize(90, 75);
	widget->setMaximumWidth(90);

		QVBoxLayout* layout_widget = new QVBoxLayout(widget);
		layout_widget->setContentsMargins(4, 4, 4, 4);
		layout_widget->setSpacing(0);
		layout_widget->setStretch(0, 1);
		layout_widget->setStretch(1, 1);

			QLineEdit* lineEdit = new QLineEdit(widget);
			lineEdit->setMinimumHeight(30);
				QFont font_lineEdit = lineEdit->font();
				font_lineEdit.setPointSize(12);
			lineEdit->setFont(font_lineEdit);
			lineEdit->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			lineEdit->setPlaceholderText("Name");

			QHBoxLayout* layout_view = new QHBoxLayout(widget);
			layout_view->setSpacing(0);

				QPushButton* button = new QPushButton(widget);
				button->setEnabled(false);
				button->setMinimumHeight(30);
				button->setMaximumWidth(30);
				button->setIcon(QIcon(":/icons/external.png"));
				button->setIconSize(QSize(18, 18));

			layout_view->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
			layout_view->addWidget(button);
			layout_view->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

		layout_widget->addWidget(lineEdit);
		layout_widget->addLayout(layout_view);

	widget->setLayout(layout_widget);	// TODO: remove?

	return widget;
}
