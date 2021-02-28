#pragma once
#include <string>
#include <memory>
#include <functional>

class Dir;
class Node;

using SNode = std::shared_ptr<Node>;
using callback = std::function<void(SNode)>;

class Node : public std::enable_shared_from_this<Node> {
public:
    Node(std::string name, Dir *parent = {}, callback update = {});
    virtual size_t Size() = 0;
    void SetParent(Dir *parent);
    Dir* GetParent();
    void SetName(std::string name);
    std::string GetName();
    std::string GetFullName();
    void SetUpdate(callback update);
    virtual ~Node() {}
protected:
    callback update;
private:
    std::string name;
    Dir *parent;
};
