#include "propertiespanel.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QCheckBox>
#include <QLabel>

PropertiesPanel::PropertiesPanel(QWidget* parent)
		: QScrollArea{ parent }, m_scanlines(this)
{
	QPushButton* button = new QPushButton(this);
	button->setText("Render");
	QObject::connect(button, &QPushButton::clicked, this, &PropertiesPanel::renderButtonClicked);

	QCheckBox* checkBox = new QCheckBox(this);
	checkBox->setChecked(false);
	checkBox->setText("Auto render");
	QObject::connect(checkBox, &QCheckBox::toggled, this, &PropertiesPanel::setAutoRender);

	m_performanceList = new PerformanceList(this);
	m_performanceList->clear();


	m_cameraWidget = new CameraWidget(this);

	m_rendererWidget = new RendererPropertiesWidget(this);

	m_scanlines.setText("Scanlines:");

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(&m_scanlines);
	layout->addWidget(m_performanceList);
	layout->addWidget(button);
	layout->addWidget(checkBox);
	layout->addWidget(m_rendererWidget);
	layout->addWidget(m_cameraWidget);
	setLayout(layout);
}

void PropertiesPanel::setCamera(const raytracer::ref<raytracer::Camera>& camera)
{
	m_cameraWidget->setCamera(camera);
}

void PropertiesPanel::setRenderer(const raytracer::ref<raytracer::Renderer>& renderer)
{
	m_rendererWidget->setRenderer(renderer);
}

void PropertiesPanel::displayScanlines(int scanlines)
{
    m_scanlines.setText("Scanlines: " + QString::number(scanlines));
}

void PropertiesPanel::renderButtonClicked()
{
	emit onRender();
}

void PropertiesPanel::setAutoRender(bool enabled)
{
	emit autoRenderChanged(enabled);
}
