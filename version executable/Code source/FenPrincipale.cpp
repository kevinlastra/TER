#include "FenPrincipale.h"
#include "FenCodeGenere.h"
#include "feuillenotation.h"

#include <QFormLayout>
#include <QFileDialog>
#include <QMessageBox>

FenPrincipale::FenPrincipale()
{

    setWindowTitle("Correcteur de Notation");

    QVBoxLayout *principal = new QVBoxLayout;
    setLayout(principal);



    setFixedSize(300, 100);

    m_title = new QLabel();
    m_title->setText("Correcteur de notation");
    m_title->setAlignment(Qt::AlignCenter);
    principal->addWidget(m_title);

    m_ouvrirFichier = new QPushButton("A partir d'un fichier PGN");
    m_ouvrirFichier->move(40, 50);
    principal->addWidget(m_ouvrirFichier);

    QObject::connect(m_ouvrirFichier, SIGNAL(clicked()), this, SLOT(ouvrirFichier()));

    m_manuel = new QPushButton("Rentrer manuellement la grille de notation");
    m_manuel->move(40, 50);
    principal->addWidget(m_manuel);

    QObject::connect(m_manuel, SIGNAL(clicked()), this, SLOT(ecrireFichier()));



}


void FenPrincipale::ouvrirFichier()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString());

    if (!fichier.isEmpty()){
        FenCodeGenere *fenetreCode = new FenCodeGenere(fichier, this);
        fenetreCode->exec();
    }
    else {
        QMessageBox::critical(this, "Erreur", "Vous n'avez pas choisi de fichier!");
    }

    // On cr?e puis affiche la fen?tre qui affichera le code g?n?r?, qu'on lui envoie en param?tre
}

void FenPrincipale::ecrireFichier()
{
    FeuilleNotation *feuille = new FeuilleNotation(this);
    feuille->exec();
}
