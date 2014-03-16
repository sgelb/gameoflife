#ifndef GOLBOARD_H
#define GOLBOARD_H

#include <QBasicTimer>
#include <QFrame>

class GolBoard : public QFrame
{
    Q_OBJECT

    public:
        GolBoard(QWidget *parent = 0);

    public slots:
        void start();
        void pause();
        void populate();
        void clear();

    protected:
        void paintEvent(QPaintEvent *event);
        void timerEvent(QTimerEvent *event);

    private:
        enum { BoardWidth = 20, BoardHeight = 20 };

        int timeOutTime() { return 1000; }
        int squareWidth() { return contentsRect().width() / BoardWidth; }
        int squareHeight() { return contentsRect().height() / BoardHeight; }
        void drawCell(QPainter &painter, int x, int y);

        QBasicTimer timer;
};

#endif
