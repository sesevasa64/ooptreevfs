#pragma once
#include <list>
#include "node.hpp"
#include "file.hpp"

using SNodes = std::list<SNode>;
using SDir = std::shared_ptr<Dir>;

class Dir : public Node {
public:
    Dir(std::string name, Dir *parent = {});
    void Add(SNode node);
    void Remove(SNode node);
    void AddFileByName(std::string name);
    void AddDirByName(std::string name);
    void AddDirRecursive(std::string fullname);
    void AddFileRecursive(std::string fullname);
    void RemoveByName(std::string name);
    SNode GetNodeByName(std::string name);
    SDir  GetDirByName(std::string name);
    SFile GeFileByName(std::string name);
    bool IsNodeExist(std::string name);
    bool IsNodeExist(SNode node);
    void PrintContent();
    void PrintContentRecursive();
    size_t Count();
    size_t Size() override;
    void SetCreate(callback create);
    void SetRemove(callback remove);
private:
    SDir ProceedPath(std::string fullname);
    callback create, remove;
    SNodes nodes;
};