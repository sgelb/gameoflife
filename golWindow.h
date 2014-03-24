#ifndef GOLWINDOW_H
#define GOLWINDOW_H

#include <QFrame>
#include <QWidget>

class GolBoard;
class QGroupBox;
class QLabel;
class QPushButton;
class QScreen;
class QSlider;
class QSpinBox;
class QString;

class GolWindow : public QWidget
{
    Q_OBJECT

public:
    GolWindow();

public slots:
    void changeLabel(QString, QString);
    void changeSliderLabel(int);
    void checkPauseBtn();

private:
    QLabel *aliveCellsLabel;
    GolBoard *board;
    QPushButton *clearBtn;
    QLabel *iterationLabel;
    QPushButton *pauseBtn;
    QSpinBox *popRatioBox;
    QPushButton *populateBtn;
    QLabel *speedLabel;
    QSlider *speedSlider;
    QPushButton *startBtn;
    void createControlsBox(QGroupBox*);
    void createPrefsBox(QGroupBox*);
    void createStatsBox(QGroupBox*);
    void createSignals();
};

#endif
