#include "A9.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include "ui_shelterWidget.h"
#include "ui_adminmodeWidget.h"
#include "ui_add_widget.h"
#include "File_open.h"

A9::A9(QWidget *parent)
    : QMainWindow(parent)
{
    service.take_all_dogs_from_file();
    service.take_all_adopted_dogs_from_file();
    all_dogs = service.get_all_dogs();
    adopted_dogs = service.get_all_adopted_dogs();
    ui.setupUi(this);
}

A9::~A9()
{}

void A9::csv_file_selector() {
    this->file_type = "csv";
    this->centralWidget = new QWidget{};
    this->shelterWidget = new QWidget{};
    Ui::Form shelterUi;
    shelterUi.setupUi(this->shelterWidget);
    QPushButton* pushButton = shelterUi.pushButton;
    QObject::connect(pushButton, &QPushButton::clicked, this, &A9::admin_mode);
    QPushButton* pushButton_2 = shelterUi.pushButton_2;
    QObject::connect(pushButton_2, &QPushButton::clicked, this, &A9::user_mode);
    QPushButton* pushButton_3 = shelterUi.pushButton_3;
    QObject::connect(pushButton_3, &QPushButton::clicked, this, &A9::open_file);
    this->setCentralWidget(this->shelterWidget);
}

void A9::htm_file_selector() {
    this->file_type = "html";
    this->centralWidget = new QWidget{};
    this->shelterWidget = new QWidget{};
    Ui::Form shelterUi;
    shelterUi.setupUi(this->shelterWidget);
    QPushButton* pushButton = shelterUi.pushButton;
    QObject::connect(pushButton, &QPushButton::clicked, this, &A9::admin_mode);
    QPushButton* pushButton_2 = shelterUi.pushButton_2;
    QObject::connect(pushButton_2, &QPushButton::clicked, this, &A9::user_mode);
    QPushButton* pushButton_3 = shelterUi.pushButton_3;
    QObject::connect(pushButton_3, &QPushButton::clicked, this, &A9::open_file);
    this->setCentralWidget(this->shelterWidget);
}

void A9::admin_mode()
{   
    all_dogs = service.get_all_dogs();
    this->centralWidget = new QWidget{};
    this->adminModeWidget = new QWidget{};
    Ui::AdminMode adminModeUi;
    adminModeUi.setupUi(this->adminModeWidget);
    this->populate(adminModeUi);
    QPushButton* pushButton = adminModeUi.pushButton;
    QObject::connect(pushButton, &QPushButton::clicked, this, &A9::add_dog_window);
    QPushButton* pushButton_2 = adminModeUi.pushButton_2;
    QObject::connect(pushButton_2, &QPushButton::clicked, this, &A9::delete_dog_window);
    QPushButton* pushButton_3 = adminModeUi.pushButton_3;
    QObject::connect(pushButton_3, &QPushButton::clicked, this, &A9::update_dog_window);
    QPushButton* pushButton_4 = adminModeUi.pushButton_4;
    QObject::connect(pushButton_4, &QPushButton::clicked, this, &A9::back_button);
    this->setCentralWidget(this->adminModeWidget);
}

void A9::populate(Ui::AdminMode adminModeUi) {
    adminModeUi.DogsList->clear();
    for (int i = 0; i < all_dogs.size(); i++)
        adminModeUi.DogsList->addItem(QString::fromStdString(all_dogs[i].toString()));
    adminModeUi.DogsList->setCurrentRow(0);
}

void A9::add_dog_window() {
    this->centralWidget = new QWidget{};
    this->addModeWidget = new QWidget{};
    addWidgetUi.setupUi(this->addModeWidget);
    this->populate_add_list(addWidgetUi);
    QPushButton* pushButton = addWidgetUi.pushButton;
    QObject::connect(pushButton, &QPushButton::clicked, this, &A9::add_new_dog);
    QPushButton* pushButton_2 = addWidgetUi.pushButton_2;
    QObject::connect(pushButton_2, &QPushButton::clicked, this, &A9::exit_button);
    this->setCentralWidget(this->addModeWidget);
}

