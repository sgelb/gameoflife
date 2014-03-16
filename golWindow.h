#ifndef GOLWINDOW_H
#define GOLWINDOW_H

#include <QFrame>
#include <QWidget>

class QPushButton;
class QSpinBox;
class GolBoard;

class GolWindow : public QWidget
{
    Q_OBJECT

public:
    GolWindow();

private:
    GolBoard *board;
    QPushButton *startBtn;
    QPushButton *pauseBtn;
    QPushButton *clearBtn;
    QPushButton *populateBtn;
    QSpinBox *popRatioBox;
};

#endif
