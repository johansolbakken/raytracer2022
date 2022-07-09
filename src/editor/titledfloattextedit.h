#ifndef TITLEDFLOATTEXTEDIT_H
#define TITLEDFLOATTEXTEDIT_H

#include <QWidget>

#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QValidator>

// TODO: Rename file

class TitledTextEdit : public QWidget
{
Q_OBJECT
public:
	TitledTextEdit(QWidget* parent = nullptr);

	~TitledTextEdit();

	void setTitle(const std::string& text);

	void setValidator(QValidator* val);

	void setValue(const std::string& text);

	void setValue(float f);

	void setValue(int n);

	std::string valueString()
	{
		return m_lineEdit->text().toStdString();
	}

	float valueFloat()
	{
		return m_lineEdit->text().toFloat();
	}

	int valueInt()
	{
		return m_lineEdit->text().toInt();
	}

signals:

	void returnPressed();

private slots:

	void returnPressedHandle();

private:
	QHBoxLayout m_layout;
	QLabel* m_label;
	QLineEdit* m_lineEdit;
};

#endif // TITLEDFLOATTEXTEDIT_H
