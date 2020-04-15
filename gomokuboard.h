#ifndef GOMOKUBOARD_H
#define GOMOKUBOARD_H

#include "Game.h"

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class GomokuBoard;
}

class GomokuBoard : public QWidget
{
    Q_OBJECT

public:
    enum GameState { GAME, END };
    explicit GomokuBoard(QWidget *parent = nullptr);
    ~GomokuBoard();
    void start(int human, int max_depth);
    void reset();
    GameState getState() const { return state; }

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent* event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::GomokuBoard *ui;

    GameState state;

    Game* game;

    int human;

    int width;
    int height;
    bool choice; // 0 horizontal, 1 vertical

    int margin;
    int padding;
    int blockCnt;
    int blockSize;

    int leftBorder;
    int rightBorder;
    int topBorder;
    int bottomBorder;

    void updateParams();
};

#endif // GOMOKUBOARD_H
