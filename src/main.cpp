#include "main.h"

#include <QApplication>

#include "mainwidget.h"

static fa::QtAwesome* mAwesome = nullptr;

static void
makeQtAwesome()
{
  mAwesome = new fa::QtAwesome(qApp);
  mAwesome->initFontAwesome();
}

fa::QtAwesome*
awesome()
{
  return mAwesome;
}

int
main(int argc, char* argv[])
{
  QApplication a(argc, argv);

  makeQtAwesome();
  MainWidget w;
  w.show();
  return a.exec();
}
