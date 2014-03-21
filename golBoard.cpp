#include <QtWidgets>
#include <iostream>

#include "golBoard.h"

GolBoard::GolBoard(QWidget *parent) : QFrame(parent)
{
    setFrameStyle(QFrame::Panel);
    height = 250;
    width = 250;
    cellsize = 3;
    resize(width*cellsize+2*frameWidth(), height*cellsize+2*frameWidth());
    populate();
    isPaused = true;
    iteration = 0;
    timeoutTime = 25;
    popRatio = 0.4f;
    std::srand(time(0));
}

/* TODO: make sure that board has right w*h-ration when resizing */

QSize GolBoard::sizeHint() const
{
    return QSize(width*cellsize+2*frameWidth(), height*cellsize+2*frameWidth());
}

QSize GolBoard::minimumSizeHint() const
{
    return QSize(width*cellsize+1, height*cellsize+1);
}


/* TODO: create start/pause-toggle button */

void GolBoard::start() {
    /* TODO: disable startBtn */
    /* TODO: enable pauseBtn*/
    if (isPaused) {
        isPaused = false;
    }
    timer.start(timeoutTime, this);
}

void GolBoard::pause() {
    /* TODO: enable startBtn */
    /* TODO: disable pauseBtn*/
    if (isPaused) {
        return;
    }
    isPaused = true;
    timer.stop();
    update();
}

void GolBoard::populate() {
    grid.clear();
    for (int i=0; i<width*height; i++) {
        grid << (rand() < popRatio * ((double)RAND_MAX + 1.0));
    }
    update();
}

void GolBoard::clear() {
    for (int i=0; i<width*height; i++) {
        grid[i] = 0;
    }
    isPaused = true;
    timer.stop();
    iteration = 0;
    emit changeLabel("iterationLabel", QString("Iteration: %1").arg(iteration));
    emit changeLabel("aliveCellsLabel", QString("Alive cells: 0"));
    emit checkPauseBtn();
    update();
}

void GolBoard::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);
    QPainter painter(this);
    for (int i=0; i < height; i++) {
        for (int j=0; j < width; j++) {
            if (grid[i*width + j]) {
                drawCell(painter, i, j);
            }
        }
    }
}

int GolBoard::neighbor_count(int n) {

    /* | n-w-1 | n-w | n-w+1 | */
    /* | n-1   | n   | n+1   | */
    /* | n+w-1 | n+w | n+w+1 | */

    int w = width;
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
    if (yCoord+1 < height) {
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
    int aliveCells = 0;
    tmp_grid.clear();
    for (int i=0; i<width*height; i++) {
        tmp_grid << 0;
    }
    for (int n=0; n<grid.size(); n++) { 
        int ncount = neighbor_count(n);

        if ((0 < grid.at(n)) && (2 == ncount || 3 == ncount)) {
            /* Any live cell with two or three live neighbours
             * lives on */
            tmp_grid[n] = 1;
            aliveCells++;
        }
        else if ((0 == grid.at(n)) && (3 == ncount)) {
            /* Any dead cell with exactly three live neighbours becomes
             * alive */
            tmp_grid[n] = 1;
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
    painter.fillRect(x*cellsize+1, y*cellsize+1, cellsize, cellsize, color);
}

void GolBoard::timerEvent(QTimerEvent *event) {
    if (event->timerId() == timer.timerId()) {
        iterate();
        timer.start(timeoutTime, this);
        update();
    } else {
        QFrame::timerEvent(event);
    }
}

void GolBoard::resizeEvent(QResizeEvent *event) {
    QSize s = event->size();
    int t = std::min(s.width(), s.height());
    cellsize = t/width;
    resize(width*cellsize+2*frameWidth(), height*cellsize+2*frameWidth());
}

void GolBoard::setTimeoutTime(int timeout) {
    timeoutTime = 1000/timeout;
}

void GolBoard::setPopRatio(int p) {
    popRatio = p / 100.0f;
}

void GolBoard::setBoardSize(int w, int h) {
    width = w;
    height = h;
}