void A9::populate_add_list(Ui::AddWidget addModeUi) {
    addModeUi.DogsList->clear();
    for (int i = 0; i < all_dogs.size(); i++)
        addModeUi.DogsList->addItem(QString::fromStdString(all_dogs[i].toString()));
    addModeUi.DogsList->setCurrentRow(0);
}

void A9::add_new_dog() {
    std::string breed = addWidgetUi.breedLineEdit->text().toStdString();
    std::string name = addWidgetUi.nameLineEdit->text().toStdString();
    std::string ageText = addWidgetUi.ageLineEdit->text().toStdString();
    std::string photo = addWidgetUi.photoLineEdit->text().toStdString();
    if (breed.empty() || name.empty() || ageText.empty() || photo.empty()) {
        QMessageBox::critical(this, "Error", "Please fill in all the required fields.");
        return;
    }
    bool ok;
    int age = QString(ageText.c_str()).toInt(&ok);
    if (!ok || age < 0) {
        QMessageBox::critical(this, "Error", "Invalid age. Please enter a valid integer.");
        return;
    }
    while (service.check_if_dog_with_this_id_exist(id_counter) == true)
        id_counter++;
    this->service.add_new_dog(breed, name, age, photo, id_counter);
    id_counter++;
    all_dogs = service.get_all_dogs();
    add_dog_window();
}

void A9::exit_button() {
    admin_mode();
}

void A9::delete_dog_window() {
    this->centralWidget = new QWidget{};
    this->deleteModeWidget = new QWidget{};
    deleteWidgetUi.setupUi(this->deleteModeWidget);
    this->populate_delete_list(deleteWidgetUi);
    QPushButton* pushButton = deleteWidgetUi.pushButton;
    QObject::connect(pushButton, &QPushButton::clicked, this, &A9::delete_dog);
    QPushButton* pushButton_2 = deleteWidgetUi.pushButton_2;
    QObject::connect(pushButton_2, &QPushButton::clicked, this, &A9::exit_button);
    this->setCentralWidget(this->deleteModeWidget);
}

void A9::populate_delete_list(Ui::DeleteWidget deleteModeUi) {
    deleteModeUi.DogsList->clear();
    for (int i = 0; i < all_dogs.size(); i++)
        deleteModeUi.DogsList->addItem(QString::fromStdString(all_dogs[i].toString()));
    deleteModeUi.DogsList->setCurrentRow(0);
}

void A9::delete_dog() {
    std::string idText = deleteWidgetUi.idLineEdit->text().toStdString();
    if (idText.empty()) {
        QMessageBox::critical(this, "Error", "Please fill in the required field.");
        return;
    }
    bool ok;
    int id = QString(idText.c_str()).toInt(&ok);
    if (!ok || id < 0) {
        QMessageBox::critical(this, "Error", "Invalid ID. Please enter a valid ID.");
        return;
    }
    if (this->service.check_if_dog_with_this_id_exist(id) == false) {
        QMessageBox::critical(this, "Error", "Dog with this ID does not exist.");
        return;
    }
    this->service.delete_dog(id);
    all_dogs = service.get_all_dogs();
    delete_dog_window();
}

void A9::update_dog_window() {
    this->centralWidget = new QWidget{};
    this->updateModeWidget = new QWidget{};
    updateWidgetUi.setupUi(this->updateModeWidget);
    this->populate_update_list(updateWidgetUi);
    QPushButton* pushButton = updateWidgetUi.pushButton;
    QObject::connect(pushButton, &QPushButton::clicked, this, &A9::update_dog);
    QPushButton* pushButton_2 = updateWidgetUi.pushButton_2;
    QObject::connect(pushButton_2, &QPushButton::clicked, this, &A9::exit_button);
    this->setCentralWidget(this->updateModeWidget);
}

void A9::populate_update_list(Ui::UpdateWidget updateModeUi) {
    updateModeUi.DogsList->clear();
    for (int i = 0; i < all_dogs.size(); i++)
        updateModeUi.DogsList->addItem(QString::fromStdString(all_dogs[i].toString()));
    updateModeUi.DogsList->setCurrentRow(0);
}

