import codecs
import os
import re

src_dir = "botzone/"

src = ["Action.h", "ChessBoard.h", "EvalField.h", "MCTree.h", "OpeningBook.h", "Player.h", "Bot.h", "Logger.h",
       "ChessBoard.cpp", "EvalField.cpp", "MCTree.cpp", "OpeningBook.cpp", "Bot.cpp", "Logger.cpp", "main.cpp"]
src = [src_dir + x for x in src]

lines = []
for filename in src:
    assert (os.path.isfile(filename))
    fobj = codecs.open(filename, "r", "utf-8")
    lines += fobj.readlines()
    lines[-1] += "\n"
    fobj.close()

lines = "".join(lines)

# suppress redundant include header macros
lines = re.sub(r"\s*#include *\"(?!json).*\".*\n", "\n", lines)

target = "AlphaAmazons.cpp"

fobj = codecs.open(target, "w", "utf-8")
fobj.writelines(lines)
fobj.close()
