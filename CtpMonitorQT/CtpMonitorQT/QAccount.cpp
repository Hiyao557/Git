#include "QAccount.h"

QAccount::QAccount(QWidget *parent)
	: QWidget(parent)
{
	setWindowTitle(tr("Paint Demo"));
	setPalette(QPalette(Qt::white)); //设置背景颜色
	setAutoFillBackground(true);//设置自动填充背景色
	perset = 0;
}

QAccount::~QAccount()
{


}

void QAccount::paintEvent(QPaintEvent *)
{

	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing); 
	int m_persent = perset;//绘制的环的比例 
	int m_rotateAngle = 360*m_persent/100; 
	int side = qMin(width(), height())-20; 
	QRectF outRect(20, 20, side, side);//矩形长宽为窗口的长宽
	QRectF inRect(40, 40, side-40, side-40);
	QString valueStr = QString(u8"多头占比 %1%  ").arg(QString::number(m_persent)); //画外圆
	p.setPen(Qt::NoPen);
	p.setBrush(QBrush(QColor(97, 117, 118)));
	p.drawEllipse(outRect); //画内圆
	p.setBrush(QBrush(QColor(255, 107, 107))); 
	p.drawPie(outRect, (90-m_rotateAngle)*16, m_rotateAngle*16); //画遮罩，遮罩颜色为窗口颜色
	p.setBrush(palette().window().color());
	p.drawEllipse(inRect); //画文字 
	QFont f = QFont("Microsoft YaHei", 15, QFont::Bold); 
	p.setFont(f); p.setFont(f); p.setPen(QColor("#555555"));
	p.drawText(inRect, Qt::AlignCenter, valueStr);
	


}

void QAccount::setPerset(int perset)
{

	this->perset = perset;


}
