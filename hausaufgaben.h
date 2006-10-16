#include <qapplication.h>
#include <qstring.h>

class Hausaufgaben: public QObject
{
   Q_OBJECT
public slots:

signals:

private:
  QString m_username;
  QString m_password;
  QString m_dateiname;
  QString m_title;
  QString m_nachricht;
  bool m_fertig;
public:
  void SetUsername(QString  user);
  void SetPassword(QString pw);
  void SetDateiname(QString filename);
  void SetTitle(QString text);
  void SetNachricht(QString text);
  void SetFertig(bool fertig);
  QString GetUsername();
  QString GetPassword ();
  QString GetDateiname ();
  QString GetTitle ();
  QString GetNachricht ();
  bool GetFertig ();
};

