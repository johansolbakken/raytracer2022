#include "tripplefloatinputwidget.h"

#include <QDoubleValidator>

TrippleFloatInputWidget::TrippleFloatInputWidget(QWidget* parent)
		: QGroupBox{ parent },
		  m_validator(-100.0, 100, 3),
		  m_xLabel(this),
		  m_yLabel(this),
		  m_zLabel(this)
{
	m_x = new QLineEdit(this);
	m_x->setValidator(&m_validator);
	m_y = new QLineEdit(this);
	m_y->setValidator(&m_validator);
	m_z = new QLineEdit(this);
	m_z->setValidator(&m_validator);

	QObject::connect(m_x, &QLineEdit::returnPressed, this, &TrippleFloatInputWidget::returnPressedHandle);
	QObject::connect(m_y, &QLineEdit::returnPressed, this, &TrippleFloatInputWidget::returnPressedHandle);
	QObject::connect(m_z, &QLineEdit::returnPressed, this, &TrippleFloatInputWidget::returnPressedHandle);

	m_xLabel.setText("x:");
	m_yLabel.setText("y:");
	m_zLabel.setText("z:");

	setLayout(&m_layout);
	m_layout.addWidget(&m_xLabel);
	m_layout.addWidget(m_x);
	m_layout.addWidget(&m_yLabel);
	m_layout.addWidget(m_y);
	m_layout.addWidget(&m_zLabel);
	m_layout.addWidget(m_z);
}

TrippleFloatInputWidget::~TrippleFloatInputWidget()
{
	delete m_x;
	delete m_y;
	delete m_z;
}

void TrippleFloatInputWidget::setValues(float x, float y, float z)
{
	m_x->setText(QString::number(x));
	m_y->setText(QString::number(y));
	m_z->setText(QString::number(z));
}

void TrippleFloatInputWidget::returnPressedHandle()
{
	emit returnPressed();
}
