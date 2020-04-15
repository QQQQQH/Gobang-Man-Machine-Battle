#include "Game.h"

// 返回以p点出发，右，下，右下，左下方的估值
int Game::evaluate(const Point &p) const {
    int value = 0;
    const int chessP = chessBoard[p.x][p.y];
    for (int i = 1; i <= 4; ++i) {
        // 如果不是第一个连点就不计算
        if (get_neighbor(p, i, -1) == chessP) {
            continue;
        }

        // 从前2两格到后4格读取临近的棋子
        // 1表示棋子与p位置的棋子相同，0表示空，2表示棋子不同或超出边界
        string chessLain = "";
        for (int j = -2; j <= 4; ++j) {
            if (!j) {
                chessLain += "1";
            }
            else {
                int neighbor = get_neighbor(p, i, j);
                chessLain += neighbor == 0 ? "0" : (neighbor == chessP ? "1" : "2");
            }
        }
        string chessLain05 = chessLain.substr(0, 5),
               chessLain06 = chessLain.substr(0, 6),
               chessLain15 = chessLain.substr(1, 5),
               chessLain16 = chessLain.substr(1, 6),
               chessLain25 = chessLain.substr(2, 5);

        // 活四
        if (chessLain16 == "011110") {
            value += values[1];
            continue;
        }

        // 冲四
        if (chessLain15 == "01111" || chessLain25 == "10111" || chessLain25 == "11011" ||
            chessLain25 == "11101" || chessLain25 == "11110") {
            value += values[2];
            continue;
        }

        // 活三
        if (chessLain06 == "001110" || chessLain16 == "010110" ||
            chessLain16 == "011010" || chessLain16 == "011100") {
            value += values[2];
            continue;
        }

        // 眠三

        // 00111
        // 01011
        // 01101
        // 01110
        // 10011
        // 10101
        // 10110
        // 11001
        // 11010
        // 11100

        if (chessLain05 == "00111" || chessLain15 == "01011" ||
            chessLain15 == "01101" || chessLain15 == "01110" ||
            chessLain25 == "10011" || chessLain25 == "10101" ||
            chessLain25 == "10110" || chessLain25 == "11001" ||
            chessLain25 == "11010" || chessLain25 == "11100") {
            value += values[3];
            continue;
        }
    }
    return value;
}

// 返回整个棋盘的估值之和（估值越大对于human越有利）
int Game::evaluate() const {
    int value = 0;
    for (int i = 0; i < GRID_NUM; ++i) {
        for (int j = 0; j < GRID_NUM; ++j) {
            const int chessP = chessBoard[i][j];
            if (chessP) {
                const Point p(i, j);
                int valueP = evaluate(p);
                if (chessP == human) {
                    value += valueP;
                }
                else {
                    value -= valueP / 2;
                }
            }
        }
    }
    return value;

    //由于五子棋搜索分支庞大，通常无法直接搜索到胜负终局，当搜索到一定深度时需要根据局面返回搜索结果。
    //参考资料：
    //张明亮, 吴俊, 李凡长. 五子棋机器博弈系统评估函数的设计[J]. 计算机应用, 2012, 32(07):1969-1972.
    //裴博文. 五子棋人工智能权重估值算法[J]. 电脑编程技巧与维护, 2008(6):69-75.
    //https://www.cnblogs.com/maxuewei2/p/4825520.html
}
