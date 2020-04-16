#include "Game.h"

// 生成全部合法走法集
vector <Point> Game::create_moves(const int player)  {
    struct Moves {
        Point p;
        int value;
        Moves(const Point &p0, const int value0): p(p0), value(value0) {}
        bool operator < (const Moves &m) const {
            return value < m.value;
        }
    };

    vector <Point> moves;
    priority_queue<Moves> q;

    for (int i = 0; i < GRID_NUM; ++i) {
        for (int j = 0; j < GRID_NUM; ++j) {
            if (!chessBoard[i][j]) {
                Point p(i, j);
                bool candidate = false;
                for (int k = 1; k <= 4; ++k) {
                    // 只筛选出现有棋子周围的点作为落点，排除落子太远的情况，减小搜索空间
                    if (get_neighbor(p, k, 1) > 0 || get_neighbor(p, k, -1) > 0) {
                        candidate = true;
                        break;
                    }
                }
                if (candidate) {
                    // 计算候选落点的估值，加入优先队列，优先搜索估值较大的落点
                    set_chess(p, player);
                    int value = evaluate_priority(p);
                    q.push(Moves(p, value));
                    unset_chess(p);
                    //                    moves.push_back(p);
                }
            }
        }
    }
    while (!q.empty()) {
        moves.push_back(q.top().p);
        q.pop();
    }
    return moves;
}
