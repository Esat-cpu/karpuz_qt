#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

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
    int sure;

    int max_skor;
    int kes_karpuz;
    int kac_karpuz;

    void sureBitti();
    void skorOku();
    void skorYaz();
    void karpuzOlustur();


private slots:
    void zamanGuncelle();
};
#endif // DIALOG_H
