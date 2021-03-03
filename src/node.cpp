#include "node.hpp"
#include "dir.hpp"
#include <iostream>
#include "vfs.hpp"

void IObservable::SetObserver(IObserver *observer) {
    this->observer = observer;
}

Node::Node(std::string name, Dir *parent) 
: name(name), parent(nullptr) {
    SetParent(parent);
}

void Node::SetParent(Dir *parent) {
    if (this->parent == parent) {
        return;
    }
    SNode node = shared_from_this();
    if (this->parent) {
        this->parent->Remove(node);
    }
    this->parent = parent;
    if (parent && !parent->IsNodeExist(node)) {
        parent->Add(node);
    }
    // Мб вообще удалить
    //update(node);
}

Dir* Node::GetParent() {
    return parent;
}

void Node::SetName(std::string name) {
    this->name = name;
    Update();
}

std::string Node::GetName() {
    return name;
}

std::string Node::GetFullName() {
    if (parent) {
        return parent->GetFullName() + "/" + name;
    }
    return GetName();
}