void A9::update_dog() {
    std::string idText = updateWidgetUi.idLineEdit->text().toStdString();
    std::string newAgeText = updateWidgetUi.newageLineEdit->text().toStdString();
    std::string newPhotoText = updateWidgetUi.newphotoLineEdit->text().toStdString();
    if (idText.empty() || newAgeText.empty() || newPhotoText.empty()) {
        QMessageBox::critical(this, "Error", "Please fill in all the required fields.");
        return;
    }
    bool ok;
    int id = QString(idText.c_str()).toInt(&ok);
    if (!ok || id < 0) {
        QMessageBox::critical(this, "Error", "Invalid ID. Please enter a valid ID.");
        return;
    }
    int newAge = QString(newAgeText.c_str()).toInt(&ok);
    if (!ok || newAge < 0) {
        QMessageBox::critical(this, "Error", "Invalid Age. Please enter a valid integer.");
        return;
    }
    if (this->service.check_if_dog_with_this_id_exist(id) == false) {
        QMessageBox::critical(this, "Error", "Dog with this ID does not exist.");
        return;
    }
    this->service.update_dog(id, newAge, newPhotoText);
    all_dogs = service.get_all_dogs();
    update_dog_window();
}

void A9::back_button() {
    if (this->file_type == "csv")
        csv_file_selector();
    else
        htm_file_selector();
}

void A9::user_mode() {
    all_dogs = service.get_all_dogs();
    adopted_dogs = service.get_all_adopted_dogs();
    this->centralWidget = new QWidget{};
    this->userModeWidget = new QWidget{};
    Ui::UserWidget userModeUi;
    userModeUi.setupUi(this->userModeWidget);
    this->populate_user_mode(userModeUi);
    QPushButton* pushButton = userModeUi.pushButton;
    QObject::connect(pushButton, &QPushButton::clicked, this, &A9::adopt_dogs_window);
    QPushButton* pushButton_2 = userModeUi.pushButton_2;
    QObject::connect(pushButton_2, &QPushButton::clicked, this, &A9::search_dogs_window);
    QPushButton* pushButton_3 = userModeUi.pushButton_3;
    QObject::connect(pushButton_3, &QPushButton::clicked, this, &A9::adopt_list);
    QPushButton* pushButton_4 = userModeUi.pushButton_4;
    QObject::connect(pushButton_4, &QPushButton::clicked, this, &A9::back_button);
    this->setCentralWidget(this->userModeWidget);
}

void A9::populate_user_mode(Ui::UserWidget userModeUi) {
    userModeUi.DogsList->clear();
    for (int i = 0; i < all_dogs.size(); i++)
        userModeUi.DogsList->addItem(QString::fromStdString(all_dogs[i].toString()));
    userModeUi.DogsList->setCurrentRow(0);
}

void A9::adopt_dogs_window() {
    this->centralWidget = new QWidget{};
    this->adoptModeWidget = new QWidget{};
    adoptWidgetUi.setupUi(this->adoptModeWidget);
    this->populate_adopt_dogs_list(adoptWidgetUi);
    QPushButton* pushButton = adoptWidgetUi.pushButton;
    QObject::connect(pushButton, &QPushButton::clicked, this, &A9::adopt_dogs);
    QPushButton* pushButton_2 = adoptWidgetUi.pushButton_2;
    QObject::connect(pushButton_2, &QPushButton::clicked, this, &A9::exit_user_mode_button);
    this->setCentralWidget(this->adoptModeWidget);
}

void A9::populate_adopt_dogs_list(Ui::adoptDogsWidget adoptWidgetUi) {
    adoptWidgetUi.DogsList->clear();
    for (int i = 0; i < all_dogs.size(); i++)
        adoptWidgetUi.DogsList->addItem(QString::fromStdString(all_dogs[i].toString()));
    adoptWidgetUi.DogsList->setCurrentRow(0);
}

void A9::exit_user_mode_button() {
    user_mode();
}

