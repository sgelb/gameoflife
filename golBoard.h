#ifndef GOLBOARD_H
#define GOLBOARD_H

#include <QBasicTimer>
#include <QFrame>
#include <vector>


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
        void setTimeoutTime(int timeout);
        void setPopRatio(int ratio);

    signals:
        void changeLabel(QString label, QString text);

    protected:
        void paintEvent(QPaintEvent *event);
        void timerEvent(QTimerEvent *event);

    private:
        enum { BoardWidth = 100, BoardHeight = 100, Cellsize = 8 };

        void drawCell(QPainter &painter, int x, int y);
        void iterate();
        int neighbor_count(int);

        QBasicTimer timer;
        QList<int> grid;
        QList<int> tmp_grid;
        QString iterationText;
        int seed;
        int iteration;
        double popRatio;
        bool isPaused;
        bool isStarted;
        int timeoutTime;
};

#endif
