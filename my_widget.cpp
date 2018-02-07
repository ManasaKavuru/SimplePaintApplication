#include <iostream>
using namespace std;

#include "my_widget.h"


#include <qfiledialog.h>
#include <qpainter.h>
#include <qmessagebox.h>
#include <QMenuBar>
#include <QColorDialog>
#include <QLabel>
#include <QToolBar>
#include <QMouseEvent>
#include <QProcess>
#include <QIODevice>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QGroupBox>

MyMainWindow::MyMainWindow(QWidget* parent, const char* name)
:QMainWindow(parent)
{
    //undo_lenght = 10;
    penWidth = 10;
    QMenu* file = new QMenu("File", this);
    QMenu* file1 = new QMenu("Edit", this);
    drawing = false;
    drawPen = false;
    setMouseTracking(true);

    file->addAction("New image", this, SLOT(OnNewImage()));
    file->addAction("Load image", this, SLOT(OnLoadImage()));
    file->addAction("Save image", this, SLOT(OnSaveImage()));
    file->addAction("Clear", this, SLOT(OnClearImage()));
    file1->addAction("Undo", this, SLOT(Undo()));
    file1->addAction("Redo", this, SLOT(Redo()));
    file->addAction("Foreground color", this, SLOT(OnForegroundColor()));
    file->addAction("Background color", this, SLOT(OnBackgroundColor()));

    menuBar()->addMenu(file);
    menuBar()->addMenu(file1);
    image = new QPixmap();
        //QMenu* file = new QMenu("File", this);
     QPixmap newpix("./Icon/new_icon.bmp");
     QPixmap loadpix("./Icon/open_icon.bmp");
     QPixmap savepix("./Icon/save_icon.bmp");
     QPixmap clearpix("./Icon/clearall_icon.bmp");
     QPixmap linepix("./Icon/line_icon.bmp");
     QPixmap penpix("./Icon/pen_icon.bmp");
     QPixmap undopix("./Icon/undo_icon.bmp");
     QPixmap redopix("./Icon/redo_icon.bmp");
     QPixmap fontpix("./Icon/fcolor_icon.bmp");
     QPixmap backpix("./Icon/bcolor_icon.bmp");
     QToolBar *toolbar = addToolBar("main toolbar");
   //  toolbar->setGeometry(250,250);

   /*  QWidget spacer;
     spacer.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
     spacer.setMinimumWidth(50000);
     toolbar->addWidget(&spacer);*/



     QAction *newImage = toolbar->addAction(QIcon(newpix),"New File");
     connect(newImage, SIGNAL(triggered()), this, SLOT(OnNewImage()));

     QAction *loadImage = toolbar->addAction(QIcon(loadpix),"Load image");
     connect(loadImage, SIGNAL(triggered()), this, SLOT(OnLoadImage()));

     QAction *saveImage = toolbar->addAction(QIcon(savepix),"Save image");
     connect(saveImage, SIGNAL(triggered()), this, SLOT(OnSaveImage()));

     QAction *selectPen = toolbar->addAction(QIcon(penpix),"Pen");
     connect(selectPen, SIGNAL(triggered()), this, SLOT(OnSelectingPen()));

     QAction *clearImage = toolbar->addAction(QIcon(clearpix),"Clear");
     connect(clearImage, SIGNAL(triggered()), this, SLOT(OnClearImage()));

     QAction *undoImage = toolbar->addAction(QIcon(undopix),"Undo");
     connect(undoImage, SIGNAL(triggered()), this, SLOT(Undo()));

     QAction *redoImage = toolbar->addAction(QIcon(redopix),"Redo");
     connect(redoImage, SIGNAL(triggered()), this, SLOT(Redo()));

     QAction *lineImage = toolbar->addAction(QIcon(linepix),"Line");
     connect(lineImage, SIGNAL(triggered()), this, SLOT(OnSelectingLine()));


     QAction *fontImage = toolbar->addAction(QIcon(fontpix),"Foreground Color");
     connect(fontImage, SIGNAL(triggered()), this, SLOT(OnForegroundColor()));

     QAction *backImage = toolbar->addAction(QIcon(backpix),"Background Color");
     connect(backImage, SIGNAL(triggered()), this, SLOT(OnBackgroundColor()));




}


MyMainWindow::~MyMainWindow()
{
	delete image;
    //delete pixmap;
}

void MyMainWindow::paintEvent(QPaintEvent* e)
{
    QPainter paint(this);
	if (! image->isNull())
	{
       paint.drawPixmap(0, menuBar()->height(), (*image));

    }


}

void MyMainWindow::OnLoadImage()
{
    QString s = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Images (*.bmp)"));
	if (! s.isNull())
	{
		image->load(s);
	}

     this->repaint();
}

