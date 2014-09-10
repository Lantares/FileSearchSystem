#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);

    setWindowTitle("FES3.0");
    int V = 100;
    ui->listWidget->setMaximumHeight(100);



    ui->stackedWidget->setFrameStyle(1);
    QWidget *PageWidget[V];
    for(int i = 0; i < V; i++)
    {
        PageWidget[i] = new QWidget;
        label[i] = new QTextEdit(PageWidget[i]);
        label[i]->setMinimumWidth(281);
        label[i]->setMinimumHeight(231);
        label[i]->setReadOnly(1);
        ui->stackedWidget->addWidget(PageWidget[i]);
    }

    QWidget *PageWidget_2[V];
    for(int i = 0; i < V; i++)
    {
        PageWidget_2[i] = new QWidget;
        QTW[i] = new QTableWidget(PageWidget_2[i]);
        QTW[i]->setMaximumWidth(201);
        QTW[i]->setMinimumHeight(231);
        QTW[i]->setColumnCount(2);
        QStringList headers;
        headers << tr( "單詞" ) << tr( "數量" ) ;
        QTW[i]->setHorizontalHeaderLabels( headers );
        ui->stackedWidget_2->addWidget(PageWidget_2[i]);


    }


    QObject::connect(ui->listWidget, SIGNAL(currentRowChanged(int)), ui->stackedWidget, SLOT(setCurrentIndex(int)));
    QObject::connect(ui->listWidget, SIGNAL(currentRowChanged(int)), ui->stackedWidget_2, SLOT(setCurrentIndex(int)));


}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    file.clear();
    QFileDialog* openFilePath = new QFileDialog( this, " 请选择文件夹","file");     //打开一个目录选择对话框
    openFilePath->setFileMode( QFileDialog::DirectoryOnly );
    openFilePath->setDirectory("C:");
    if ( openFilePath->exec() == QDialog::Accepted )
    {

       ui->label->setText(openFilePath->selectedFiles()[0]);
       ui->lineEdit->setReadOnly(0);
        file.seturl(openFilePath->selectedFiles()[0].toStdString());
        file.setTIF();
        int num = file.getfilenum();
        ui->tableWidget->setRowCount(num);
        for(int i = 0; i < num; i++)
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(file.getfilename(i).data()));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(file.geturl(i).data()));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(file.getAllnum(i), 10)));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(file.getwordnum(i), 10)));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(file.gettime(i).data()));

        }
        ui->tableWidget->resizeColumnsToContents();
    }
    delete openFilePath;

}

