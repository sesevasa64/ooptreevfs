#include "vfs.hpp"
#include <fstream>
#include <iostream>
using namespace std;

inline bool isFileExist(const string& name) {
    ifstream f(name);
    return f.good();
}

Archive::Archive(const std::string& name) : archiveName(name) {
    root = make_shared<Dir>(string());
    bool isExist = isFileExist(name);
    if (isExist) {
        mode = "rb+"; 
    }
    else {
        mode = "wb+";
    }
    int err = mtar_open(&tar, name.c_str(), mode.c_str());
    freopen(name.c_str(), "rb+", (FILE*)tar.stream);
    if (isExist) {
        loadArchive();
    }
    root->SetObserver(this);
}

Archive::~Archive() {
    mtar_close(&tar);
}

SDir Archive::getRoot() {
    return root;
}

void Archive::Print() {
    root->PrintContentRecursive();
}

void Archive::Add(const SNode& node) {
    root->Add(node);
}

SFile Archive::AddFile(const std::string& fullname) {
    return root->AddFileRecursive(fullname);
}

SDir Archive::AddDir(const std::string& fullname) {
    return root->AddDirRecursive(fullname);
}

SDir Archive::GetDir(const std::string& fullname) {
    return root->GetDirByNameRecursive(fullname);
}
    
SFile Archive::GetFile(const std::string& fullname) {
    return root->GeFileByNameRecursive(fullname);
}

void Archive::RemoveRecursive(const std::string& fullname) {
    root->RemoveByNameRecursive(fullname);
}

void Archive::loadArchive() {
    mtar_header_t header;
    while (true) {
        int res = mtar_read_header(&tar, &header);
        if (res == MTAR_ENULLRECORD || res == MTAR_EREADFAIL) {
            break;
        }
        if (header.type == MTAR_TDIR) {
            auto dir = AddDir(header.name);
        }
        else if (header.type == MTAR_TREG) {
            auto file = AddFile(header.name);
            char *ptr = (char*)calloc(1, header.size + 1);
            mtar_read_data(&tar, ptr, header.size);
            file->SetContent(ptr);
            free(ptr);

        }
        mtar_next(&tar);
    }
}

void Archive::Create(Dir *dir) {
    cout << "onCreate = " << dir->GetFullName() << endl;
    mtar_write_dir_header(&tar, dir->GetFullName().c_str() + 1);
}

void Archive::Create(File *file) {
    cout << "onCreate = " << file->GetFullName() << endl;
    std::string content = file->toString();
    mtar_write_file_header(&tar, file->GetFullName().c_str() + 1, content.size());
    mtar_write_data(&tar, content.c_str(), content.size()); 
}

void Archive::Remove(Dir *dir) {
    mtar_header_t header;
    string name = dir->GetFullName();
    cout << "onRemove = " << name << endl;
    const char *fname = name.c_str();
    mtar_delete_header(&tar, archiveName.c_str(), fname + 1);
}

void Archive::Remove(File *file) {
    mtar_header_t header;
    string name = file->GetFullName();
    cout << "onRemove = " << name << endl;
    const char *fname = name.c_str();
    mtar_delete_header(&tar, archiveName.c_str(), fname + 1);
}

void Archive::Update(Node *node) {
    string name = node->GetFullName();
    cout << "onUpdate = " << name << endl;
    node->Remove();
    node->Create();
}

void Archive::Update(Dir *dir) {
    string name = dir->GetFullName();
    cout << "onUpdate = " << name << endl;
    dir->Remove();
    dir->Create();
}

void Archive::Update(File *file) {
    string name = file->GetFullName();
    cout << "onUpdate = " << name << endl;
    file->Remove();
    file->Create();
}
