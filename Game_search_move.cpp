#include "Game.h"

// 返回下一步机器下棋的位置
Point Game::search_move() {
    int value = INF, alpha = -INF, beta = INF;
    Point nextPoint;

    vector <Point> moves = create_moves();
    const int movesSize = moves.size();
    for (int i = 0; i < movesSize; ++i) {
        set_chess(moves[i], bot);
        int res = max_value(1, alpha, beta);
        if (res < value) {
            value = res;
            nextPoint = moves[i];
        }
        beta = min(beta, value);
        unset_chess(moves[i]);
    }
    return nextPoint;
}

int Game::max_value(const int depth, int alpha, const int beta) {
    int gameOver = game_over();
    if (gameOver) {
        if (gameOver == human) {
            return values[0];
        }
        else {
            return values[4];
        }
    }
    if (depth >= max_depth) {
        return evaluate();
    }

    int value = -INF;
    vector <Point> moves = create_moves();
    const int movesSize = moves.size();
    for (int i = 0; i < movesSize; ++i) {
        set_chess(moves[i], human);
        value = max(value, min_value(depth + 1, alpha, beta));
        if (value >= beta) {
            unset_chess(moves[i]);
            return value;
        }
        alpha = max(alpha, value);
        unset_chess(moves[i]);
    }
    return value;
}

int Game::min_value(const int depth, const int alpha, int beta) {
    int gameOver = game_over();
    if (gameOver) {
        if (gameOver == human) {
            return values[0];
        }
        else {
            return values[4];
        }
    }
    int value = INF;
    vector <Point> moves = create_moves();
    const int movesSize = moves.size();
    for (int i = 0; i < movesSize; ++i) {
        set_chess(moves[i], bot);
        value = min(value, max_value(depth + 1, alpha, beta));
        if (value <= alpha) {
            unset_chess(moves[i]);
            return value;
        }
        beta = min(beta, value);
        unset_chess(moves[i]);
    }
    return value;
}
