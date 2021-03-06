#pragma once
#include <list>
#include "node.hpp"
#include "file.hpp"

using SNodes = std::list<SNode>;
using SDirIt = SNodes::iterator;
using SDir = std::shared_ptr<Dir>;

class Dir : public Node {
public:
    explicit Dir(std::string name, Dir *parent = {});
    void Add(const SNode& node);
    void Remove(const SNode& node);
    SFile AddFileByName(const std::string &name);
    SDir  AddDirByName(const std::string &name);
    SDir  AddDirRecursive(const std::string& fullname);
    SFile AddFileRecursive(const std::string& fullname);
    //void RemoveByName(std::string name);
    void RemoveByNameRecursive(const std::string& fullname);
    SNode GetNodeByName(const std::string& name);
    SNode GetNodeByNameRecursive(const std::string& fullname);
    SDir  GetDirByName(const std::string& name);
    SDir  GetDirByNameRecursive(const std::string& fullname);
    SFile GeFileByName(const std::string& name);
    SFile GeFileByNameRecursive(const std::string& fullname);
    bool IsNodeExist(const std::string& name);
    bool IsNodeExist(const SNode& node);
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
    SDir ProceedPath(const std::string& fullname);
    SNodes nodes;
};
