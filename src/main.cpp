#include <iostream>
#include "dir.hpp"
#include "file.hpp"
#include "vfs.hpp"
using namespace std;

int main() {
    Archive archive("test.tar");
    archive.AddFile("games/apex/apex.exe");
    auto file = archive.GetFile("games/apex/apex.exe");
    file->Push("first line");
    file->Push("second line");
    archive.RemoveRecursive("games/apex/apex.exe");
    archive.AddFile(".gitignore");
    cout << 1 << endl;
    return 0;
}
