#ifndef _GAME_H_
#define _GAME_H_

#include <algorithm>
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
    int game_over()const;
    int get_chess(const Point &p)const;
    bool set_chess(const Point &p, const int player);
    bool unset_chess(const Point &p);
    Point search_move();

  private:
    int human,      // 玩家所执子
        bot,        // 机器所执子
        max_depth;  // 搜索的最大深度
    int chessBoard[GRID_NUM][GRID_NUM] = {0};     // 棋盘
    const int values[5] = {1000, 100, 10, 1, -1}; // 不同等级估值对应的分数

    bool in_board(const Point &p)const;
    vector <Point> create_moves() const;
    int evaluate(const Point &p) const;
    int evaluate() const;
    int get_neighbor(const Point &p, const int theta, const int rho)const ;

    int max_value(const int depth, int alpha, const int beta);
    int min_value(const int depth, const int alpha, int beta);
};

#endif