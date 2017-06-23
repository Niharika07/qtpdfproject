#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QtDebug>
#include <QtCore>
#include <QFile>
#include <QString>
#include <QIODevice>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QDir>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include "xmlgen.h"
#include "xmlwriter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(ui->,ui->progressBar,SLOT(setMaximum(int)));
    setWindowFlags( (windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);
    QWidget::setWindowTitle ( "Document Generator" );
    QWidget::setWindowIcon(QIcon("C:/Qt/images/iconimage"));
    QPixmap pix("C:/Qt/images/dispimage11");
    ui->label_image->setPixmap(pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_source_clicked()
{
    QString filename1= QFileDialog::getExistingDirectory(this,tr("open file"),"E://");
    ui->lineEdit_source->insert(filename1);
}

void MainWindow::on_pushButton_target_clicked()
{
    QString filename2= QFileDialog::getExistingDirectory(this,tr("open file"),"E://");
    ui->lineEdit_target->insert(filename2);

}

void MainWindow::on_pushButton_extract_clicked()
{
    if(ui->lineEdit_source->text()==NULL && ui->lineEdit_target->text()==NULL )
        {
            QMessageBox::information(this,"Document Generator","Please enter the deatils");
        }
    else if(ui->lineEdit_source->text()==NULL && ui->lineEdit_target->text()!=NULL)
        {
            QMessageBox::information(this,"Document Generator","Please enter the source location");
        }
    else if(ui->lineEdit_source->text()!=NULL && ui->lineEdit_target->text()==NULL)
        {
            QMessageBox::information(this,"Document Generator","Please enter the target location");
        }
    else if(!QFile::exists(ui->lineEdit_source->text()))
        {
            QMessageBox::information(this,"Document Generator","Please enter valid source location");
        }
    else if(!QFile::exists(ui->lineEdit_target->text()))
        {
            QMessageBox::information(this,"Document Generator","Please enter valid target location");
        }

    else
    {

    //calling xml generator
        QString testmf1 = ui->lineEdit_source->text()+"/" ;
        QString testmf2= ui->lineEdit_source->text()+"/";
        QDir directory= ui->lineEdit_source->text()+"/";
        QString tarpdf=ui->lineEdit_target->text();
        QString xmlfile=ui->lineEdit_target->text()+"/myxml.xml";
        QString pdfxml=ui->lineEdit_target->text();
        QString testmfxml= ui->lineEdit_source->text();
        makexml(testmf1,testmf2,directory,xmlfile,testmfxml);

        ui->progressBar->setValue(50);
     //callingpdf generator
        xmlwriter b1;
        b1.getfilepath(pdfxml,tarpdf);

    ui->progressBar->setValue(100);
    //opening the xml file
    QMessageBox::StandardButton reply= QMessageBox::question(this,"Document Generator"
                                                             ,"Extraction of the comments is done\n Do you want to open the file?",
                                                             QMessageBox::Yes | QMessageBox::No);
    if(reply==QMessageBox::Yes)
            {
            QDesktopServices::openUrl(QUrl("file:///"+tarpdf+"Doc.pdf",QUrl::TolerantMode));
            }
    else
            {exit(0);}
exit(0);

}

}
