#include "dir.hpp"
#include "file.hpp"
#include "vfs.hpp"
#include <iostream>
using namespace std;

void addToArchive(Archive &archive) {
    auto file = archive.AddFile("games/apex/apex.exe");
    file->Push("first line");
    file->Push("second line");
    //archive.RemoveRecursive("games/apex/apex.exe");
    archive.AddFile(".gitignore");
}

void loadAndPrintArchive(Archive &archive) {
    archive.Print();
    auto file = archive.GetFile("games/apex/apex.exe");
    cout << file << endl;
    /*
    auto d1 = make_shared<Dir>("photos");
    auto d2 = d1->AddDirByName("chelyabinsk");
    auto f1 = d2->AddFileByName("tree.jpg");
    f1->Push("0x09a2sd1dfb4sh");
    archive.Add(d1);
    */
}

void updateFileInArchive(Archive &archive) {
    auto file = archive.GetFile("games/apex/apex.exe");
    file->Line(0) = "peepoClown";
    file->Line(0) += ", feelsHappyMan";
}

int main() {
    Archive archive("test.tar");
    //addToArchive(archive);
    loadAndPrintArchive(archive);
    //updateFileInArchive(archive);
    cout << "sizeof(IObserver*) = " << sizeof(IObserver*) << endl;
    return 0;
}
