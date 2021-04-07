#include "calculator.h"
#include "ui_calculator.h"
#include <QRegularExpression>
#include <math.h>


double calcVal = 0.0;
bool divFLAG = false;
bool multFLAG = false;
bool addFLAG = false;
bool subFLAG = false;
bool powFLAG = false;


Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i=0; i<10; ++i){
        QString butName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    QString Operations[] = {"Divide", "Multiply", "Add", "Subtract", "Power"};
    QPushButton *opButton[5];
    for (int i=0; i<5; ++i){
        opButton[i] = Calculator::findChild<QPushButton *>(Operations[i]);
        connect(opButton[i], SIGNAL(released()), this, SLOT(MathButtonPressed()));
    }

    QString Others[] = {"ChangeSign", "Sqrt", "Clear", "Equals", "Dot"};
    QPushButton *othButton[5];
    for (int i=0; i<5; ++i){
        othButton[i] = Calculator::findChild<QPushButton *>(Others[i]);
        if (Others[i] == "ChangeSign") connect(othButton[i], SIGNAL(released()), this, SLOT(ChangeNumberSign()));
        else if (Others[i] == "Sqrt") connect(othButton[i], SIGNAL(released()), this, SLOT(DoSqrt()));
        else if (Others[i] == "Clear") connect(othButton[i], SIGNAL(released()), this, SLOT(DoClear()));
        else if (Others[i] == "Equals") connect(othButton[i], SIGNAL(released()), this, SLOT(EqualButton()));
        else connect(othButton[i], SIGNAL(released()), this, SLOT(CalcDot()));
    }

}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if((displayVal.toDouble()==0) || (displayVal.toDouble()==0.0)){
        ui->Display->setText(butVal);
    }
    else{
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
}

void Calculator::MathButtonPressed(){
    divFLAG = false;
    multFLAG = false;
    addFLAG = false;
    subFLAG = false;
    powFLAG = false;

    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal,"/", Qt::CaseInsensitive)==0){
        divFLAG = true;
        ui->Display->setText("/");
    }
    else if(QString::compare(butVal,"*", Qt::CaseInsensitive)==0){
        multFLAG = true;
        ui->Display->setText("*");
    }
    else if(QString::compare(butVal,"+", Qt::CaseInsensitive)==0){
        addFLAG = true;
        ui->Display->setText("+");
    }
    else if(QString::compare(butVal,"-", Qt::CaseInsensitive)==0){
        subFLAG = true;
        ui->Display->setText("-");
    }
    else{
        powFLAG = true;
        ui->Display->setText("^");
    }
}

void Calculator::EqualButton(){
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(addFLAG || subFLAG || multFLAG || divFLAG || powFLAG){
        if(addFLAG){
            solution = calcVal + dblDisplayVal;
        }
        else if(subFLAG){
            solution = calcVal - dblDisplayVal;
        }
        else if(multFLAG){
            solution = calcVal * dblDisplayVal;
        }
        else if(divFLAG){
            solution = calcVal / dblDisplayVal;
        }
        else{
            solution = pow(calcVal,dblDisplayVal);
        }
    }

    ui->Display->setText(QString::number(solution));
}

void Calculator::ChangeNumberSign(){
    QString displayVal = ui->Display->text();
    double dblDisplayValSign = -1 * displayVal.toDouble();
    ui->Display->setText(QString::number(dblDisplayValSign));
}

void Calculator::DoSqrt(){
    QString displayVal = ui->Display->text();
    double dblDisplayValSign = sqrt(displayVal.toDouble());
    ui->Display->setText(QString::number(dblDisplayValSign));
}

void Calculator::DoClear(){
    ui->Display->setText(QString::number(0.0));
}

void Calculator::CalcDot(){
    ui->Display->setText(ui->Display->text() + ".");
}
