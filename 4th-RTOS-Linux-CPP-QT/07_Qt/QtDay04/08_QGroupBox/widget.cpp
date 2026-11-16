#include "widget.h"

#include <QGroupBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QGridLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 480);

    //------第一个分组框，里面都是单选按钮-----
    QGroupBox *rBox1 = new QGroupBox("性别");

    QRadioButton *man = new QRadioButton("男");
    QRadioButton *woman = new QRadioButton("女");

    QVBoxLayout *vlayout = new QVBoxLayout;

    vlayout->addWidget(man);
    vlayout->addWidget(woman);

    rBox1->setLayout(vlayout);

    //------第二个分组框，里面都是复选按钮-----
    QGroupBox *rBox2 = new QGroupBox("复选按钮组");

    QCheckBox *cbox1 = new QCheckBox("QCheckBox1");
    QCheckBox *cbox2 = new QCheckBox("QCheckBox2");
    QCheckBox *cbox3 = new QCheckBox("QCheckBox3");

    QVBoxLayout *vlayout2 = new QVBoxLayout;

    vlayout2->addWidget(cbox1);
    vlayout2->addWidget(cbox2);
    vlayout2->addWidget(cbox3);

    rBox2->setLayout(vlayout2);

    //------第三个分组框，里面既有单选按钮也有复选按钮-----
    QGroupBox *rBox3 = new QGroupBox("组合按钮组");

    QRadioButton *radio11 = new QRadioButton("QRadioButton11");
    QRadioButton *radio22 = new QRadioButton("QRadioButton22");
    QCheckBox *cbox11 = new QCheckBox("QCheckBox11");
    QCheckBox *cbox22 = new QCheckBox("QCheckBox22");

    QVBoxLayout *vlayout3 = new QVBoxLayout;

    vlayout3->addWidget(radio11);
    vlayout3->addWidget(radio22);
    vlayout3->addWidget(cbox11);
    vlayout3->addWidget(cbox22);

    rBox3->setLayout(vlayout3);

    //----最后对三个分组框进行网格布局
    QGridLayout *glayout = new QGridLayout;
    glayout->addWidget(rBox1, 0, 0, 1, 1);
    glayout->addWidget(rBox2, 0, 2, 1, 1);
    glayout->addWidget(rBox3, 1, 1, 1, 1);

    setLayout(glayout);

    woman->setChecked(true);
    cbox2->setTristate(true);
    cbox2->setCheckState(Qt::PartiallyChecked);
    radio11->setChecked(true);
    cbox22->setChecked(true);
    //cbox22->setCheckState(Qt::Checked);
}

Widget::~Widget()
{
}

