#include "vfs.hpp"
#include <fstream>
#include <iostream>
using namespace std;
using namespace placeholders;

inline bool isFileExist(const std::string& name) {
    ifstream f(name);
    return f.good();
}

void mtar_delete_header(mtar_t *tar, string archiveName, const char *headerName) {
    const int size = 512;
    char buf[size];
    string tmp = "tmp.tar";
    mtar_header_t header;
    int error = mtar_find(tar, headerName, &header);
    if (error != 0) {
        return;
    }
    int header_pos = tar->pos;
    FILE *cur_file = (FILE*)tar->stream;
    FILE *tmp_file = fopen(tmp.c_str(), "wb+");
    fseek(cur_file, 0, SEEK_SET);
    while (true) {
        fread(buf, size, 1, cur_file);
        if (feof(cur_file)) {
            break;
        }
        if (ftell(cur_file) - size != header_pos ) {
            fwrite(buf, size, 1, tmp_file);
        }
    }
    error = fclose(cur_file);
    error = remove(archiveName.c_str());
    error = fclose(tmp_file);
    error = rename(tmp.c_str(), archiveName.c_str());
    tar->stream = fopen(archiveName.c_str(), "rb+");
    // На всякий случай
    error = mtar_seek(tar, header_pos);
}

Archive::Archive(std::string name) : archiveName(name) {
    root = make_shared<Dir>(string());
    root->SetObserver(this);
    if (isFileExist(name)) {
        //loadArchive();
        mode = "rb+"; 
    }
    else {
        mode = "wb+";
    }
    int err = mtar_open(&tar, name.c_str(), mode.c_str());
    freopen(name.c_str(), "rb+", (FILE*)tar.stream);
}

Archive::~Archive() {
    // Не обязательно
    // mtar_finalize(&tar);
    mtar_close(&tar);
}

SDir Archive::getRoot() {
    return root;
}

void Archive::Print() {
    root->PrintContentRecursive();
}

void Archive::AddFile(std::string fullname) {
    root->AddFileRecursive(fullname);
}

void Archive::AddDir(std::string fullname) {
    root->AddDirRecursive(fullname);
}

SDir Archive::GetDir(std::string fullname) {
    return root->GetDirByNameRecursive(fullname);
}
    
SFile Archive::GetFile(std::string fullname) {
    return root->GeFileByNameRecursive(fullname);
}

void Archive::RemoveRecursive(std::string fullname) {
    root->RemoveByNameRecursive(fullname);
}

void Archive::loadArchive() {
    mtar_header_t header;
    while (true) {
        int res = mtar_read_header(&tar, &header);
        if (res == MTAR_ENULLRECORD) {
            break;
        }
        if (header.type == MTAR_TDIR) {
            AddDir(header.name);
        }
        else if (header.type == MTAR_TREG) {
            AddFile(header.name);
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
    mtar_delete_header(&tar, archiveName, fname + 1);
}

void Archive::Remove(File *file) {
    mtar_header_t header;
    string name = file->GetFullName();
    cout << "onRemove = " << name << endl;
    const char *fname = name.c_str();
    mtar_delete_header(&tar, archiveName, fname + 1);
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
