#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <QtWidgets>

class Calculator : public QWidget
{
    Q_OBJECT
public:
    Calculator(QWidget* pwgt = 0);
    QPushButton* createButton(const QString& str);
    void calculate();

private:
    QStack<QString> calculation;
    QLCDNumber* indicator;
    QString expression;

public slots:
    void slotButtonClicked();
};

#endif // CALCULATOR_H
