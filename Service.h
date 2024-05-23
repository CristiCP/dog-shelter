#pragma once
#include "Dog.h"
#include "Repository.h"
#include <string>

class DogService
{
private:
	DogRepository& repository;
public:
	
	DogService(DogRepository& r) : repository{ r } {}
	DogRepository& getRepo() const { return repository; }
	std::vector<Dog> get_all_dogs() const;
	std::vector<Dog> get_all_adopted_dogs() const;
	bool check_if_dog_with_this_id_exist(const int dog_id) const;
	bool check_if_dog_with_this_information_exist(const Dog& dog) const;
	void add_new_dog(const std::string dog_breed,const std::string dog_name,int dog_age,const std::string dog_photo,int id);
	void delete_dog(const int dog_id);
	void update_dog(const int dog_id,const int new_age,const std::string new_photo);
	void adopt_dog(const Dog& dog);
	bool check_if_dog_is_already_adopted(const Dog& dog);
	void take_all_dogs_from_file();
	void take_all_adopted_dogs_from_file();
	void save_all_dogs_in_csv_file();
	void save_all_dogs_in_html_file();
};