#include "QAccount.h"

QAccount::QAccount(QWidget *parent)
	: QWidget(parent)
{
	setWindowTitle(tr("Paint Demo"));
	setPalette(QPalette(Qt::white)); //���ñ�����ɫ
	setAutoFillBackground(true);//�����Զ���䱳��ɫ
	perset = 0;
}

QAccount::~QAccount()
{


}

void QAccount::paintEvent(QPaintEvent *)
{

	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing); 
	int m_persent = perset;//���ƵĻ��ı��� 
	int m_rotateAngle = 360*m_persent/100; 
	int side = qMin(width(), height())-20; 
	QRectF outRect(20, 20, side, side);//���γ���Ϊ���ڵĳ���
	QRectF inRect(40, 40, side-40, side-40);
	QString valueStr = QString(u8"��ͷռ�� %1%  ").arg(QString::number(m_persent)); //����Բ
	p.setPen(Qt::NoPen);
	p.setBrush(QBrush(QColor(97, 117, 118)));
	p.drawEllipse(outRect); //����Բ
	p.setBrush(QBrush(QColor(255, 107, 107))); 
	p.drawPie(outRect, (90-m_rotateAngle)*16, m_rotateAngle*16); //�����֣�������ɫΪ������ɫ
	p.setBrush(palette().window().color());
	p.drawEllipse(inRect); //������ 
	QFont f = QFont("Microsoft YaHei", 15, QFont::Bold); 
	p.setFont(f); p.setFont(f); p.setPen(QColor("#555555"));
	p.drawText(inRect, Qt::AlignCenter, valueStr);
	


}

void QAccount::setPerset(int perset)
{

	this->perset = perset;


}
