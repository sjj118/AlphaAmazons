import codecs
import os
import re

src = ["common/Action.h", "common/ChessBoard.h", "common/ChessBoard.cpp", "common/Logger.h", "common/Logger.cpp",
       "control/Player.h", "bot/OpeningBook.h", "bot/OpeningBook.cpp", "bot/EvalField.h", "bot/EvalField.cpp",
       "bot/MCTree.h", "bot/MCTree.cpp", "bot/Bot.h", "bot/Bot.cpp", "botzone.cpp"]

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
