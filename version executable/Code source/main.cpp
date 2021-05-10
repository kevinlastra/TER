#include <QApplication>
#include "FenPrincipale.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    FenPrincipale fenetre;
    fenetre.setWindowTitle("Correcteur de Notation");
    fenetre.show();

    return app.exec();
}