void Widget::on_lineEdit_textChanged(const QString &arg1)
{
    serach e;
    if(isright(arg1))
    {
        vector<string> s = e.exp(file.getfileset(), arg1.toStdString());
        ui->listWidget->clear();
        for(unsigned int i = 0; i < s.size(); i++)
        {
            ui->listWidget->addItem(new QListWidgetItem(QString::fromStdString(s[i])));
            label[i]->clear();
            QString BUFs = QString::fromStdString(file.getfile(s[i]));

            for(unsigned int j = 0; j < e.getkeyword().size(); j++)
            {
                if(e.getkeyword()[j] == ",")
                    BUFs.replace(QRegExp(QString::fromStdString(e.getkeyword()[j])), "<span style=\"background-color:#FFFF00;\">" + QString::fromStdString(e.getkeyword()[j]) + "</span>");
                if(e.getkeyword()[j] == ".")
                {
                    BUFs.replace(QRegExp("\\."), "<span style=\"background-color:#FFFF00;\">" + QString::fromStdString(e.getkeyword()[j]) + "</span>");
                    continue;
                }
                if(e.getkeyword()[j] == "c++")
                    BUFs.replace(QRegExp("c\\+\\+"), "<span style=\"background-color:#FFFF00;\">" + QString::fromStdString(e.getkeyword()[j]) + "</span>");
                if(e.getkeyword()[j] == "(" || e.getkeyword()[j] == ")" )
                    BUFs.replace(QRegExp("\\" + QString::fromStdString(e.getkeyword()[j])), "<span style=\"background-color:#FFFF00;\">" + QString::fromStdString(e.getkeyword()[j]) + "</span>");
                BUFs.replace(QRegExp(" " + QString::fromStdString(e.getkeyword()[j]) + " "), " <span style=\"background-color:#FFFF00;\">" + QString::fromStdString(e.getkeyword()[j]) + "</span> ");
                BUFs.replace(QRegExp(" " + QString::fromStdString(e.getkeyword()[j]) + ","), " <span style=\"background-color:#FFFF00;\">" + QString::fromStdString(e.getkeyword()[j]) + "</span>,");
                BUFs.replace(QRegExp("\n" + QString::fromStdString(e.getkeyword()[j]) + ","), "\n<span style=\"background-color:#FFFF00;\">" + QString::fromStdString(e.getkeyword()[j]) + "</span>,");
                BUFs.replace(QRegExp("\"" + QString::fromStdString(e.getkeyword()[j]) + " "), "\"<span style=\"background-color:#FFFF00;\">" + QString::fromStdString(e.getkeyword()[j]) + "</span> ");
                BUFs.replace(QRegExp(" " + QString::fromStdString(e.getkeyword()[j]) + "\""), " <span style=\"background-color:#FFFF00;\">" + QString::fromStdString(e.getkeyword()[j]) + "</span>\"");
                BUFs.replace(QRegExp("\"" + QString::fromStdString(e.getkeyword()[j]) + "\""), "\"<span style=\"background-color:#FFFF00;\">" + QString::fromStdString(e.getkeyword()[j]) + "</span>\"");
                BUFs.replace(QRegExp("\\(" + QString::fromStdString(e.getkeyword()[j]) + "\\)"), "(<span style=\"background-color:#FFFF00;\">" + QString::fromStdString(e.getkeyword()[j]) + "</span>)");
                BUFs.replace(QRegExp("^" + QString::fromStdString(e.getkeyword()[j]) + " "), "<span style=\"background-color:#FFFF00;\">" + QString::fromStdString(e.getkeyword()[j]) + "</span> ");
                BUFs.replace(QRegExp(" " + QString::fromStdString(e.getkeyword()[j]) + "$"), " <span style=\"background-color:#FFFF00;\">" + QString::fromStdString(e.getkeyword()[j]) + "</span>");
                BUFs.replace(QRegExp(" " + QString::fromStdString(e.getkeyword()[j]) + "\n"), " <span style=\"background-color:#FFFF00;\">" + QString::fromStdString(e.getkeyword()[j]) + "</span>\n");
                BUFs.replace(QRegExp("\n" + QString::fromStdString(e.getkeyword()[j]) + " "), "\n<span style=\"background-color:#FFFF00;\">" + QString::fromStdString(e.getkeyword()[j]) + "</span> ");
                BUFs.replace(QRegExp(" " + QString::fromStdString(e.getkeyword()[j]) + "\\."), " <span style=\"background-color:#FFFF00;\">" + QString::fromStdString(e.getkeyword()[j]) + "</span>.");
                BUFs.replace(QRegExp("," + QString::fromStdString(e.getkeyword()[j]) + " "), ",<span style=\"background-color:#FFFF00;\">" + QString::fromStdString(e.getkeyword()[j]) + "</span> ");
                BUFs.replace(QRegExp("," + QString::fromStdString(e.getkeyword()[j]) + ","), ",<span style=\"background-color:#FFFF00;\">" + QString::fromStdString(e.getkeyword()[j]) + "</span>,");
                BUFs.replace(QRegExp("," + QString::fromStdString(e.getkeyword()[j]) + "\\."), ",<span style=\"background-color:#FFFF00;\">" + QString::fromStdString(e.getkeyword()[j]) + "</span>.");
                BUFs.replace(QRegExp("\\." + QString::fromStdString(e.getkeyword()[j]) + " "), ".<span style=\"background-color:#FFFF00;\">" + QString::fromStdString(e.getkeyword()[j]) + "</span> ");
                BUFs.replace(QRegExp("\\." + QString::fromStdString(e.getkeyword()[j]) + ","), ".<span style=\"background-color:#FFFF00;\">" + QString::fromStdString(e.getkeyword()[j]) + "</span>,");
                BUFs.replace(QRegExp("\\." + QString::fromStdString(e.getkeyword()[j]) + "\\."), ".<span style=\"background-color:#FFFF00;\">" + QString::fromStdString(e.getkeyword()[j]) + "</span>.");
                 BUFs.replace(QRegExp(" " + QString::fromStdString(e.getkeyword()[j]) + "\\)"), " <span style=\"background-color:#FFFF00;\">" + QString::fromStdString(e.getkeyword()[j]) + "</span>)");
                  BUFs.replace(QRegExp("\\(" + QString::fromStdString(e.getkeyword()[j]) + " "), "(<span style=\"background-color:#FFFF00;\">" + QString::fromStdString(e.getkeyword()[j]) + "</span> ");
            }

            label[i]->setHtml(BUFs);

            /*
            for(unsigned int j = 0; j < e.getkeyword().size(); j++)
            {
                    QString searchString = QString::fromStdString(e.getkeyword()[j]);
                    QTextDocument *document = label[i]->document();

                    QTextCursor highlightCursor(document);
                    QTextCursor cursor(document);

                    cursor.beginEditBlock();

                    QTextCharFormat plainFormat(highlightCursor.charFormat());
                    QTextCharFormat colorFormat = plainFormat;
                    colorFormat.setForeground(Qt::red);

                    while (!highlightCursor.isNull() && !highlightCursor.atEnd()) {
                        highlightCursor = document->find(searchString, highlightCursor,
                                QTextDocument::FindWholeWords);

                        if (!highlightCursor.isNull()) {
                            highlightCursor.movePosition(QTextCursor::WordRight,
                                    QTextCursor::KeepAnchor);
                            highlightCursor.mergeCharFormat(colorFormat);
                        }
                    }
                    cursor.endEditBlock();
            }
            */

            QTW[i]->clear();
            QStringList headers;
            headers << tr( "單詞" ) << tr( "數量" ) ;
            QTW[i]->setHorizontalHeaderLabels( headers );
            QTW[i]->setRowCount(file.getwordnum(s[i]));
            for(int j = 0; j < file.getwordnum(s[i]); j++)
            {
                QTW[i]->setRowHeight(j, 20);
                if(e.isinset(file.gettablefirst(s[i], j)))
                {
                    QTableWidgetItem *item = new QTableWidgetItem(file.gettablefirst(s[i], j).data());
                    item->setBackgroundColor(QColor(255,255,0));
                    QTW[i]->setItem(j, 0, item);
                    QTableWidgetItem *item_2 = new QTableWidgetItem(QString::number(file.gettablesecond(s[i], j), 10));
                    item_2->setBackgroundColor(QColor(255,255,0));
                    QTW[i]->setItem(j, 1, item_2);
                }
                else
                {
                QTW[i]->setItem(j, 0, new QTableWidgetItem(file.gettablefirst(s[i], j).data()));
                QTW[i]->setItem(j, 1, new QTableWidgetItem(QString::number(file.gettablesecond(s[i], j), 10)));
                }
            }

            QTW[i]->resizeColumnsToContents();
            QTW[i]->setEditTriggers(0);

        }
        ui->label_7->setText("語法正確");
    }
    else
    {
        ui->label_7->setText("語法錯誤");
    }
}




