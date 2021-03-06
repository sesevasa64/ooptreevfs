#pragma once
#include <vector>
#include "node.hpp"

class File;

using Lines = std::vector<std::string>;
using SFile = std::shared_ptr<File>;

class Proxy {
public:
    Proxy(File *file, std::string *ptr);
    void operator=(std::string str);
    void operator+=(const std::string& str);
private:
    std::string *ptr; 
    File *file;
};

class File : public Node {
public:
    explicit File(std::string name);
    size_t Size() override;
    Proxy Line(size_t pos);
    void Insert(size_t pos, const std::string& str);
    void Push(const std::string& str);
    void Remove(size_t pos);
    std::string toString();
    void Create() override;
    void Remove() override;
    void Update() override;
    void SetContent(const std::string& content);
    Proxy operator[](size_t pos);
    friend std::ostream& operator<<(std::ostream& out, const File &file);
    friend std::ostream& operator<<(std::ostream& out, const SFile& file);
private:
    void CheckPos(size_t pos);
    Lines lines;
};
