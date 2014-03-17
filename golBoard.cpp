#include <QtWidgets>
#include <iostream>

#include "golBoard.h"

GolBoard::GolBoard(QWidget *parent) : QFrame(parent)
{
    setFrameStyle(QFrame::Panel);
    resize(Cellsize*BoardWidth, Cellsize*BoardHeight);
    populate();
    isPaused = false;
    isStarted = false;
    iteration = 0;
}

/* TODO: make sure that board has right w*h-ration when resizing */

QSize GolBoard::sizeHint() const
{
    return QSize(BoardWidth*Cellsize + frameWidth() * 2,
                 BoardHeight*Cellsize + frameWidth() * 2);
}

QSize GolBoard::minimumSizeHint() const
{
    return QSize(BoardWidth*Cellsize + frameWidth() * 2,
                 BoardHeight*Cellsize + frameWidth() * 2);
}

/* TODO: create start/pause-toggle button */
/* TODO: disable buttons */

void GolBoard::start() {
    if (isPaused) {
        return;
    }
    isStarted = true;
    timer.start(timeoutTime(), this);
}

void GolBoard::pause() {
    if (!isStarted) {
        return;
    }
    isPaused = !isPaused;
    if (isPaused) {
        timer.stop();
    } else {
        timer.start(timeoutTime(), this);
    }
    update();
}

void GolBoard::populate() {
    seed = (int) time(0);
    std::srand(seed);
    double p = 0.6f;
    for (int i=0; i<BoardWidth*BoardHeight; i++) {
        grid.insert(i, (rand() < p * ((double)RAND_MAX + 1.0)));
    }
    update();
}

void GolBoard::clear() {
    for (int i=0; i<BoardWidth*BoardHeight; i++) {
        grid.insert(i, 0);
    }
    update();
}

void GolBoard::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);
    QPainter painter(this);
    /* QRect rect = contentsRect(); */
    for (int i=0; i < BoardHeight; i++) {
        for (int j=0; j < BoardWidth; j++) {
            if (grid.value(i*BoardWidth + j)) {
                drawCell(painter, i, j);
            }
        }
    }
}

int GolBoard::neighbor_count(int n) {

    /* | n-w-1 | n-w | n-w+1 | */
    /* | n-1   | n   | n+1   | */
    /* | n+w-1 | n+w | n+w+1 | */

    int w = BoardWidth;
    int ncount = 0;
    /* x- and y-coordinate of n */
    int xCoord = n%w;
    int yCoord = n/w;

    /* check row above n */
    if (yCoord > 0) {
        /* check neighbor NW */
        if (xCoord > 0 && grid.at(n-w-1)) ncount++;
        /* check neighbor N */
        if (grid.at(n-w)) ncount++;
        /* check neighbor NE */
        if (xCoord+1 < w && grid.at(n-w+1)) ncount++;
    }

    /* check neighbor W */
    if (xCoord > 0 && grid.at(n-1)) ncount++;
    /* check neighbor E */
    if (xCoord+1 < w && grid.at(n+1)) ncount++;

    /* check row below n */
    if (yCoord+1 < BoardHeight) {
        /* check neighbor SW */
        if (xCoord > 0 && grid.at(n+w-1)) ncount++;
        /* check neighbor S */
        if (grid.at(n+w)) ncount++;
        /* check neighbor SE */
        if (xCoord+1 < w && grid.at(n+w+1)) ncount++;
    }

    return ncount;
}

void GolBoard::iterate() {
    QList<int> tmp_grid;
    int aliveCells = 0;
    for (int i=0; i<BoardWidth*BoardHeight; i++) {
        tmp_grid.insert(i, 0);
    }
    for (int n=0; n<grid.size(); n++) { 
        int ncount = neighbor_count(n);

        if (grid.at(n) && (2 == ncount || 3 == ncount)) {
            /* Any live cell with two or three live neighbours
             * lives on */
            tmp_grid.insert(n, 1);
            aliveCells++;
        }
        else if (!grid.at(n) && 3 == ncount) {
            /* Any cell with exactly three live neighbours becomes
             * alive */
            tmp_grid.insert(n, 1);
            aliveCells++;
        }
    }
    grid = tmp_grid;

    iteration++;
    emit changeLabel("iterationLabel", QString("Iteration: %1").arg(iteration));
    emit changeLabel("aliveCellsLabel", QString("Alive cells: %1").arg(aliveCells));
}

void GolBoard::drawCell(QPainter &painter, int x, int y) {
    QColor color = Qt::black;
    painter.fillRect(x*Cellsize+1, y*Cellsize+1, Cellsize, Cellsize, color);
}

void GolBoard::timerEvent(QTimerEvent *event) {
    if (event->timerId() == timer.timerId()) {
        iterate();
        update();
        timer.start(timeoutTime(), this);
    } else {
        QFrame::timerEvent(event);
    }
}
