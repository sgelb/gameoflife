#include <QtWidgets>

#include "golBoard.h"

GolBoard::GolBoard(QWidget *parent) : QFrame(parent)
{
    setFrameStyle(QFrame::Panel);
}

void GolBoard::start() {
}

void GolBoard::pause() {
}

void GolBoard::populate() {
}

void GolBoard::clear() {
}

void GolBoard::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);
    QPainter painter(this);
    QRect rect = contentsRect();
    painter.drawText(rect, Qt::AlignCenter, tr("Game of Life"));
}

void GolBoard::drawCell(QPainter &painter, int x, int y) {
}

void GolBoard::timerEvent(QTimerEvent *event) {
}
