#pragma once
#include <stack>
#include <vector>
#include <string>

class StringStack {
private:
    std::stack<std::string> s;

public:
    void push(const std::string& str);
    std::string pop();
    void reverse();
    void purge();
    void renumber() const;
    bool empty() const;
    void loadFromFile(const char* filename);
};

class Lines {
public:
    static std::vector<std::string> readLines(const char* filename);
    static void writeLinesToFile(const char* filename, const std::vector<std::string>& lines, bool append = false);
};

class FileCopier : public Lines {
public:
    static void copyWithRenumbering(const char* srcFilename, const char* destFilename);
};

void listTextFiles(char files[][255], int& fileCount);
void printFileContent(const char* fileName);
void saveToJsonFile(const char* filename);
