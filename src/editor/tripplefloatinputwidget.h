#ifndef TRIPPLEFLOATINPUTWIDGET_H
#define TRIPPLEFLOATINPUTWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QHBoxLayout>
#include <QLabel>

class TrippledoubleInputWidget : public QGroupBox
{
Q_OBJECT
public:
	explicit TrippledoubleInputWidget(QWidget* parent = nullptr);

	~TrippledoubleInputWidget();

	void setValues(double x, double y, double z);

	double getX() const
	{
        return m_x->text().toDouble();
	}

	double getY() const
	{
        return m_y->text().toDouble();
	}

	double getZ() const
	{
        return m_z->text().toDouble();
	}

signals:

	void returnPressed();

private slots:

	void returnPressedHandle();

private:
	QLineEdit* m_x, * m_y, * m_z;
	QDoubleValidator m_validator;

	QLabel m_xLabel, m_yLabel, m_zLabel;
	QHBoxLayout m_layout;

};

#endif // TRIPPLEFLOATINPUTWIDGET_H
