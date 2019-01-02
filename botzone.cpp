#include <iostream>
#include <fstream>
#include <ctime>
#include "common/Logger.h"
#include "bot/OpeningBook.h"
#include "common/Action.h"
#include "bot/Bot.h"

using namespace std;

int main() {
    srand((unsigned) time(nullptr));
/* 长时运行 */
    ifstream bookData("data/openingBook5_5000*7930.data", ios::in);
    auto *bot = new Bot();
    bookData.close();
    int turn;
    cin >> turn;
    Action act;
    double timeLimit = 2;
    while (!bot->getBoard().isFinished()) {
        cin >> act;
        if (act.x0 != -1) bot->doAction(act);
        act = bot->getAction(timeLimit);
        cout << act << endl;
        cout << Logger::debug << endl;
        cout << Logger::data << endl;
        cout << Logger::globaldata << endl;
        Logger::clear();
        cout << ">>>BOTZONE_REQUEST_KEEP_RUNNING<<<" << endl;
        bot->doAction(act);
        timeLimit = 1;
    }
//*/
/* 单回合
    int turn;
    cin >> turn;
    Action act;
    double timeLimit = 2;
    cin >> act;
    ifstream bookData("data/openingBook5_5000*7930.data", ios::in);
    auto *bot = new Bot();
    bookData.close();
    if (act.x0 != -1)bot->doAction(act);
    for (int i = 1; i < turn; ++i) {
        cin >> act;
        bot->doAction(act);
        cin >> act;
        bot->doAction(act);
        timeLimit = 1;
    }
        cout << bot->getAction(timeLimit) << endl;
        cout << Logger::debug << endl;
        cout << Logger::data << endl;
        cout << Logger::globaldata << endl;
        Logger::clear();
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