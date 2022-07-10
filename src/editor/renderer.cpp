#include "renderer.h"
#include "utils/timer.h"

#include <QResizeEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QThread>
#include <sstream>
#include <iomanip>

Renderer::Renderer(QWidget* parent)
		: QWidget{ parent }
{
	raytracer::RendererSpecification spec{};
	spec.backgroundColor = { 0.01, 0.01, 0.01 };
	spec.recursionDepth = 25;
	spec.samplesPerPixel = 16;

	m_renderer.reset(new raytracer::Renderer(spec));
	createCamera();
	createWorld();
}

void Renderer::resizeEvent(QResizeEvent* event)
{
	auto size = event->size();
	m_camera->onResize(size.width(), size.height());
	m_renderer->onResize(size.width(), size.height());
}

void Renderer::paintEvent(QPaintEvent* event)
{
	auto image = m_renderer->getFinalImage();
	image->flipHorizontal();

	QImage qImage((uchar*)image->data(), image->width(), image->height(), QImage::Format_RGBA8888);

	QPoint point(0, 0);

	QPainter painter(this);
	painter.drawImage(point, qImage);
	painter.end();
	m_enabled = false;
}

void Renderer::createCamera()
{
	using namespace raytracer;

	CameraSpecification spec{};
	spec.aspect_ratio = (double)width() / (double)height();
	spec.lookFrom = { 13, 2, 3 };
	spec.lookAt = { 0, 0, 0 };
	spec.focusDistance = 10.0;
	spec.vfov = 20.0f;

	m_camera = createRef<Camera>(spec);
}

void Renderer::createWorld()
{
	using namespace raytracer;

	m_world = createRef<HittableList>();

	auto texture = createRef<CheckerTexture>(Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9));
	auto material = createRef<Lambertian>(texture);

	auto diffuseLight = createRef<DiffuseLight>(Color(4, 4, 4));

	m_world->add<Sphere>(Point3(0, -10, 0), 10, diffuseLight);
	m_world->add<Sphere>(Point3(0, 10, 0), 10, material);
}


void Renderer::onRender()
{
	m_enabled = true;
	renderImage();
}

void Renderer::setAutoRender(bool enabled)
{
	m_autoRender = enabled;
}

void Renderer::renderFrame()
{
	raytracer::ScopedTimer timer("Renderer::paintEvent", [&](raytracer::ScopedTimerResult result)
	{
		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << result.time << "ms | " << result.name;
		emit hasRenderResult(stream.str());
	});
	{
		raytracer::ScopedTimer timer("raytracer::Renderer::render", [&](raytracer::ScopedTimerResult result)
		{
			std::stringstream stream;
			stream << std::fixed << std::setprecision(2) << result.time << "ms | " << result.name;
			emit hasRenderResult(stream.str());
		});
		m_renderer->render(m_world, m_camera);
	}
}

void Renderer::renderImage()
{
	delete m_thread;
	m_thread = QThread::create([&]()
	{
		bool first = true;
		while (first || m_autoRender)
		{
			renderFrame();
			update();
			first = false;
		}
	});

	m_thread->start();
}
