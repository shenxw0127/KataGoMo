#include "../game/gamelogic.h"

/*
 * gamelogic.cpp
 * Logics of game rules
 * Some other game logics are in board.h/cpp
 *
 * Gomoku as a representive
 */

#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>
#include <numeric>    // For std::iota (potentially, or manual loops)
#include <set>        // Though not strictly needed for the final version of isSymmetric

using namespace std;


// --- Assume previous definitions for Board, Loc, Player, Color, Location namespace ---
// Minimal forward declarations if not fully included:
// typedef short Loc;
// typedef int8_t Color;
// typedef int8_t Player;
// static constexpr Color C_EMPTY = 0; // Example
// static constexpr int MAX_ARR_SIZE = 20*20; // Example, ensure it's large enough
// struct Board {
//     int x_size; int y_size; Color colors[MAX_ARR_SIZE];
//     Board(int x=0, int y=0): x_size(x), y_size(y) {}
//     bool isOnBoard(Loc l) const { /* ... */ return false; }
// };
// namespace Location {
//   int getX(Loc l, int xs) { return 0; }
//   int getY(Loc l, int xs) { return 0; }
//   Loc getLoc(int x, int y, int xs) { return 0; }
//   void getAdjacentOffsets(short adj_offsets[8], int x_size) { /* ... */ }
// }
// --- End of assumed definitions ---






bool isQueenMove(const Board& board,Loc locSrc, Loc locDst)
{
    if (!board.isOnBoard(locSrc))return false;
    if (!board.isOnBoard(locDst))return false;
    if(board.colors[locSrc]==C_EMPTY)return false;
    if(board.colors[locDst]!=C_EMPTY)return false;
    if (locSrc == locDst)return false;

    int x1 = Location::getX(locSrc, board.x_size);
    int y1 = Location::getY(locSrc, board.x_size);
    int x2 = Location::getX(locDst, board.x_size);
    int y2 = Location::getY(locDst, board.x_size);
    int dx = x2 - x1, dy = y2 - y1;

    if (dx != 0 && dy != 0 && dx != dy && dx != -dy)
        return false;

    int d = std::max(std::max(dx, -dx), std::max(dy, -dy));

    if (dx > 0)dx = 1;
    else if (dx < 0)dx = -1;
    if (dy > 0)dy = 1;
    else if (dy < 0)dy = -1;

    for (int i = 1; i < d; i++)
    {
        int x = x1 + i * dx;
        int y = y1 + i * dy;
        Loc loc = Location::getLoc(x, y, board.x_size);
        if (board.colors[loc] != C_EMPTY)
            return false;
    }
    return true;
}
bool GameLogic::isLegal(const Board& board, Player pla, Loc loc) {
    if (pla != board.nextPla)
    {
        std::cout << "Error next player ";
        return false;
    }
    if (loc == board.PASS_LOC)//pass直接判负，但是不作为“illegal move”
        return true;

    if (!board.isOnBoard(loc))
        return false;

    //TODO: Add some logic
    if (board.stage == 0)//选子
    {
        return board.colors[loc] == pla;
    }
    else if (board.stage == 1)//落子
    {
        Loc chosenMove = board.midLocs[0];
        return isQueenMove(board,chosenMove, loc);
    }
    else if (board.stage == 2)//放障碍
    {
        Loc chosenMove = board.midLocs[1];
        return isQueenMove(board,chosenMove, loc);
    }

    ASSERT_UNREACHABLE;
//    return false;
}





Color GameLogic::checkWinnerAfterPlayed(
  const Board& board,
  const BoardHistory& hist,
  Player pla,
  Loc loc) {
  if(loc == Board::PASS_LOC) {
      return getOpp(pla);  // pass is not allowed
  }

  return C_WALL;
}

GameLogic::ResultsBeforeNN::ResultsBeforeNN() {
  inited = false;
  winner = C_WALL;
  myOnlyLoc = Board::NULL_LOC;
}

void GameLogic::ResultsBeforeNN::init(const Board& board, const BoardHistory& hist, Color nextPlayer) {
  if(inited)
    return;
  inited = true;

  return;
}
