#include "rendererpropertieswidget.h"

#include <QObject>

RendererPropertiesWidget::RendererPropertiesWidget(QWidget* parent)
		: QGroupBox{ parent },
		  m_validator(1, 1000, this),
		  m_layout(this),
		  m_samplesTextEdit(this),
		  m_recursionTextEdit(this)
{
	setTitle("Renderer");

	m_samplesTextEdit.setValidator(&m_validator);
	m_samplesTextEdit.setTitle("Samples per pixel");
	m_recursionTextEdit.setValidator(&m_validator);
	m_recursionTextEdit.setTitle("Maximum recursion depth");

	m_layout.addWidget(&m_samplesTextEdit);
	m_layout.addWidget(&m_recursionTextEdit);

	QObject::connect(&m_samplesTextEdit, &TitledTextEdit::returnPressed, this,
			&RendererPropertiesWidget::returnPressedHandler);
	QObject::connect(&m_recursionTextEdit, &TitledTextEdit::returnPressed, this,
			&RendererPropertiesWidget::returnPressedHandler);

	setLayout(&m_layout);
	updateValues();
}

void RendererPropertiesWidget::setRenderer(const raytracer::ref<raytracer::Renderer>& renderer)
{
	m_rendererRef = renderer;
	updateValues();
}

void RendererPropertiesWidget::updateValues()
{
	if (m_rendererRef)
	{
		setEnabled(true);

		m_recursionTextEdit.setValue(m_rendererRef->maximumRecursionDepth());
		m_samplesTextEdit.setValue(m_rendererRef->samplesPerPixel());


	}
	else
	{
		setEnabled(false);
	}
}

void RendererPropertiesWidget::returnPressedHandler()
{
	raytracer::RendererSpecification spec(m_rendererRef->specification());
	spec.recursionDepth = m_recursionTextEdit.valueInt();
	spec.samplesPerPixel = m_samplesTextEdit.valueInt();

	m_rendererRef->init(spec);
}
