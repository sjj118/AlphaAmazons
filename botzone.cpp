#include <iostream>
#include <fstream>
#include <ctime>
#include "common/Logger.h"
#include "common/Action.h"
#include "bot/Bot.h"

using namespace std;

int main() {
    srand(20000107);
/* 长时运行 */
#ifdef _BOTZONE_ONLINE
    auto *bot = new Bot();
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
/* 单回合 */
#else
    int turn;
    cin >> turn;
    Action act;
    double timeLimit = 2;
    cin >> act;
    auto *bot = new Bot();
    if (act.x0 != -1)bot->doAction(act);
    for (int i = 1; i < turn; ++i) {
        cin >> act;
        bot->doAction(act);
        cin >> act;
        bot->doAction(act);
        timeLimit = 1;
    }
    while (true) {
        cout << bot->getAction(timeLimit) << endl;
        cout << Logger::debug << endl;
        cout << Logger::data << endl;
        cout << Logger::globaldata << endl;
        Logger::clear();
    }
#endif
//*/
    return 0;
}