#include <qapplication.h>
#include <qnetwork.h>
#include <qstring.h>
#include <qpushbutton.h>
#include <qfont.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qtextedit.h>
#include <qsqldriver.h>
#include <qsqldatabase.h>
#include <qsqlquery.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qgroupbox.h>
#include <qfileinfo.h>
#include <cstdlib>
#include <ctime>
#include <qftp.h>
#include <qregexp.h>

#include <hausaufgaben.h>
#include <TfmFortschritt.h>

#define DB_ADRESS_DRIVER	"QMYSQL3"
#define DB_ADRESS_HOST		"zeeman.dyndns.org"
#define DB_ADRESS_DBNAME	"stundenplan"
#define DB_ADRESS_USER		"stufe"
#define DB_ADRESS_PASSWD	"lfsm"

#define FOREN_DRIVER		"QMYSQL3"
#define FOREN_HOST		"zeeman.dyndns.org"
#define FOREN_DBNAME		"stufenportal"
#define FOREN_USER		"stufe"
#define FOREN_PASSWD	"lfsm"

#define FTP_HOST			"zeeman.dyndns.org"
#define FTP_USER			"www"
#define FTP_PASSWD		"xxxxxxxxxxxx"
#define FTP_PATH			"/stufe/portal/phpBB2/files/"

class TfmMain : public QWidget
{
Q_OBJECT
private:
    QLabel* lbUsername;
    QLabel* lbPassword;
    QLabel* lbSchiene;
    QLabel* lbFach;

    QLineEdit* leUsername;
    QLineEdit* lePassword;
    QLineEdit* leFilename;

    QPushButton* btUpload;
    QPushButton* btQuit;
    QPushButton* btDatei;

    QComboBox* cbSchiene;
    QComboBox* cbFach;

    QTextEdit* teNachricht;

    QGroupBox* gb_nach;
    QGroupBox* gb_login;
    QGroupBox* gb_control;

    TfmFortschritt* Fortschritt;
public slots:
    void handleActivated( int Schiene);
    void my_upload ( );
    void dateiauswahl( );
    void posttopic ();
    void FftpProgress(int done, int total);
  public:
    TfmMain( QWidget *parent=0, const char *name=0 );
};
