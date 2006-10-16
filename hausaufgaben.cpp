#include <qapplication.h>
#include <qstring.h>
#include <hausaufgaben.h>

QString Hausaufgaben::GetUsername ()
{
return m_username;
}

QString Hausaufgaben::GetPassword ()
{
return m_password;;
}

QString Hausaufgaben::GetDateiname ()
{
return m_dateiname;
}

QString Hausaufgaben::GetTitle ()
{
return m_title;
}

QString Hausaufgaben::GetNachricht ()
{
return m_nachricht;
}

bool Hausaufgaben::GetFertig ()
{
return m_fertig;
}


void Hausaufgaben::SetFertig(bool fertig)
{
  m_fertig = fertig;
 }
void Hausaufgaben::SetUsername(QString  user)
{
  m_username = user;
}
void Hausaufgaben::SetPassword(QString pw)
{
  m_password = pw;
}
void Hausaufgaben::SetDateiname(QString filename)
{
  m_dateiname = filename;
}
void Hausaufgaben::SetTitle(QString text)
{
  m_title = text;
}
void Hausaufgaben::SetNachricht(QString text)
{
  m_nachricht = text;
}

