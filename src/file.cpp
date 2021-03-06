#include "file.hpp"
#include <iostream>
#include <sstream>
#include "vfs.hpp"
using namespace std;

vector<string> split(const string& str) {
    vector<string> res;
    size_t pos = 0;
    while (true) {
        auto tmp = str.find('\n', pos);
        if (tmp == string::npos) {
            break;
        }
        res.push_back(str.substr(pos, tmp - pos));
        pos = tmp + 1;
    }
    return res;
}

Proxy::Proxy(File *file, string *ptr) : file(file), ptr(ptr) {}

void Proxy::operator=(string str) {
    *ptr = std::move(str);
    file->Update();
}

void Proxy::operator+=(const string& str) {
    *ptr += str;
    file->Update();
}

File::File(string name) : Node(std::move(name)) {
    SetObserver(&Null::get());
}

void File::CheckPos(size_t pos) {
    if (pos >= lines.size()) {
        throw invalid_argument("CheckPos(): index out of range");
    }
}

Proxy File::Line(size_t pos) {
    return (*this)[pos];
}

Proxy File::operator[](size_t pos) {
    CheckPos(pos);
    return {this, &lines[pos]};
}

void File::Insert(size_t pos, const string& str) {
    if (pos > lines.size()) {
        throw invalid_argument("Insert(): index out of range");
    }
    lines.insert(lines.begin() + pos, str);
    Update();
}

void File::Push(const string& str) {
    lines.push_back(str);
    Update();
}

void File::Remove(size_t pos) {
    CheckPos(pos);
    lines.erase(lines.begin() + pos);
    Update();
}

size_t File::Size() {
    size_t size = 0;
    for (auto &line : lines) {
        size += line.size();
    }
    return size;
}

std::string File::toString() {
    std::stringstream ss;
    for (auto &line : lines) {
        ss << line << "\n";
    }
    return ss.str();
}

void File::SetContent(const string& content) {
    lines = split(content);
}

ostream& operator<<(ostream& out, const File &file) {
    size_t last = file.lines.size() - 1;
    for (int i = 0; i < last; i++) {
        out << file.lines[i] << "\n";
    }
    return out << file.lines[last];
}

ostream& operator<<(ostream& out, const SFile& file) {
    return out << *file;
}

void File::Create() {
    observer->Create(this);
}

void File::Remove() {
    observer->Remove(this);
}

void File::Update() {
    observer->Update(this);
}
