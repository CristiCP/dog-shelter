#pragma once

#include "Dog.h"
#include <qwidget.h>
#include <QtWidgets/QMainWindow>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>

class GUI : public QWidget
{
    Q_OBJECT
private:
    std::vector<Dog> dogs;

public:
    GUI(const std::vector<Dog>& dogs, QWidget* parent = 0);
    void initGUI();
    ~GUI();

private:
    QListWidget* dogs_list;

    QLineEdit* dog_breed;
    QLineEdit* dog_name;
    QLineEdit* dog_age;
    QLineEdit* dog_photo;

    QPushButton* admin_button;
    QPushButton* user_button;

    QPushButton* exit_button;
    QPushButton* add_button;
    QPushButton* remove_button;
    QPushButton* update_button;
    QPushButton* display_button;
    QPushButton* display_by_age_button;
    QPushButton* display_adopted_dogs_button;
    QPushButton* adopt_dogs_button;

    void populateList();
    void connectSignalsAndSlots();

    void listItemChanged();
    int getSelectedIndex();

signals:
    void mySignal();
};
