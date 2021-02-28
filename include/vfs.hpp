#pragma once
#include "microtar.h"
#include "dir.hpp"

class Archive {
public:
    Archive(std::string name);
private:
    void onAdd(SNode node);
    void onRemove(SNode node);
    void onUpdate(SNode node);
    mtar_t tar;
    SDir root;
};
