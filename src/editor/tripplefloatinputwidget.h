#ifndef TRIPPLEFLOATINPUTWIDGET_H
#define TRIPPLEFLOATINPUTWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QHBoxLayout>
#include <QLabel>

class TrippleFloatInputWidget : public QGroupBox
{
Q_OBJECT
public:
	explicit TrippleFloatInputWidget(QWidget* parent = nullptr);

	~TrippleFloatInputWidget();

	void setValues(float x, float y, float z);

	float getX() const
	{
		return m_x->text().toFloat();
	}

	float getY() const
	{
		return m_y->text().toFloat();
	}

	float getZ() const
	{
		return m_z->text().toFloat();
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
