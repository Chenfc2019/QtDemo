#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QFontDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QFont>
#include <QFile>
#include <QColor>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->resize(1200,800);

    //点击新建弹出模态对话框
    connect(ui->actionnew,&QAction::triggered,this,[=](){
        //模态对话框，不可以对其他窗口进行操作
        QDialog * dialog = new QDialog(this);
        //默认弹出窗口太小会报警告
        dialog->resize(200,200);
        dialog->setWindowTitle("模态对话框");
        //阻塞，后面的代码不会运行
        dialog->exec();
        qDebug()<<"模态对话框创建了";
    });

    //点击打开弹出非模态对话框，可以对其他窗口进行操作
    connect(ui->actionopen,&QAction::triggered,this,[=](){
        //QDialog ndlog(this);方式窗口一闪而过，因为创建代的是临时变量，运行后变量被销毁
        //对象被创建到堆区
        QDialog * ndlog = new QDialog(this);
        ndlog->resize(400,300);
        ndlog->setWindowTitle("非模态对话框");
        //设置关闭对话框后释放创建的对话框对象
        ndlog->setAttribute(Qt::WA_DeleteOnClose);
        //显示非模态对话框
        ndlog->show();
    });

    //消息对话框 参数1 父亲 参数2 弹框标题 参数3 显示内容 参数4 按钮的值 参数5 默认关联回车键
    //错误对话框
    connect(ui->actionerror,&QAction::triggered,this,[=](){
        QMessageBox::critical(this,"错误","操作有误！");
    });

    //信息对话框
    connect(ui->actioninformation,&QAction::triggered,this,[=](){
        QMessageBox::information(this,"信息","这是一条提示信息");
    });

    //警告对话框
    connect(ui->actionwarming,&QAction::triggered,this,[=](){
        QMessageBox::warning(this,"警告","这是一条警告");
    });

    //问题对话框
    connect(ui->actionproblem,&QAction::triggered,this,[=](){
        QMessageBox::StandardButton  retbtn = QMessageBox::question(this,"确认问题","保存该文件？",QMessageBox::Save|QMessageBox::Cancel);
        //获取选中值
        if(retbtn == QMessageBox::Save)
        {
            qDebug()<<"选中保存";
        }
        else{
            qDebug()<<"选中取消";
        }
    });

    //字体对话框
    connect(ui->actionfont,&QAction::triggered,this,[=](){
        bool ok;
         QFont font = QFontDialog::getFont(&ok, QFont("Helvetica [Cronyx]", 10), this);
         if (ok) {
             // the user clicked OK and font is set to the font the user selected
             qDebug()<<"字体："<<font.family()<<"大小:"<<font.pointSize()<<"是否加粗："<<font.bold()<<"是否倾斜："<<font.italic();
         } else {
             qDebug()<<"取消了";
         }
    });

    //颜色对话框
    connect(ui->actioncolor,&QAction::triggered,this,[=](){
        QColor color = QColorDialog::getColor(Qt::red,this,"选择颜色");
        qDebug()<<"颜色值：("<<color.red()<<","<<color.green()<<","<<color.blue()<<")";
    });

    //文件对话框
    connect(ui->actionfile,&QAction::triggered,this,[=](){
        //参数1：父级 参数2：窗口标题 参数3：默认打开文件路径 参数4：过滤文件类型
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("打开文件"),
                                                        "D://images",
                                                        tr("Images (*.png *.xpm *.jpg)"));
        qDebug()<<"文件名："<<fileName;
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}