void MyMainWindow::OnNewImage()
{
    pixmap = new QPixmap(500,500);
    pixmap->fill(Qt::white);
    label1 = new QLabel(this);
    label1->setGeometry(0,50,500,500);

    int w =label1->width();
    int h =label1->height();

 current_pos.clear();

  penWidthChanged = false;
//QLabel *label = new QLabel(this);
label1->setPixmap(pixmap->scaled(w,h,Qt::KeepAspectRatio));

label1->show();
}

void MyMainWindow::OnSaveImage()
{
    QString s = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "/home",
                                                    tr("Images (*.bmp)"));
    if (! s.isNull())
    {
        pixmap->save(s);
    }

     }
void MyMainWindow::OnBackgroundColor()

{
    QColor color = QColorDialog::getColor(Qt::black, this);
    if(color.isValid())
    {
        QString textColorName;
    textColorName = color.name();
    //QMessageBox::information(this, "Text Color", "You selected "+textColorName);
    }
   backgroundcolor = color;
  pixmap->fill(backgroundcolor);
  //this->repaint();
 /*QPalette sample_palette = label1->palette();

  sample_palette.setColor(label1->backgroundRole(),Qt::yellow);
  sample_palette.setColor(label1->foregroundRole(),Qt::yellow);

  label1->setPalette(sample_palette);
  label1->show();*/
  label1->setPixmap(*pixmap);
label1->show();

}

void MyMainWindow::OnForegroundColor()
{
/*QColorDialog *colorDialog = new QColorDialog(this);

this->setCentralWidget(colorDialog);
foregroundcolor = colorDialog->getColor(Qt::white);
}*/
    QColor color = QColorDialog::getColor(Qt::black, this);
    if(color.isValid())
    {
        QString textColorName;
    textColorName = color.name();
    //QMessageBox::information(this, "Text Color", "You selected "+textColorName);
    }
   foregroundcolor = color;
}
void MyMainWindow::OnSelectingPen()
{
    drawPen = true;



}
void MyMainWindow::OnSelectingLine()
{
    drawPen = false;



}

void MyMainWindow::mousePressEvent(QMouseEvent * event)
{
    drawing = true;
if(drawPen)
{
    if(event->button() == Qt::LeftButton)
       {

           current_pos <<event->pos();
           drawing = true;
       }
    else if(event->button() == Qt::RightButton)
    {
  rightClickToolsForPen();
}
}
else
{
    if(event->button() == Qt::LeftButton)
       {

           lastpoint = event->pos();
           drawing = true;
           firstpoint = event->pos();
           drawLine(firstpoint, lastpoint);
       }
    else if(event->button() == Qt::RightButton)
    {
  rightClickToolsForLine();
}
}

}
void MyMainWindow::mouseReleaseEvent(QMouseEvent *event)
{

    drawing = false;
   int iNum = current_pos.count();
  //current_pos.clear();
   //for (int i=0;i<iNum;i++)
     //  delete (current_pos.takeAt(i));
}
void MyMainWindow::mouseMoveEvent(QMouseEvent *event)
{

    if(drawPen)
    {
    if((event->buttons() & Qt::LeftButton))
       {
        current_pos << event->pos();
        drawLineTo(current_pos);

       }
    }
    else
    {
    if((event->buttons() & Qt::LeftButton))
       {
        lastpoint = event->pos();
        drawLine(firstpoint,lastpoint);


       }
    }
}

void MyMainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{

}

void MyMainWindow:: drawLine(QPoint point1, QPoint point2)
{
  QPainter paint( pixmap);


  paint.setRenderHint(QPainter::Antialiasing, true);
  //paint.setPen(QPen(Qt::black, 12, Qt::SolidLine, Qt::RoundCap));
  pen = new QPen(foregroundcolor);
  pen->setWidth(penWidth);
  //pen->setDashPattern(linePattern);
  if(linePattern=="Qt::DotLine")
      pen->setStyle(Qt::DotLine);
  paint.setPen(*pen);
  label1->setPixmap(*pixmap);


  paint.drawPixmap(0,40,(*pixmap));
  paint.drawLine(point1, point2);
  label1->show();

}

void MyMainWindow::drawLineTo(QList<QPoint> pos)
{
    QPainter paint( pixmap);

    pen = new QPen(foregroundcolor);
    pen->setWidth(penWidth);

    paint.setPen(*pen);
    //paint.setPen(QPen(Qt::green, 12));
    QPalette sample_palette = label1->palette();

    sample_palette.setColor(label1->backgroundRole(),Qt::yellow);
    sample_palette.setColor(label1->foregroundRole(),Qt::yellow);


     label1->setPixmap(*pixmap);
     label1->setPalette(sample_palette);

     paint.drawPixmap(0,50,(*pixmap));

     foreach(QPoint point, pos)
         {
         paint.drawPoint(point);

     }
     label1->show();
}

