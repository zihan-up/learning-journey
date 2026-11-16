#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void onDigitClicked();      // 数字按钮点击
    void onOperatorClicked();   // 运算符（+ - * /）点击
    void onEqualClicked();      // 等于 (=) 点击
    void onClearClicked();      // 清除 (C) 点击

private:
    Ui::Calculator *ui;

    QString m_currentInput;       // 当前输入的数字
    QString m_pendingOperator;    // 缓存的运算符（+ - * /）
    double m_result;              // 存储计算结果
    bool m_waitingForOperand;     // 是否等待新的操作数
};

#endif // CALCULATOR_H
