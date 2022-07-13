#include "renderer.h"
#include "utils/timer.h"

#include <QResizeEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QThread>
#include <sstream>
#include <future>
#include <iomanip>

Renderer::Renderer(QWidget* parent)
		: QWidget{ parent }
{
	raytracer::RendererSpecification spec{};
	spec.backgroundColor = { 0.01, 0.01, 0.01 };
    spec.recursionDepth = 50;
    spec.samplesPerPixel = 100;

	m_renderer.reset(new raytracer::Renderer(spec));
	createCamera();
	createWorld();

    m_renderer->registerCallback([&](int scanlines){
        emit hasScanlines(scanlines);
        update();
    });
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
    //image->flipHorizontal();

    QImage qImage;
    {
        std::lock_guard guard(image->mutex());
        qImage = QImage((uchar*)image->data(), image->width(), image->height(), QImage::Format_RGBA8888);
    }

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
    spec.vfov = 40.0f;
    spec.lookFrom = {278, 278, -800 };
    spec.lookAt = { 278, 278, 0 };
    spec.focusDistance = 10.0;
    spec.aperture = 0.0;
    spec.time0 = 0.0;
    spec.time1 = 1.0;

	m_camera = createRef<Camera>(spec);
}

void Renderer::createWorld()
{
    using namespace raytracer;

    m_world = createRef<HittableList>();

    auto red   = createRef<Lambertian>(Color(.65, .05, .05));
    auto white = createRef<Lambertian>(Color(.73, .73, .73));
    auto green = createRef<Lambertian>(Color(.12, .45, .15));
    auto light = createRef<DiffuseLight>(Color(15, 15, 15));

    m_world->add<yz_rect>(0, 555, 0, 555, 555, green);
    m_world->add<yz_rect>(0, 555, 0, 555, 0, red);
    m_world->add<FlipFace>(createRef<xz_rect>(213, 343, 227, 332, 554, light));
    m_world->add<xz_rect>(0, 555, 0, 555, 555, white);
    m_world->add<xz_rect>(0, 555, 0, 555, 0, white);
    m_world->add<xy_rect>(0, 555, 0, 555, 555, white);

    ref<Hittable> box1 = createRef<Box>(Point3(0,0,0), Point3(165,330,165), white);
    box1 = createRef<RotateY>(box1, 15);
    box1 = createRef<Translate>(box1, Vector3(265,0,295));
    m_world->add(box1);

    ref<Hittable> box2 = createRef<Box>(Point3(0,0,0), Point3(165,165,165), white);
    box2 = createRef<RotateY>(box2, -18);
    box2 = createRef<Translate>(box2, Vector3(130,0,65));
    m_world->add(box2);
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
