#include <iostream>
#include "dir.hpp"
#include "file.hpp"
#include "vfs.hpp"
using namespace std;

using fptr = void (Node::*)(SNode);

void doJob(SNode node) { cout << "SNode doing job!" << endl; }
void doJob(SDir dir) { cout << "SDir doing job!" << endl; }
void doJob(SFile file) { cout << "SFile doing job!" << endl; } 

int main() {
    Archive archive("test.tar");
    archive.AddFile("games/apex/apex.exe");
    auto file = archive.GetFile("games/apex/apex.exe");
    file->Push("first line");
    file->Push("second line");
    //archive.RemoveRecursive("games/apex/apex.exe");
    archive.AddFile(".gitignore");
    cout << 1 << endl;

    SNode node = make_shared<File>(string());
    doJob(node);
    return 0;
}
