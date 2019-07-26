#include "QtLogWidget.h"
#include "LOGGER.h"
#include <QScrollBar>
using namespace CTPTOOL;
QtLogWidget::QtLogWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QObject::connect(this, SIGNAL(appendlog(QString)), this, SLOT(OnAppendLog(QString)));
	LOGGER::GetInstance()->hxevent.Adddealer(this);
}
void QtLogWidget::OnAppendLog(QString log)
{ 
	if (ui.plainTextEdit->blockCount() > 100) {
		ui.plainTextEdit->setPlainText("");
	}

	auto workCursor = ui.plainTextEdit->textCursor();
	     workCursor.movePosition(QTextCursor::End);
	     workCursor.insertText(log);
	     workCursor.insertBlock();
		QScrollBar *scrollbar = ui.plainTextEdit->verticalScrollBar();
		 if (scrollbar)
			  {
			  scrollbar->setSliderPosition(scrollbar->maximum());
			     }
	
}
QtLogWidget::~QtLogWidget()
{
	LOGGER::GetInstance()->hxevent.Movedealer(this);
}

void QtLogWidget::OnHxEvent(eventstruct event)
{
	emit appendlog(QString::fromLocal8Bit(event.message.data()));
}
