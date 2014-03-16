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
}

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
}

void GolBoard::clear() {
}

void GolBoard::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);
    QPainter painter(this);
    QRect rect = contentsRect();
    if (isPaused) {
        painter.drawText(rect, Qt::AlignCenter, tr("Game of Life is paused"));
    } else {
        painter.drawText(rect, Qt::AlignCenter, tr("Game of Life is running"));
    }
}

void GolBoard::drawCell(QPainter &painter, int x, int y) {
}

void GolBoard::timerEvent(QTimerEvent *event) {
    if (event->timerId() == timer.timerId()) {
        update();
        timer.start(timeoutTime(), this);
    } else {
        QFrame::timerEvent(event);
    }
}
