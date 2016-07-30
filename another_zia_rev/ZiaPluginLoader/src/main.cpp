#include <QtGui>
#include "ZiaPluginLoader.h"

int	main(int argc, char** argv)
{
  QApplication		app(argc, argv);
  ZiaPluginLoader	ziaPluginLoader;

  ziaPluginLoader.show();
  return (app.exec());
}
