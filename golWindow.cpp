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

    connect(startBtn, SIGNAL(clicked()), board, SLOT(start()));
    connect(pauseBtn, SIGNAL(clicked()), board, SLOT(pause()));
    connect(populateBtn, SIGNAL(clicked()), board, SLOT(populate()));
    connect(clearBtn, SIGNAL(clicked()), board, SLOT(clear()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(startBtn, 0, 0);
    layout->addWidget(pauseBtn, 1, 0);
    layout->addWidget(populateBtn, 2, 0);
    layout->addWidget(clearBtn, 3, 0);
    layout->addWidget(board, 0, 1, 4, 1);
    setLayout(layout);

    setWindowTitle(tr("Game of Life"));
    resize(550, 370);
}
