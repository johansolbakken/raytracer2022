#ifndef RENDERER_H
#define RENDERER_H

#include <QWidget>
#include <QThread>

#include <raytracer.h>
#include <QSemaphore>

class Renderer : public QWidget
{
Q_OBJECT
public:
	explicit Renderer(QWidget* parent = nullptr);

	raytracer::ref<raytracer::Renderer> rendererRef() const
	{
		return m_renderer;
	}

	raytracer::ref<raytracer::Camera> camera() const
	{
		return m_camera;
	}

signals:

	void hasRenderResult(const std::string& result);

	void hasScanlines(int scanlines);

public slots:

	void onRender();

	void setAutoRender(bool enabled);

protected:
	void resizeEvent(QResizeEvent* event) override;

	void paintEvent(QPaintEvent* event) override;

private:
	void createCamera();

	void createWorld();

	void renderImage();

	void renderFrame();

	raytracer::ref<raytracer::Renderer> m_renderer;
	raytracer::ref<raytracer::Camera> m_camera;
	raytracer::ref<raytracer::HittableList> m_world;

	QThread* m_thread = nullptr;

	QSemaphore* m_sem;
	bool m_autoRender = false;
	bool m_enabled = false;
};

#endif // RENDERER_H
