#include <qapplication.h>

#include <TfmMain.h>

int main( int argc, char **argv )
{
    QApplication a( argc, argv );
    qInitNetworkProtocols();
    TfmMain w;
    w.setGeometry( 100, 100, 200, 120 );
    a.setMainWidget( &w );
    a.setFont(QFont("Arial",10));
    w.show();
    return a.exec();
}


