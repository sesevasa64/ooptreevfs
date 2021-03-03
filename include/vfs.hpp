#pragma once
#include "microtar.h"
#include "dir.hpp"

class Archive {
public:
    Archive(std::string name);
    void AddFile(std::string fullname);
    void AddDir(std::string fullname);
    SDir GetDir(std::string fullname);
    SFile GetFile(std::string fullname);
    void RemoveRecursive(std::string fullname);
    SDir getRoot();
    void Print();
    ~Archive();
private:
    void loadArchive();
    void writeDir(SDir dir);
    void writeFile(SFile file);
    void onAdd(SNode node);
    void onRemove(SNode node);
    void onUpdate(SNode node);
    std::string archiveName, mode;
    mtar_t tar;
    SDir root;
};
