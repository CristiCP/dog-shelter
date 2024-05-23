#pragma once
#include "Dog.h"
#include "RepositoryValidator.h"
#include "Exception.h"
#include <vector>

class DogRepository
{
private:
	std::vector<Dog> dogs;
	std::vector<Dog> adopted_dogs;

public:
	DogRepository() {}
	void add_new_dog(const Dog& new_dog);
	void delete_dog(const int dog);
	void update_dog(const int dog_id,const int new_age,const std::string new_photo);
	std::vector<Dog> get_dogs() const {return dogs; }
	std::vector<Dog> get_adopted_dogs() const { return adopted_dogs; }
	void adopt_dog(const Dog& dog);
	void take_all_dogs_from_file();
	void take_all_adopted_dogs_from_file();
	void save_all_dogs_in_file();
	void save_all_adopted_dogs_in_file();
	void save_all_dogs_in_csv_file();
	void save_all_dogs_in_html_file();
};