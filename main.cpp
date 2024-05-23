#include <QApplication>
#include "Ui.h"
#include "Repository.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    DogRepository repository;
    repository.take_all_dogs_from_file();
    GUI w{ repository.get_dogs() };
    w.initGUI();
    w.show();
    return app.exec();
}