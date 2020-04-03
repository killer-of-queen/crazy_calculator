#include "calculator.h"

Calculator::Calculator(QWidget* pwgt) : QWidget(pwgt)
{

    indicator = new QLCDNumber(12);

    indicator->setSegmentStyle(QLCDNumber::Flat);

    QPalette palette = indicator->palette();

    palette.setColor(palette.WindowText, QColor(255, 255, 255));
    palette.setColor(palette.Background, QColor(65, 105, 225));
    indicator->setPalette(palette);
    indicator->setAutoFillBackground(true);

    indicator->setFixedHeight(80);

    QChar Buttons[4][4] {
                    {'1', '2', '3', '+'},
                    {'4', '5', '6', '-'},
                    {'7', '8', '9', '/'},
                    {'0', '.', '=', '*'}
    };

    QGridLayout* grid = new QGridLayout;
    grid->addWidget(indicator, 0, 0, 1, 4);
    grid->addWidget(createButton("CE"), 1, 0);
    grid->addWidget(createButton("←"), 1, 1);
    grid->addWidget(createButton("("), 1, 2);
    grid->addWidget(createButton(")"), 1, 3);
    grid->setSpacing(20);
    grid->setContentsMargins(25, 25, 25, 25);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            grid->addWidget(createButton(Buttons[i][j]), i + 2, j);
        }
    }
    grid->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(grid);
}

QPushButton* Calculator::createButton(const QString &str) {
    QPushButton* button = new QPushButton(str);
    button->setFixedSize(100, 50);
    connect(button, SIGNAL(clicked()), SLOT(slotButtonClicked()));
    return button;
}

void Calculator::slotButtonClicked() {
    QString str = ((QPushButton*)sender()) -> text();

    if (str == "CE") {
        expression.clear();
        calculation.clear();
        indicator->display("0");
        return;
    }

    QRegExp number("[1-9]");
    if(number.exactMatch(str)) {
        expression += str;
        indicator->display(expression);
        return;
    }

    if (str == "0" && expression.size() != 0) {
       expression += str;
       indicator->display(expression);
       return;
    }

    QRegExp operation("[\\.,\\/,\\+,\\-,\\*]");
    if(operation.exactMatch(str)) {
        if (calculation.size() == 0 && expression.size() == 0) {
            calculation.push_back("0");
        } else {
            calculation.push_back(expression);
            expression.clear();
        }
        if (calculation.size() > 2) {
            calculate();
        } else if (calculation.size() == 2) {
            calculation.pop();
        }
        calculation.push_back(str);
        return;
    }

    if (str == ".") {
        if (expression.size() == 0) {
        expression += "0.";
        indicator->display(expression);
        return;
       }

       QRegExp dot("\\.");
       if (dot.indexIn(expression) == -1) {
        expression += str;
        indicator->display(expression);
        return;
       }

       return;
    }

    if (str == "=") {
        if (expression.size() > 0) {
            calculation.push(expression);
            expression.clear();
        }

        if (calculation.size() > 2) {
            calculate();
            return;
        } else if (calculation.size() == 2) {
            calculation.pop();
        } else if (calculation.size() == 0) {
            calculation.push("0");
        }

        indicator->display(calculation.at(0));
        return;
    }
}

void Calculator::calculate() {
    qreal operand2 = calculation.pop().toDouble();
    QString operation = calculation.pop();
    qreal operand1 = calculation.pop().toDouble();
    QString result;
    calculation.clear();

    if (operation == "+") {
        result = QString::number((operand1 + operand2), 'g', 10);
    }

    if (operation == "-") {
        result = QString::number((operand1 - operand2), 'g', 10);
    }

    if (operation == "*") {
        result = QString::number((operand1 * operand2), 'g', 10);
    }

    if (operation == "/") {
        result = QString::number((operand1 / operand2), 'g', 10);
    }

    calculation.push_back(result);
    indicator->display(result);
    return;
}
