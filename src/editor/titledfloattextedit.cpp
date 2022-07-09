#include "titledfloattextedit.h"


TitledTextEdit::TitledTextEdit(QWidget* parent)
		: QWidget(parent),
		  m_layout(this)
{
	m_label = new QLabel(this);
	m_lineEdit = new QLineEdit(this);
	m_lineEdit->setPlaceholderText(m_label->text());

	setLayout(&m_layout);
	m_layout.addWidget(m_label);
	m_layout.addWidget(m_lineEdit);

	QObject::connect(m_lineEdit, &QLineEdit::returnPressed, this, &TitledTextEdit::returnPressedHandle);
}

TitledTextEdit::~TitledTextEdit()
{
	delete m_label;
	delete m_lineEdit;
}

void TitledTextEdit::setTitle(const std::string& text)
{
	auto str = QString::fromStdString(text);
	m_label->setText(str);
	m_lineEdit->setPlaceholderText(str);
}

void TitledTextEdit::setValue(const std::string& text)
{
	m_lineEdit->setText(QString::fromStdString(text));
}

void TitledTextEdit::setValue(float f)
{
	m_lineEdit->setText(QString::number(f));
}

void TitledTextEdit::setValue(int n)
{
	m_lineEdit->setText(QString::number(n));
}

void TitledTextEdit::setValidator(QValidator* val)
{
	m_lineEdit->setValidator(val);
}

void TitledTextEdit::returnPressedHandle()
{
	emit returnPressed();
}
