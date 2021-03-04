#pragma once
#include <vector>
#include "node.hpp"

using Lines = std::vector<std::string>;

class File : public Node {
public:
    File(std::string name);
    size_t Size() override;
    // Заменить на std::string& operator[](size_t pos);
    // И надо заменить std::string& на прокси объект
    // чтобы отслеживать состояние линий
    std::string& Read(size_t pos);
    void Insert(size_t pos, std::string str);
    void Push(std::string str);
    void Remove(size_t pos);
    std::string toString();
    void Create();
    void Remove();
    void Update();
    void SetContent(std::string content);
    friend std::ostream& operator<<(std::ostream& out, const File &file);
private:
    void CheckPos(size_t pos);
    Lines lines;
};

using SFile = std::shared_ptr<File>;
