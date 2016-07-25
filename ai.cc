#include "ai.h"
#include "board.h"

AI::AI() {}

AI::~AI() {}

void AI::makeMove();
void AI::openingMove();
void AI::moveLevel1();
void AI::moveLevel2();
void AI::moveLevel3();
void AI::moveLevel4();
int AI::value(ChessPiece *p);
