#include <iostream>
#include <cstring>
#include "textutils.h"

using namespace std;

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

    StringStack s;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1: Print file contents\n";
        cout << "2: Load file into stack\n";
        cout << "3: Print and free stack\n";
        cout << "4: Reverse stack\n";
        cout << "5: Read file line-by-line using Lines\n";
        cout << "6: Enter text and save to file (Lines)\n";
        cout << "7: Exit\n";
        cout << "8: Copy file with renumbered lines\n";
        cout << "9: Save text to JSON file\n";
        cout << "Enter the number of your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            printFileContent(selectedFile);
            break;

        case 2:
            s.loadFromFile(selectedFile);
            break;

        case 3:
            if (s.empty()) {
                cout << "Stack is empty.\n";
            }
            else {
                s.renumber();
                s.purge();
            }
            break;

        case 4:
            s.reverse();
            cout << "Stack reversed.\n";
            break;

        case 5: {
            vector<string> lines = Lines::readLines(selectedFile);
            cout << "\nLine-by-line file content:\n";
            int lineNo = 1;
            for (const auto& line : lines) {
                cout << lineNo++ << ": " << line << endl;
            }
            break;
        }

        case 6: {
            cin.ignore();
            vector<string> userLines;
            string input;
            cout << "Enter lines to save (type 'END' on a new line to finish):\n";
            while (true) {
                getline(cin, input);
                if (input == "END") break;
                userLines.push_back(input);
            }

            char targetFile[255];
            cout << "\nEnter the name of the file to save into: ";
            cin.getline(targetFile, sizeof(targetFile));

            bool validFile = false;
            for (int i = 0; i < fileCount; i++) {
                if (strcmp(targetFile, files[i]) == 0) {
                    validFile = true;
                    break;
                }
            }

            if (!validFile) {
                cout << "File not found in directory. Try again.\n";
                break;
            }

            int modeChoice;
            cout << "Choose mode:\n1 - Overwrite file\n2 - Append to file\nYour choice: ";
            cin >> modeChoice;
            bool append = (modeChoice == 2);

            Lines::writeLinesToFile(targetFile, userLines, append);
            break;
        }

        case 7:
            cout << "Exiting program.\n";
            s.purge();
            return 0;

        case 8: {
            char destFile[255];
            cout << "Enter destination file name: ";
            cin >> ws;
            cin.getline(destFile, sizeof(destFile));

            FileCopier::copyWithRenumbering(selectedFile, destFile);
            break;
        }

        case 9: {
            char jsonFile[255];
            cout << "Enter JSON file name: ";
            cin >> ws;
            cin.getline(jsonFile, sizeof(jsonFile));

            saveToJsonFile(jsonFile);
            break;
        }

        default:
            cout << "Invalid choice, please try again.\n";
        }
    }
}
