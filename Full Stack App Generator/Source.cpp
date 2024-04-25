#include <windows.h>
#include <iostream>
#include <string>
#include <filesystem>

using namespace std;
namespace fs = filesystem;


int displayMainMenu() {
    cout << "1. Create a new app" << endl;
    cout << "2. Work on an existing app" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice (1-3): ";

    int choice;
    cin >> choice;


    return choice; // Return the user's choice
}

vector<string> getFolders(const string& basePath) {
    vector<string> folderNames; // To store folder names

    if (fs::exists(basePath) && fs::is_directory(basePath)) { // Check if the base path exists and is a directory
        for (const auto& entry : fs::directory_iterator(basePath)) { // Iterate over all entries
            if (fs::is_directory(entry.path())) { // Check if it's a folder
                string folderName = entry.path().filename().string(); // Get folder name
                folderNames.push_back(folderName); // Add to the list
            }
        }
    }

    return folderNames; // Return the list of folder names
}

void openFolderInVSCode(const std::string& basePath) {
    // Retrieve folder names
    vector<string> folders = getFolders(basePath);

    if (folders.empty()) {
        cout << "No folders found in the specified path." << endl;
        return;
    }

    // Display available folders
    cout << "Available folders:" << endl;
    for (size_t i = 0; i < folders.size(); ++i) {
        cout << i + 1 << ". " << folders[i] << endl;
    }

    // Prompt the user to select a folder
    cout << "Select a folder number to open in Visual Studio Code: ";
    int folderChoice;
    cin >> folderChoice;

    if (folderChoice >= 1 && folderChoice <= folders.size()) { // Valid choice
        string selectedFolder = basePath + "\\" + folders[folderChoice - 1];
        string command = "code \"" + selectedFolder + "\""; // Open VS Code in the specified folder
        system(command.c_str()); // Execute the command
    }
    else {
        cout << "Invalid choice. Please enter a number within the valid range." << endl;
    }
}

void createFolder(const std::string& basePath) {
    std::cout << "Enter the name of the initial folder: ";

    std::string folderName;
    std::cin.ignore(); // Clear any leftover newline in the buffer
    std::getline(std::cin, folderName); // Get the full folder name, including spaces

    std::string initialFolder = basePath + "\\" + folderName;

    if (!fs::exists(initialFolder)) {
        fs::create_directory(initialFolder);
        std::cout << "Web App folder created successfully: " << initialFolder << std::endl;
    }
    else {
        std::cout << "Folder already exists: " << initialFolder << std::endl;
    }

    // Create Frontend and Backend subfolders
    std::string frontendFolder = initialFolder + "\\Frontend";
    std::string backendFolder = initialFolder + "\\Backend";

    if (!fs::exists(frontendFolder)) {
        fs::create_directory(frontendFolder);
    }

    if (!fs::exists(backendFolder)) {
        fs::create_directory(backendFolder);
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
            openFolderInVSCode(basePath);
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
