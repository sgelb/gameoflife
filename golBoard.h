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
        void clear();
        void pause();
        void populate();
        void setBoardSize(int w, int h);
        void setPopRatio(int ratio);
        void setTimeoutTime(int timeout);
        void start();

    signals:
        void changeLabel(QString label, QString text);
        void checkPauseBtn();

    protected:
        void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void paintEvent(QPaintEvent *event);
        void resizeEvent(QResizeEvent * event);
        void timerEvent(QTimerEvent *event);
        void wheelEvent(QWheelEvent *event);

    private:
        void drawCell(QPainter &painter, int x, int y);
        void iterate();
        int neighbor_count(int);

        int cellsize;
        QList<int> grid;
        int height;
        bool isPaused;
        int iteration;
        QString iterationText;
        double popRatio;
        int timeoutTime;
        QBasicTimer timer;
        QList<int> tmp_grid;
        int width;
};

#endif
