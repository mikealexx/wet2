#include "UpTree.h"

UpTree::UpTree(Player* player, UpTree* parent, permutation_t& spiritRank, int gamesPlayedRank):
    player(player),
    parent(parent),
    spiritRank(spiritRank),
    gamesPlayedRank(),
    playerId(player->getId()),
    size(1)
{}

int UpTree::getPlayerId() const {
    return this->playerId;
}