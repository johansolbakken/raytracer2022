#ifndef PERFORMANCELIST_H
#define PERFORMANCELIST_H

#include <QWidget>
#include <QListWidget>

class PerformanceList : public QListWidget
{
Q_OBJECT
public:
	explicit PerformanceList(QWidget* parent = nullptr);

signals:

public slots:

	void clearRows();

	void addRow(const std::string& text);
};

#endif // PERFORMANCELIST_H
