#ifndef PROPERTIESPANEL_H
#define PROPERTIESPANEL_H

#include <QWidget>
#include <QScrollArea>

#include "performancelist.h"
#include "camerawidget.h"
#include "rendererpropertieswidget.h"

class PropertiesPanel : public QScrollArea
{
Q_OBJECT
public:
	explicit PropertiesPanel(QWidget* parent = nullptr);

	void setCamera(const raytracer::ref<raytracer::Camera>&);

	void setRenderer(const raytracer::ref<raytracer::Renderer>&);

signals:
	void onRender();

	void autoRenderChanged(bool enabled);

public slots:
	void displayScanlines(int scanlines);

private slots:

	void renderButtonClicked();

	void setAutoRender(bool enabled);

public:
	PerformanceList* performanceList()
	{
		return m_performanceList;
	}

private:
	PerformanceList* m_performanceList;
	CameraWidget* m_cameraWidget;
	RendererPropertiesWidget* m_rendererWidget;

	QLabel m_scanlines;

};

#endif // PROPERTIESPANEL_H
