#include <iostream>
#include <fstream>
#include "GTree.h"

using namespace std;

int main() {
    auto *board = new ChessBoard();
    auto *tree = new GTree(*board);
    auto file = new ofstream();
    char c;
    while (cin >> c) {
        switch (c) {
            case 'w':
                int sec;
                cin >> sec;
                while (sec--) {
                    tree->work(CLOCKS_PER_SEC);
                    cout << sec << "s remaining" << endl;
                }
                break;
            case 'c':
                int vis;
                cin >> vis;
                cout << tree->count(vis) << endl;
                break;
            case 'p':
                int v;
                cin >> v;
                file->open("data/openingBook.data", ios::out);
                tree->output(*file, v);
                file->flush();
                file->close();
                break;
            case 'q':
                return 0;
            default:
                break;
        }
    }
    return 0;
}