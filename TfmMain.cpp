#include <TfmMain.h>

int OldProzent;
void meldung(QString text);
void error(QString text);
Hausaufgaben HA;

TfmMain::TfmMain( QWidget *parent, const char *name ) : QWidget( parent, name )
{
    setMinimumSize( 400, 570 );
    setMaximumSize( 400, 570 );

    gb_login = new QGroupBox("Logindaten", this);
    gb_login->setColumnLayout(0, Qt::Vertical );
    gb_login->setGeometry(5,0,390,50);

    gb_nach = new QGroupBox("Nachricht", this);
    gb_nach->setGeometry(5,67,390,440);

    gb_control = new QGroupBox("", this);
    gb_control->setGeometry(5, 525, 390, 40);

    lbUsername = new QLabel(gb_login);
    lbPassword = new QLabel(gb_login);
    lbSchiene = new QLabel(gb_nach);
    lbFach = new QLabel(gb_nach);

    leUsername = new QLineEdit("", gb_login, "leUsername");
    lePassword = new QLineEdit("", gb_login, "lePassword");
    leFilename = new QLineEdit("", gb_nach, "leFilename");

    btQuit = new QPushButton( "Beenden", gb_control, "btQuit" );
    btDatei=new QPushButton(". . .", gb_nach, "btDatei");
    btUpload=new QPushButton("Hochladen", gb_control, "btUpload");

    cbSchiene = new QComboBox( FALSE, gb_nach, "cbSchiene" );
    cbFach = new QComboBox( TRUE, gb_nach, "cbFach" );

    teNachricht = new QTextEdit (gb_nach, "teNachricht");

    setTabOrder( leUsername, lePassword);
    setTabOrder(lePassword, cbSchiene);
    setTabOrder(cbSchiene, cbFach);
    setTabOrder(cbFach, teNachricht);
    setTabOrder(teNachricht, btDatei);
    setTabOrder(btDatei,btUpload);
    setTabOrder(btUpload, btQuit);

    btQuit->setGeometry(310, 5, 75, 30 );

    lbUsername->setText ( "Benutzername:");
    lbUsername->setGeometry(10,15,90,25);

    lbPassword->setText("Passwort:");
    lbPassword->setGeometry(220,15,75,25);

    lbSchiene->setText ("Schiene:");
    lbSchiene->setGeometry(43,13,50,25);

    lbFach->setText ("Fach:");
    lbFach->setGeometry(240,13,35,25);

    leUsername->setGeometry(100,15,100,25);

    lePassword->setGeometry(280,15,100,25);
    lePassword->setEchoMode(QLineEdit::Password);

    cbSchiene->setGeometry(100, 13, 100, 25);
    cbSchiene->insertItem("GK 1",-1);
    cbSchiene->insertItem("GK 2",-1);
    cbSchiene->insertItem("GK 3",-1);
    cbSchiene->insertItem("GK 4",-1);
    cbSchiene->insertItem("GK 5",-1);
    cbSchiene->insertItem("GK 6",-1);
    cbSchiene->insertItem("GK 7",-1);
    cbSchiene->insertItem("GK 8",-1);
    cbSchiene->insertItem("LK 1",-1);
    cbSchiene->insertItem("LK 2",-1);
    cbSchiene->insertItem("(leer)",-1);

    cbFach->setGeometry(280, 13, 100, 25);

    teNachricht->setGeometry(5, 45, 380,350);
    teNachricht->setTextFormat( PlainText );

    leFilename->setGeometry(5,408,340,25);

    btDatei->setGeometry( 350,408,30,25);

    btUpload->setGeometry( 5, 5, 75, 30);

    connect( btQuit, SIGNAL(clicked()), qApp, SLOT(quit()) );
    connect (cbSchiene, SIGNAL(activated( int ) ), this , SLOT(handleActivated( int ) ) );
    connect ( btUpload, SIGNAL (clicked()), this, SLOT (my_upload()));
    connect ( btDatei, SIGNAL (clicked()), this, SLOT (dateiauswahl()));

    }

