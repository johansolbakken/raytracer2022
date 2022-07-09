#include "performancelist.h"

PerformanceList::PerformanceList(QWidget* parent)
		: QListWidget{ parent }
{

}

void PerformanceList::clearRows()
{
	clear();
}

void PerformanceList::addRow(const std::string& text)
{
	addItem(QString::fromStdString(text));
}
