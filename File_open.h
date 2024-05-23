#pragma once

#include <string>

class AdoptionListViewer {
protected:
    std::string file_path;

public:
    AdoptionListViewer(const std::string& filePath);

    virtual void view() = 0;
};

class CSVAdoptionListViewer : public AdoptionListViewer {
public:
    CSVAdoptionListViewer(const std::string& filePath);

    void view() override;
};

class HTMLAdoptionListViewer : public AdoptionListViewer {
public:
    HTMLAdoptionListViewer(const std::string& filePath);

    void view() override;
};
