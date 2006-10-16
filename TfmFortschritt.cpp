#include <TfmFortschritt.h>

TfmFortschritt::TfmFortschritt( QWidget *parent, const char *name ) : QWidget( parent, name )
{
  setMinimumSize( 300, 160 );
  setMaximumSize( 300, 160 );
  this->setCaption("Fortschritt des Vorgangs");

  pbBalken = new QProgressBar(200, this,"pbBalken");
  pbBalken->setGeometry(5,5,290,25);

  lbListe = new QListBox(this, "lbListe");
  lbListe->setGeometry(5,40,290,110);
}

void TfmFortschritt::AddListe(QString Eintrag)
{
  lbListe->insertItem(Eintrag, -1);
  lbListe->setCurrentItem(lbListe->numRows() -1);
}

void TfmFortschritt::SetProgress(int Progress)
{
if (Progress== -1) {
  pbBalken->setProgress(200);
  return;
  }
  pbBalken->setProgress(pbBalken->progress() + Progress);
}
