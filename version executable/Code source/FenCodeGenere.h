#ifndef HEADER_FENCODEGENERE
#define HEADER_FENCODEGENERE

#include <QDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QtGui>
#include <QScrollBar>
#include <string>


class FenCodeGenere : public QDialog
{

    Q_OBJECT

	public:
        FenCodeGenere(QString &code, QWidget *parent);

    public slots:
        void write1();
        void write2();
        void write3();
        void write4();
        void write5();
        void write6();
        void write7();
        void write8();
        void write9();
        void write10();

	private:
        std::string line;
        QLabel *codeGenere;
        QPushButton *fermer;
        QScrollBar *scroll;
        std::vector<std::string> timelines;
};


#endif
