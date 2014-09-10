#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QListWidget>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QInputDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QDebug>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTextBrowser>

#include "fileset.h"
#include "serach.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    fileset file;

    QTextEdit *label[100];
    QTableWidget *QTW[100];

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);


private:
    Ui::Widget *ui;
    bool isright(QString str);

};

#endif // WIDGET_H
