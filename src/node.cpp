#include "node.hpp"
#include "dir.hpp"
#include "dummy.hpp"
#include <iostream>

Node::Node(std::string name, Dir *parent, callback update) 
: name(name), parent(nullptr), update(dummy) {
    SetUpdate(update);
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
    update(shared_from_this());
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

void Node::SetUpdate(callback update) {
    if (update) {
        this->update = update;
    }
}
