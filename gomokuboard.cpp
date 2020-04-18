#include "gomokuboard.h"
#include "ui_gomokuboard.h"

#include <QPainter>
#include <QDebug>

GomokuBoard::GomokuBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GomokuBoard),
    state(END),
    game(nullptr),
    human(1),
    margin(10),
    padding(10),
    blockCnt(16) {
    ui->setupUi(this);

    setEnabled(false);

    updateParams();
}

GomokuBoard::~GomokuBoard() {
    delete ui;

    if (game) {
        delete game;
    }
}

void GomokuBoard::updateParams() {
    width = size().width();
    height = size().height();

    choice = width > height;

    blockSize = ((choice ? height : width) - 2 * margin - 2 * padding) / blockCnt;

    leftBorder = (width - 2 * margin - 2 * padding - blockCnt * blockSize) / 2;
    rightBorder = width - leftBorder;
    topBorder = (height - 2 * margin - 2 * padding - blockCnt * blockSize) / 2;
    bottomBorder = height - topBorder;

}

void GomokuBoard::resizeEvent(QResizeEvent *event) {
    updateParams();
}

void GomokuBoard::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 绘制棋盘
    painter.drawPixmap(leftBorder, topBorder,
                       blockCnt * blockSize + 2 * margin + 2 * padding,
                       blockCnt * blockSize + 2 * margin + 2 * padding,
                       QPixmap("://image/board"));

    painter.setPen(QPen(Qt::black));

    painter.drawRect(leftBorder + margin, topBorder + margin,
                     blockCnt * blockSize + 2 * padding, blockCnt * blockSize + 2 * padding);

    // 绘制网格
    for (int i = 0; i < blockCnt + 1; i++) {
        int horizontalPos = leftBorder + margin + padding + i * blockSize;
        int verticalPos = topBorder + margin + padding + i * blockSize;
        painter.drawLine(leftBorder + margin + padding, verticalPos,
                         rightBorder - margin - padding - 1, verticalPos);
        painter.drawLine(horizontalPos, topBorder + margin + padding,
                         horizontalPos, bottomBorder - margin - padding - 1);
    }

    // 绘制棋子
    if (state != GAME) {
        return;
    }
    for (int i = 0; i < blockCnt - 1; i++) {
        for (int j = 0; j < blockCnt - 1; j++) {
            int piece = game->get_chess(Point(i, j));
            if (piece > 0) {
                int pieceSize = blockSize;
                painter.drawPixmap(leftBorder + margin + padding + (i + 1)*blockSize - pieceSize / 2,
                                   topBorder + margin + padding + (j + 1)*blockSize - pieceSize / 2,
                                   pieceSize,
                                   pieceSize,
                                   QPixmap("://image/" + QString::number(piece)));
            }


        }
    }
}

/*
 * 计算距离鼠标点击位置最近的落子点，并在此落子
 */
void GomokuBoard::mouseReleaseEvent(QMouseEvent *event) {
    if (state != GAME) {
        return;
    }

    // 边缘不能落子
    if (event->x() - leftBorder - margin - padding - blockSize / 2 <= 0 ||
        event->y() - topBorder - margin - padding - blockSize / 2 <= 0 ||
        event->x() - rightBorder + margin + padding + blockSize / 2 >= 0 ||
        event->y() - bottomBorder + margin + padding + blockSize / 2 >= 0) {
        return;
    }

    int xPos = event->x() - leftBorder - margin - padding - blockSize;
    int yPos = event->y() - topBorder - margin - padding - blockSize;

    int x = xPos / blockSize + (xPos % blockSize > blockSize / 2);
    int y = yPos / blockSize + (yPos % blockSize > blockSize / 2);

    if (game->set_chess(Point(x, y), human)) {
        update();
        int result = game->game_over(Point(x, y));
        if (result) {
            emit gameOver(result);
            reset();
            return;
        }

        Point p = game->search_move();
        if (!game->set_chess(p, 3 - human)) {
            game->unset_chess(Point(x, y));
        }
        update();
        result = game->game_over(p);
        if (result) {
            emit gameOver(result);
            reset();
            return;
        }
    }
}

void GomokuBoard::start(int human0, int max_depth) {
    if (game) {
        delete game;
    }
    human = human0;
    game = new Game(human, max_depth);
    state = GAME;
    setEnabled(true);
    if (human == 2) {
        game->bot_first();
        update();
    }
}

void GomokuBoard::reset() {
    state = END;
    if (game) {
        delete game;
    }
    game = nullptr;
    setEnabled(false);
    update();
}

