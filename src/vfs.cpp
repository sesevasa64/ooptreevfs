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
    root->SetCreate(bind(&Archive::onAdd, this, _1));
    root->SetRemove(bind(&Archive::onRemove, this, _1));
    root->SetUpdate(bind(&Archive::onUpdate, this, _1));
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

void Archive::writeDir(SDir dir) {
    mtar_write_dir_header(&tar, dir->GetFullName().c_str() + 1);
    //auto names = dir->getAllNamesRecursive();
    //for (auto& name : names) {

    //}
}

void Archive::writeFile(SFile file) {
    std::string content = file->toString();
    mtar_write_file_header(&tar, file->GetFullName().c_str() + 1, content.size());
    mtar_write_data(&tar, content.c_str(), content.size()); 
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

void Archive::onAdd(SNode node) {
    cout << "onAdd = " << node->GetFullName() << endl;
    SDir dir = dynamic_pointer_cast<Dir>(node);
    if (dir) {
        writeDir(dir);
    }
    else {
        SFile file = dynamic_pointer_cast<File>(node);
        writeFile(file);      
    }
}

void Archive::onRemove(SNode node) {
    mtar_header_t header;
    string name = node->GetFullName();
    cout << "onRemove = " << name << endl;
    const char *fname = name.c_str();
    mtar_delete_header(&tar, archiveName, fname + 1);
}

void Archive::onUpdate(SNode node) {
    string name = node->GetFullName();
    cout << "onUpdate = " << name << endl;
    onRemove(node);
    onAdd(node);
}
