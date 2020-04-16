#include "Game.h"

#include <random>

// 判断游戏是否结束，若结束则返回获胜方编号，否则返回0
int Game::game_over(const Point &p) const {
    int chessP = chessBoard[p.x][p.y];
    for (int i = 1; i <= 4; ++i) {
        int cnt = 1;
        for (int j = 1; j <= 4; ++j) {
            if (get_neighbor(p, i, j) != chessP) {
                break;
            }
            ++cnt;
        }
        if (cnt >= 5) {
            return chessP;
        }
        for (int j = 1; j <= 4; ++j) {
            if (get_neighbor(p, i, -j) != chessP) {
                break;
            }
            if (++cnt >= 5) {
                return chessP;
            }
        }
    }
    return 0;
}

// 返回p位置的棋子，若p位置超出边界则返回-1
int Game::get_chess(const Point &p) const {
    if (!in_board(p)) {
        return OUT;
    }
    return chessBoard[p.x][p.y];
}

// player在p位置下棋，如果p位置超出边界或已有棋子则返回false，成功下棋则返回true
bool Game::set_chess(const Point &p, const int player) {
    if (get_chess(p)) {
        return false;
    }
    chessBoard[p.x][p.y] = player;
    return true;
}

// 删除p位置的棋子，如果p位置超出边界则返回false，成功删除则返回true
bool Game::unset_chess(const Point &p) {
    if (!in_board(p)) {
        return false;
    }
    chessBoard[p.x][p.y] = BLANK;
    return true;
}


// 返回p是否在棋盘内
bool Game::in_board(const Point &p) const {
    return p.x >= 0 && p.x < GRID_NUM && p.y >= 0 && p.y < GRID_NUM;
}



void Game::bot_first() {
    default_random_engine e; //默认随机数引擎
    e.seed((unsigned int)time(0));
    uniform_int_distribution<unsigned> u(0, (GRID_NUM - 1) / 3);
    set_chess(Point((GRID_NUM - 1) / 3 + u(e), (GRID_NUM - 1) / 3 + u(e)), bot);
}
