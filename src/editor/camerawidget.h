#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QWidget>
#include <raytracer.h>
#include <QLineEdit>
#include <QGroupBox>

#include "titledfloattextedit.h"
#include "tripplefloatinputwidget.h"

class CameraWidget : public QGroupBox
{
Q_OBJECT
public:
	explicit CameraWidget(QWidget* parent = nullptr);

	void setCamera(const raytracer::ref<raytracer::Camera>& camera);

signals:

private:
	void updateValues();

private slots:

	void returnPressedHandler();

private:
	QVBoxLayout* m_layout;

	raytracer::ref<raytracer::Camera> m_cameraRef = nullptr;

	TitledTextEdit* m_vfov, * m_aperture, * m_focusDist, * t0, * t1;
	TrippledoubleInputWidget* m_lookFrom, * m_lookAt;

	QDoubleValidator m_validator;
};

#endif // CAMERAWIDGET_H
