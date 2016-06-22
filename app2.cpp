#include <QApplication>
#include "appview2.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  Form form;

	int	width_ = 640;
	int height_ = 480;
	char buf[1024];
	sprintf(buf,"videotestsrc ! video/x-raw,format=RGB, width=%d,height=%d ! appsink name=sink", width_, height_); // or I420

  form.gstInit(buf);
 
  form.show();
  return app.exec();
}