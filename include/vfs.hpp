#pragma once
#include "microtar.h"
#include "dir.hpp"

class IObserver {
public:
    virtual void Create(Dir *dir) = 0;
    virtual void Create(File *file) = 0;
    virtual void Remove(Dir *dir) = 0;
    virtual void Remove(File *file) = 0;
    virtual void Update(Node *node) = 0;
    virtual void Update(Dir *dir) = 0;
    virtual void Update(File *file) = 0;
};

class Archive : public IObserver {
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
    void Create(Dir *dir);
    void Create(File *file);
    void Remove(Dir *dir);
    void Remove(File *file);
    void Update(Node *node);
    void Update(Dir *dir);
    void Update(File *file);
private:
    void loadArchive();
    std::string archiveName, mode;
    mtar_t tar;
    SDir root;
};
