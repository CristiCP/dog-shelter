#include "Service.h"
#include <iostream>
#include <string>

void DogService::take_all_dogs_from_file()
{
	repository.take_all_dogs_from_file();
}

void DogService::take_all_adopted_dogs_from_file()
{
	repository.take_all_adopted_dogs_from_file();
}

bool DogService::check_if_dog_with_this_id_exist(const int dog_id) const
{
	std::vector<Dog> dogs = repository.get_dogs();
	const auto it = std::find_if(dogs.begin(), dogs.end(),[dog_id](const Dog& dog) 
		{ return dog.get_id() == dog_id; });
	return it != dogs.end();
}

bool DogService::check_if_dog_with_this_information_exist(const Dog& dog) const
{
	const std::vector<Dog>& dogs = repository.get_dogs();
	const auto it = std::find_if(dogs.begin(), dogs.end(),
		[dog](const Dog& d) 
		{
			return d.get_name() == dog.get_name()
				&& d.get_breed() == dog.get_breed()
				&& d.get_age() == dog.get_age()
				&& d.get_photo() == dog.get_photo();
		});
	return it != dogs.end();
}

void DogService::add_new_dog(const std::string dog_breed, const std::string dog_name, int dog_age, const std::string dog_photo, int id)
{
	Dog dog(dog_breed, dog_name, dog_age, dog_photo, id);
	this->repository.add_new_dog(dog);
}

void DogService::delete_dog(const int dog_id)
{
	this->repository.delete_dog(dog_id);
}

void DogService::update_dog(const int dog_id,const int new_age,const std::string new_photo)
{
	this->repository.update_dog(dog_id,new_age,new_photo);
}

std::vector<Dog> DogService::get_all_dogs() const
{
	return this->repository.get_dogs();
}

std::vector<Dog> DogService::get_all_adopted_dogs() const
{
	return this->repository.get_adopted_dogs();
}

void DogService::adopt_dog(const Dog& dog)
{
	this->repository.adopt_dog(dog);
}

bool DogService::check_if_dog_is_already_adopted(const Dog& dog)
{
	const std::vector<Dog> dogs = this->get_all_adopted_dogs();
	const auto it = std::find_if(dogs.begin(), dogs.end(),
		[dog](const Dog& d) 
		{
			return d.get_name() == dog.get_name()
				&& d.get_breed() == dog.get_breed()
				&& d.get_age() == dog.get_age()
				&& d.get_photo() == dog.get_photo();
		});
	return it != dogs.end();
}

void DogService::save_all_dogs_in_csv_file() {
	repository.save_all_dogs_in_csv_file();
}

void DogService::save_all_dogs_in_html_file() {
	repository.save_all_dogs_in_html_file();
}