void TfmMain::handleActivated( int Schiene)
{
char SQLQuery[128];
Schiene++;
if (Schiene > 8) {
  Schiene = Schiene + 2;
  }
if (Schiene == 13 ) {
  cbFach->clear();

return;
}
    QSqlDatabase *StundenDB = QSqlDatabase::addDatabase( DB_ADRESS_DRIVER );
    if ( ! StundenDB )
		{
			qWarning( "Keine Verbindung zum Stundenplan-DB-Server" );
    }
  if( StundenDB ) {
       StundenDB->setHostName( DB_ADRESS_HOST );
       StundenDB->setDatabaseName( DB_ADRESS_DBNAME );
       StundenDB->setUserName(DB_ADRESS_USER  );
       StundenDB->setPassword(DB_ADRESS_PASSWD  );
      if( StundenDB->open() ) {
     sprintf( SQLQuery, "SELECT Kursname FROM stundenplan WHERE SID=%d", Schiene );
     QSqlQuery query( SQLQuery );
	   if( query.isActive() ) {
		cbFach->clear();
	       while( query.next() ) {
		if ( query.value( 0 ).toString() != "frei") {
		cbFach->insertItem (query.value( 0 ).toString(), -1 ); }
		}
	}
}
}

}

void TfmMain::my_upload ( )
{
QString title="";
QFileInfo* DateiInfo;
HA.SetFertig(TRUE);

  if ( leUsername->text () != "" or leUsername->text () == "Anonymous" ) {
  HA.SetUsername( leUsername->text () );
  }
  else { HA.SetFertig(FALSE);
  meldung("Benutzername");
  return;
  }

  if ( lePassword->text () != "" ) {
  HA.SetPassword( lePassword->text () );
  }
  else {  HA.SetFertig(FALSE);
  meldung("Passwort");
  return;
  }


  if ( cbFach->currentText ()  != "" ) {
  if ( cbSchiene->currentText() != "(leer)" ) {
   title = cbSchiene->currentText();
  title.append ( " - "); }
  title.append ( cbFach->currentText() );
  HA.SetTitle(title);
 }
  else { HA.SetFertig(FALSE);
  meldung("GK/Fach");
  return;
   }

  if ( teNachricht->text () != ""  ) {
  HA.SetNachricht ( teNachricht->text () );
    }
  else { HA.SetFertig(FALSE);
    meldung("Nachricht");
    return;
     }

  DateiInfo = new QFileInfo(leFilename->text () );
    if ( DateiInfo->exists () ) {
    HA.SetDateiname( leFilename->text () );
    }
  else {  HA.SetFertig(FALSE);
  meldung("Dateiname");
  return;
    }

  posttopic ();
  }

