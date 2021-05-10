#include "FenCodeGenere.h"
#include <iostream>
#include <fstream>
#include "TimeDivision.h"
#include "Lecture.h"
#include "Ecriture.h"
#include "Identify.h"
#include "Comparer.h"

#include <QScrollArea>
#include <QVBoxLayout>

FenCodeGenere::FenCodeGenere(QString &code, QWidget *parent = 0) : QDialog(parent)
{
    setWindowTitle("Correcteur de Notation");

    string file = code.toLocal8Bit().constData();
    string path(file);
    Lecture lecture;
    lecture.Read(&path);
    string* s = lecture.return_lm();
    int size = lecture.get_size();

    Identify iden(s,size);
    TimeDivision* tl = iden.get_TimeLines();

    cout <<"  NB TIMELINES "<< tl->size()<<endl;
    tl->clear_tl();
    cout <<"  NB TIMELINES "<< tl->size()<<endl;

    system("mkdir output");
    string write_path= "output/results.pgn";
    Ecriture ecriture;
    timelines = ecriture.Write(tl,&write_path);

    QGridLayout *timel = new QGridLayout;

    int x;
    if (tl->size() > 10) {
        x = 10;
    }
    else {
        x = tl->size();
    }

    QString a1;
    QString b1;
    QString c1;
    QString d1;
    QString e1;
    QString f1;
    QString g1;
    QString h1;
    QString i1;
    QString j1;

    QPushButton *a = new QPushButton;
    QPushButton *b = new QPushButton;
    QPushButton *c = new QPushButton;
    QPushButton *d = new QPushButton;
    QPushButton *e = new QPushButton;
    QPushButton *f = new QPushButton;
    QPushButton *g = new QPushButton;
    QPushButton *h = new QPushButton;
    QPushButton *i = new QPushButton;
    QPushButton *j = new QPushButton;
    a->setText("Télécharger");
    b->setText("Télécharger");
    c->setText("Télécharger");
    d->setText("Télécharger");
    e->setText("Télécharger");
    f->setText("Télécharger");
    g->setText("Télécharger");
    h->setText("Télécharger");
    i->setText("Télécharger");
    j->setText("Télécharger");

    ifstream fichier(file);


    QString lec;

    while(getline(fichier, line)) {
        lec += QString::fromStdString(line + "\n");
    }



    QLabel *textoriginal = new QLabel;
    textoriginal->setText(lec);
    timel->addWidget(textoriginal, 1, 0);

    for (int o = 1; o <= x; o++){
        QLabel *text = new QLabel;
        QString aaa = QString::fromStdString(timelines.at(o-1));
        QString bbb;

        QStringList ccc;
        QStringList ddd;
        QStringList eee;
        ccc = lec.split("\n");
        ddd = aaa.split("\n");
        for (int s = 0; s < min(ddd.size(), ccc.size()) ; s++) {
            if (ccc[s] != ddd[s]) {
                bbb += ddd[s] + "\n";
                eee += ddd[s];
            }
            else {
                bbb += "\n";
            }
        }
        text->setText(bbb);
        cout << eee.size() << endl;
        if (eee.size() < 2) {
            text->setText("Aucun changement");
        }
        else if (eee.size() == 2) {
            text->setStyleSheet("QLabel { color : #1F6286; }");
        }
        else if (eee.size() == 3) {
            text->setStyleSheet("QLabel { color : #4C8548; }");
        }
        else if (eee.size() == 4) {
            text->setStyleSheet("QLabel { color : #AF8B1B; }");
        }

        else if (eee.size() > 4) {
            text->setStyleSheet("QLabel { color : #AF1B1B; }");
        }
        timel->addWidget(text, 1, o);
    }

    QLabel *originel = new QLabel;
    originel->setText("Original");
    timel->addWidget(originel, 0, 0);

    for (int vv = 0 ; vv < x; vv++) {
        QLabel *correction = new QLabel;
        correction->setText("Correction n°" + QString::number(vv + 1));
        timel->addWidget(correction, 0, vv + 1);
    }

    switch (x) {
    case 1:
    {
        a1 = QString::fromStdString(timelines.at(0));
        timel->addWidget(a, 2, 1);
    }
        break;
    case 2:
    {
        a1 = QString::fromStdString(timelines.at(0));
        b1 = QString::fromStdString(timelines.at(1));
        timel->addWidget(a, 2, 1);
        timel->addWidget(b, 2, 2);
    }
        break;
    case 3:
    {
        a1 = QString::fromStdString(timelines.at(0));
        b1 = QString::fromStdString(timelines.at(1));
        c1 = QString::fromStdString(timelines.at(2));
        timel->addWidget(a, 2, 1);
        timel->addWidget(b, 2, 2);
        timel->addWidget(c, 2, 3);
    }
        break;
    case 4 :
    {
        a1 = QString::fromStdString(timelines.at(0));
        b1 = QString::fromStdString(timelines.at(1));
        c1 = QString::fromStdString(timelines.at(2));
        d1 = QString::fromStdString(timelines.at(3));
        timel->addWidget(a, 2, 1);
        timel->addWidget(b, 2, 2);
        timel->addWidget(c, 2, 3);
        timel->addWidget(d, 2, 4);
    }
        break;
    case 5:
    {
        a1 = QString::fromStdString(timelines.at(0));
        b1 = QString::fromStdString(timelines.at(1));
        c1 = QString::fromStdString(timelines.at(2));
        d1 = QString::fromStdString(timelines.at(3));
        e1 = QString::fromStdString(timelines.at(4));
        timel->addWidget(a, 2, 1);
        timel->addWidget(b, 2, 2);
        timel->addWidget(c, 2, 3);
        timel->addWidget(d, 2, 4);
        timel->addWidget(e, 2, 5);
    }
        break;
    case 6:
    {
        a1 = QString::fromStdString(timelines.at(0));
        b1 = QString::fromStdString(timelines.at(1));
        c1 = QString::fromStdString(timelines.at(2));
        d1 = QString::fromStdString(timelines.at(3));
        e1 = QString::fromStdString(timelines.at(4));
        f1 = QString::fromStdString(timelines.at(5));
        timel->addWidget(a, 2, 1);
        timel->addWidget(b, 2, 2);
        timel->addWidget(c, 2, 3);
        timel->addWidget(d, 2, 4);
        timel->addWidget(e, 2, 5);
        timel->addWidget(f, 2, 6);
    }
        break;
    case 7:
    {
        a1 = QString::fromStdString(timelines.at(0));
        b1 = QString::fromStdString(timelines.at(1));
        c1 = QString::fromStdString(timelines.at(2));
        d1 = QString::fromStdString(timelines.at(3));
        e1 = QString::fromStdString(timelines.at(4));
        f1 = QString::fromStdString(timelines.at(5));
        g1 = QString::fromStdString(timelines.at(6));
        timel->addWidget(a, 2, 1);
        timel->addWidget(b, 2, 2);
        timel->addWidget(c, 2, 3);
        timel->addWidget(d, 2, 4);
        timel->addWidget(e, 2, 5);
        timel->addWidget(f, 2, 6);
        timel->addWidget(g, 2, 7);
    }
        break;
    case 8:
    {
        a1 = QString::fromStdString(timelines.at(0));
        b1 = QString::fromStdString(timelines.at(1));
        c1 = QString::fromStdString(timelines.at(2));
        d1 = QString::fromStdString(timelines.at(3));
        e1 = QString::fromStdString(timelines.at(4));
        f1 = QString::fromStdString(timelines.at(5));
        g1 = QString::fromStdString(timelines.at(6));
        h1 = QString::fromStdString(timelines.at(7));
        timel->addWidget(a, 2, 1);
        timel->addWidget(b, 2, 2);
        timel->addWidget(c, 2, 3);
        timel->addWidget(d, 2, 4);
        timel->addWidget(e, 2, 5);
        timel->addWidget(f, 2, 6);
        timel->addWidget(g, 2, 7);
        timel->addWidget(h, 2, 8);
    }
        break;
    case 9 :
    {
        a1 = QString::fromStdString(timelines.at(0));
        b1 = QString::fromStdString(timelines.at(1));
        c1 = QString::fromStdString(timelines.at(2));
        d1 = QString::fromStdString(timelines.at(3));
        e1 = QString::fromStdString(timelines.at(4));
        f1 = QString::fromStdString(timelines.at(5));
        g1 = QString::fromStdString(timelines.at(6));
        h1 = QString::fromStdString(timelines.at(7));
        i1 = QString::fromStdString(timelines.at(8));
        timel->addWidget(a, 2, 1);
        timel->addWidget(b, 2, 2);
        timel->addWidget(c, 2, 3);
        timel->addWidget(d, 2, 4);
        timel->addWidget(e, 2, 5);
        timel->addWidget(f, 2, 6);
        timel->addWidget(g, 2, 7);
        timel->addWidget(h, 2, 8);
        timel->addWidget(i, 2, 9);
    }
        break;
    case 10:
    {
        a1 = QString::fromStdString(timelines.at(0));
        b1 = QString::fromStdString(timelines.at(1));
        c1 = QString::fromStdString(timelines.at(2));
        d1 = QString::fromStdString(timelines.at(3));
        e1 = QString::fromStdString(timelines.at(4));
        f1 = QString::fromStdString(timelines.at(5));
        g1 = QString::fromStdString(timelines.at(6));
        h1 = QString::fromStdString(timelines.at(7));
        i1 = QString::fromStdString(timelines.at(8));
        j1 = QString::fromStdString(timelines.at(9));
        timel->addWidget(a, 2, 1);
        timel->addWidget(b, 2, 2);
        timel->addWidget(c, 2, 3);
        timel->addWidget(d, 2, 4);
        timel->addWidget(e, 2, 5);
        timel->addWidget(f, 2, 6);
        timel->addWidget(g, 2, 7);
        timel->addWidget(h, 2, 8);
        timel->addWidget(i, 2, 9);
        timel->addWidget(j, 2, 10);
    }
        break;
    default:
        break;
    }

    fermer = new QPushButton("Fermer");
    timel->addWidget(fermer, 3, 0, 1, x+1);

    setLayout(timel);

    QObject::connect(fermer, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(a, SIGNAL(clicked()), this, SLOT(write1()));
    QObject::connect(b, SIGNAL(clicked()), this, SLOT(write2()));
    QObject::connect(c, SIGNAL(clicked()), this, SLOT(write3()));
    QObject::connect(d, SIGNAL(clicked()), this, SLOT(write4()));
    QObject::connect(e, SIGNAL(clicked()), this, SLOT(write5()));
    QObject::connect(f, SIGNAL(clicked()), this, SLOT(write6()));
    QObject::connect(g, SIGNAL(clicked()), this, SLOT(write7()));
    QObject::connect(h, SIGNAL(clicked()), this, SLOT(write8()));
    QObject::connect(i, SIGNAL(clicked()), this, SLOT(write9()));
    QObject::connect(j, SIGNAL(clicked()), this, SLOT(write10()));
}

void FenCodeGenere::write1(){
    QMessageBox::information(this, "Générer", "Votre fichier à bien été crée!");
    // Création d'un objet QFile
    QFile file("output/fichier.pgn");
    // On ouvre notre fichier en lecture seule et on vérifie l'ouverture
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    // Création d'un objet QTextStream à partir de notre objet QFile
    QTextStream flux(&file);
    // Écriture des différentes lignes dans le fichier
    flux << QString::fromStdString(timelines.at(0)) << Qt::endl;

}

void FenCodeGenere::write2()
{
    QMessageBox::information(this, "Générer", "Votre fichier à bien été crée!");
    // Création d'un objet QFile
    QFile file("output/fichier.pgn");
    // On ouvre notre fichier en lecture seule et on vérifie l'ouverture
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    // Création d'un objet QTextStream à partir de notre objet QFile
    QTextStream flux(&file);
    // Écriture des différentes lignes dans le fichier
    flux << QString::fromStdString(timelines.at(1)) << Qt::endl;
}

void FenCodeGenere::write3()
{
    QMessageBox::information(this, "Générer", "Votre fichier à bien été crée!");
    // Création d'un objet QFile
    QFile file("output/fichier.pgn");
    // On ouvre notre fichier en lecture seule et on vérifie l'ouverture
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    // Création d'un objet QTextStream à partir de notre objet QFile
    QTextStream flux(&file);
    // Écriture des différentes lignes dans le fichier
    flux << QString::fromStdString(timelines.at(2)) << Qt::endl;
}

void FenCodeGenere::write4()
{
    QMessageBox::information(this, "Générer", "Votre fichier à bien été crée!");
    // Création d'un objet QFile
    QFile file("output/fichier.pgn");
    // On ouvre notre fichier en lecture seule et on vérifie l'ouverture
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    // Création d'un objet QTextStream à partir de notre objet QFile
    QTextStream flux(&file);
    // Écriture des différentes lignes dans le fichier
    flux << QString::fromStdString(timelines.at(3)) << Qt::endl;
}

void FenCodeGenere::write5()
{
    QMessageBox::information(this, "Générer", "Votre fichier à bien été crée!");
    // Création d'un objet QFile
    QFile file("output/fichier.pgn");
    // On ouvre notre fichier en lecture seule et on vérifie l'ouverture
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    // Création d'un objet QTextStream à partir de notre objet QFile
    QTextStream flux(&file);
    // Écriture des différentes lignes dans le fichier
    flux << QString::fromStdString(timelines.at(4)) << Qt::endl;
}

void FenCodeGenere::write6()
{
    QMessageBox::information(this, "Générer", "Votre fichier à bien été crée!");
    // Création d'un objet QFile
    QFile file("output/fichier.pgn");
    // On ouvre notre fichier en lecture seule et on vérifie l'ouverture
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    // Création d'un objet QTextStream à partir de notre objet QFile
    QTextStream flux(&file);
    // Écriture des différentes lignes dans le fichier
    flux << QString::fromStdString(timelines.at(5)) << Qt::endl;
}

void FenCodeGenere::write7()
{
    QMessageBox::information(this, "Générer", "Votre fichier à bien été crée!");
    // Création d'un objet QFile
    QFile file("output/fichier.pgn");
    // On ouvre notre fichier en lecture seule et on vérifie l'ouverture
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    // Création d'un objet QTextStream à partir de notre objet QFile
    QTextStream flux(&file);
    // Écriture des différentes lignes dans le fichier
    flux << QString::fromStdString(timelines.at(6)) << Qt::endl;
}

void FenCodeGenere::write8()
{
    QMessageBox::information(this, "Générer", "Votre fichier à bien été crée!");
    // Création d'un objet QFile
    QFile file("output/fichier.pgn");
    // On ouvre notre fichier en lecture seule et on vérifie l'ouverture
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    // Création d'un objet QTextStream à partir de notre objet QFile
    QTextStream flux(&file);
    // Écriture des différentes lignes dans le fichier
    flux << QString::fromStdString(timelines.at(7)) << Qt::endl;
}

void FenCodeGenere::write9()
{
    QMessageBox::information(this, "Générer", "Votre fichier à bien été crée!");
    // Création d'un objet QFile
    QFile file("output/fichier.pgn");
    // On ouvre notre fichier en lecture seule et on vérifie l'ouverture
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    // Création d'un objet QTextStream à partir de notre objet QFile
    QTextStream flux(&file);
    // Écriture des différentes lignes dans le fichier
    flux << QString::fromStdString(timelines.at(8)) << Qt::endl;
}

void FenCodeGenere::write10()
{
    QMessageBox::information(this, "Générer", "Votre fichier à bien été crée!");
    // Création d'un objet QFile
    QFile file("output/fichier.pgn");
    // On ouvre notre fichier en lecture seule et on vérifie l'ouverture
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    // Création d'un objet QTextStream à partir de notre objet QFile
    QTextStream flux(&file);
    // Écriture des différentes lignes dans le fichier
    flux << QString::fromStdString(timelines.at(9)) << Qt::endl;
}
