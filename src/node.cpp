#include "node.hpp"
#include "dir.hpp"
#include "vfs.hpp"
#include <iostream>
#include <utility>

void IObservable::SetObserver(IObserver *obs) {
    this->observer = obs;
}

Node::Node(std::string name, Dir *parent) 
: m_name(std::move(name)), parent(nullptr) {
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
    // Надо попробовать улучшить это 
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
    m_name = std::move(name);
    Update();
}

std::string Node::GetName() {
    return m_name;
}

std::string Node::GetFullName() {
    if (parent) {
        return parent->GetFullName() + "/" + m_name;
    }
    return GetName();
}
