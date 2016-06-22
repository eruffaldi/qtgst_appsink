#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

int main( int argc, char **argv )
{
	//Q_INIT_RESOURCE(application);

	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("QtProject");
	QCoreApplication::setApplicationName("Application Example");
	QCoreApplication::setApplicationVersion(QT_VERSION_STR);

	/*
 	QImage myImage;
    QLabel myLabel;
    myLabel.resize( 200, 200 );
    myLabel.setPixmap(myImage);
    myLabel.show();
    */

 	QPixmap image;
 	image.load("x.png");
    QGraphicsScene scene;
    scene.addPixmap(image);
    scene.setSceneRect(image.rect());
 	image.load("y.jpg");
    scene.invalidate();
    QGraphicsView view;
    view.setScene(&scene);
    view.show();
    return app.exec();
}