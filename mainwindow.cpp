#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ui->layout_disp->setAlignment(ui->spinBox_disp_row, Qt::AlignCenter);
	ui->layout_disp->setAlignment(ui->widget_disp_name, Qt::AlignCenter);

	disp_rows.push_back(ui->scrollArea_disp_row);

	QSpinBox* spinBox = ui->spinBox_disp_row;
	disp_spinBoxes.push_back(spinBox);
	QObject::connect(	spinBox,	&QSpinBox::editingFinished,
						[=]() { emit update_disp_name_signal(0); }	);
	QObject::connect(	this,	&MainWindow::update_disp_name_signal,
						this,	&MainWindow::update_disp_name	);

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
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
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

		QVBoxLayout* layout_widget = new QVBoxLayout();
		layout_widget->setContentsMargins(4, 4, 4, 4);
		layout_widget->setSpacing(0);
		layout_widget->setStretch(0, 1);
		layout_widget->setStretch(1, 1);

			QLineEdit* lineEdit = new QLineEdit();
			lineEdit->setMinimumHeight(30);
				QFont font_lineEdit = lineEdit->font();
				font_lineEdit.setPointSize(12);
			lineEdit->setFont(font_lineEdit);
			lineEdit->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			lineEdit->setPlaceholderText("Name");

			QHBoxLayout* layout_view = new QHBoxLayout();
			layout_view->setSpacing(0);

				QPushButton* button = new QPushButton();
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

QWidget* MainWindow::get_widget_piece()
{
	QWidget* widget = new QWidget(ui->scrollArea_pieces->widget());

	QGridLayout* layout_main = new QGridLayout();
	layout_main->setContentsMargins(0, 0, 0, 0);
	layout_main->setHorizontalSpacing(30);

		QLineEdit* lineEdit_title = new QLineEdit();
			QFont font_title = lineEdit_title->font();
			font_title.setItalic(true);
		lineEdit_title->setFont(font_title);
		lineEdit_title->setPlaceholderText("Title");

		QHBoxLayout* layout_parts = new QHBoxLayout();
		layout_parts->setSpacing(4);
		layout_parts->addWidget(new QCheckBox("Solo"));
		layout_parts->addSpacerItem(new QSpacerItem(30, 0, QSizePolicy::Maximum, QSizePolicy::Maximum));
		layout_parts->addWidget(new QLabel("Parts:"));
			QPushButton* button_parts_remove = new QPushButton();
			button_parts_remove->setMinimumHeight(25);
			button_parts_remove->setMaximumWidth(25);
			button_parts_remove->setIcon(QIcon(":/icons/minus.png"));
			button_parts_remove->setIconSize(QSize(12, 12));
		layout_parts->addWidget(button_parts_remove);
			QLineEdit* lineEdit_parts = new QLineEdit();
			lineEdit_parts->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
			lineEdit_parts->setMaximumWidth(25);
			lineEdit_parts->setText("3");
			lineEdit_parts->setMaxLength(3);
			lineEdit_parts->setAlignment(Qt::AlignCenter);
			lineEdit_parts->setValidator(new QIntValidator(1, 999, this));
		layout_parts->addWidget(lineEdit_parts);
			QPushButton* button_parts_add = new QPushButton();
			button_parts_add->setMinimumHeight(25);
			button_parts_add->setMaximumWidth(25);
			button_parts_add->setIcon(QIcon(":/icons/plus.png"));
			button_parts_add->setIconSize(QSize(12, 12));
		layout_parts->addWidget(button_parts_add);
		layout_parts->addSpacerItem(new QSpacerItem(30, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

		QVBoxLayout* layout_balance = new QVBoxLayout();
		layout_balance->setSpacing(2);
		layout_balance->addWidget(new QLabel("Balance priority:"));
			QSlider* slider = new QSlider();
			slider->setMinimum(1);
			slider->setMaximum(3);
			slider->setPageStep(1);
			slider->setOrientation(Qt::Horizontal);
			slider->setInvertedControls(true);
		layout_balance->addWidget(slider);
			QHBoxLayout* layout_balance_labels = new QHBoxLayout();
			layout_balance_labels->addWidget(new QLabel("1st"));
			layout_balance_labels->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
			layout_balance_labels->addWidget(new QLabel("3rd"));
		layout_balance->addLayout(layout_balance_labels);

		QPushButton* button_remove = new QPushButton();
		button_remove->setMinimumHeight(30);
		button_remove->setMaximumWidth(30);
		button_remove->setIcon(QIcon(":/icons/trash.png"));
		button_remove->setIconSize(QSize(20, 20));

		QVBoxLayout* layout_move = new QVBoxLayout();
			QPushButton* button_move_up = new QPushButton();
			button_move_up->setMinimumHeight(30);
			button_move_up->setMaximumWidth(30);
			button_move_up->setIcon(QIcon(":/icons/up.png"));
			button_move_up->setIconSize(QSize(18, 18));
		layout_move->addWidget(button_move_up);
			QPushButton* button_move_down = new QPushButton();
			button_move_down->setMinimumHeight(30);
			button_move_down->setMaximumWidth(30);
			button_move_down->setIcon(QIcon(":/icons/down.png"));
			button_move_down->setIconSize(QSize(18, 18));
		layout_move->addWidget(button_move_down);

		QFrame* line = new QFrame();
		line->setFrameShape(QFrame::HLine);
		line->setFrameShadow(QFrame::Sunken);

	layout_main->addWidget(lineEdit_title, 0, 0);
	layout_main->addLayout(layout_parts, 1, 0, 1, 2);
	layout_main->addLayout(layout_balance, 2, 0);
	layout_main->addWidget(button_remove, 0, 1);
	layout_main->addLayout(layout_move, 2, 1);
	layout_main->addWidget(line, 3, 0, 1, 2);

	widget->setLayout(layout_main);

	return widget;
}
