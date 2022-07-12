#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDockWidget>

MainWindow::MainWindow(QWidget* parent)
		: QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	setCentralWidget(nullptr);

	QDockWidget* dock = new QDockWidget(tr("Properties"), this);
	dock->setAllowedAreas(Qt::AllDockWidgetAreas);
	m_properties = new PropertiesPanel(this);
	dock->setWidget(m_properties);
	addDockWidget(Qt::RightDockWidgetArea, dock);

	dock = new QDockWidget(tr("Renderer"), this);
	dock->setAllowedAreas(Qt::AllDockWidgetAreas);
	m_renderer = new Renderer(this);
	dock->setWidget(m_renderer);
	addDockWidget(Qt::LeftDockWidgetArea, dock);

	m_properties->setCamera(m_renderer->camera());
	m_properties->setRenderer(m_renderer->rendererRef());

	QObject::connect(m_properties, &PropertiesPanel::onRender, m_renderer, &Renderer::onRender);
	QObject::connect(m_properties, &PropertiesPanel::autoRenderChanged, m_renderer, &Renderer::setAutoRender);
	QObject::connect(m_renderer, &Renderer::hasRenderResult, m_properties->performanceList(), &PerformanceList::addRow);
	QObject::connect(m_renderer, &Renderer::hasScanlines, m_properties, &PropertiesPanel::displayScanlines);
}

MainWindow::~MainWindow()
{
	delete ui;
	delete m_renderer;
}
