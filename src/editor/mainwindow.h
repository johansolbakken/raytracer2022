#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "renderer.h"
#include "propertiespanel.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);

	~MainWindow();

    void createActions();
    void createMenu();


private slots:
    void renderTriggered(bool enabled);
    void saveImage();
    void copyImage();

private:
    QAction* m_actionRender;
    QAction* m_actionStopRender;
    QAction* m_actionCopy;
    QAction* m_actionSave;

private:
	Ui::MainWindow* ui;
	Renderer* m_renderer;
	PropertiesPanel* m_properties;
};

#endif // MAINWINDOW_H
