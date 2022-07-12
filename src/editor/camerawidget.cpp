#include "camerawidget.h"

#include <QGroupBox>

CameraWidget::CameraWidget(QWidget* parent)
		: QGroupBox{ parent }, m_validator(-100.0, 100, 3)
{
	setTitle("Camera");
	m_lookFrom = new TrippledoubleInputWidget(this);
	m_lookFrom->setTitle("Look from");
	m_lookAt = new TrippledoubleInputWidget(this);
	m_lookAt->setTitle("Look at");

	m_vfov = new TitledTextEdit(this);
	m_vfov->setTitle("Vertical FOV");

	m_aperture = new TitledTextEdit(this);
	m_aperture->setTitle("Aperture");

	m_focusDist = new TitledTextEdit(this);
	m_focusDist->setTitle("Focus distance");

	t0 = new TitledTextEdit(this);
	t0->setTitle("Start time");

	t1 = new TitledTextEdit(this);
	t1->setTitle("End time");

	QObject::connect(m_vfov, &TitledTextEdit::returnPressed, this, &CameraWidget::returnPressedHandler);
	QObject::connect(m_aperture, &TitledTextEdit::returnPressed, this, &CameraWidget::returnPressedHandler);
	QObject::connect(m_focusDist, &TitledTextEdit::returnPressed, this, &CameraWidget::returnPressedHandler);
	QObject::connect(t0, &TitledTextEdit::returnPressed, this, &CameraWidget::returnPressedHandler);
	QObject::connect(t1, &TitledTextEdit::returnPressed, this, &CameraWidget::returnPressedHandler);
	QObject::connect(m_lookAt, &TrippledoubleInputWidget::returnPressed, this, &CameraWidget::returnPressedHandler);
	QObject::connect(m_lookFrom, &TrippledoubleInputWidget::returnPressed, this, &CameraWidget::returnPressedHandler);

	m_layout = new QVBoxLayout();
	m_layout->addWidget(m_vfov);
	m_layout->addWidget(m_aperture);
	m_layout->addWidget(m_focusDist);
	m_layout->addWidget(m_lookFrom);
	m_layout->addWidget(m_lookAt);
	m_layout->addWidget(t0);
	m_layout->addWidget(t1);
	setLayout(m_layout);
	updateValues();
}

void CameraWidget::setCamera(const raytracer::ref<raytracer::Camera>& camera)
{
	m_cameraRef = camera;
	updateValues();
}

void CameraWidget::updateValues()
{
	if (m_cameraRef)
	{
		setEnabled(true);

		auto lookFrom = m_cameraRef->lookFrom();
		m_lookFrom->setValues(lookFrom.x, lookFrom.y, lookFrom.z);

		auto lookAt = m_cameraRef->lookAt();
		m_lookAt->setValues(lookAt.x, lookAt.y, lookAt.z);

		m_vfov->setValue(m_cameraRef->vfov());
		m_aperture->setValue(m_cameraRef->aperture());
		m_focusDist->setValue(m_cameraRef->focusDistance());
		t0->setValue(m_cameraRef->time0());
		t1->setValue(m_cameraRef->time1());

	}
	else
	{
		setEnabled(false);
	}
}

void CameraWidget::returnPressedHandler()
{
	raytracer::CameraSpecification spec(m_cameraRef->specification());

	spec.lookFrom = { m_lookFrom->getX(), m_lookFrom->getY(), m_lookFrom->getZ() };
	spec.lookAt = { m_lookAt->getX(), m_lookAt->getY(), m_lookAt->getZ() };
    spec.vfov = m_vfov->valueDouble();
    spec.aperture = m_aperture->valueDouble();
    spec.focusDistance = m_focusDist->valueDouble();
    spec.time0 = t0->valueDouble();
    spec.time1 = t1->valueDouble();

	m_cameraRef->init(spec);
}



