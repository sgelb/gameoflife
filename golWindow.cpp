#include <QtWidgets>

#include <iostream>
#include "golWindow.h"
#include "golBoard.h"

GolWindow::GolWindow()
{
    /* TODO: refactor */
    board = new GolBoard;
    QWidget *sidebar = new QWidget;

    startBtn = new QPushButton(tr("&Start"));
    startBtn->setCheckable(true);
    startBtn->setAutoExclusive(true);
    pauseBtn = new QPushButton(tr("&Pause"));
    pauseBtn->setCheckable(true);
    pauseBtn->setChecked(true);
    pauseBtn->setAutoExclusive(true);
    populateBtn = new QPushButton(tr("&Random"));
    clearBtn = new QPushButton(tr("&Clear"));

    QGroupBox *groupBox = new QGroupBox("Controls");
    QVBoxLayout *vbox = new QVBoxLayout;
    speedLabel = new QLabel(tr("25 iterations/sec"));
    speedSlider = new QSlider(Qt::Horizontal);
    speedSlider->setValue(25);
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

    /* TODO: connect gridSize */

    QLabel *gridSizeLabel = new QLabel(tr("Grid size"));
    QHBoxLayout *hbox = new QHBoxLayout;
    QLineEdit *xSizeEdit = new QLineEdit("100");
    xSizeEdit->setMaxLength(3);
    QLineEdit *ySizeEdit = new QLineEdit("100");
    ySizeEdit->setMaxLength(3);
    hbox->addWidget(xSizeEdit);
    hbox->addWidget(new QLabel(tr("x")));
    hbox->addWidget(ySizeEdit);

    QLabel *popRatioLabel = new QLabel(tr("Initial ratio of alive cells"));
    popRatioBox = new QSpinBox;
    popRatioBox->setRange(0, 100);
    popRatioBox->setSingleStep(1);
    popRatioBox->setValue(30);
    popRatioBox->setSuffix("%");
    QPushButton *setBtn = new QPushButton(tr("Set"));

    vbox2->addWidget(gridSizeLabel);
    vbox2->addLayout(hbox);
    vbox2->addWidget(popRatioLabel);
    vbox2->addWidget(popRatioBox);
    vbox2->addWidget(setBtn);
    groupBox2->setLayout(vbox2);

    /* new connect syntax doesn't work with overloaded methods, usign old syntax */
    /* connect(popRatioBox, &QSpinBox::valueChanged, board, &GolBoard::setPopRatio); */
    connect(popRatioBox, SIGNAL(valueChanged(int)), board, SLOT(setPopRatio(int)));


    QGroupBox *groupBox3 = new QGroupBox(tr("Statistics"));
    QVBoxLayout *vbox3 = new QVBoxLayout;
    iterationLabel = new QLabel(tr("Iterations: 0"));
    aliveCellsLabel = new QLabel(tr("Alive cells: 0"));
    vbox3->addWidget(iterationLabel);
    vbox3->addWidget(aliveCellsLabel);
    groupBox3->setLayout(vbox3);

    connect(board, &GolBoard::changeLabel, this, &GolWindow::changeLabel);
    connect(board, &GolBoard::checkPauseBtn, this, &GolWindow::checkPauseBtn);

    QVBoxLayout *vbox4 = new QVBoxLayout(sidebar);
    vbox4->addWidget(groupBox, 0, Qt::AlignTop);
    vbox4->addWidget(groupBox2, 0, Qt::AlignTop);
    vbox4->addWidget(groupBox3, 0, Qt::AlignTop);
    vbox4->insertStretch(-1, 0);


    QHBoxLayout *layout = new QHBoxLayout;
    sidebar->setFixedWidth(sidebar->minimumSizeHint().width());
    layout->addWidget(sidebar);
    layout->addWidget(board);
    setLayout(layout);
    setWindowTitle(tr("Conway\'s Game of Life"));
}

void GolWindow::changeSliderLabel(int value) {
    speedLabel->setText(QString(tr("%1 iterations/sec").arg(value)));
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

void GolWindow::checkPauseBtn() {
    pauseBtn->setChecked(true);
}
