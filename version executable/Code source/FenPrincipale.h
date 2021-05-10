#ifndef HEADER_FENPRINCIPALE
#define HEADER_FENPRINCIPALE

#include <QCheckBox>
#include <QDateEdit>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QTextEdit>
#include <QtGui>


class FenPrincipale : public QWidget
{
    Q_OBJECT

    public:
    FenPrincipale();

    public slots:
    void ouvrirFichier();
    void ecrireFichier();

    private:
    QPushButton *m_ouvrirFichier;
    QPushButton *m_manuel;
    QLabel *m_title;
};

#endif