void A9::adopt_dogs() {
    std::string idText = adoptWidgetUi.idLineEdit->text().toStdString();
    if (idText.empty()) {
        QMessageBox::critical(this, "Error", "Please fill in the required field.");
        return;
    }
    bool ok;
    int id = QString(idText.c_str()).toInt(&ok);
    if (!ok || id < 0) {
        QMessageBox::critical(this, "Error", "Invalid ID. Please enter a valid ID.");
        return;
    }
    if (this->service.check_if_dog_with_this_id_exist(id) == false) {
        QMessageBox::critical(this, "Error", "Dog with this ID does not exist.");
        return;
    }
    if (this->service.check_if_dog_is_already_adopted(id) == true) {
        QMessageBox::critical(this, "Error", "Dog with this ID is already adopted.");
        return;
    }
    this->service.adopt_dog(id);
}

void A9::adopt_list() {
    this->centralWidget = new QWidget{};
    this->adoptListWidget = new QWidget{};
    adoptListWidgetUi.setupUi(this->adoptListWidget);
    this->populate_adopt_dogs_list_view(adoptListWidgetUi);
    QPushButton* pushButton = adoptListWidgetUi.pushButton;
    QObject::connect(pushButton, &QPushButton::clicked, this, &A9::exit_user_mode_button);
    this->setCentralWidget(this->adoptListWidget);
}

void A9::populate_adopt_dogs_list_view(Ui::AdoptionListViewWidget adoptListWidgetUi) {
    adoptListWidgetUi.DogsList->clear();
    for (int i = 0; i < adopted_dogs.size(); i++)
        adoptListWidgetUi.DogsList->addItem(QString::fromStdString(adopted_dogs[i].toString()));
    adoptListWidgetUi.DogsList->setCurrentRow(0);
}

void A9::open_file() {
    if (file_type == "csv") {
        std::string csv_file_path = "adoption_list.csv";
        CSVAdoptionListViewer csv_viewer(csv_file_path);
        csv_viewer.view();
    }
    else if (file_type == "html") {
        std::string html_file_path = "adoption_list.html";
        HTMLAdoptionListViewer html_viewer(html_file_path);
        html_viewer.view();
    }
}

void A9::search_dogs_window() {
    this->centralWidget = new QWidget{};
    this->searchDogsWidget = new QWidget{};
    searchDogsWidgetUi.setupUi(this->searchDogsWidget);
    QPushButton* pushButton = searchDogsWidgetUi.pushButton;
    QObject::connect(pushButton, &QPushButton::clicked, this, &A9::search_specific_dogs);
    QPushButton* pushButton_2 = searchDogsWidgetUi.pushButton_2;
    QObject::connect(pushButton_2, &QPushButton::clicked, this, &A9::exit_user_mode_button);
    this->setCentralWidget(this->searchDogsWidget);
}

void A9::search_specific_dogs() {
    std::string breedText = searchDogsWidgetUi.breedLineEdit->text().toStdString();
    if (breedText.empty()) {
        QMessageBox::critical(this, "Error", "Please fill in the required fields.");
        return;
    }
    std::string ageText = searchDogsWidgetUi.ageLineEdit->text().toStdString();
    if (ageText.empty()) {
        QMessageBox::critical(this, "Error", "Please fill in the required fields.");
        return;
    }
    bool ok;
    int age = QString(ageText.c_str()).toInt(&ok);
    if (!ok || age < 0) {
        QMessageBox::critical(this, "Error", "Invalid age. Please enter a valid number.");
        return;
        }
    this->populate_search_specific_dogs_list(searchDogsWidgetUi,breedText, age);
}

void A9::populate_search_specific_dogs_list(Ui::searchDogsWidget searchDogsWidgetUi,const std::string dog_breed,const int dog_age) {
    searchDogsWidgetUi.DogsList->clear();
    for (int i = 0; i < service.search_specific_dogs(dog_breed,dog_age).size(); i++)
        searchDogsWidgetUi.DogsList->addItem(QString::fromStdString(service.search_specific_dogs(dog_breed, dog_age)[i].toString()));
    searchDogsWidgetUi.DogsList->setCurrentRow(0);
}