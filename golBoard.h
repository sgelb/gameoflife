#ifndef GOLBOARD_H
#define GOLBOARD_H

#include <QBasicTimer>
#include <QFrame>
#include <vector>


class GolBoard : public QFrame
{
    Q_OBJECT

    public:
        bool hasHeightForWidth() const { return true; }
        int heightForWidth( int w ) const { return w; }
        QSize minimumSizeHint() const;
        GolBoard(QWidget *parent = 0);
        QSize sizeHint() const;

    public slots:
        void pause();
        void populate();
        void reset();
        void setBoardSize(int w, int h);
        void setPopRatio(int ratio);
        void setTimeoutTime(int timeout);
        void start();

    signals:
        void changeLabel(QString, QString);
        void checkPauseBtn();

    protected:
        void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void paintEvent(QPaintEvent *event);
        void resizeEvent(QResizeEvent * event);
        void timerEvent(QTimerEvent *event);
        void wheelEvent(QWheelEvent *event);

    private:
        int boardHeight;
        int boardWidth;
        int cellsize;
        void drawCell(QPainter &painter, int x, int y);
        QList<int> grid;
        bool isPaused;
        void iterate();
        int iteration;
        QString iterationText;
        int neighbor_count(int);
        double popRatio;
        int timeoutTime;
        QBasicTimer timer;
        QList<int> tmp_grid;
};

#endif
