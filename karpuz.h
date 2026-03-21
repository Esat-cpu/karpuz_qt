#ifndef KARPUZ_H
#define KARPUZ_H

#include <QLabel>
#include <QMouseEvent>
#include <QTimer>

class Karpuz : public QLabel
{
    Q_OBJECT
public:
    Karpuz(QWidget* parent);

    void mousePressEvent(QMouseEvent*event) override;

signals:
    void kesildi();
};

#endif // KARPUZ_H
