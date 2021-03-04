#include <iostream>
#include "dir.hpp"
#include "file.hpp"
#include "vfs.hpp"
using namespace std;

void addToArchive(Archive &archive) {
    archive.AddFile("games/apex/apex.exe");
    auto file = archive.GetFile("games/apex/apex.exe");
    file->Push("first line");
    file->Push("second line");
    //archive.RemoveRecursive("games/apex/apex.exe");
    archive.AddFile(".gitignore");
}

void loadAndPrintArchive(Archive &archive) {
    archive.Print();
    auto file = archive.GetFile("games/apex/apex.exe");
    cout << *file << endl;
}

int main() {
    Archive archive("test.tar");
    // addToArchive(archive);
    loadAndPrintArchive(archive);
    cout << 1 << endl;
    return 0;
}
