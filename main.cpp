#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Action.h"
#include "ChessBoard.h"
#include "EvalField.h"
#include "MCTree.h"

using namespace std;

int _nodeCnt = 0;
string _debug, _data, _globaldata;

//// BotZone 模式
//#ifdef _BOTZONE_ONLINE

int main() {
    srand((unsigned) time(nullptr));
/* 长时运行 */
    auto *board = new ChessBoard();
    auto *tree = new MCTree(*board);
    int turn;
    cin >> turn;
    Action act;
    auto timeLimit = int(1.98 * CLOCKS_PER_SEC);
    while (!board->isFinished()) {
        cin >> act;
        if (act.x0 != -1)board->doAction(act), tree->doAction(act);
        act = tree->getAction(timeLimit);
        cout << act << endl;
        cout << _debug << endl;
        cout << _data << endl;
        cout << _globaldata << endl;
        _debug = "";
        _data = "";
        _globaldata = "";
        cout << ">>>BOTZONE_REQUEST_KEEP_RUNNING<<<" << endl;
        board->doAction(act);
        tree->doAction(act);
        timeLimit = int(0.99 * CLOCKS_PER_SEC);
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
    cout << tree->getAction(timeLimit) << endl;
    cout << _debug << endl;
    cout << _data << endl;
    cout << _globaldata << endl;
//*/
    return 0;
}
//
//#else  // 本地模式
//
//class GameTable : public ChessBoard {
//public:
//    GameTable() : ChessBoard() {};
//
//    explicit GameTable(vector<Action> acts) : GameTable() {
//        for (auto act:acts)acts[++turn] = act;
//    }
//
//    int curTurn() {
//        return turn;
//    }
//
//    int curColor() {
//        return color;
//    }
//
//    int getGrid(int x, int y) {
//        return grid[x][y];
//    }
//
//};
//
//GameTable *table;
//
//int main(int argc, char **argv) {
//    srand((unsigned) time(nullptr));
//    MCTree::testTime();
////    QApplication ui(arsgc, argv);
////    QMainWindow win;
////    win.show();
////    return QApplication::exec();
//}
//
//#endif
//

/* Alternative
 * 1. 模拟跑完整局/跑若干局后调用估价函数/使用更快但不精确的估价函数/只取估价的正负号/考虑估价代表的优势大小
 * 2. 一个节点被访问若干次后才被扩展
 * 3. 选择下个节点时将局面的估价加入评估，权重随访问次数递减
 */