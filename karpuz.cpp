#include "karpuz.h"

Karpuz::Karpuz(QWidget* parent)
    : QLabel(parent)
{
    this->setPixmap(QPixmap(":/images/images/1.png"));
    setScaledContents(true);
    setFixedSize(80, 80);
}


void Karpuz::mousePressEvent(QMouseEvent* event) {
    this->setPixmap(QPixmap(":/images/images/2.png"));
    setScaledContents(true);
    setFixedSize(80, 80);

    emit kesildi();

    QTimer::singleShot(1750, this, &QObject::deleteLater);
}
