#include "Game.h"

// 返回下一步机器下棋的位置

int cnt1, cnt2;
Point Game::search_move() {
    cnt1 = cnt2 = 0;
    int value = INF, alpha = -INF, beta = INF;
    Point nextPoint;

    vector <Point> moves = create_moves(bot);
    const int movesSize = moves.size();
    for (int i = 0; i < movesSize; ++i) {
        set_chess(moves[i], bot);
        int res = max_value(1, moves[i], alpha, beta);
        if (res < value) {
            value = res;
            nextPoint = moves[i];
        }
        beta = min(beta, value);
        unset_chess(moves[i]);
    }
    //     cout << cnt1 << " " << cnt2 << endl;
    //    cout << value << endl;
    return nextPoint;
}

int Game::max_value(const int depth, const Point &p0, int alpha, const int beta) {
    ++cnt1;
    int gameOver = game_over(p0);
    if (gameOver) {
        if (gameOver == human) {
            return values[0];
        }
        else {
            return values[4];
        }
    }
    if (depth >= max_depth) {
        ++cnt2;
        return evaluate(human);
    }

    int value = -INF;
    vector <Point> moves = create_moves(human);
    const int movesSize = moves.size();
    for (int i = 0; i < movesSize; ++i) {
        set_chess(moves[i], human);
        value = max(value, min_value(depth + 1, moves[i], alpha, beta));
        if (value >= beta) {
            unset_chess(moves[i]);
            return value;
        }
        alpha = max(alpha, value);
        unset_chess(moves[i]);
    }
    return value;
}

int Game::min_value(const int depth, const Point &p0, const int alpha, int beta) {
    ++cnt1;
    int gameOver = game_over(p0);
    if (gameOver) {
        if (gameOver == human) {
            return values[0];
        }
        else {
            return values[4];
        }
    }
    if (depth >= max_depth) {
        ++cnt2;
        return evaluate(bot);
    }

    int value = INF;
    vector <Point> moves = create_moves(bot);
    const int movesSize = moves.size();
    for (int i = 0; i < movesSize; ++i) {
        set_chess(moves[i], bot);
        value = min(value, max_value(depth + 1, moves[i], alpha, beta));
        if (value <= alpha) {
            unset_chess(moves[i]);
            return value;
        }
        beta = min(beta, value);
        unset_chess(moves[i]);
    }
    return value;
}
