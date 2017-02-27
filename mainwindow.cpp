#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ui->layout_disp->setAlignment(ui->spinBox_disp_row, Qt::AlignCenter);
	ui->layout_disp->setAlignment(ui->widget_disp_name, Qt::AlignCenter);

	QLineEdit* lineEdit_name = ui->lineEdit_disp_name;
	QObject::connect(	lineEdit_name,	&QLineEdit::editingFinished,
						this,			&MainWindow::update_names	);

	QComboBox* comboBox_leader = ui->comboBox_section_leader;
	QObject::connect(	comboBox_leader,	&QComboBox::currentTextChanged,
						this,				&MainWindow::update_sectionLeaderDisp	);

	QPushButton* button_row_add = ui->button_rows_add;
	QPushButton* button_row_rem = ui->button_rows_remove;
	QObject::connect(	button_row_add,	&QPushButton::clicked,
						this,			&MainWindow::add_disp_row	);
	QObject::connect(	button_row_rem,	&QPushButton::clicked,
						this,			&MainWindow::remove_disp_row	);
}

MainWindow::~MainWindow()
{
	delete ui;
}

QScrollArea* MainWindow::get_scrollArea_row()
{
	QScrollArea* scrollArea = new QScrollArea(ui->scrollArea_disp->widget());
	scrollArea->setWidget(new QWidget());
		QSizePolicy sizePolicy = scrollArea->sizePolicy();
		sizePolicy.setVerticalPolicy(QSizePolicy::Minimum);
	scrollArea->setSizePolicy(sizePolicy);
	scrollArea->setFrameShape(QFrame::NoFrame);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setWidgetResizable(true);

		QHBoxLayout* layout = new QHBoxLayout();
		layout->setContentsMargins(0, 0, 0, 0);
		layout->setSpacing(12);
			QWidget* widget = get_widget_name();
			layout->addWidget(widget);

	scrollArea->widget()->setLayout(layout);	// TODO: remove?

	return scrollArea;
}

QSpinBox* MainWindow::get_spinBox_row()
{
	QSpinBox* spinBox = new QSpinBox(ui->scrollArea_disp->widget());
	spinBox->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	spinBox->setMinimum(1);
	spinBox->setValue(1);
	return spinBox;
}

QWidget* MainWindow::get_widget_name()
{
	QWidget* widget = new QWidget(ui->scrollArea_disp->widget());
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

			QHBoxLayout* layout_view = new QHBoxLayout();
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

	QObject::connect(	lineEdit,	&QLineEdit::editingFinished,
						this,		&MainWindow::update_names	);

	return widget;
}
