#include "File_open.h"
#include <iostream>
#include <fstream>
#include <windows.h>

AdoptionListViewer::AdoptionListViewer(const std::string& filePath) : file_path(filePath) {}

CSVAdoptionListViewer::CSVAdoptionListViewer(const std::string& filePath) : AdoptionListViewer(filePath) {}

void CSVAdoptionListViewer::view() {
    if (std::ifstream(file_path)) {
        std::string file_extension = file_path.substr(file_path.find_last_of('.') + 1);

        if (file_extension == "csv") {
            system(("notepad " + file_path).c_str());
        }
    }
}

HTMLAdoptionListViewer::HTMLAdoptionListViewer(const std::string& filePath) : AdoptionListViewer(filePath) {}

void HTMLAdoptionListViewer::view() {
    if (std::ifstream(file_path)) {
        std::string file_extension = file_path.substr(file_path.find_last_of('.') + 1);

        if (file_extension == "html") {
            std::wstring wide_file_path(file_path.begin(), file_path.end());
            ShellExecute(NULL, L"open", wide_file_path.c_str(), NULL, NULL, SW_SHOWNORMAL);
        }
    }
}