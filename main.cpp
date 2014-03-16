#include <QtWidgets>
#include <stdlib.h>

#include "golWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GolWindow window;
    window.show();
    return app.exec();
}
