#ifndef _GAME_H_
#define _GAME_H_

#include <algorithm>
#include <ctime>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

//点
struct Point {
    int x, y;
    Point() {}
    Point(int x0, int y0): x(x0), y(y0) {}
};


//棋盘
class Game {
  public:
    static const int OUT = -1,      // 超出边界
                     BLANK = 0,     // 空白点
                     BLACK = 1,     // 黑子
                     WHITE = 2,     // 白子
                     GRID_NUM = 15, // 棋盘规模
                     INF = 0x7ffffff;

    // 声明对象时需指定玩家是执黑子(1)还是白子(2)，并指定搜索的最大深度
    Game(const int human0, const int max_depth0): human(human0), bot(3 - human0), max_depth(max_depth0) {}
    int game_over(const Point &p)const;
    int get_chess(const Point &p)const;
    bool set_chess(const Point &p, const int player);
    bool unset_chess(const Point &p);
    Point search_move();
    void bot_first();

  private:
    int human,      // 玩家所执子
        bot,        // 机器所执子
        max_depth;  // 搜索的最大深度
    int chessBoard[GRID_NUM][GRID_NUM] = {0};     // 棋盘
    const int values[5] = {2000000, 20000, 200, 2,  -2000000}; // 不同等级估值对应的分数

    bool in_board(const Point &p)const;
    vector <Point> create_moves(const int player);
    int evaluate(const Point &p) const;
    int evaluate(const int nextPlayer) const;
    int evaluate_priority(const Point &p) const;
    int get_neighbor(const Point &p, const int theta, const int rho)const ;

    int max_value(const int depth, const Point &p0, int alpha, const int beta);
    int min_value(const int depth, const Point &p0, const int alpha, int beta);
};

#endif
