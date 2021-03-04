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
    SFile AddFile(std::string fullname);
    SDir  AddDir(std::string fullname);
    SDir  GetDir(std::string fullname);
    SFile GetFile(std::string fullname);
    void RemoveRecursive(std::string fullname);
    SDir getRoot();
    void Print();
    ~Archive();
    void Create(Dir *dir) override;
    void Create(File *file) override;
    void Remove(Dir *dir) override;
    void Remove(File *file) override;
    void Update(Node *node) override;
    void Update(Dir *dir) override;
    void Update(File *file) override;
private:
    void loadArchive();
    std::string archiveName, mode;
    mtar_t tar;
    SDir root;
};

class Null : public IObserver {
public:
    void Create(Dir *dir) override {}
    void Create(File *file) override {}
    void Remove(Dir *dir) override {}
    void Remove(File *file) override {}
    void Update(Node *node) override {}
    void Update(Dir *dir) override {}
    void Update(File *file) override {}
    static Null& get() {
        static Null obs;
        return obs;
    }
private:
    Null() {}
};
