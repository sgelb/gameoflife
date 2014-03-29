#ifndef GOLWINDOW_H
#define GOLWINDOW_H

#include <QFrame>
#include <QWidget>

class GolBoard;
class QGroupBox;
class QLabel;
class QPushButton;
class QScreen;
class QScrollArea;
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
    void setMinSizeScrollArea();

private:
    GolBoard *board;
    QLabel *aliveCellsLabel;
    QLabel *iterationLabel;
    QLabel *speedLabel;
    QPushButton *clearBtn;
    QPushButton *pauseBtn;
    QPushButton *populateBtn;
    QPushButton *startBtn;
    QScrollArea *scrollArea;
    QSlider *speedSlider;
    QSpinBox *popRatioBox;
    QWidget *sidebar;
    void createControlsBox(QGroupBox*);
    void createPrefsBox(QGroupBox*);
    void createSignals();
    void createStatsBox(QGroupBox*);
};

#endif
