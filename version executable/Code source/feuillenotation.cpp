#include "FenCodeGenere.h"
#include "feuillenotation.h"
#include <fstream>
#include <string>

FeuilleNotation::FeuilleNotation(QWidget *parent) : QDialog(parent)
{
    setFixedSize(500, 1000);

    setWindowTitle("Correcteur de Notation");

    QMessageBox::warning(this, "Fichier", "Pour remplir le fichier utiliser:\n\"_\" si la case est vide");

    principal = new QGridLayout();
    int k = 1;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 40; j++) {
            if (i == 0 || i == 4) {
                QLabel *x = new QLabel;
                x->setText(QString::number(k));
                k++;
                principal->addWidget(x, j, i);
            }
        }
    }

    //Les line edits...
    int a = 1;
    int b = 0;
    int c = 0;

    s1 = new QLineEdit;
    principal->addWidget(s1, b, a);
    //T[0] = s1;
    b++;
    s2 = new QLineEdit;
    principal->addWidget(s2, b, a);
    //T[2] = s2;
    b++;
    s3 = new QLineEdit;
    principal->addWidget(s3, b, a);
    //T[4] = s3;
    b++;
    s4 = new QLineEdit;
    principal->addWidget(s4, b, a);
    //T[6] = s4;
    b++;
    s5 = new QLineEdit;
    principal->addWidget(s5, b, a);
    //T[8] = s5;
    b++;
    s6 = new QLineEdit;
    principal->addWidget(s6, b, a);
    //T[10] = s6;
    b++;
    s7 = new QLineEdit;
    principal->addWidget(s7, b, a);
    //T[12] = s7;
    b++;
    s8 = new QLineEdit;
    principal->addWidget(s8, b, a);
    //T[14] = s8;
    b++;
    s9 = new QLineEdit;
    principal->addWidget(s9, b, a);
    //T[16] = s9;
    b++;
    s10 = new QLineEdit;
    principal->addWidget(s10, b, a);
    //T[18] = s10;
    b++;

    s11 = new QLineEdit;
    principal->addWidget(s11, b, a);
    //T[20] = s11;
    b++;
    s12 = new QLineEdit;
    principal->addWidget(s12, b, a);
    //T[22] = s12;
    b++;
    s13 = new QLineEdit;
    principal->addWidget(s13, b, a);
    //T[24] = s13;
    b++;
    s14 = new QLineEdit;
    principal->addWidget(s14, b, a);
    //T[26] = s14;
    b++;
    s15 = new QLineEdit;
    principal->addWidget(s15, b, a);
    //T[28] = s15;
    b++;
    s16 = new QLineEdit;
    principal->addWidget(s16, b, a);
    //T[30] = s16;
    b++;
    s17 = new QLineEdit;
    principal->addWidget(s17, b, a);
    //T[32] = s17;
    b++;
    s18 = new QLineEdit;
    principal->addWidget(s18, b, a);
    //T[34] = s18;
    b++;
    s19 = new QLineEdit;
    principal->addWidget(s19, b, a);
    //T[36] = s19;
    b++;
    s20 = new QLineEdit;
    principal->addWidget(s20, b, a);
    //T[38] = s20;
    b++;

    s21 = new QLineEdit;
    principal->addWidget(s21, b, a);
    //T[40] = s21;
    b++;
    s22 = new QLineEdit;
    principal->addWidget(s22, b, a);
    //T[42] = s22;
    b++;
    s23 = new QLineEdit;
    principal->addWidget(s23, b, a);
    //T[44] = s23;
    b++;
    s24 = new QLineEdit;
    principal->addWidget(s24, b, a);
    //T[46] = s24;
    b++;
    s25 = new QLineEdit;
    principal->addWidget(s25, b, a);
    //T[48] = s25;
    b++;
    s26 = new QLineEdit;
    principal->addWidget(s26, b, a);
    //T[50] = s26;
    b++;
    s27 = new QLineEdit;
    principal->addWidget(s27, b, a);
    //T[52] = s27;
    b++;
    s28 = new QLineEdit;
    principal->addWidget(s28, b, a);
    //T[54] = s28;
    b++;
    s29 = new QLineEdit;
    principal->addWidget(s29, b, a);
    //T[56] = s29;
    b++;
    s30 = new QLineEdit;
    principal->addWidget(s30, b, a);
    //T[58] = s30;
    b++;

    s31 = new QLineEdit;
    principal->addWidget(s31, b, a);
    //T[60] = s31;
    b++;
    s32 = new QLineEdit;
    principal->addWidget(s32, b, a);
    //T[62] = s32;
    b++;
    s33 = new QLineEdit;
    principal->addWidget(s33, b, a);
    //T[64] = s33;
    b++;
    s34 = new QLineEdit;
    principal->addWidget(s34, b, a);
    //T[66] = s34;
    b++;
    s35 = new QLineEdit;
    principal->addWidget(s35, b, a);
    //T[68] = s35;
    b++;
    s36 = new QLineEdit;
    principal->addWidget(s36, b, a);
    //T[70] = s36;
    b++;
    s37 = new QLineEdit;
    principal->addWidget(s37, b, a);
    //T[72] = s37;
    b++;
    s38 = new QLineEdit;
    principal->addWidget(s38, b, a);
    //T[74] = s38;
    b++;
    s39 = new QLineEdit;
    principal->addWidget(s39, b, a);
    //T[76] = s39;
    b++;
    s40 = new QLineEdit;
    principal->addWidget(s40, b, a);
    //T[78] = s40;
    b = 0;
    a++;
    c++;

    s41 = new QLineEdit;
    principal->addWidget(s41, b, a);
    //T[1] = s41;
    b++;
    s42 = new QLineEdit;
    principal->addWidget(s42, b, a);
    //T[3] = s42;
    b++;
    s43 = new QLineEdit;
    principal->addWidget(s43, b, a);
    //T[5] = s43;
    b++;
    s44 = new QLineEdit;
    principal->addWidget(s44, b, a);
    //T[7] = s44;
    b++;
    s45 = new QLineEdit;
    principal->addWidget(s45, b, a);
    //T[9] = s45;
    b++;
    s46 = new QLineEdit;
    principal->addWidget(s46, b, a);
    //T[11] = s46;
    b++;
    s47 = new QLineEdit;
    principal->addWidget(s47, b, a);
    //T[13] = s47;
    b++;
    s48 = new QLineEdit;
    principal->addWidget(s48, b, a);
    //T[15] = s48;
    b++;
    s49 = new QLineEdit;
    principal->addWidget(s49, b, a);
    //T[17] = s49;
    b++;
    s50 = new QLineEdit;
    principal->addWidget(s50, b, a);
    //T[19] = s50;
    b++;

    s51 = new QLineEdit;
    principal->addWidget(s51, b, a);
    //T[21] = s51;
    b++;
    s52 = new QLineEdit;
    principal->addWidget(s52, b, a);
    //T[23] = s52;
    b++;
    s53 = new QLineEdit;
    principal->addWidget(s53, b, a);
    //T[25] = s53;
    b++;
    s54 = new QLineEdit;
    principal->addWidget(s54, b, a);
    //T[27] = s54;
    b++;
    s55 = new QLineEdit;
    principal->addWidget(s55, b, a);
    //T[29] = s55;
    b++;
    s56 = new QLineEdit;
    principal->addWidget(s56, b, a);
    //T[31] = s56;
    b++;
    s57 = new QLineEdit;
    principal->addWidget(s57, b, a);
    //T[33] = s57;
    b++;
    s58 = new QLineEdit;
    principal->addWidget(s58, b, a);
    //T[35] = s58;
    b++;
    s59 = new QLineEdit;
    principal->addWidget(s59, b, a);
    //T[37] = s59;
    b++;
    s60 = new QLineEdit;
    principal->addWidget(s60, b, a);
    //T[39] = s60;
    b++;

    s61 = new QLineEdit;
    principal->addWidget(s61, b, a);
    //T[41] = s61;
    b++;
    s62 = new QLineEdit;
    principal->addWidget(s62, b, a);
    //T[43] = s62;
    b++;
    s63 = new QLineEdit;
    principal->addWidget(s63, b, a);
    //T[45] = s63;
    b++;
    s64 = new QLineEdit;
    principal->addWidget(s64, b, a);
    //T[47] = s64;
    b++;
    s65 = new QLineEdit;
    principal->addWidget(s65, b, a);
    //T[49] = s65;
    b++;
    s66 = new QLineEdit;
    principal->addWidget(s66, b, a);
    //T[51] = s66;
    b++;
    s67 = new QLineEdit;
    principal->addWidget(s67, b, a);
    //T[53] = s67;
    b++;
    s68 = new QLineEdit;
    principal->addWidget(s68, b, a);
    //T[55] = s68;
    b++;
    s69 = new QLineEdit;
    principal->addWidget(s69, b, a);
    //T[57] = s69;
    b++;
    s70 = new QLineEdit;
    principal->addWidget(s70, b, a);
    //T[59] = s70;
    b++;

    s71 = new QLineEdit;
    principal->addWidget(s71, b, a);
    //T[61] = s71;
    b++;
    s72 = new QLineEdit;
    principal->addWidget(s72, b, a);
    //T[63] = s72;
    b++;
    s73 = new QLineEdit;
    principal->addWidget(s73, b, a);
    //T[65] = s73;
    b++;
    s74 = new QLineEdit;
    principal->addWidget(s74, b, a);
    //T[67] = s74;
    b++;
    s75 = new QLineEdit;
    principal->addWidget(s75, b, a);
    //T[69] = s75;
    b++;
    s76 = new QLineEdit;
    principal->addWidget(s76, b, a);
    //T[71] = s76;
    b++;
    s77 = new QLineEdit;
    principal->addWidget(s77, b, a);
    //T[73] = s77;
    b++;
    s78 = new QLineEdit;
    principal->addWidget(s78, b, a);
    //T[75] = s78;
    b++;
    s79 = new QLineEdit;
    principal->addWidget(s79, b, a);
    //T[77] = s79;
    b++;
    s80 = new QLineEdit;
    principal->addWidget(s80, b, a);
    //T[79] = s80;
    int d = b;
    int e = b;
    b = 0;
    a++;
    a++;
    a++;
    c = 0;

    t1 = new QLineEdit;
    principal->addWidget(t1, b, a);
    //T[80] = t1;
    d++;
    b++;
    t2 = new QLineEdit;
    principal->addWidget(t2, b, a);
    //T[82] = t2;
    d++;
    b++;
    t3 = new QLineEdit;
    principal->addWidget(t3, b, a);
    //T[84] = t3;
    d++;
    b++;
    t4 = new QLineEdit;
    principal->addWidget(t4, b, a);
    //T[86] = t4;
    d++;
    b++;
    t5 = new QLineEdit;
    principal->addWidget(t5, b, a);
    //T[88] = t5;
    d++;
    b++;
    t6 = new QLineEdit;
    principal->addWidget(t6, b, a);
    //T[90] = t6;
    d++;
    b++;
    t7 = new QLineEdit;
    principal->addWidget(t7, b, a);
    //T[92] = t7;
    d++;
    b++;
    t8 = new QLineEdit;
    principal->addWidget(t8, b, a);
    //T[94] = t8;
    d++;
    b++;
    t9 = new QLineEdit;
    principal->addWidget(t9, b, a);
    //T[96] = t9;
    d++;
    b++;
    t10 = new QLineEdit;
    principal->addWidget(t10, b, a);
    //T[98] = t10;
    d++;
    b++;

    t11 = new QLineEdit;
    principal->addWidget(t11, b, a);
    //T[100] = t11;
    d++;
    b++;
    t12 = new QLineEdit;
    principal->addWidget(t12, b, a);
    //T[102] = t12;
    d++;
    b++;
    t13 = new QLineEdit;
    principal->addWidget(t13, b, a);
    //T[104] = t13;
    d++;
    b++;
    t14 = new QLineEdit;
    principal->addWidget(t14, b, a);
    //T[106] = t14;
    d++;
    b++;
    t15 = new QLineEdit;
    principal->addWidget(t15, b, a);
    //T[108] = t15;
    d++;
    b++;
    t16 = new QLineEdit;
    principal->addWidget(t16, b, a);
    //T[110] = t16;
    d++;
    b++;
    t17 = new QLineEdit;
    principal->addWidget(t17, b, a);
    //T[112] = t17;
    d++;
    b++;
    t18 = new QLineEdit;
    principal->addWidget(t18, b, a);
    //T[114] = t18;
    d++;
    b++;
    t19 = new QLineEdit;
    principal->addWidget(t19, b, a);
    //T[116] = t19;
    d++;
    b++;
    t20 = new QLineEdit;
    principal->addWidget(t20, b, a);
    //T[118] = t20;
    d++;
    b++;

    t21 = new QLineEdit;
    principal->addWidget(t21, b, a);
    //T[120] = t21;
    d++;
    b++;
    t22 = new QLineEdit;
    principal->addWidget(t22, b, a);
    //T[122] = t22;
    d++;
    b++;
    t23 = new QLineEdit;
    principal->addWidget(t23, b, a);
    //T[124] = t23;
    d++;
    b++;
    t24 = new QLineEdit;
    principal->addWidget(t24, b, a);
    //T[126] = t24;
    d++;
    b++;
    t25 = new QLineEdit;
    principal->addWidget(t25, b, a);
    //T[128] = t25;
    d++;
    b++;
    t26 = new QLineEdit;
    principal->addWidget(t26, b, a);
    //T[130] = t26;
    d++;
    b++;
    t27 = new QLineEdit;
    principal->addWidget(t27, b, a);
    //T[132] = t27;
    d++;
    b++;
    t28 = new QLineEdit;
    principal->addWidget(t28, b, a);
    //T[134] = t28;
    d++;
    b++;
    t29 = new QLineEdit;
    principal->addWidget(t29, b, a);
    //T[136] = t29;
    d++;
    b++;
    t30 = new QLineEdit;
    principal->addWidget(t30, b, a);
    //T[138] = t30;
    d++;
    b++;

    t31 = new QLineEdit;
    principal->addWidget(t31, b, a);
    //T[140] = t31;
    d++;
    b++;
    t32 = new QLineEdit;
    principal->addWidget(t32, b, a);
    //T[142] = t32;
    d++;
    b++;
    t33 = new QLineEdit;
    principal->addWidget(t33, b, a);
    //T[144] = t33;
    d++;
    b++;
    t34 = new QLineEdit;
    principal->addWidget(t34, b, a);
    //T[146] = t34;
    d++;
    b++;
    t35 = new QLineEdit;
    principal->addWidget(t35, b, a);
    //T[148] = t35;
    d++;
    b++;
    t36 = new QLineEdit;
    principal->addWidget(t36, b, a);
    //T[150] = t36;
    d++;
    b++;
    t37 = new QLineEdit;
    principal->addWidget(t37, b, a);
    //T[152] = t37;
    d++;
    b++;
    t38 = new QLineEdit;
    principal->addWidget(t38, b, a);
    //T[154] = t38;
    d++;
    b++;
    t39 = new QLineEdit;
    principal->addWidget(t39, b, a);
    //T[156] = t39;
    d++;
    b++;
    t40 = new QLineEdit;
    principal->addWidget(t40, b, a);
    //T[158] = t40;
    b = 0;
    d = e;
    a++;
    c++;

    t41 = new QLineEdit;
    principal->addWidget(t41, b, a);
    //T[81] = t41;
    d++;
    b++;
    t42 = new QLineEdit;
    principal->addWidget(t42, b, a);
    //T[83] = t42;
    d++;
    b++;
    t43 = new QLineEdit;
    principal->addWidget(t43, b, a);
    //T[85] = t43;
    d++;
    b++;
    t44 = new QLineEdit;
    principal->addWidget(t44, b, a);
    //T[87] = t44;
    d++;
    b++;
    t45 = new QLineEdit;
    principal->addWidget(t45, b, a);
    //T[89] = t45;
    d++;
    b++;
    t46 = new QLineEdit;
    principal->addWidget(t46, b, a);
    //T[91] = t46;
    d++;
    b++;
    t47 = new QLineEdit;
    principal->addWidget(t47, b, a);
    //T[93] = t47;
    d++;
    b++;
    t48 = new QLineEdit;
    principal->addWidget(t48, b, a);
    //T[95] = t48;
    d++;
    b++;
    t49 = new QLineEdit;
    principal->addWidget(t49, b, a);
    //T[97] = t49;
    d++;
    b++;
    t50 = new QLineEdit;
    principal->addWidget(t50, b, a);
    //T[99] = t50;
    d++;
    b++;

    t51 = new QLineEdit;
    principal->addWidget(t51, b, a);
    //T[101] = t51;
    d++;
    b++;
    t52 = new QLineEdit;
    principal->addWidget(t52, b, a);
    //T[103] = t52;
    d++;
    b++;
    t53 = new QLineEdit;
    principal->addWidget(t53, b, a);
    //T[105] = t53;
    d++;
    b++;
    t54 = new QLineEdit;
    principal->addWidget(t54, b, a);
    //T[107] = t54;
    d++;
    b++;
    t55 = new QLineEdit;
    principal->addWidget(t55, b, a);
    //T[109] = t55;
    d++;
    b++;
    t56 = new QLineEdit;
    principal->addWidget(t56, b, a);
    //T[111] = t56;
    d++;
    b++;
    t57 = new QLineEdit;
    principal->addWidget(t57, b, a);
    //T[113] = t57;
    d++;
    b++;
    t58 = new QLineEdit;
    principal->addWidget(t58, b, a);
    //T[115] = t58;
    d++;
    b++;
    t59 = new QLineEdit;
    principal->addWidget(t59, b, a);
    //T[117] = t59;
    d++;
    b++;
    t60 = new QLineEdit;
    principal->addWidget(t60, b, a);
    //T[119] = t60;
    d++;
    b++;

    t61 = new QLineEdit;
    principal->addWidget(t61, b, a);
    //T[121] = t61;
    d++;
    b++;
    t62 = new QLineEdit;
    principal->addWidget(t62, b, a);
    //T[123] = t62;
    d++;
    b++;
    t63 = new QLineEdit;
    principal->addWidget(t63, b, a);
    //T[125] = t63;
    d++;
    b++;
    t64 = new QLineEdit;
    principal->addWidget(t64, b, a);
    //T[127] = t64;
    d++;
    b++;
    t65 = new QLineEdit;
    principal->addWidget(t65, b, a);
    //T[129] = t65;
    d++;
    b++;
    t66 = new QLineEdit;
    principal->addWidget(t66, b, a);
    //T[131] = t66;
    d++;
    b++;
    t67 = new QLineEdit;
    principal->addWidget(t67, b, a);
    //T[133] = t67;
    d++;
    b++;
    t68 = new QLineEdit;
    principal->addWidget(t68, b, a);
    //T[135] = t68;
    d++;
    b++;
    t69 = new QLineEdit;
    principal->addWidget(t69, b, a);
    //T[137] = t69;
    d++;
    b++;
    t70 = new QLineEdit;
    principal->addWidget(t70, b, a);
    //T[139] = t70;
    d++;
    b++;

    t71 = new QLineEdit;
    principal->addWidget(t71, b, a);
    //T[141] = t71;
    d++;
    b++;
    t72 = new QLineEdit;
    principal->addWidget(t72, b, a);
    //T[143] = t72;
    d++;
    b++;
    t73 = new QLineEdit;
    principal->addWidget(t73, b, a);
    //T[145] = t73;
    d++;
    b++;
    t74 = new QLineEdit;
    principal->addWidget(t74, b, a);
    //T[147] = t74;
    d++;
    b++;
    t75 = new QLineEdit;
    principal->addWidget(t75, b, a);
    //T[149] = t75;
    d++;
    b++;
    t76 = new QLineEdit;
    principal->addWidget(t76, b, a);
    //T[151] = t76;
    d++;
    b++;
    t77 = new QLineEdit;
    principal->addWidget(t77, b, a);
    //T[153] = t77;
    d++;
    b++;
    t78 = new QLineEdit;
    principal->addWidget(t78, b, a);
    //T[155] = t78;
    d++;
    b++;
    t79 = new QLineEdit;
    principal->addWidget(t79, b, a);
    //T[155] = t79;
    d++;
    b++;
    t80 = new QLineEdit;
    principal->addWidget(t80, b, a);
    //T[159] = t80;


    //Fin des line edits...

    QLabel *x = new QLabel;
    x->setText("Resultat :");
    principal->addWidget(x, 40, 0);

    result = new QLineEdit;
    principal->addWidget(result, 40, 1, 1, 6);

    valide = new QPushButton;
    valide->setText("Envoie");
    principal->addWidget(valide, 41, 1, 1, 7);



    area = new QScrollArea;
    area->setBackgroundRole(QPalette::Dark);
    area->setWidget(s1);

    connect(valide, SIGNAL(clicked()), this, SLOT(ouvrir()));

    setLayout(principal);
}

