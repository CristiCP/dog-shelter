#include "Ui.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <qlabel.h>

GUI::GUI(const std::vector<Dog>& dogs, QWidget* parent) : QWidget{ parent }, dogs{ dogs } {
    this->initGUI();
    this->populateList();
    this->connectSignalsAndSlots();
}

void GUI::initGUI() {
    QHBoxLayout* layout = new QHBoxLayout{ this };
    dogs_list = new QListWidget{};

    layout->addWidget(dogs_list);

    QVBoxLayout* dogs_data_layout = new QVBoxLayout{};
    dogs_data_layout->addLayout(dogs_data_layout);

    QFormLayout* dogs_info_layout = new QFormLayout{};
    QLabel* breed_label = new QLabel{ "&Breed" };
    dog_breed = new QLineEdit{};
    breed_label->setBuddy(dog_breed);

    QLabel* name_label = new QLabel{ "&Name" };
    dog_name = new QLineEdit{};
    name_label->setBuddy(dog_name);

    QLabel* age_label = new QLabel{ "&Age" };
    dog_age = new QLineEdit{};
    age_label->setBuddy(dog_age);

    QLabel* photo_label = new QLabel{ "&Photo" };
    dog_photo = new QLineEdit{};
    photo_label->setBuddy(dog_photo);

    dogs_info_layout->addRow(breed_label, dog_breed);
    dogs_info_layout->addRow(name_label, dog_name);
    dogs_info_layout->addRow(age_label, dog_age);
    dogs_info_layout->addRow(photo_label, dog_photo);

    dogs_data_layout->addLayout(dogs_info_layout);

    layout->addLayout(dogs_data_layout);

    QVBoxLayout* buttonsLayout = new QVBoxLayout{this};
    exit_button = new QPushButton{ "Exit" };
    admin_button = new QPushButton{ "Administrator mode" };
    user_button = new QPushButton{ "User mode" };
    add_button = new QPushButton{ "Add dog" };
    remove_button = new QPushButton{ "Remove event" };
    update_button = new QPushButton{ "Update event" };
    display_button = new QPushButton{ "Display dogs" };
    display_by_age_button = new QPushButton{ "Display dogs by age" };
    adopt_dogs_button = new QPushButton{ "Adopt dogs" };
    display_adopted_dogs_button = new QPushButton{ "Display adopted dogs" };
    buttonsLayout->addWidget(exit_button);
    buttonsLayout->addWidget(admin_button);
    buttonsLayout->addWidget(user_button);
    buttonsLayout->addWidget(add_button);
    buttonsLayout->addWidget(remove_button);
    buttonsLayout->addWidget(update_button);
    buttonsLayout->addWidget(display_button);
    buttonsLayout->addWidget(display_by_age_button);
    buttonsLayout->addWidget(adopt_dogs_button);
    buttonsLayout->addWidget(display_adopted_dogs_button);

    layout->addLayout(buttonsLayout);
}

GUI::~GUI()
{}

void GUI::populateList() {
    dogs_list->clear();
    for (int i=0;i<dogs.size();i++)
        dogs_list->addItem(QString::fromStdString(dogs[i].toString()));
    dogs_list->setCurrentRow(0);
}

void GUI::connectSignalsAndSlots() {
    QObject::connect(dogs_list, &QListWidget::itemSelectionChanged, this, &GUI::listItemChanged);

    QObject::connect(add_button, &QPushButton::clicked, this, [&]() {
        populateList();
        dogs_list->setCurrentRow(dogs.size() - 1);
        });
    emit mySignal();
}

void GUI::listItemChanged() {
    int index = getSelectedIndex();
    if (index < 0)
        return;

    Dog dog = dogs[index];
    dog_breed->setText(QString::fromStdString(dog.get_breed()));
    dog_name->setText(QString::fromStdString(dog.get_name()));
    dog_photo->setText(QString::fromStdString(dog.get_photo()));
}

int GUI::getSelectedIndex() {
    int currentRow = dogs_list->currentRow();

    return currentRow;
}