void MyMainWindow::rightClickToolsForPen()

{


    slider = new QSlider(Qt::Horizontal);
   // QDialog *mydialog = new QDialog();
        slider->setMinimum(0);
        slider->setMaximum(100);
        lineEdit = new QLineEdit();

        QObject::connect(slider, SIGNAL(valueChanged(int)),
                         this, SLOT(onValueChanged(int)));

        QHBoxLayout *layout = new QHBoxLayout();
        QRadioButton *flat = new QRadioButton("flat");
            QRadioButton *round = new QRadioButton("round");
            QRadioButton *square = new QRadioButton("square");
            flat->setChecked(true);

            QObject::connect(flat, SIGNAL(clicked()), this, SLOT(onClicked()));
            QObject::connect(round, SIGNAL(clicked()), this, SLOT(onClicked()));
            QObject::connect(square, SIGNAL(clicked()), this, SLOT(onClicked()));
        //QDialog *mydialog = new QDialog();
        //slider->show();
        //mydialog->addAction();
        //layout->addWidget(mydialog);
            layout->addWidget(flat);
            layout->addWidget(round);
            layout->addWidget(square);
        //QGroupBox group =new QGroupBox("Pen style");
        layout->addWidget(slider);
        layout->addWidget(lineEdit);
        layout->addWidget(lineEdit);
        //layout->;
        QWidget *wrapper = new QWidget();
        wrapper->setLayout(layout);
        wrapper->show();
}
void MyMainWindow::rightClickToolsForLine()

{


    slider = new QSlider(Qt::Horizontal);
   // QDialog *mydialog = new QDialog();
        slider->setMinimum(1);
        slider->setMaximum(100);
        slider->setObjectName("line width");
        //slider->se
        lineEdit = new QLineEdit();

        QObject::connect(slider, SIGNAL(valueChanged(int)),
                         this, SLOT(onValueChanged(int)));

        QHBoxLayout *layout = new QHBoxLayout();
        QRadioButton *solid = new QRadioButton("solid line");
        QRadioButton *dash = new QRadioButton("dash line");
        QRadioButton *dot = new QRadioButton("dot line");
           solid->setChecked(true);

            QObject::connect(solid, SIGNAL(clicked()), this, SLOT(onClicked()));
            QObject::connect(dash, SIGNAL(clicked()), this, SLOT(onClicked()));
            QObject::connect(dot, SIGNAL(clicked()), this, SLOT(onClickedDot()));
        //QDialog *mydialog = new QDialog();
        //slider->show();
        //mydialog->addAction();
        //layout->addWidget(mydialog);
            layout->addWidget(solid);
            layout->addWidget(dash);
            layout->addWidget(dot);
        //QGroupBox group =new QGroupBox("Pen style");
        layout->addWidget(slider);
        layout->addWidget(lineEdit);
        layout->addWidget(lineEdit);
        //layout->;
        QWidget *wrapper = new QWidget();
        wrapper->setLayout(layout);
        wrapper->show();
}

void MyMainWindow::onValueChanged(int value)
{
    int pos = slider->sliderPosition();
    QString text = QString::number(pos);
    lineEdit->setText(text);
    penWidth = pos;
}
void MyMainWindow::onClickedDot()
{

    linePattern ="Qt::DotLine";
}
void MyMainWindow::Undo(){

/*
    if (!hList.empty())
    {
        rList.push(hList.back());
        hList.pop_back();

    }

    currentImage = new QImage(w,h, QImage::Format_ARGB32);
    currentImage->fill(qRgba(255,255,255,0));

    if (!hList.empty())
    {
        QPainter p1(currentImage);
        p1.drawPixmap(0,0,*hList.back());
    }
    else
    {
        QPainter p1(currentImage);
        p1.drawPixmap(0,0,*fixImage);
    }
    re_paint();*/

}

void MyMainWindow::Redo(){

}

void MyMainWindow::OnClearImage(){
 if(pixmap){


    delete pixmap;

     //image= NULL;
 }
  //  delete pixmap;
 current_pos.clear();
    pixmap = new QPixmap(500,500);
    pixmap->fill(Qt::white);
    label1 = new QLabel(this);
    label1->setGeometry(0,50,500,500);

    int w =label1->width();
    int h =label1->height();
    label1->setPixmap(pixmap->scaled(w,h,Qt::KeepAspectRatio));

    label1->show();


}

