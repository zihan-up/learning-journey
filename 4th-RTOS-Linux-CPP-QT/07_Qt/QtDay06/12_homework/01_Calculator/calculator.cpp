#include "calculator.h"
#include "ui_calculator.h"
#include <QDebug>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Calculator)
    , m_currentInput("")
    , m_pendingOperator("")
    , m_result(0.0)
    , m_waitingForOperand(false)
{
    ui->setupUi(this);

    // 信号槽连接：数字按钮 0-9
    for (int i = 0; i < 10; ++i)
    {
        //UI按钮命名：Button0, Button1...
        QString buttonName = "Button" + QString::number(i);
        QPushButton *digitButton = findChild<QPushButton *>(buttonName);
        connect(digitButton, &QPushButton::clicked, this, &Calculator::onDigitClicked);
    }

    // 信号槽连接：运算符（+ - * /）
    connect(ui->ButtonPlus, &QPushButton::clicked, this, &Calculator::onOperatorClicked);
    connect(ui->ButtonMinus, &QPushButton::clicked, this, &Calculator::onOperatorClicked);
    connect(ui->ButtonMultiply, &QPushButton::clicked, this, &Calculator::onOperatorClicked);
    connect(ui->ButtonDivide, &QPushButton::clicked, this, &Calculator::onOperatorClicked);

    // 信号槽连接：= 和 C
    connect(ui->ButtonEqual, &QPushButton::clicked, this, &Calculator::onEqualClicked);
    connect(ui->ButtonClear, &QPushButton::clicked, this, &Calculator::onClearClicked);

    ui->display->setText("0");  // 初始化显示0
}

Calculator::~Calculator()
{
    delete ui;
}

// 数字按钮点击
void Calculator::onDigitClicked()
{
    //sender用于在槽函数内部获取触发当前槽执行的信号发送者对象
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    QString digit = clickedButton->text();

    if (m_waitingForOperand)
    {
        m_currentInput = digit;
        m_waitingForOperand = false;
    }
    else
    {
        m_currentInput += digit;
    }

    ui->display->setText(m_currentInput);
}

// 运算符（+ - * /）点击
void Calculator::onOperatorClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    QString newOperator = clickedButton->text();

    // 计算之前的运算
    double operand = m_currentInput.toDouble();

    if (!m_pendingOperator.isEmpty())
    {
        if (m_pendingOperator == "+")
        {
            m_result += operand;
        }
        else if (m_pendingOperator == "-")
        {
            m_result -= operand;
        }
        else if (m_pendingOperator == "*")
        {
            m_result *= operand;
        }
        else if (m_pendingOperator == "/")
        {
            if (operand != 0.0)
            {
                m_result /= operand;
            }
            else
            {
                ui->display->setText("Error");
                return;
            }
        }
    }
    else
    {
        m_result = operand;
    }

    m_pendingOperator = newOperator;
    m_waitingForOperand = true;
    ui->display->setText(QString::number(m_result));
}

// 等于 (=) 点击
void Calculator::onEqualClicked()
{
    if (!m_pendingOperator.isEmpty())
    {
        double operand = m_currentInput.toDouble();

        // 执行最后的运算
        if(m_pendingOperator == "+")
        {
            m_result += operand;
        }
        else if(m_pendingOperator == "-")
        {
            m_result -= operand;
        }
        else if(m_pendingOperator == "*")
        {
            m_result *= operand;
        }
        else if(m_pendingOperator == "/")
        {
            if (operand != 0.0)
            {
                m_result /= operand;
            } else
            {
                ui->display->setText("Error");
                m_pendingOperator.clear();
                return;
            }
        }

        m_currentInput = QString::number(m_result);
        m_pendingOperator.clear();
        m_waitingForOperand = true;
        ui->display->setText(m_currentInput);
    }
}

//清除点击
void Calculator::onClearClicked()
{
    m_currentInput = "0";
    m_pendingOperator.clear();
    m_result = 0.0;
    m_waitingForOperand = false;
    ui->display->setText(m_currentInput);
}
