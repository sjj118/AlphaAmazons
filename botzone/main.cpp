#include <iostream>
#include <fstream>
#include <ctime>
#include "Logger.h"
#include "OpeningBook.h"
#include "Action.h"
#include "Bot.h"

using namespace std;

int main() {
    srand((unsigned) time(nullptr));
/* 长时运行 */
    auto *board = new ChessBoard();
    ifstream bookData("data/openingBook.data", ios::in);
    auto *book = new OpeningBook(bookData);
    bookData.close();
    auto *bot = new Bot(*board, *book);
    int turn;
    cin >> turn;
    Action act;
    double timeLimit = 1.98;
    while (!board->isFinished()) {
        cin >> act;
        if (act.x0 != -1)board->doAction(act), bot->doAction(act);
        act = bot->getAction(timeLimit);
        cout << act << endl;
        cout << Logger::debug << endl;
        cout << Logger::data << endl;
        cout << Logger::globaldata << endl;
        Logger::clear();
        cout << ">>>BOTZONE_REQUEST_KEEP_RUNNING<<<" << endl;
        board->doAction(act);
        bot->doAction(act);
        timeLimit = 0.99;
    }
//*/
/* 单回合
    int turn;
    cin >> turn;
    Action act;
    int timeLimit = int(1.98 * CLOCKS_PER_SEC);
    cin >> act;
    auto *board = new ChessBoard();
    if (act.x0 != -1)board->doAction(act);
    for (int i = 1; i < turn; ++i) {
        cin >> act;
        board->doAction(act);
        cin >> act;
        board->doAction(act);
        timeLimit = int(0.99 * CLOCKS_PER_SEC);
    }
    auto *tree = new MCTree(*board);
    while (true) {
        cout << tree->getAction(timeLimit) << endl;
        cout << _debug << endl;
        cout << _data << endl;
        cout << _globaldata << endl;
        _debug = "";
        _data = "";
        _globaldata = "";
    }
//*/
    return 0;
}


/* Alternative
 * 1. 使用更快但不精确的估价函数/只取估价的正负号/考虑估价代表的优势大小
 * 2. 一个节点被访问若干次后才被扩展
 * 3. 伪随机
 * 4. 论文 refinement 5
 * 5. 位运算
 */