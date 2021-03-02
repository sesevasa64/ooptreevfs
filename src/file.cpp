#include "file.hpp"
#include <iostream>
#include <sstream>

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
    update(shared_from_this());
}

void File::Push(std::string str) {
    lines.push_back(str);
    update(shared_from_this());
}

void File::Remove(size_t pos) {
    CheckPos(pos);
    lines.erase(lines.begin() + pos);
    update(shared_from_this());
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
    std::cout << "size = " << lines.size() << std::endl;
    for (auto &line : lines) {
        ss << line << "\n";
    }
    return ss.str();
}

std::ostream& operator<<(std::ostream& out, const File &file) {
    size_t last = file.lines.size() - 1;
    for (int i = 0; i < last; i++) {
        out << file.lines[i] << "\n";
    }
    return out << file.lines[last];
}
