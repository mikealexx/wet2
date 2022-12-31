#include "Team.h"
#include "wet2util.h"

Team::Team(int id):
    id(id),
    points(0),
    gamesPlayed(0),
    ability(0),
    size(0),
    goalKeepers(0),
    teamSpirit(permutation_t::neutral()),
    rootPlayer(nullptr),
    lastPerm(permutation_t::neutral()),
    lastGamesPlayed(0),
    stats(id, ability)
{}

int Team::getID() const {
    return this->id;
}

int Team::getPoints() const {
    return this->points;
}

int Team::getGamesPlayed() const {
    return this->gamesPlayed;
}

int Team::getAbility() const {
    return this->ability;
}

int Team::getSize() const {
    return this->size;
}

int Team::getGoalKeepers() const {
    return this->goalKeepers;
}

permutation_t Team::getTeamSpirit() const {
    return this->teamSpirit;
}

UpTreeNode* Team::getRootPlayer() const {
    return this->rootPlayer;
}

permutation_t Team::getlastPerm() const {
    return this->lastPerm;
}

int Team::getLastGamesPlayed() const {
    return this->lastGamesPlayed;
}

void Team::addPoints(int points) {
    this->points += points;
}

void Team::addGamesPlayed(int games) {
    this->gamesPlayed += games;
}

void Team::addAbility(int ability) {
    this->ability += ability;
}

void Team::addToSize(int size) {
    this->size += size;
}

void Team::addGoalKeepers(int keepers) {
    this->goalKeepers += keepers;
}

void Team::setTeamSpirit(permutation_t teamSpirit) {
    this->teamSpirit = teamSpirit;
}

void Team::setLastPerm(permutation_t perm) {
    this->lastPerm = perm;
}

void Team::setLastGamesPlayed(int games) {
    this->lastGamesPlayed = games;
}