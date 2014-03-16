#ifndef GOLBOARD_H
#define GOLBOARD_H

#include <QBasicTimer>
#include <QFrame>

class GolBoard : public QFrame
{
    Q_OBJECT

    public:
        GolBoard(QWidget *parent = 0);
        QSize sizeHint() const;
        QSize minimumSizeHint() const;

    public slots:
        void start();
        void pause();
        void populate();
        void clear();

    protected:
        void paintEvent(QPaintEvent *event);
        void timerEvent(QTimerEvent *event);

    private:
        enum { BoardWidth = 100, BoardHeight = 100, Cellsize = 5 };

        /* int squareWidth() { return contentsRect().width() / BoardWidth; } */
        /* int squareHeight() { return contentsRect().height() / BoardHeight; } */
        int timeoutTime() { return 1000; }
        void drawCell(QPainter &painter, int x, int y);

        QBasicTimer timer;
        bool isPaused;
        bool isStarted;
};

#endif
