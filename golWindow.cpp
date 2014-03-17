#include <QtWidgets>

#include "golWindow.h"
#include "golBoard.h"

GolWindow::GolWindow()
{
    board = new GolBoard;
    startBtn = new QPushButton(tr("&Start"));
    pauseBtn = new QPushButton(tr("&Pause"));
    populateBtn = new QPushButton(tr("&Random populate"));
    clearBtn = new QPushButton(tr("&Clear"));

    QGroupBox *groupBox = new QGroupBox("Controls");
    QVBoxLayout *vbox = new QVBoxLayout;
    speedLabel = new QLabel(tr("Speed (1 iterations/sec)"));
    speedSlider = new QSlider(Qt::Horizontal);
    speedSlider->setTickInterval(1);
    speedSlider->setMinimum(1);
    speedSlider->setMaximum(100);

    vbox->addWidget(startBtn);
    vbox->addWidget(pauseBtn);
    vbox->addWidget(populateBtn);
    vbox->addWidget(clearBtn);
    vbox->addWidget(speedLabel);
    vbox->addWidget(speedSlider);
    groupBox->setLayout(vbox);

    connect(startBtn, &QPushButton::clicked, board, &GolBoard::start);
    connect(pauseBtn, &QPushButton::clicked, board, &GolBoard::pause);
    connect(populateBtn, &QPushButton::clicked, board, &GolBoard::populate);
    connect(clearBtn, &QPushButton::clicked, board, &GolBoard::clear);
    connect(speedSlider, &QSlider::valueChanged, board, &GolBoard::setTimeoutTime);
    connect(speedSlider, &QSlider::valueChanged, this, &GolWindow::changeSliderLabel);

    QGroupBox *groupBox2 = new QGroupBox(tr("Preferences"));
    QVBoxLayout *vbox2 = new QVBoxLayout;
    QLabel *popRatioLabel = new QLabel(tr("Initial ratio of alive cells"));
    popRatioBox = new QSpinBox;
    popRatioBox->setRange(0, 100);
    popRatioBox->setSingleStep(1);
    popRatioBox->setValue(30);
    popRatioBox->setSuffix("%");
    vbox2->addWidget(popRatioLabel);
    vbox2->addWidget(popRatioBox);
    groupBox2->setLayout(vbox2);

    /* new connect syntax doesn't work with overloaded methods, usign old syntax */
    /* connect(popRatioBox, &QSpinBox::valueChanged, board, &GolBoard::setPopRatio); */
    connect(popRatioBox, SIGNAL(valueChanged(int)), board, SLOT(setPopRatio(int)));


    QGroupBox *groupBox3 = new QGroupBox(tr("Statistics"));
    QVBoxLayout *vbox3 = new QVBoxLayout;
    iterationLabel = new QLabel(tr("Iteration: 0"));
    aliveCellsLabel = new QLabel(tr("Alive cells: 0"));
    vbox3->addWidget(iterationLabel);
    vbox3->addWidget(aliveCellsLabel);
    groupBox3->setLayout(vbox3);

    connect(board, &GolBoard::changeLabel, this, &GolWindow::changeLabel);


    QGridLayout *layout = new QGridLayout;
    layout->addWidget(groupBox, 0, 0);
    layout->addWidget(groupBox2, 1, 0);
    layout->addWidget(groupBox3, 2, 0);
    layout->addWidget(board, 0, 1, 4, 4);
    setLayout(layout);

    setWindowTitle(tr("Game of Life"));
    /* resize(550, 370); */
}

void GolWindow::changeSliderLabel(int value) {
    speedLabel->setText(QString(tr("Speed (%1 iterations/sec)").arg(value)));
}

void GolWindow::changeLabel(QString label, QString text) {
    if (0 == QString::compare(label, "iterationLabel")) {
        iterationLabel->setText(text);
        return;
    }
    if (0 == QString::compare(label, "aliveCellsLabel")) {
        aliveCellsLabel->setText(text);
        return;
    }
}
