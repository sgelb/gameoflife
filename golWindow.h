#ifndef GOLWINDOW_H
#define GOLWINDOW_H

#include <QFrame>
#include <QWidget>

class QPushButton;
class QSpinBox;
class GolBoard;
class QSlider;
class QString;
class QLabel;

class GolWindow : public QWidget
{
    Q_OBJECT

public:
    GolWindow();

public slots:
    void changeLabel(QString, QString);

private:
    GolBoard *board;
    QPushButton *startBtn;
    QPushButton *pauseBtn;
    QPushButton *clearBtn;
    QPushButton *populateBtn;
    QSpinBox *popRatioBox;
    QSlider *speedSlider;
    QLabel *iterationLabel;
    QLabel *aliveCellsLabel;
};

#endif
