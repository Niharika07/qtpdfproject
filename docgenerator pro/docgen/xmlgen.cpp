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
xmlgen::xmlgen()
    {}

void makexml(QString testmf1,QString testmf2,QDir directory,QString xmlfile,QString testmfxml)
{
    int z2,z3,i,j=1;
    QStringList comb,func,work;
    QDomDocument doc;
    QDomElement root,name,fname,des,name2,fpara2,fpara,fp2,fp;
    QDomElement des2,fn,ftype2,ftype,fn2,ft2,ft,fnname,desname,fnname2,desname2;
    QDomElement auth2,date2,view2,viewname2,datevalue2,authname2,auth,date1,view,viewname,datevalue,authname;
    QString tauth,tview,tdate,tempauth,tempview,tempdate;
    QString x1="/*",tempname,mfxml,mt,tempdes,tname,tdes,tempstr,mtext22,text1,text2,text22,ttype,tpara;
    QString x2="*/",tg0="/*",tg1="function:",tg2="working",tg3="\n",tg4="\t",tg5="*/";
    QString rg0="/",tg6="type",tg7="parameters",tg8="author",tg9="date",tg10="reviewer",temppara,temptype;
    QString c1=":",mf,x3="//function",x4="//reviewer",x5="/*function";
    int len=0,len1=0,z5,z4,z6;

    testmfxml.replace("/","-");


    QStringList listdir=directory.entryList();
    int lendir=listdir.size();
    root=doc.createElement(testmfxml);
    doc.appendChild(root);

    for(i=2;i<lendir;i++)
    {
     mf=testmf1.operator +=(listdir[i]);
     mfxml=listdir[i];

    //reading the main file...
    QFile mfile(mf);
    if(!mfile.open(QFile::ReadOnly | QFile::Text))
            {
                qDebug() <<"file not found";

            }
    QTextStream in(&mfile);
    QString mtext=in.readAll();//saving whole file into a string
    mt=mtext;

    int cnt=mtext.QString::count(x1);
    int flag=mtext.QString::count(x3);

    //creating files as nodes
    fname = doc.createElement(mfxml);
    root.appendChild(fname);
    mfile.close();


    if(mtext.contains(x3))//for "//" comments
    {
    do
    {

    tempstr =mtext;
    //finding the index of //function
    QFile file1(mf);
    if(!file1.open(QFile::ReadOnly | QFile::Text))
            {
                qDebug() <<"file not found";

            }
    QTextStream fin1(&file1);
    z4=mt.indexOf(x3)+len1;
    text1 = fin1.read(z4);
    file1.close();

    //finding index of \n after //review
    QFile file2(mf);
    if(!file2.open(QFile::ReadOnly | QFile::Text))
            {
                qDebug() <<"file not found";

            }
    QTextStream fin2(&file2);
    z5=mt.indexOf(x4)+len1;
    tempstr.remove(1,z5);
    z6=tempstr.indexOf("\n");
    text2 = fin2.read(z5+z6);
    file2.close();

    QString only=text2.remove(text1);



    len1+=only.size();
    text22= mt.remove(only);
    mt=text22;
    only=only.remove(rg0);
    only=only.remove(tg1);
    only=only.remove(tg2);
    only=only.remove(tg3);
    only=only.remove(tg4);
    only=only.remove(tg6);
    only=only.remove(tg7);
    only=only.remove(tg8);
    only=only.remove(tg9);
    only=only.remove(tg10);

    QStringList arr = only.split(':');
       qDebug() <<arr<<endl;
       tname=arr[0];
       //child of file nodes: function
        name2 = doc.createElement("function");
       fname.appendChild(name2);

       //child of function: function_name
       fn2=doc.createElement("function_name");
       name2.appendChild(fn2);


       fn2.appendChild(doc.createTextNode(tname));

       //child of function: description
       tdes=arr[1];
       des2 = doc.createElement("Function_description");
       name2.appendChild(des2);


       des2.appendChild(doc.createTextNode(tdes));


       //child of function: type
       ttype=arr[2];
       ft2=doc.createElement("Return_type");
       name2.appendChild(ft2);

       ft2.appendChild(doc.createTextNode(ttype));

       //child of function: parameters
       tpara=arr[3];
       fp2=doc.createElement("Arguement");
       name2.appendChild(fp2);

       fp2.appendChild(doc.createTextNode(tpara));

       //child of function: Author
       tauth=arr[4];
       auth2 = doc.createElement("Author");
       name2.appendChild(auth2);

       auth2.appendChild(doc.createTextNode(tauth));

       //child of function: Date
       tdate=arr[5];
       date2 = doc.createElement("Date");
       name2.appendChild(date2);

       date2.appendChild(doc.createTextNode(tdate));

       //child of function: Reviewer
       tview=arr[6];
       view2 = doc.createElement("Reviewer");
       name2.appendChild(view2);

       view2.appendChild(doc.createTextNode(tview));



       qDebug() <<mfxml;
       j++;
    flag--;
      }while(flag>0);

    }

    if(mtext.contains(x5))// for "/**/" comments
    {
    do
    {
    //reading again for index of  /*
    QFile mfile2(mf);
    if(!mfile2.open(QFile::ReadOnly | QFile::Text))
            {
                qDebug() <<"file not found";

            }
    QTextStream in1(&mfile2);

    z3=mtext.indexOf(x1)+len;
    QString mtext11 = in1.read(z3);
    mfile2.close();


    //reading again for index of */
    QFile mfile3(mf);

    if(!mfile3.open(QFile::ReadOnly | QFile::Text))
            {

                qDebug() <<"file not found";

            }
    QTextStream in2(&mfile3);
    z2=mtext.indexOf(x2)+len;
    QString mtext12 = in2.read(z2+2);
    mfile3.close();
    QString sub=mtext12.remove(mtext11);
     len+=sub.size();
     mtext22= mtext.remove(sub);
     mtext=mtext22;
    if(sub.contains(tg1) && sub.contains(tg2))
    {
        sub=sub.remove(tg0);
        sub=sub.remove(tg1);
        sub=sub.remove(tg2);
        sub=sub.remove(tg3);
        sub=sub.remove(tg4);
        sub=sub.remove(tg5);
        sub=sub.remove(tg6);
        sub=sub.remove(tg7);
        sub=sub.remove(tg8);
        sub=sub.remove(tg9);
        sub=sub.remove(tg10);

        QStringList list = sub.split(':');
        qDebug() <<list<<endl;
        tempname=list[0];
        //child of file nodes: function
        name = doc.createElement("function");
        fname.appendChild(name);

        //child of function : function_name
        fn=doc.createElement("function_name");
        name.appendChild(fn);


        fn.appendChild(doc.createTextNode(tempname));

        //child of function: description
        tempdes=list[1];
        des = doc.createElement("Function_description");
        name.appendChild(des);


        des.appendChild(doc.createTextNode(tempdes));

        //child of function: type
        temptype=list[2];
        ft=doc.createElement("Return_type");
        name.appendChild(ft);

        ft.appendChild(doc.createTextNode(temptype));

        //child of function: parameters
        temppara=list[3];
        fp=doc.createElement("Arguement");
        name.appendChild(fp);


        fp.appendChild(doc.createTextNode(temppara));

        //child of function: Author
        tempauth=list[4];
        auth = doc.createElement("Author");
        name.appendChild(auth);


        auth.appendChild(doc.createTextNode(tempauth));

        //child of function: Date
        tempdate=list[5];
        date1 = doc.createElement("Date");
        name.appendChild(date1);

        date1.appendChild(doc.createTextNode(tempdate));

        //child of function: Reviewer
        tempview=list[6];
        view = doc.createElement("Reviewer");
        name.appendChild(view);


        view.appendChild(doc.createTextNode(tempview));


        qDebug() <<mfxml;
        j++;
       cnt--;
    }
    else
        {
        cnt--;
        }
    }while(cnt>0);
    }
    //int f=(i/(lendir-2))*100;

    //writing to xml
    QFile xfile(xmlfile);
        if(!xfile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "Failed to open file for writting";
            //return -1;
        }
        else
        {
            QTextStream stream(&xfile);
            stream << doc.toString();
            xfile.close();
            qDebug() << "Finished";
        }
    testmf1=testmf2;
    z2=0;
    z3=0;
    z4=0;
    z5=0;
    z6=0;
    len=0;
    len1=0;
    j=1;
    mfxml==NULL;
    mf==NULL;
    }

}
