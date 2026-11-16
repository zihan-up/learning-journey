#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPushButton button("OFF");
    button.resize(400, 300);

    button.setCheckable(true);  //让按钮支持 toggled

    QObject::connect(&button, &QPushButton::toggled, [&](bool checked) {
        button.setText(checked ? "ON" : "OFF");
        button.setStyleSheet(checked ? "background-color: green" : "background-color: red");
    });

    button.show();
    return app.exec();
}
