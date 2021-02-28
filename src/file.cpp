#include "file.hpp"
#include <iostream>

File::File(std::string name) : Node(name) {}

void File::CheckPos(size_t pos) {
    if (pos >= lines.size()) {
        throw std::invalid_argument("index out of range");
    }
}

std::string& File::Read(size_t pos) {
    CheckPos(pos);
    return lines[pos];
}

void File::Insert(size_t pos, std::string str) {
    if (pos > lines.size()) {
        throw std::invalid_argument("index out of range");
    }
    lines.insert(lines.begin() + pos, str);
}

void File::Push(std::string str) {
    lines.push_back(str);
}

void File::Remove(size_t pos) {
    CheckPos(pos);
    lines.erase(lines.begin() + pos);
}

size_t File::Size() {
    size_t size = 0;
    for (auto &line : lines) {
        size += line.size();
    }
    return size;
}

std::ostream& operator<<(std::ostream& out, const File &file) {
    size_t last = file.lines.size() - 1;
    for (int i = 0; i < last; i++) {
        out << file.lines[i] << "\n";
    }
    return out << file.lines[last];
}