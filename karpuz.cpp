#include "karpuz.h"

Karpuz::Karpuz(QWidget* parent)
    : QLabel(parent)
{
    this->setPixmap(QPixmap(":/images/images/1.png"));
}


void Karpuz::mousePressEvent(QMouseEvent* event) {
    this->setPixmap(QPixmap(":/images/images/2.png"));

    emit kesildi();

    QTimer::singleShot(1750, this, &QObject::deleteLater);
}
