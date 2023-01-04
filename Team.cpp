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
    stats(ability, id)
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

shared_ptr<UpTree> Team::getRoot() const {
    return this->rootPlayer;
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

TeamStats Team::getStats() const{
    return this->stats;
}

void Team::updateStats() {
    this->stats = TeamStats(this->getAbility(), this->getID());
}

void Team::setRoot(shared_ptr<UpTree> root) {
    this->rootPlayer = root;
}