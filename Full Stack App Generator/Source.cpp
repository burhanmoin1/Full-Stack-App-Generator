#include <windows.h>
#include <iostream>
#include <string>
#include <filesystem>

using namespace std;
namespace fs = filesystem;


int displayMainMenu() {
    cout << "Options:" << endl;
    cout << "1. Create a new app" << endl;
    cout << "2. Work on an existing app" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice (1-3): ";

    int choice;
    cin >> choice;


    return choice; // Return the user's choice
}

void displayFolders(const string& basePath) {
    if (fs::exists(basePath) && fs::is_directory(basePath)) { // Check if the base path exists and is a directory
        cout << "Folders in " << basePath << ":" << endl;
        for (const auto& entry : fs::directory_iterator(basePath)) { // Iterate over all entries in the directory
            if (fs::is_directory(entry.path())) { // Check if the entry is a folder
                cout << "- " << entry.path().filename().string() << endl; // Output the folder name
            }
        }
    }
    else {
        cout << "Path does not exist or is not a directory." << endl;
    }
}

void VisualStudioOpen() {
    const wchar_t* vsCodePath = L"C:\\Users\\XC\\AppData\\Local\\Programs\\Microsoft VS Code\\Code.exe";

    // Open Visual Studio Code
    HINSTANCE result = ShellExecuteW(NULL, L"open", vsCodePath, NULL, NULL, SW_SHOW);

    if (reinterpret_cast<int>(result) <= 32) { // Check for failure
        cerr << "Failed to open Visual Studio Code." << endl;
    }
    else {
        cout << "Visual Studio Code opened successfully." << endl;
    }
}

void createFolder(const string& basePath) {
    string webapp = " Web App";
    cout << "Enter the name of the initial folder: ";
    string folderName;
    cin >> folderName;

    string initialFolder = basePath + "\\" + folderName + webapp;

    if (!fs::exists(initialFolder)) {
        fs::create_directory(initialFolder);
        cout << "Created folder: " << initialFolder << endl;
    }
    else {
        cout << "Folder already exists: " << initialFolder << endl;
    }

    // Create subfolders
    string frontendFolder = initialFolder + "\\Frontend";
    string backendFolder = initialFolder + "\\Backend";

    if (!fs::exists(frontendFolder)) {
        fs::create_directory(frontendFolder);
        cout << "App created successfully" << endl;
    }
    if (!fs::exists(backendFolder)) {
        fs::create_directory(backendFolder);
        cout << "Created subfolder: " << backendFolder << endl;
    }
}
void exitProgram() {
    cout << "Exiting program." << endl;
    exit(0); // Terminate the program
}

int main() {
    string basePath = "C:\\Users\\XC\\OneDrive\\Documents\\Full Stack App Generator CProject";
    while (true) { // Main program loop
        int choice = displayMainMenu(); // Get the user's choice

        if (choice == -1) { // If invalid input, continue the loop
            continue;
        }

        switch (choice) {
        case 1: {
            createFolder(basePath); // Create a new app
            break;
        }
        case 2: {
            displayFolders(basePath);
            break;
        }
        case 3: {
            exitProgram();
            break;
        }
        default: {
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        }
    }

    return 0;
}
