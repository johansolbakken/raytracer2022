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
	spec.recursionDepth = 25;
	spec.samplesPerPixel = 16;

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
	image->flipHorizontal();

    QImage qImage;
    {
        std::lock_guard(image->mutex());
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
    spec.lookFrom = { 478, 278, -600 };
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

    HittableList boxes1;
    auto ground = createRef<Lambertian>(Color(0.48, 0.83, 0.53));

    const int boxes_per_side = 20;
    for (int i = 0; i < boxes_per_side; i++)
    {
        for (int j = 0; j < boxes_per_side; j++)
        {
            auto w = 100.0;
            auto x0 = -1000.0 + i * w;
            auto z0 = -1000.0 + j * w;
            auto y0 = 0.0;
            auto x1 = x0 + w;
            auto y1 = randomdouble(1, 101);
            auto z1 = z0 + w;

            boxes1.add<Box>(Point3(x0, y0, z0), Point3(x1, y1, z1), ground);
        }
    }

    m_world = createRef<HittableList>();

    m_world->add<BvhNode>(boxes1, 0, 1);

    auto light = createRef<DiffuseLight>(Color(7, 7, 7));
    m_world->add<xz_rect>(123, 423, 147, 412, 554, light);

    auto center1 = Point3(400, 400, 200);
    auto center2 = center1 + Vector3(30, 0, 0);
    auto moving_sphere_material = createRef<Lambertian>(Color(0.7, 0.3, 0.1));
    m_world->add<MovingSphere>(center1, center2, 0, 1, 50, moving_sphere_material);

    m_world->add<Sphere>(Point3(260, 150, 45), 50, createRef<Dielectric>(1.5));
    m_world->add<Sphere>(Point3(0, 150, 145), 50, createRef<Metal>(Color(0.8, 0.8, 0.9), 1.0));

    auto boundary = createRef<Sphere>(Point3(360, 150, 145), 70, createRef<Dielectric>(1.5));
    m_world->add(boundary);
    m_world->add<ConstantMedium>(boundary, 0.2, Color(0.2, 0.4, 0.9));
    boundary = createRef<Sphere>(Point3(0, 0, 0), 5000, createRef<Dielectric>(1.5));
    m_world->add<ConstantMedium>(boundary, .0001, Color(1, 1, 1));

    auto emat = createRef<Lambertian>(createRef<ImageTexture>("/Users/johansolbakken/Developer/raytracer2022/src/examples/earth-image/images/earthmap.jpg"));
    m_world->add<Sphere>(Point3(400, 200, 400), 100, emat);
    auto pertext = createRef<NoiseTexture>(0.1);
    m_world->add<Sphere>(Point3(220, 280, 300), 80, createRef<Lambertian>(pertext));

    HittableList boxes2;
    auto white = createRef<Lambertian>(Color(.73, .73, .73));
    int ns = 1000;
    for (int j = 0; j < ns; j++)
    {
        boxes2.add<Sphere>(randomVec3(0, 165), 10, white);
    }

    m_world->add<Translate>(createRef<RotateY>(createRef<BvhNode>(boxes2, 0.0, 1.0), 15), Vector3(-100, 270, 395));
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
