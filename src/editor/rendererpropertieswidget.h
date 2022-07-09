#ifndef RENDERERPROPERTIESWIDGET_H
#define RENDERERPROPERTIESWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QIntValidator>

#include <raytracer.h>

#include "titledfloattextedit.h"


class RendererPropertiesWidget : public QGroupBox
{
Q_OBJECT
public:
	explicit RendererPropertiesWidget(QWidget* parent = nullptr);

	void setRenderer(const raytracer::ref<raytracer::Renderer>& renderer);

signals:

private:
	void updateValues();

private slots:

	void returnPressedHandler();

private:
	raytracer::ref<raytracer::Renderer> m_rendererRef = nullptr;

	QIntValidator m_validator;
	QVBoxLayout m_layout;

	TitledTextEdit m_recursionTextEdit;
	TitledTextEdit m_samplesTextEdit;
};

#endif // RENDERERPROPERTIESWIDGET_H
