#include <QtWidgets>

#include "golWindow.h"
#include "golBoard.h"

GolWindow::GolWindow()
{
    board = new GolBoard;
    startBtn = new QPushButton(tr("&Start"));
    pauseBtn = new QPushButton(tr("&Pause"));
    populateBtn = new QPushButton(tr("&Populate"));
    clearBtn = new QPushButton(tr("&Clear"));
    popRatioBox = new QSpinBox;
    popRatioBox->setRange(0, 100);
    popRatioBox->setSingleStep(1);
    popRatioBox->setValue(50);
    popRatioBox->setSuffix("%");

    connect(startBtn, SIGNAL(clicked()), board, SLOT(start()));
    connect(pauseBtn, SIGNAL(clicked()), board, SLOT(pause()));
    connect(populateBtn, SIGNAL(clicked()), board, SLOT(populate()));
    connect(clearBtn, SIGNAL(clicked()), board, SLOT(clear()));

    QGroupBox *groupBox = new QGroupBox;
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(startBtn);
    vbox->addWidget(pauseBtn);
    vbox->addWidget(populateBtn);
    vbox->addWidget(clearBtn);
    groupBox->setLayout(vbox);

    QGroupBox *groupBox2 = new QGroupBox(tr("Preferences"));
    QLabel *popRatioLabel = new QLabel(tr("Inital ratio of alive cells"));
    QVBoxLayout *vbox2 = new QVBoxLayout;
    vbox2->addWidget(popRatioLabel);
    vbox2->addWidget(popRatioBox);
    groupBox2->setLayout(vbox2);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(groupBox, 0, 0);
    layout->addWidget(groupBox2, 1, 0);
    layout->addWidget(board, 0, 1, 4, 4);
    setLayout(layout);

    setWindowTitle(tr("Game of Life"));
    /* resize(550, 370); */
}
