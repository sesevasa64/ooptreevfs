#pragma once
#include <list>
#include "node.hpp"
#include "file.hpp"

using SNodes = std::list<SNode>;
using SDirIt = SNodes::iterator;
using SDir = std::shared_ptr<Dir>;

class Dir : public Node {
public:
    Dir(std::string name, Dir *parent = {});
    void Add(SNode node);
    void Remove(SNode node);
    SFile AddFileByName(std::string name);
    SDir  AddDirByName(std::string name);
    SDir  AddDirRecursive(std::string fullname);
    SFile AddFileRecursive(std::string fullname);
    void RemoveByName(std::string name);
    void RemoveByNameRecursive(std::string fullname);
    SNode GetNodeByName(std::string name);
    SNode GetNodeByNameRecursive(std::string fullname);
    SDir  GetDirByName(std::string name);
    SDir  GetDirByNameRecursive(std::string fullname);
    SFile GeFileByName(std::string name);
    SFile GeFileByNameRecursive(std::string fullname);
    bool IsNodeExist(std::string name);
    bool IsNodeExist(SNode node);
    void PrintContent();
    void PrintContentRecursive();
    size_t Count();
    size_t Size() override;
    void Create() override;
    void Remove() override;
    void Update() override;
    SDirIt begin() { return nodes.begin(); }
    SDirIt end() { return nodes.end(); }
    void SetObserver(IObserver *observer) override;
private:
    SDir ProceedPath(std::string fullname);
    SNodes nodes;
};
