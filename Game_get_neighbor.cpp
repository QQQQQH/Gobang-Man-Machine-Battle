#include "Game.h"


/*
    返回以p为原点，theta方向距离为rho的点坐标
    theta=1~4，从正右方开始，顺时针旋转
    若不在棋盘内则返回-1
*/
int Game::get_neighbor(const Point &p, const int theta, const int rho)const {
    int x = p.x, y = p.y;
    switch (theta) {
    case 1 :
        x = x + rho;
        break;
    case 2 :
        x = x + rho;
        y = y + rho;
        break;
    case 3 :
        y = y + rho;
        break;
    case 4 :
        x = x - rho;
        y = y + rho;
        break;
    }
    return in_board(p) ? chessBoard[x][y] : OUT;
}
