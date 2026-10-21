#include <bits/stdc++.h>

// Homework for 21.10.2026
// To complete the homework, it MUST be uploaded to your oop repo on Github!!

// 0. Enforce that no file/directory with the same names can be created in the same dir.
// 1. When printing the directory, print the contents of all child directories!!!
// 2. Implement 'Up' function that return the parent directory of the current directory
//    If no parent is available, print '/(root)'
// 3. Implement "Find" that searches for a file or directory inside a specific directory.
//    The file/directory can be nested inside a subdirectory
// 4. DirectorySize function includes the size of child directories

using namespace std;

struct File
{
    string name;
    string extension;
    uint64_t byteSize;
};

string getFullFilename(File &f)
{
     return f.name + '.' + f.extension;
}

struct Directory
{
    string name;
    vector<File *> files;
    vector<Directory *> dirs;
    Directory *parent = nullptr;
};

uint64_t getDirectorySize(Directory &dir)
{
    uint64_t siz = 0;
    for (size_t  i = 0; i < dir.files.size(); i++)
    {
        siz += dir.files[i]->byteSize;
    }
    for (size_t i = 0; i < dir.dirs.size(); ++i)
    {
        siz += getDirectorySize(*dir.dirs[i]);
        // 4. DirectorySize function includes the size of child directories
    }
    return siz;
}

bool addFile(File *f, Directory &dir)
{
    string name = getFullFilename(*f);

    for (size_t i = 0; i < dir.files.size(); i++)
    {
        if (getFullFilename(*dir.files[i]) == name)
        {
            return false;
            // 0. Enforce that no file with the same names can be created in the same dir.
        }
    }
    dir.files.push_back(f);
    return true;
}
bool addDirectory(Directory *d, Directory &dir) {
    string name = d->name;

    for (size_t i = 0; i < dir.dirs.size(); ++i)
    {
        if (dir.dirs[i]->name == name)
        {
            return false;
            // 0. Enforce that no directory with the same names can be created in the same dir.
        }
    }
    dir.dirs.push_back(d);
    d->parent = &dir;
    return true;
}

bool Exists(Directory *dir, const string &filename)
{
    for (size_t i = 0; i < dir->files.size(); i++)
    {
        if (getFullFilename(*dir->files[i]) == filename)
        {
            return true;
        }
    }
    return false;
}

bool moveFile(const string &filename, Directory &from, Directory &to)
{
    if (Exists(&to, filename))
    {
        return false;
    }

    File *file = nullptr;
    for (size_t i = 0; i < from.files.size(); i++)
    {
        if (filename == getFullFilename(*from.files[i]))
        {
            file = from.files[i];
            for (size_t j = i; j < from.files.size() - 1; j++)
            {
                from.files[j] = from.files[j + 1];
            }
            from.files.pop_back();
            to.files.push_back(file);
            return true;
        }
    }
    return false;
}

void printDir(const Directory &dir, int depth = 0)
{
    cout << dir.name << endl;

    for (size_t i = 0; i < dir.files.size(); i++)
    {
        cout << getFullFilename(*dir.files[i]) << endl;
    }
    for (size_t i = 0; i < dir.dirs.size(); i++)
    {
        printDir(*dir.dirs[i], depth + 1);
        // 1. When printing the directory, print the contents of all child directories!!!
    }
}

Directory* up(Directory *dir)
{
    // 2. Implement 'Up' function that return the parent directory of the current directory
    //    If no parent is available, print '/(root)'
    if (dir -> parent == nullptr)
    {
        cout << "/(root)" << endl;
    }

    return dir->parent;
}

bool findx(Directory *dir, const string &targetName)
{
    for (size_t i = 0; i < dir->files.size(); i++)
    {
        if (getFullFilename(*dir->files[i]) == targetName)
        {
            return true;
        }
    }

    for (size_t i = 0; i < dir->dirs.size(); i++)
    {
        if (dir->dirs[i]->name == targetName)
        {
            return true;
        }

        if (findx(dir->dirs[i], targetName))
        {
            return true;
        }
    }

    return false;
}

int main()
{

    Directory root, child1, child2;
    root.name = "downloads";
    child1.name = "C1";
    child2.name = "C2";

    child1.parent = &root;
    child2.parent = &child1;

    root.dirs.push_back(&child1);
    child1.dirs.push_back(&child2);

    File a, b, c;

    a.name = "A";
    a.extension = "txt";
    a.byteSize = 500;

    b.name = "B";
    b.extension = "jpeg";
    b.byteSize = 4000000;

    c.name = "C";
    c.extension = "cpp";
    c.byteSize = 10000;

    addFile(&a, root);
    addFile(&b, child1);
    addFile(&c, child2);

    Directory docs;
    docs.name = "documents";

    addDirectory(&docs, root);

    if (moveFile("A.txt", root, child2))
    {
    cout << "File moved successfully!" << endl;
    }

    cout<<endl<<"Printing child1:"<<endl;

    printDir(child1);

    cout<<endl;

    if (findx(&child1, "A.txt"))
    {
    cout << "File was found";
    }
    else
    {
    cout << "File not found";
    }

return 0;
}
