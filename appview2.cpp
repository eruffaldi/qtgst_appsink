#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QShortcut>
#include <QPixmap>
 
#include "appview2.h"
 
Form::Form(QWidget *parent)
    : QWidget(parent),pipeline_(0)
{
 
	QShortcut *shortcutUp = new QShortcut(QKeySequence("Up"), this);
	QObject::connect(shortcutUp, SIGNAL(activated()), this, SLOT(onToggleZoom()));
	shortcutUp->setAutoRepeat(false);
}

Form::~Form()
{
	gstClose();	
}

void Form::onToggleZoom()
{
	zoomed_ = !zoomed_;
	update();
}

void Form::gstInit(QString filter)
{
    gstClose();
    gst_init(NULL,NULL);
    pipeline_ = gst_parse_launch(filter.toLocal8Bit().constData(), &error_);
    if (!pipeline_)
    {
        std::cout << "PIPELINE FAILED " << filter.toLocal8Bit().constData() << std::endl;
        return;
    }

    sink_ = gst_bin_get_by_name(GST_BIN(pipeline_), "sink");

    // TODO check presence of AppSink if not add ...
    appsink_ = (GstAppSink*)(sink_);
    g_signal_connect(pipeline_, "deep-notify", G_CALLBACK(gst_object_default_deep_notify ), NULL);             
    gst_app_sink_set_emit_signals(appsink_, true);
    gst_app_sink_set_drop(appsink_, true);
    gst_app_sink_set_max_buffers(appsink_, 1);    
    gst_element_set_state(pipeline_, GST_STATE_PLAYING);
    bus_ = gst_element_get_bus(pipeline_);

    startTimer(30);
}


void Form::timerEvent(QTimerEvent * event)
{
	if(!pipeline_)
		return;

	// polling
	GstSample * sample = gst_app_sink_pull_sample(appsink_);
	GstBuffer * gstImageBuffer= gst_sample_get_buffer(sample); 
	GstCaps * c = gst_sample_get_caps(sample); 
 	const GstStructure *str = gst_caps_get_structure (c, 0);
	gint width, height;

	if (!gst_structure_get_int (str, "width", &width) ||
      !gst_structure_get_int (str, "height", &height)) {
	}
	else
	{
		buffer.resize(width*height*3);
		gst_buffer_extract(gstImageBuffer, 0, buffer.data(), buffer.size());		
		image = QImage((unsigned char*)buffer.data(),width,height,QImage::Format_RGB888);
		update();
	}	
	gst_buffer_unref(gstImageBuffer);    
}

void Form::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
	QRect target = rect();
	QRect source = image.rect();

	// NOTE: unfortunately QPainter can't draw scaled images (really?)
    if(zoomed_)
    {
    	static bool x = true;
    	int dx = image.width()/8;
    	int dy = image.height()/8;
    	source.adjust(dx,dy,-dx,-dy);
	    painter.drawImage(target,image,source);
    }
    else
    {
	    painter.drawImage(0,0,image);	
    }
}

void Form::gstClose()
{
    if(pipeline_)
    {
    	killTimer(timerid_);
	    gst_element_set_state(pipeline_, GST_STATE_NULL);
	    gst_object_unref(sink_);
	    gst_object_unref(pipeline_);
	    gst_object_unref(bus_);
	    pipeline_ = 0;
	    sink_ = 0;
	    bus_ = 0;
    }
}
