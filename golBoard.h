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

    signals:
        void changeLabel(QString label, QString text);

    protected:
        void paintEvent(QPaintEvent *event);
        void timerEvent(QTimerEvent *event);

    private:
        enum { BoardWidth = 100, BoardHeight = 100, Cellsize = 5 };

        int timeoutTime() { return 500; }
        void drawCell(QPainter &painter, int x, int y);
        void iterate();
        int neighbor_count(int);

        QBasicTimer timer;
        QList<int> grid;
        QString iterationText;
        int seed;
        int iteration;
        bool isPaused;
        bool isStarted;
};

#endif
