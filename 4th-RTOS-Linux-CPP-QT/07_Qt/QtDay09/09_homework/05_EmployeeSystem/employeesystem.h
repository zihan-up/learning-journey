#ifndef EMPLOYEESYSTEM_H
#define EMPLOYEESYSTEM_H

#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QInputDialog>

class EmployeeSystem : public QWidget
{
    Q_OBJECT
public:
    EmployeeSystem(QWidget *parent = nullptr) ;

    ~EmployeeSystem();

private:
    void setWidgetLayout();
    void connectSignals();
    void addTestData();

private slots:
    void addEmployee();
    void removeEmployee();
    void filterEmployees(const QString &text);

private:
    QListWidget *m_employeeList;
    QLineEdit *m_searchEdit;
    QPushButton *m_addButton;
    QPushButton *m_removeButton;
};
#endif // EMPLOYEESYSTEM_H
