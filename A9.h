#pragma once

#include <QtWidgets/QMainWindow>
#include <string>
#include <vector>
#include "ui_A9.h"
#include "Dog.h"
#include "ui_adminmodeWidget.h"
#include "ui_add_widget.h"
#include "ui_delete_widget.h"
#include "ui_update_widget.h"
#include "ui_userModeWidget.h"
#include "ui_adopt_dogs_widgetui.h"
#include "ui_adoption_list_view.h"
#include "ui_search_dogs_widget.h"
#include "Repository.h"
#include "Service.h"

class A9 : public QMainWindow
{
    Q_OBJECT

public:
    A9(QWidget* parent = nullptr);
    ~A9();

private:
    std::vector<Dog> all_dogs;
    std::vector<Dog> adopted_dogs;
    std::string file_type;
    Ui::A9Class ui;
    Ui::AddWidget addWidgetUi;
    Ui::DeleteWidget deleteWidgetUi;
    Ui::UpdateWidget updateWidgetUi;
    Ui::adoptDogsWidget adoptWidgetUi;
    Ui::AdoptionListViewWidget adoptListWidgetUi;
    Ui::searchDogsWidget searchDogsWidgetUi;
    DogRepository repository;
    DogService service{ repository };
    QWidget* shelterWidget;
    QWidget* adminModeWidget;
    QWidget* userModeWidget;
    QWidget* addModeWidget;
    QWidget* deleteModeWidget;
    QWidget* updateModeWidget;
    QWidget* adoptModeWidget;
    QWidget* adoptListWidget;
    QWidget* searchDogsWidget;
    QWidget* centralWidget;
    void populate(Ui::AdminMode adminModeUi);
    void populate_add_list(Ui::AddWidget addModeUi);
    void populate_delete_list(Ui::DeleteWidget deleteModeUi);
    void populate_update_list(Ui::UpdateWidget updateModeUi);
    void populate_user_mode(Ui::UserWidget userModeUi);
    void populate_adopt_dogs_list(Ui::adoptDogsWidget adoptWidgetUi);
    void populate_adopt_dogs_list_view(Ui::AdoptionListViewWidget adoptListWidgetUi);
    void populate_search_specific_dogs_list(Ui::searchDogsWidget searchDogsWidgetUi,const std::string dog_breed,const int dog_age);
    int id_counter=1;

public slots:
    void csv_file_selector();
    void htm_file_selector();
    void admin_mode();
    void add_dog_window();
    void add_new_dog();
    void exit_button();
    void delete_dog_window();
    void delete_dog();
    void update_dog_window();
    void update_dog();
    void back_button();
    void user_mode();
    void adopt_dogs_window();
    void exit_user_mode_button();
    void adopt_dogs();
    void adopt_list();
    void open_file();
    void search_dogs_window();
    void search_specific_dogs();
};