#include "dir.hpp"
#include "file.hpp"
#include "dummy.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

Dir::Dir(std::string name, Dir *parent) 
: Node(name, parent), create(dummy), remove(dummy) {}

void Dir::Add(SNode node) {
    if (IsNodeExist(node->GetName())) {
        throw std::invalid_argument("node with this name already exist");
    }
    nodes.push_back(node);
    if (node->GetParent() != this) {
        node->SetParent(this);
    }
    node->SetUpdate(update);
    create(node);
}

void Dir::Remove(SNode node) {
    auto it = std::find(nodes.begin(), nodes.end(), node);
    if (it == nodes.end()) {
        return;
    }
    nodes.erase(it);
    remove(node);
    node->SetParent(nullptr);
}

size_t Dir::Count() {
    return nodes.size();
}

size_t Dir::Size() {
    size_t size = 0;
    for (auto &node : nodes) {
        size += node->Size();
    }
    return size;
}

void Dir::AddFileByName(std::string name) {
    SFile node = std::make_shared<File>(name);
    Add(node);
}

void Dir::AddDirByName(std::string name) {
    SDir node = std::make_shared<Dir>(name);
    Add(node);
    node->SetCreate(create);
    node->SetRemove(remove);
}

SNode Dir::GetNodeByName(std::string name) {
    for (auto &node : nodes) {
        if (node->GetName() == name) {
            return node;
        }
    }
    return nullptr;
}

SDir Dir::GetDirByName(std::string name) {
    SNode node = GetNodeByName(name);
    return std::dynamic_pointer_cast<Dir>(node);
}

SFile Dir::GeFileByName(std::string name) {
    SNode node = GetNodeByName(name);
    return std::dynamic_pointer_cast<File>(node);
}

SNode Dir::GetNodeByNameRecursive(std::string fullname) {
    auto pos = fullname.rfind('/');
    auto name = fullname.substr(pos + 1);
    auto dir = ProceedPath(fullname);
    return dir->GetNodeByName(name);
}

SDir Dir::GetDirByNameRecursive(std::string fullname) {
    SNode node = GetNodeByNameRecursive(fullname);
    return dynamic_pointer_cast<Dir>(node);
}

SFile Dir::GeFileByNameRecursive(std::string fullname) {
    SNode node = GetNodeByNameRecursive(fullname);
    return dynamic_pointer_cast<File>(node);
}

bool Dir::IsNodeExist(std::string name) {
    for (auto &node : nodes) {
        if (node->GetName() == name) {
            return true;
        }
    }
    return false;
}

bool Dir::IsNodeExist(SNode node) {
    return IsNodeExist(node->GetName());
}

void Dir::PrintContent() {
    for (auto &node : nodes) {
        std::cout << node->GetFullName() << std::endl;
    }
}

void Dir::PrintContentRecursive() {
    for (auto &node : nodes) {
        std::cout << node->GetFullName() << std::endl;
        auto dir = std::dynamic_pointer_cast<Dir>(node); 
        if (dir) {
            dir->PrintContentRecursive();
        }
    }
}

void Dir::SetCreate(callback create) {
    if (create) {
        this->create = create;
    }
}

void Dir::SetRemove(callback remove) {
    if (remove) {
        this->remove = remove;
    }
}

SDir Dir::ProceedPath(std::string fullname) {
    auto pos = fullname.find('/');
    auto name = fullname.substr(0, pos);
    if (pos != string::npos) {
        SNode node = GetNodeByName(name);
        auto path = fullname.substr(pos + 1);
        if (node) {
            SDir dir = dynamic_pointer_cast<Dir>(node);
            if (!dir) {
                throw std::invalid_argument(
                    "file with this name already exist"
                );
            }
            return dir->ProceedPath(path);
        }
        SDir dir = make_shared<Dir>(name);
        this->Add(dir);
        dir->SetCreate(create);
        dir->SetRemove(remove);
        return dir->ProceedPath(path);
    }
    else {
        SNode res = shared_from_this();
        return static_pointer_cast<Dir>(res);
    }
}

void Dir::AddDirRecursive(std::string fullname) {
    auto pos = fullname.rfind('/');
    auto name = fullname.substr(pos + 1);
    auto dir = ProceedPath(fullname);
    dir->AddDirByName(name);
}

void Dir::AddFileRecursive(std::string fullname) {
    auto pos = fullname.rfind('/');
    auto name = fullname.substr(pos + 1);
    auto dir = ProceedPath(fullname);
    dir->AddFileByName(name);
}

void Dir::RemoveByNameRecursive(std::string fullname) {
    auto pos = fullname.rfind('/');
    auto name = fullname.substr(pos + 1);
    auto dir = ProceedPath(fullname);
    auto node = dir->GetNodeByName(name);
    if (!node) {
        throw std::invalid_argument(
            "node with this name dont exist!"
        );
    }
    dir->Remove(node);
}

vector<string> Dir::getAllNamesRecursive() {
    vector<string> names;
    for (auto &node : nodes) {
        names.push_back(node->GetFullName());
        auto dir = dynamic_pointer_cast<Dir>(node);
        if (dir) {
            auto subnames = dir->getAllNamesRecursive();
            names.insert(names.end(), subnames.begin(), subnames.end());
        }
    }
    return names;
}
