#pragma once
#include <string>
#include <memory>

class Dir;
class Node;
class IObserver;

using SNode = std::shared_ptr<Node>;

class IObservable {
public:
    virtual void Create() = 0;
    virtual void Remove() = 0;
    virtual void Update() = 0;
    virtual void SetObserver(IObserver *observer);
protected:
    IObserver *observer;
};

class Node : public IObservable, public std::enable_shared_from_this<Node> {
public:
    explicit Node(std::string name, Dir *parent = {});
    virtual size_t Size() = 0;
    void SetParent(Dir *parent);
    Dir* GetParent();
    void SetName(std::string name);
    std::string GetName();
    std::string GetFullName();
    virtual ~Node() = default;
private:
    std::string m_name;
    Dir *parent;
};