void FeuilleNotation::ouvrir(){

    QString notation;
    bool stop = false;

    while (!stop){
        if (s1->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "1. ";
            notation += s1->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s41->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s41->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s2->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "2. ";
            notation += s2->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s42->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s42->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s3->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "3. ";
            notation += s3->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s43->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s43->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s4->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "4. ";
            notation += s4->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s44->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s44->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s5->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "5. ";
            notation += s5->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s45->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s45->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s6->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "6. ";
            notation += s6->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s46->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s46->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s7->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "7. ";
            notation += s7->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s47->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s47->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s8->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "8. ";
            notation += s8->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s48->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s48->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s9->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "9. ";
            notation += s9->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s49->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s49->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s10->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "10. ";
            notation += s10->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s50->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s50->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s11->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "11. ";
            notation += s11->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s51->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s51->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s12->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "12. ";
            notation += s12->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s52->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s52->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s13->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "13. ";
            notation += s13->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s53->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s53->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s14->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "14. ";
            notation += s14->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s54->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s54->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s15->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "15. ";
            notation += s15->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s55->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s55->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s16->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "16. ";
            notation += s16->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s56->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s56->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }

        if (s17->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "17. ";
            notation += s17->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s57->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s57->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s18->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "18. ";
            notation += s18->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s58->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s58->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s19->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "19. ";
            notation += s19->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s59->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s59->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s20->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "20. ";
            notation += s20->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s60->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s60->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s21->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "21. ";
            notation += s21->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s61->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s61->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s22->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "22. ";
            notation += s22->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s62->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s62->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s23->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "23. ";
            notation += s23->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s63->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s63->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s24->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "24. ";
            notation += s24->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s64->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s64->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s25->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "25. ";
            notation += s25->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s65->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s65->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s26->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "26. ";
            notation += s26->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s66->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s66->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s27->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "27. ";
            notation += s27->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s67->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s67->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s28->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "28. ";
            notation += s28->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s68->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s68->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s29->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "29. ";
            notation += s29->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s69->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s69->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s30->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "30. ";
            notation += s30->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s70->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s70->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s31->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "31. ";
            notation += s31->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s71->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s71->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s32->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "32. ";
            notation += s32->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s72->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s72->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s33->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "33. ";
            notation += s33->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s73->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s73->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s34->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "34. ";
            notation += s34->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s74->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s74->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s35->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "35. ";
            notation += s35->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s75->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s75->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }

        if (s36->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "36. ";
            notation += s36->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s76->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s76->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s37->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "37. ";
            notation += s37->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s77->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s77->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s38->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "38. ";
            notation += s38->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s78->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s78->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s39->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "39. ";
            notation += s39->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s79->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s79->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (s40->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "40. ";
            notation += s40->text();
            notation += " ";
        }
        else {
            break;
        }
        if (s80->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += s80->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t1->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "41. ";
            notation += t1->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t41->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t41->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t2->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "42. ";
            notation += t2->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t42->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t42->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t3->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "43. ";
            notation += t3->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t43->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t43->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t4->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "44. ";
            notation += t4->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t44->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t44->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t5->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "45. ";
            notation += t5->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t45->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t45->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t6->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "46. ";
            notation += t6->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t46->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t46->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t7->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "47. ";
            notation += t7->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t47->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t47->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t8->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "48. ";
            notation += t8->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t48->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t48->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t9->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "49. ";
            notation += t9->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t49->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t49->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t10->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "50. ";
            notation += t10->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t50->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t50->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t11->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "51. ";
            notation += t11->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t51->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t51->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t12->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "52. ";
            notation += t12->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t52->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t52->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t13->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "53. ";
            notation += t13->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t53->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t53->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t14->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "54. ";
            notation += t14->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t54->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t54->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t15->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "55. ";
            notation += t15->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t55->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t55->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t16->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "56. ";
            notation += t16->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t56->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t56->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t17->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "57. ";
            notation += t17->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t57->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t57->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t18->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "58. ";
            notation += t18->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t58->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t58->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t19->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "59. ";
            notation += t19->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t59->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t59->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t20->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "60. ";
            notation += t20->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t60->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t60->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t21->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "61. ";
            notation += t21->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t61->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t61->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t22->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "62. ";
            notation += t22->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t62->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t62->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t23->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "63. ";
            notation += t23->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t63->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t63->text();
            notation += "\n";
        }
        else {
            notation += "\n";
        }


        if (t24->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "64. ";
            notation += t24->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t64->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t64->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t25->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "65. ";
            notation += t25->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t65->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t65->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t26->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "66. ";
            notation += t26->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t66->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t66->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t27->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "67. ";
            notation += t27->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t67->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t67->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t28->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "68. ";
            notation += t28->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t68->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t68->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t29->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "69. ";
            notation += t29->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t69->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t69->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t30->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "70. ";
            notation += t30->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t70->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t70->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t31->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "71. ";
            notation += t31->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t71->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t71->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t32->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "72. ";
            notation += t32->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t72->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t72->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t33->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "73. ";
            notation += t33->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t73->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t73->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t34->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "74. ";
            notation += t34->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t74->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t74->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t35->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "75. ";
            notation += t35->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t75->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t75->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t36->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "76. ";
            notation += t36->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t76->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t76->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t37->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "77. ";
            notation += t37->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t77->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t77->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t38->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "78. ";
            notation += t38->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t78->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t78->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t39->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "79. ";
            notation += t39->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t79->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t79->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }


        if (t40->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += "80. ";
            notation += t40->text();
            notation += " ";
        }
        else {
            break;
        }
        if (t80->text().isEmpty()) {
            stop = true;
        }
        if (!stop) {
            notation += t80->text();
            notation += "\n";
        }
        else {
            notation += "\n";
            break;
        }
    }


    notation += result->text();

    system("mkdir input");
    // Création d'un objet QFile
    QFile file("./input/fichier.pgn");
    // On ouvre notre fichier en lecture seule et on vérifie l'ouverture
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    // Création d'un objet QTextStream à partir de notre objet QFile
    QTextStream flux(&file);
    // Écriture des différentes lignes dans le fichier
    flux << notation << Qt::endl;

    QString fichier = "./input/fichier.pgn";

    FenCodeGenere *fenetreCode = new FenCodeGenere(fichier, this);
    fenetreCode->exec();

}
