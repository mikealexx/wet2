#include "UpTree.h"

UpTree::UpTree(shared_ptr<Player> player, const permutation_t& spiritRank, int gamesPlayedRank, int teamId):
    player(player),
    parent(nullptr),
    spiritRank(spiritRank),
    gamesPlayedRank(),
    playerId(player->getId()),
    teamId(teamId),
    size(1),
    lastPerm(permutation_t::neutral())
{}

int UpTree::getPlayerId() const {
    return this->playerId;
}

int UpTree::getSize() const {
    return this->size;
}

void UpTree::setSize(int size) {
    this->size = size;
}

int UpTree::getGamesPlayedRank() const {
    return this->gamesPlayedRank;
}

void UpTree::setGamesPlayedRank(int rank) {
    this->gamesPlayedRank = rank;
}

permutation_t UpTree::getSpiritRank() const {
    return this->spiritRank;
}

void UpTree::setSpiritRank(permutation_t rank) {
    this->spiritRank = rank;
}

shared_ptr<UpTree> UpTree::getParent() const {
    return this->parent;
}

void UpTree::setParent(shared_ptr<UpTree> tree) {
    this->parent = tree;
}

permutation_t UpTree::getLastPerm() const {
    return this->lastPerm;
}

void UpTree::setLastPerm(permutation_t perm) {
    this->lastPerm = perm;
}

shared_ptr<Player> UpTree::getPlayer() const {
    return this->player;
}

int UpTree::getTeamId() const {
    return this->teamId;
}

void UpTree::setTeamId(const int& id) {
    this->teamId = id;
}