void TfmMain::posttopic ()
{
QString SQLQuery, user_id, topic_id, post_id, attach_id, mime_type, realfile, zufall;
QByteArray data;
QFileInfo DateiInfo(HA.GetDateiname());
QFtp* FTPUpload;
QFile* Datei;
Fortschritt = new TfmFortschritt;
Fortschritt->setGeometry( 100, 100, 200, 120 );
Fortschritt->show();
Fortschritt->AddListe("Vorgang gestartet");
Fortschritt->SetProgress(7);

if ( ! HA.GetFertig () ) {
  return;
}
Fortschritt->AddListe("Daten sind konsistent");
Fortschritt->SetProgress(7);
srand(static_cast<unsigned>(time(0)));
realfile = HA.GetTitle ();
realfile.append ("_");
realfile.append ( QString::number(rand() % 1000) );
realfile.append ("_");
realfile.append (DateiInfo.fileName ());
realfile.replace( QRegExp(" "), "_" );
Fortschritt->AddListe("Titel erzeugt");
Fortschritt->SetProgress(7);
HA.SetNachricht ( HA.GetNachricht ().append ("\n\r\n\rDer Link zum Herunterladen der Hausaufgaben ist:\n\r ") );
HA.SetNachricht ( HA.GetNachricht().append("http://"));
HA.SetNachricht ( HA.GetNachricht ().append(FTP_HOST));
HA.SetNachricht ( HA.GetNachricht ().append(FTP_PATH));
HA.SetNachricht ( HA.GetNachricht ().append(realfile));
teNachricht->text () = HA.GetNachricht ();
Fortschritt->AddListe("Nachrichtentext erzeugt");
Fortschritt->SetProgress(7);
    QSqlDatabase *ForenDB = QSqlDatabase::addDatabase( FOREN_DRIVER );
    if ( ! ForenDB )
		{
			error( "Keine Verbindung zur Foren-DB-Server" );
    }
 Fortschritt->AddListe("MySQL: Verbindung zum Server gestartet");
 Fortschritt->SetProgress(7);
  if( ForenDB ) {
       ForenDB->setHostName( FOREN_HOST );
       ForenDB->setDatabaseName( FOREN_DBNAME );
       ForenDB->setUserName(FOREN_USER  );
       ForenDB->setPassword(FOREN_PASSWD  );
      if( ForenDB->open() ) {
Fortschritt->AddListe("MySQL: Verbindung zum Server hergestellt");
Fortschritt->SetProgress(7);
//phpbb_users

SQLQuery = "SELECT user_id  FROM `phpbb_users` WHERE username='";
SQLQuery.append(HA.GetUsername () );
SQLQuery.append("' AND user_password=");
SQLQuery.append("md5(\"");
SQLQuery.append( HA.GetPassword () );
SQLQuery.append("\");");
QSqlQuery query( SQLQuery );
	 if( query.isActive() ) {
	 while( query.next() ) {
		user_id= query.value( 0 ).toString(); }
		}
if ( user_id == "" ) {
    QMessageBox::warning( 0 , "Hausaufgaben-Updater",
    "Keinen passenden User gefunden!\nGgf. sind Username und/oder Passwort falsch geschrieben" , "OK"  );
   return;
 }
Fortschritt->AddListe("MySQL: Username und Passwort verifiziert");
Fortschritt->SetProgress(7);
// phpbb_topics

SQLQuery ="INSERT INTO `phpbb_topics` ( `topic_id` , `forum_id` , `topic_title` , `topic_poster` , `topic_time` , `topic_views` , `topic_replies` , `topic_status` , `topic_vote` , `topic_type` , `topic_first_post_id` , `topic_last_post_id` , `topic_moved_id` , `topic_attachment` , `topic_calendar_time` , `topic_calendar_duration` , `topic_icon` ) VALUES( '', '3', '";
SQLQuery.append ( HA.GetTitle ());
SQLQuery.append ("' , '");
SQLQuery.append ( user_id );
SQLQuery.append ("',UNIX_TIMESTAMP() , '0', '0', '0', '0', '0', '0', '0', '0', '0', NULL, NULL, NULL);");
query.exec( SQLQuery );

SQLQuery = "SELECT topic_id FROM `phpbb_topics` WHERE forum_id='3' AND topic_title='";
SQLQuery.append ( HA.GetTitle () );
SQLQuery.append ("'");
query.exec (SQLQuery);
	 if( query.isActive() ) {
	 while( query.next() ) {
		topic_id= query.value( 0 ).toString(); }
		}
if (topic_id == "" ) {
 error("Interner Fehler:  topic_id nicht gefunden");
  return;
 }
Fortschritt->AddListe("MySQL: php_topics eingetragen");
Fortschritt->SetProgress(7);
// phpbb_post

SQLQuery = "INSERT INTO `phpbb_posts` ( `post_id` , `topic_id` , `forum_id` , `poster_id` , `post_time` , `poster_ip` , `post_username` , `enable_bbcode` , `enable_html` , `enable_smilies` , `enable_sig` , `post_edit_time` , `post_edit_count` , `post_attachment` , `post_bluecard` , `post_icon` ) VALUES ('', '";
SQLQuery.append (topic_id);
SQLQuery.append ("','3','");
SQLQuery.append (user_id);
SQLQuery.append ("', UNIX_TIMESTAMP(),'7f000001' ,'', '1', '0', '1', '1', NULL , '0', '1', NULL , 0);");
query.exec (SQLQuery);

SQLQuery = "SELECT post_id FROM `phpbb_posts` WHERE topic_id='";
SQLQuery.append (topic_id);
SQLQuery.append ("' AND  poster_id='");
SQLQuery.append (user_id);
SQLQuery.append ("';");
query.exec (SQLQuery);
	 if( query.isActive() ) {
	 while( query.next() ) {
		post_id= query.value( 0 ).toString(); }
		}
if (post_id == "" ) {
 error("Interner Fehler: post_id nicht gefunden");
  return;
 }
 Fortschritt->AddListe("MySQL: phpbb_post eingetragen");
 Fortschritt->SetProgress(7);
//phpbb_post_text

SQLQuery = "INSERT INTO `phpbb_posts_text` ( `post_id` , `bbcode_uid` , `post_subject` , `post_text` ) VALUES ('";
SQLQuery.append ( post_id );
SQLQuery.append ("', '', '', '");
SQLQuery.append (HA.GetNachricht () );
SQLQuery.append ("');");
query.exec (SQLQuery);

Fortschritt->AddListe("MySQL: phpbb_post_text eingetragen");
Fortschritt->SetProgress(7);
//update von phpbb_topics

SQLQuery = "UPDATE `phpbb_topics` SET `topic_first_post_id` = '";
SQLQuery.append (post_id);
SQLQuery.append ("',`topic_last_post_id` = '");
SQLQuery.append ( post_id);
SQLQuery.append ("'WHERE `topic_id` = '");
SQLQuery.append (topic_id);
SQLQuery.append ("';");
query.exec (SQLQuery);

Fortschritt->AddListe("MySQL: phpbb_topics aktualisiert");
Fortschritt->SetProgress(7);
//file upload
SQLQuery = "INSERT INTO `phpbb_attachments_desc` ( `attach_id` , `physical_filename` , `real_filename` , `download_count` , `comment` , `extension` , `mimetype` , `filesize` , `filetime` , `thumbnail` ) VALUES ('', '";

SQLQuery.append (realfile);
SQLQuery.append ("','");
SQLQuery.append ( DateiInfo.fileName () );
SQLQuery.append ( "','0','");
SQLQuery.append ( HA.GetTitle () );
SQLQuery.append ( "','");
SQLQuery.append ( DateiInfo.extension( FALSE ) );
SQLQuery.append ("','");
if ( DateiInfo.extension (FALSE) == "png" or
      DateiInfo.extension (FALSE) == "gif" or
      DateiInfo.extension (FALSE) ==  "jpeg" ) {
  mime_type = "image/";
  mime_type.append ( DateiInfo.extension (FALSE) ); }
else if ( DateiInfo.extension (FALSE) == "jpg" ) {
  mime_type = "image/jpeg"; }
else if ( DateiInfo.extension (FALSE) == "txt" or
              DateiInfo.extension (FALSE) ==  "rtf" ) {
  mime_type = "text/";
  mime_type.append ( DateiInfo.extension (FALSE) ); }
else {
  mime_type = "application/";
  mime_type.append (DateiInfo.extension (FALSE) ); }
SQLQuery.append (mime_type);
SQLQuery.append ("','");
SQLQuery.append (QString::number( DateiInfo.size () ) );
SQLQuery.append("',UNIX_TIMESTAMP(),'0');");
query.exec (SQLQuery);
Fortschritt->AddListe("MIME-type der Datei ermittelt");
Fortschritt->SetProgress(7);

//phpbb_attachments_desc

SQLQuery = "SELECT attach_id FROM `phpbb_attachments_desc` WHERE physical_filename='";
SQLQuery.append (realfile);
SQLQuery.append ("';");
query.exec (SQLQuery);
	 if( query.isActive() ) {
	 while( query.next() ) {
		attach_id= query.value( 0 ).toString(); }
		}
if (attach_id == "" ) {
 error("Interner Fehler: attach_id nicht gefunden");
  return;
 }
Fortschritt->AddListe("MySQL: phpbb_attachments_desc eingetragen");
Fortschritt->SetProgress(7);

//phpbb_attachments
SQLQuery="INSERT INTO `phpbb_attachments` ( `attach_id` , `post_id` , `privmsgs_id` , `user_id_1` , `user_id_2` ) VALUES ('";
SQLQuery.append (attach_id );
SQLQuery.append ("','");
SQLQuery.append (post_id);
SQLQuery.append ("','0','");
SQLQuery.append ( user_id );
SQLQuery.append ( "','0');");
query.exec(SQLQuery);
Fortschritt->AddListe("MySQL: phpbb_attachments eingetragen");
Fortschritt->SetProgress(7);
Datei = new QFile(HA.GetDateiname () );
Datei->open( IO_ReadOnly );
Fortschritt->AddListe("FTP: Datei zum Upload geöffnet");
FTPUpload = new QFtp(this);
connect ( FTPUpload, SIGNAL (dataTransferProgress ( int , int  )  ), this, SLOT (FftpProgress(int, int) ) );
FTPUpload->connectToHost(FTP_HOST);
Fortschritt->AddListe("FTP: Verbindung zum Server hergestellt");
FTPUpload->login(FTP_USER, FTP_PASSWD);
Fortschritt->AddListe("FTP: Eingeloggt");
FTPUpload->cd( FTP_PATH);
Fortschritt->AddListe("FTP: Datei wird hochgeladen");
FTPUpload->put(Datei, realfile);
FTPUpload->close ();
Fortschritt->AddListe("FTP-Upload beendet");
Fortschritt->SetProgress(-1);
}
}
//Fortschritt->hide();

}

