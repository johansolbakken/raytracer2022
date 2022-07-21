#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDockWidget>
#include <QToolBar>

MainWindow::MainWindow(QWidget* parent)
		: QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

    createActions();
    createMenu();

	QDockWidget* dock = new QDockWidget(tr("Properties"), this);
	dock->setAllowedAreas(Qt::AllDockWidgetAreas);
	m_properties = new PropertiesPanel(this);
	dock->setWidget(m_properties);
	addDockWidget(Qt::RightDockWidgetArea, dock);

	m_renderer = new Renderer(this);
    setCentralWidget(m_renderer);

	m_properties->setCamera(m_renderer->camera());
	m_properties->setRenderer(m_renderer->rendererRef());

    QObject::connect(m_properties, &PropertiesPanel::onRender, m_actionRender, &QAction::trigger);

    QObject::connect(m_actionRender, &QAction::triggered, m_renderer, &Renderer::onRender);
    QObject::connect(m_actionStopRender, &QAction::triggered, m_renderer, &Renderer::onAbort);

    QObject::connect(m_actionCopy, &QAction::triggered, this, &MainWindow::copyImage);
    QObject::connect(m_actionSave, &QAction::triggered, this, &MainWindow::saveImage);

	QObject::connect(m_properties, &PropertiesPanel::autoRenderChanged, m_renderer, &Renderer::setAutoRender);
	QObject::connect(m_renderer, &Renderer::hasRenderResult, m_properties->performanceList(), &PerformanceList::addRow);
    QObject::connect(m_renderer, &Renderer::renderingHasBegun, m_properties->performanceList(), &PerformanceList::clearRows);
	QObject::connect(m_renderer, &Renderer::hasScanlines, m_properties, &PropertiesPanel::displayScanlines);
}

MainWindow::~MainWindow()
{
	delete ui;
    delete m_renderer;
}

void MainWindow::createActions()
{
    m_actionRender = new QAction(this);
    m_actionRender->setObjectName("actionRender");
    m_actionRender->setIconText("Render");
    m_actionRender->setIcon(QIcon(":/images/camera.png"));

    m_actionStopRender = new QAction(this);
    m_actionStopRender->setObjectName("actionStopRender");
    m_actionStopRender->setIconText("Stop render");
    m_actionStopRender->setIcon(QIcon(":/images/cross.png"));

    m_actionCopy = new QAction(this);
    m_actionCopy->setObjectName("m_actionCopy");
    m_actionCopy->setIconText("Copy to clipboard");

    m_actionSave = new QAction(this);
    m_actionSave->setObjectName("m_actionSave");
    m_actionSave->setIconText("Save image");

}

void MainWindow::createMenu()
{
    QToolBar* toolBar = new QToolBar(this);

    toolBar->addAction(m_actionRender);
    toolBar->addAction(m_actionStopRender);
    toolBar->addSeparator();
    toolBar->addAction(m_actionCopy);
    toolBar->addAction(m_actionSave);

    addToolBar(toolBar);
}

void MainWindow::renderTriggered(bool enabled)
{
    m_renderer->onRender();
}

void MainWindow::saveImage()
{

}

void MainWindow::copyImage()
{

}
