#include <qapplication.h>
#include <qprogressbar.h>
#include <qlistbox.h>

class TfmFortschritt : public QWidget
{
Q_OBJECT
private:
  QProgressBar* pbBalken;
  QListBox* lbListe;
public slots:

  public:
    TfmFortschritt( QWidget *parent=0, const char *name=0 );
    void AddListe(QString Eintrag);
    void SetProgress(int Progress);
};
