#include <QtWidgets>
#include "calculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator calculator;

    QPixmap pic(":/penis.png");
    QCursor cur(pic);
    calculator.setCursor(cur);

    calculator.resize(230, 200);
    calculator.show();
    return a.exec();
}
