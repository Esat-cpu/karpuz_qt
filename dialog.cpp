#include "dialog.h"
#include "ui_dialog.h"

#include <QMessageBox>
#include <QTimer>
#include <QFile>

#include "karpuz.h"


static const QString SKORLAR = "dosya/skorlar.txt";
static const QString KONUMLAR = "dosya/konumlar.txt";


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    // Top barın rengi
    ui->top_bar->setStyleSheet("background-color: lightgray;");
    // Arka plan resmi
    ui->site->setStyleSheet("border-image: url(:/images/images/back.jpg);");

    // Skorlar dosyasını oku
    skorOku();

    // skor
    kes_karpuz = 0;
    kac_karpuz = 0;


    // Oyun süresi için Timer
    sure = 30;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Dialog::zamanGuncelle);
    timer->start(1000);

    // Sürekli hareket için Timer
    oyunTimer = new QTimer(this);
    connect(oyunTimer, &QTimer::timeout, this, &Dialog::animasyon);
    oyunTimer->start(16);

    // DEBUG
    karpuzOlustur(100, 100);
}

Dialog::~Dialog()
{
    delete ui;
}


// Timer için her saniye çalışan fonksiyon
void Dialog::zamanGuncelle() {
    // Süreyi güncelle
    --sure;
    ui->sure_label->setText(QString::number(sure));

    // Süre bittiğinde
    if (sure == 0) {
        timer->stop();
        oyunTimer->stop();
        sureBitti();
    }
}


// Süre bittiğinde çalışacak fonksiyon
void Dialog::sureBitti() {
    QString metin = "";

    metin.append("Oyun Bitti! ");

    // Max Skor kontrolü
    if (kes_karpuz > max_skor)
        metin.append("Tebrikler Maximum Skor Sizde!");
    else
        metin.append("Maksimum Skoru Geçemediniz!");

    metin.append("\nKesilen Karpuz Sayısı: ").append(QString::number(kes_karpuz));
    metin.append("\nKaçırılan Karpuz Sayısı: ").append(QString::number(kac_karpuz));
    metin.append("\nMaximum Skor: ").append(QString::number(max_skor));

    // Skoru kaydet
    skorYaz();

    // Mesaj göster ve çık
    QMessageBox::information(this, "Bilgi!", metin);
    this->accept();
}


// Skorlar dosyası okunur ve max_skor alınır
void Dialog::skorOku() {
    QString satir;
    QFile skorlar(SKORLAR);

    if (!skorlar.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString hataMesaji = "Skorlar dosyasını okumada hata:\n";
        hataMesaji.append(skorlar.errorString());
        QMessageBox::critical(this, "Hata!", hataMesaji);
        std::exit(1);
        return;
    }

    QTextStream stream(&skorlar);
    satir = stream.readLine();
    max_skor = satir.toInt();

    while (!stream.atEnd()) {
        satir = stream.readLine();
        int sayi = satir.toInt();
        if (max_skor < sayi) max_skor = sayi;
    }
}


// Skorlar dosyasına skor kaydedilir
void Dialog::skorYaz() {
    QFile skorlar(SKORLAR);

    if (!skorlar.open(QIODevice::Append | QIODevice::Text)) {
        QString hataMesaji = "Skorlar dosyasına yazmada hata:\n";
        hataMesaji.append(skorlar.errorString());
        QMessageBox::critical(this, "Hata!", hataMesaji);
        return;
    }

    QTextStream stream(&skorlar);
    stream << kes_karpuz << "\n";
}


// Verilen koordinatlarda karpuz oluştur
void Dialog::karpuzOlustur(int x, int y) {
    Karpuz* k = new Karpuz(this);

    connect(k, &Karpuz::kesildi, ui->site, [=](){
        karpuzlar.removeOne(k);
        ui->kesilen_label->setText(QString::number(++kes_karpuz));
    });

    k->move(x, y);
    k->show();

    karpuzlar.append(k);
}


// Karpuz hareketi ve ekran dışına çıkma kontrolü
void Dialog::animasyon() {
    QList<Karpuz*> silinecekler;

    for (Karpuz* k : karpuzlar) {
        k->move(k->x(), k->y() + 3);

        if (k->y() > ui->site->height()+100) silinecekler.append(k);
    }

    for (Karpuz* k : silinecekler) {
        karpuzlar.removeOne(k);
        k->deleteLater();
        ui->kacirilan_label->setText(QString::number(++kac_karpuz));
    }
}