bool Widget::isright(QString str)
{
    str.replace(QRegExp(" "), "");
    str.replace(QRegExp("AND"), "+");
    str.replace(QRegExp("OR"), "*");
    str.replace(QRegExp("COUNT"), "C");
    str.replace(QRegExp("NOT"), "N");
    str.replace(QRegExp("\"\\(\""), "\"#40;\"");
    str.replace(QRegExp("\"\\)\""), "\"#41;\"");
    QString p("((\"[A-Za-z0-9-+,.;#']+\")|(N(\"[A-Za-z0-9-+,.;#']+\"))|(C(\"[A-Za-z0-9-+,.;#']+\")[><=][1-9][0-9]*))");
    QString pattern("((\"[A-Za-z0-9-+,.;#']+\")|(N(\"[A-Za-z0-9-+,.;#']+\"))|(C(\"[A-Za-z0-9-+,.;#']+\")[><=][1-9][0-9]*))([*+]((\"[A-Za-z0-9-+,.;#']+\")|(N(\"[A-Za-z0-9-+,.;#']+\"))|(C(\"[A-Za-z0-9-+,.;#']+\")[><=][1-9][0-9]*)))*");
    //qDebug() << str;

    QRegExp rx(pattern);
    QRegExp rxp(p);

    QString khre("\\(([A-Za-z0-9-+*,.;#\"NC><=]+)\\)");
    QRegExp kh(khre);

    int pos = 0;
    while ((pos = kh.indexIn(str, pos)) != -1) {
        if (isright(kh.cap(1)) == 0)
            return 0;
        str.replace(kh, "\"kuohao\"");
        pos = 0;
    }

    QStringList list;

    pos = 0;

    while ((pos = rxp.indexIn(str, pos)) != -1) {
        list << rxp.cap(1);
        pos += rxp.matchedLength();
    }

    //qDebug() << list;


    return rx.exactMatch(str);
}
