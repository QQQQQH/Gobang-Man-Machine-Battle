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

        int t[7];
        for (int j = -2; j <= 4; ++j) {
            if (!j) {
                t[j + 2] = 1;
            }
            else {
                int neighbor = get_neighbor(p, i, j);
                t[j + 2] = neighbor == 0 ? 0 : (neighbor == chessP ? 1 : 2);
            }
        }

        // 连五

        // 11111

        if (t[3] == 1 && t[4] == 1 && t[5] == 1 && t[6] == 1) {
            value += values[0];
            continue;
        }

        // 活四

        // 011110

        if (t[1] == 0 && t[3] == 1 && t[4] == 1 && t[5] == 1 && t[6] == 0) {
            value += values[1];
            continue;
        }

        // 冲四

        // 01111
        // 10111
        // 11011
        // 11101
        // 11110

        if (t[1] == 0 && t[3] == 1 && t[4] == 1 && t[5] == 1 ||
            t[3] == 0 && t[4] == 1 && t[5] == 1 && t[6] == 1 ||
            t[3] == 1 && t[4] == 0 && t[5] == 1 && t[6] == 1 ||
            t[3] == 1 && t[4] == 1 && t[5] == 0 && t[6] == 1 ||
            t[3] == 1 && t[4] == 1 && t[5] == 1 && t[6] == 0) {
            value += values[2];
            continue;
        }

        // 活三

        // 001110
        // 010110
        // 011010
        // 011100

        if (t[0] == 0 && t[1] == 0 && t[3] == 1 && t[4] == 1 && t[5] == 0) {
            value += values[2];
            continue;
        }
        else if (t[1] == 0) {
            if (t[3] == 0 && t[4] == 1 && t[5] == 1 && t[6] == 0 ||
                t[3] == 1 && t[4] == 0 && t[5] == 1 && t[6] == 0 ||
                t[3] == 1 && t[4] == 1 && t[5] == 0 && t[6] == 0) {
                value += values[2];
                continue;
            }
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

        if (t[0] == 0 && t[1] == 0  && t[3] == 1 && t[4] == 1) {
            value += values[3];
            continue;
        }
        else if (t[1] == 0) {
            if (t[3] == 0 && t[4] == 1 && t[5] == 1 ||
                t[3] == 1 && t[4] == 0 && t[5] == 1 ||
                t[3] == 1 && t[4] == 1 && t[5] == 0) {
                value += values[3];
                continue;
            }
        }
        else if (t[3] == 0) {
            if (t[4] == 0 && t[5] == 1 && t[6] == 1 ||
                t[4] == 1 && t[5] == 0 && t[6] == 1 ||
                t[4] == 1 && t[5] == 1 && t[6] == 0) {
                value += values[3];
                continue;
            }
            else if (t[3] == 1) {
                if (t[4] == 0 && t[5] == 0 && t[6] == 1 ||
                    t[4] == 0 && t[5] == 1 && t[6] == 0 ||
                    t[4] == 1 && t[5] == 0 && t[6] == 0) {
                    value += values[3];
                    continue;
                }
            }
        }

        // 活2

        // 0110

        if (t[1] == 0 && t[3] == 1 && t[4] == 0) {
            value += values[3];
            continue;
        }
    }
    return value;
}

// 返回整个棋盘的估值之和（估值越大对于nextPlayer越有利）
int Game::evaluate(const int nextPlayer) const {
    int value = 0;
    for (int i = 0; i < GRID_NUM; ++i) {
        for (int j = 0; j < GRID_NUM; ++j) {
            const int chessP = chessBoard[i][j];
            if (chessP) {
                const Point p(i, j);
                int valueP = evaluate(p);
                if (chessP == nextPlayer) {
                    value += valueP;
                }
                else {
                    value -= valueP / 2;
                }
            }
        }
    }
    return value;
}

// 评估在p点落子以后，在p点附近的估值，越大对落子方越有利
int Game::evaluate_priority(const Point &p) const {
    int value = 0, left = 4, right = 4;
    const int chessP = chessBoard[p.x][p.y];
    for (int i = 1; i <= 4; ++i) {
        int cnt = 1;
        int t[9];
        bool link = true;
        for (int j = 1; j <= 4; ++j) {
            int neighbor = get_neighbor(p, i, -j);
            t[4 - j] = neighbor == 0 ? 0 : (neighbor == chessP ? 1 : 2);
            if (link) {
                if (t[4 - j] != 1) {
                    left = 4 - j + 1;
                    link = false;
                }
                else {
                    ++cnt;
                }
            }
        }
        if (cnt >= 5) {
            value += values[0];
            continue;
        }

        link = true;
        for (int j = 1; j <= 4; ++j) {
            int neighbor = get_neighbor(p, i, j);
            t[4 + j] = neighbor == 0 ? 0 : (neighbor == chessP ? 1 : 2);
            if (link) {
                if (t[4 + j] != 1) {
                    right = 4 + j - 1;
                    link = false;
                }
                else {
                    ++cnt;
                }
            }
        }
        if (cnt >= 5) {
            value += values[0];
            continue;
        }

        switch (cnt) {
        case 1:
            if (t[3] == 0) {
                if (t[2] == 1 && t[1] == 1 && t[0] == 1) {
                    value += values[2];
                    break;
                }
            }
            if (t[5] == 0) {
                if (t[6] == 1 && t[7] == 1 && t[8] == 1) {
                    value += values[2];
                    break;
                }
                if (t[3] == 0) {
                    if (t[6] == 1 && t[7] == 1 && t[8] == 0 ||
                        t[2] == 1 && t[1] == 1 && t[0] == 0) {
                        value += values[2];
                        break;
                    }
                }
            }
        case 2:
            if (t[left - 1] == 0) {
                if (t[left - 2] == 1 && t[left - 3] == 1 ||
                    t[left - 2] == 1 && t[left - 3] == 0 && t[right + 1] == 0) {
                    value += values[2];
                    break;
                }
            }
            if (t[right + 1] == 0) {
                if (t[right + 2] == 1 && t[right + 3] == 1 ||
                    t[right + 2] == 1 && t[right + 3] == 0 && t[left - 1] == 0) {
                    value += values[2];
                    break;
                }
            }
        case 3:
            if (t[left - 1] == 0 && t[left - 2] == 1 ||
                t[right + 1] == 0 && t[right + 2] == 1) {
                value += values[2];
                break;
            }
            if (t[left - 1] == 0 && t[left - 2] == 0 && t[right + 1] == 0 ||
                t[right + 1] == 0 && t[right + 2] == 0 && t[left - 1] == 0) {
                value += values[2];
                break;
            }
        case 4:
            if (t[left - 1] == 0 || t[right + 1] == 0) {
                if (t[left - 1] == 0 && t[right + 1] == 0) {
                    value += values[1];
                    break;
                }
                value += values[2];
                break;
            }
        }
    }
    return value;
}
