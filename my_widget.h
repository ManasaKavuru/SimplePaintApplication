#include <qmainwindow.h>
#include <qmessagebox.h>
//#include <qpopupmenu.h>
#include <QMenu>
#include <qmenubar.h>
#include <qapplication.h>
#include <qpixmap.h>
#include <qslider.h>
#include <stack>
#include <vector>
#include <QLineEdit>

#ifndef _MY_WIDGET_H
#define _MY_WIDGET_H

class MyMainWindow: public QMainWindow {
	// All classes that contain signals or slots
	// must mention Q_OBJECT in their declaration.
	Q_OBJECT

	public:
	MyMainWindow(QWidget* parent = 0, const char* name = 0);
	~MyMainWindow();

	/** mouse event handler */
	void mousePressEvent (QMouseEvent *);
    void mouseReleaseEvent (QMouseEvent *);

    void mouseMoveEvent (QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);

    void drawLineTo(QList<QPoint> pos);
    void drawLine(QPoint point1, QPoint point2);


	/** paint handler */
	void paintEvent(QPaintEvent *);


    void rightClickToolsForPen();

    void rightClickToolsForLine();
    QList<QPoint> current_pos; //<<<<<<<<<<<<<<<<
    bool drawing;
    bool drawPen;
    QString linePattern;

	public slots:
	void OnLoadImage();
    void OnNewImage();
    void OnSaveImage();
    void OnForegroundColor();
    void OnBackgroundColor();
    void Undo();
    void Redo();
    void OnSelectingPen();
    void OnSelectingLine();
    void OnClearImage();
    void onValueChanged(int value);
    void onClickedDot();
    //void setImagePixel(const QPoint &pos, bool opaque);

	private:
	QPixmap* image;
    QPixmap* pixmap;
    QLabel* label;
    QLabel* label1;
    QPixmap pix;
    QColor foregroundcolor;
    QColor backgroundcolor;
    QPen* pen;
    QSlider *slider;
    QLineEdit *lineEdit;
    QPoint firstpoint, lastpoint;


    //vector<QImage*> hList;
    //stack<QImage*> rList;
QImage* currentImage;

int undo_lenght;
int w;
int h;
int penWidth;
bool penWidthChanged;

};

#endif
