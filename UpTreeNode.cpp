#include "UpTreeNode.h"

UpTreeNode::UpTreeNode(Player* player, Team* team, UpTreeNode* parent):
    player(player),
    team(team),
    parent(parent),
    spiritRank(team->getlastPerm() * player->getSpirit())
{}