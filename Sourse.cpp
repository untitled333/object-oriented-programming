#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

struct Node {
    char data[255];
    Node* next;
    Node(const char* line, Node* nextNode = nullptr) {
        int i = 0;
        while (line[i] != '\0' && i < 254) {
            data[i] = line[i];
            i++;
        }
        data[i] = '\0';
        next = nextNode;
    }
};

Node* push(Node* head, const char* line) {
    return new Node(line, head);
}

Node* pop(Node* head) {
    if (!head) {
        cout << "Stack is empty.\n";
        return nullptr;
    }
    Node* temp = head;
    head = head->next;
    cout << "Popped: " << temp->data << '\n';
    delete temp;
    return head;
}

void purge(Node*& head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    cout << "Stack has been purged.\n";
}

void renumber(Node* head) {
    int lineNumber = 1;
    while (head) {
        cout << lineNumber << ": " << head->data << '\n';
        head = head->next;
        lineNumber++;
    }
}

void printFileContents(const char* filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Can't open the file.\n";
        return;
    }
    char line[255];
    while (file.getline(line, sizeof(line))) {
        cout << line << '\n';
    }
    file.close();
}

Node* LoadFileToStack(const char* filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Can't open the file.\n";
        return nullptr;
    }
    Node* stack = nullptr;
    char line[255];
    while (file.getline(line, sizeof(line))) {
        stack = push(stack, line);
    }
    file.close();
    cout << "File loaded into stack.\n";
    return stack;
}

void listTextFiles(char files[][255], int& fileCount) {
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA("*.txt", &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        DWORD error = GetLastError();
        cout << "Error finding files. Error code: " << error << endl;
        fileCount = 0;
        return;
    }

    cout << "List of .txt files in the directory: \n";
    fileCount = 0;
    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            strcpy_s(files[fileCount], findFileData.cFileName);
            cout << fileCount + 1 << ". " << files[fileCount] << endl;
            fileCount++;
        }
    } while (FindNextFileA(hFind, &findFileData) != 0 && fileCount < 100);

    if (GetLastError() != ERROR_NO_MORE_FILES) {
        cout << "Error with finding next files.\n";
    }

    FindClose(hFind);
}

void printFileContent(const char* fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Can't open the file: " << fileName << endl;
        return;
    }

    char line[255];
    int lineNumber = 1;
    while (file.getline(line, sizeof(line))) {
        cout << lineNumber++ << ". " << line << endl;
    }
    file.close();
}

int main() {
    char files[100][255];
    int fileCount = 0;
    int choice;

    
    listTextFiles(files, fileCount);
    if (fileCount == 0) {
        cout << "No .txt files found in the directory.\n";
        return 0;
    }

  
    cout << "\nEnter the name of the file you want to choose: ";
    char selectedFile[255];
    cin >> ws; 
    cin.getline(selectedFile, sizeof(selectedFile));

    bool fileFound = false;
    for (int i = 0; i < fileCount; i++) {
        if (strcmp(selectedFile, files[i]) == 0) {
            fileFound = true;
            break;
        }
    }

    if (!fileFound) {
        cout << "File not found in the directory, exiting program.\n";
        return 0;
    }

    cout << "You selected file: " << selectedFile << endl;

  
    Node* stack = nullptr;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1: Print file contents\n";
        cout << "2: Load file into stack\n";
        cout << "3: Print and free stack\n";
        cout << "4: Exit\n";
        cout << "Enter the number of your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            printFileContent(selectedFile);
            break;

        case 2:
            stack = LoadFileToStack(selectedFile);
            break;

        case 3:
            if (!stack) {
                cout << "Stack is empty.\n";
            }
            else {
                cout << "\nStack contents:\n";
                renumber(stack);
                purge(stack);
            }
            break;

        case 4:
            cout << "Exiting program.\n";
            purge(stack);
            return 0;

        default:
            cout << "Invalid choice, please try again.\n";
        }
    }
}
