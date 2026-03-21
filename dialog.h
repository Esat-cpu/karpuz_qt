#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class Karpuz;

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;

    QTimer *timer;
    QTimer *oyunTimer;
    int sure;

    int max_skor;
    int kes_karpuz;
    int kac_karpuz;
    QList<Karpuz*> karpuzlar;

    void sureBitti();
    void skorOku();
    void skorYaz();
    void karpuzOlustur(int, int);
    void animasyon();


private slots:
    void zamanGuncelle();
};
#endif // DIALOG_H
