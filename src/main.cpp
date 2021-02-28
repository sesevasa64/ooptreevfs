#include <iostream>
#include "dir.hpp"
#include "file.hpp"
#include "vfs.hpp"
using namespace std;

using fptr = void (Node::*)(SNode);

int main() {
    SDir root = make_shared<Dir>("root");
    SDir photo = make_shared<Dir>("photo");
    root->Add(photo);
    cout << photo->GetFullName() << endl;
    SFile file = make_shared<File>("text.txt");
    file->Push("first line");
    file->Push("second line");
    photo->Add(file);
    cout << file->GetFullName() << endl;
    cout << *file << endl;
    //cout << sizeof(mtar_t*) << endl;
    //cout << sizeof(callback) << endl;
    //cout << sizeof(fptr) << endl;
    //cout << sizeof(SNode) << endl;
    //auto test = root->GetDirByName("photo");
    //cout << (test == nullptr) << endl;
    //cout << test->GetName() << endl;
    //SNode node = nullptr;
    //cout << (std::dynamic_pointer_cast<Dir>(node) == nullptr) << endl;
    //string str = "root/photo/text.txt";
    //cout << str.find('/') << endl;
    //cout << str.substr(0, str.find('/')) << endl;
    //cout << str.substr(str.find('/') + 1) << endl;
    //auto pos = str.rfind('/');
    //cout << pos << endl;
    //cout << str.substr(0, pos) << endl;
    //cout << str.substr(pos + 1) << endl;
    SNode node(photo);
    SDir dir = dynamic_pointer_cast<Dir>(node);
    cout << (dir == nullptr) << endl;
    root->AddFileRecursive("games/apex/apex.exe");
    //root->AddDirRecursive("games/csgo/csgo.exe");
    //root->PrintContent();
    cout << endl;
    root->PrintContentRecursive();
    cout << root->Size() << endl;
    /*
    */
    return 0;
}
