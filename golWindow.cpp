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
    popRatioBox = new QSpinBox;
    popRatioBox->setRange(0, 100);
    popRatioBox->setSingleStep(1);
    popRatioBox->setValue(50);
    popRatioBox->setSuffix("%");

    QGroupBox *groupBox = new QGroupBox("Controls");
    QVBoxLayout *vbox = new QVBoxLayout;
    QLabel *speedLabel = new QLabel(tr("Speed (X iterations/sec)"));
    speedSlider = new QSlider(Qt::Horizontal);
    vbox->addWidget(startBtn);
    vbox->addWidget(pauseBtn);
    vbox->addWidget(populateBtn);
    vbox->addWidget(clearBtn);
    vbox->addWidget(speedLabel);
    vbox->addWidget(speedSlider);
    groupBox->setLayout(vbox);

    connect(startBtn, SIGNAL(clicked()), board, SLOT(start()));
    connect(pauseBtn, SIGNAL(clicked()), board, SLOT(pause()));
    connect(populateBtn, SIGNAL(clicked()), board, SLOT(populate()));
    connect(clearBtn, SIGNAL(clicked()), board, SLOT(clear()));


    QGroupBox *groupBox2 = new QGroupBox(tr("Preferences"));
    QVBoxLayout *vbox2 = new QVBoxLayout;
    QLabel *popRatioLabel = new QLabel(tr("Initial ratio of alive cells"));
    vbox2->addWidget(popRatioLabel);
    vbox2->addWidget(popRatioBox);
    groupBox2->setLayout(vbox2);


    QGroupBox *groupBox3 = new QGroupBox(tr("Statistics"));
    QVBoxLayout *vbox3 = new QVBoxLayout;
    iterationLabel = new QLabel(tr("Iteration: 0"));
    aliveCellsLabel = new QLabel(tr("Alive cells: 0"));
    vbox3->addWidget(iterationLabel);
    vbox3->addWidget(aliveCellsLabel);
    groupBox3->setLayout(vbox3);

    connect(board, SIGNAL(changeLabel(QString, QString)), this, SLOT(changeLabel(QString, QString)));


    QGridLayout *layout = new QGridLayout;
    layout->addWidget(groupBox, 0, 0);
    layout->addWidget(groupBox2, 1, 0);
    layout->addWidget(groupBox3, 2, 0);
    layout->addWidget(board, 0, 1, 4, 4);
    setLayout(layout);

    setWindowTitle(tr("Game of Life"));
    /* resize(550, 370); */
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
