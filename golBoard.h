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
        int heightForWidth( int w ) const { return w; }
        bool hasHeightForWidth() const { return true; }

    public slots:
        void start();
        void pause();
        void populate();
        void clear();
        void setTimeoutTime(int timeout);
        void setPopRatio(int ratio);
        void setBoardSize(int w, int h);

    signals:
        void changeLabel(QString label, QString text);
        void checkPauseBtn();

    protected:
        void paintEvent(QPaintEvent *event);
        void timerEvent(QTimerEvent *event);
        void resizeEvent(QResizeEvent * event);

    private:
        /* enum { BoardWidth = 100, BoardHeight = 100, Cellsize = 5 }; */

        void drawCell(QPainter &painter, int x, int y);
        void iterate();
        int neighbor_count(int);

        int height;
        int width;
        int cellsize;
        QBasicTimer timer;
        QList<int> grid;
        QList<int> tmp_grid;
        QString iterationText;
        int iteration;
        double popRatio;
        bool isPaused;
        int timeoutTime;
};

#endif
