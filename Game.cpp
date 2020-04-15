#include "Game.h"

#include <random>

// 判断游戏是否结束，若结束则返回获胜方编号，否则返回0
int Game::game_over() const {
    for (int i = 0; i < GRID_NUM; ++i) {
        for (int j = 0; j < GRID_NUM; ++j) {
            const Point p(i, j);
            const int chessP = chessBoard[i][j];
            for (int k = 1; k <= 4; ++k) {
                // 依次判断右，右下，下，左下方是否五子连棋
                if (chessP == get_neighbor(p, k, 1) && chessP == get_neighbor(p, k, 2) &&
                    chessP == get_neighbor(p, k, 3) && chessP == get_neighbor(p, k, 4)) {
                    return chessP;
                }
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

// 生成全部合法走法集
vector <Point> Game::create_moves() const {
    vector <Point> moves;
    for (int i = 0; i < GRID_NUM; ++i) {
        for (int j = 0; j < GRID_NUM; ++j) {
            if (!chessBoard[i][j]) {
                moves.push_back(Point(i, j));
            }
        }
    }
    return moves;
}

void Game::bot_first() {
    default_random_engine e; //默认随机数引擎
    e.seed((unsigned int)time(0));
    uniform_int_distribution<unsigned> u(0, (GRID_NUM-1)/3);
    set_chess(Point((GRID_NUM-1)/3+u(e), (GRID_NUM-1)/3+u(e)), bot);
}