void TfmMain::FftpProgress(int done, int total)
{
int Prozent;
Prozent = (done*100) / total;
Prozent = Prozent / 2;
Prozent = Prozent - OldProzent;
Fortschritt->SetProgress(Prozent);
OldProzent = Prozent;
}

void TfmMain::dateiauswahl ()
{
leFilename->setText ( QFileDialog::getOpenFileName (
                    "",
                    "PDF-Dokumente (*.pdf);;Bilder (*.png *.gif *.jpg *.jpeg);;weitere Dokumente (*.doc *.sxw *.txt *.rtf);;gepackte Archive (*.zip *.rar *.ace *.tar *.tar *bz2 *gz *.tgz;;Alle (*.*)",
                    this,
                    "open file dialog"
                    "Datei zum Hochladen auswählen" ) );
}

void meldung(QString text)
{
QString meldung;
meldung.append( "Es wurde das folgende Feld nicht ausgefüllt:\n\n" );
meldung.append( text );
meldung.append ("\n\nBitte das Feld ausfüllen und erneut auf \"Hochladen\" klicken");
QMessageBox::information( 0 , "Hausaufgaben-Updater",
    meldung , "OK"  );
}

void error(QString text)
{
QString meldung;
meldung.append( "Während des Vorgangs trat ein schwerwiegender Fehler auf:\n\n" );
meldung.append( text );
meldung.append ("\n\nDer Vorgang wurde abgebrochen");
QMessageBox::critical (0 , "Hausaufgaben-Updater",
    meldung , "OK"  );
}
