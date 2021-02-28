#pragma once
#include <vector>
#include "node.hpp"

using Lines = std::vector<std::string>;

class File : public Node {
public:
    File(std::string name);
    std::string& Read(size_t pos);
    void Insert(size_t pos, std::string str);
    void Push(std::string str);
    void Remove(size_t pos);
    size_t Size() override;
    friend std::ostream& operator<<(std::ostream& out, const File &file);
private:
    void CheckPos(size_t pos);
    Lines lines;
};

using SFile = std::shared_ptr<File>;
