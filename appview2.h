#pragma once
#include <QWidget>
#include <gst/gst.h> 
#include <gst/app/gstappsink.h>
#include <glib.h>
#include <iostream>
#include <sstream>

//#include "ui_form.h"
 
class Form : public QWidget //, private Ui::Form
{
    Q_OBJECT
 
public:
    Form(QWidget *parent = 0);
    ~Form();

    void paintEvent(QPaintEvent *event);
	void timerEvent(QTimerEvent * event);

	QImage image; 

	void gstClose();
	void gstInit(QString filter);
	QByteArray buffer;

	bool zoomed_;

private slots:
	void onToggleZoom();

private:
    GstElement *pipeline_;
    GstElement * sink_ ;
    GstAppSink * appsink_ ;
    GstMessage * msg_ ;
    GstBus * bus_ ;
    GError * error_ ;
    int timerid_ ;
};
 