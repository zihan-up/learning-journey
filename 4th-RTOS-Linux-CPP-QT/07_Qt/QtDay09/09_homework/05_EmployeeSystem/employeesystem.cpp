#include "employeesystem.h"

EmployeeSystem::EmployeeSystem(QWidget *parent)

    : QWidget(parent)
{
    setWindowTitle("员工管理系统");
    resize(600, 500);

    //进行部件布局
    setWidgetLayout();
    connectSignals();
    addTestData();
}

EmployeeSystem::~EmployeeSystem()
{

}

//进行部件布局
void EmployeeSystem::setWidgetLayout()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    m_searchEdit = new QLineEdit;
    m_searchEdit->setPlaceholderText("搜索员工...");

    m_employeeList = new QListWidget;

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    m_addButton = new QPushButton("添加员工");
    m_removeButton = new QPushButton("删除选中");

    buttonLayout->addWidget(m_addButton);
    buttonLayout->addWidget(m_removeButton);

    mainLayout->addWidget(m_searchEdit);
    mainLayout->addWidget(m_employeeList);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

void EmployeeSystem::connectSignals()
{
    connect(m_addButton, &QPushButton::clicked, this, &EmployeeSystem::addEmployee);
    connect(m_removeButton, &QPushButton::clicked, this, &EmployeeSystem::removeEmployee);
    connect(m_searchEdit, &QLineEdit::textChanged, this, &EmployeeSystem::filterEmployees);
}

void EmployeeSystem::addTestData()
{
    m_employeeList->addItems({"张三", "李四", "王五", "赵六", "钱七", "孙八"});
}


void EmployeeSystem::addEmployee()
{
    bool ok;
    QString name = QInputDialog::getText(this, "添加员工", "请输入员工姓名:",
                                         QLineEdit::Normal, "", &ok);
    if (ok && !name.isEmpty())
    {
        m_employeeList->addItem(name);
    }
}

void EmployeeSystem::removeEmployee()
{
    delete m_employeeList->takeItem(m_employeeList->currentRow());
}

void EmployeeSystem::filterEmployees(const QString &text)
{
    //m_employeeList->count()获取列表的项总数。
    for (int i = 0; i < m_employeeList->count(); ++i)
    {
        QListWidgetItem *item = m_employeeList->item(i);
        //检查文本是否包含text，忽略大小写
        //控制项的显示/隐藏状态
        item->setHidden(!item->text().contains(text, Qt::CaseInsensitive));
    }
}
