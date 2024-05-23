#include "Dog.h"
using namespace std;

Dog::Dog() : breed(breed), name(name), age(age), photo(photo),id(id) {}

Dog::Dog(const std::string& breed, const std::string& name, int age, const std::string& photo,int id)
{
	this->breed = breed;
	this->name = name;
	this->age = age;
	this->photo = photo;
	this->id = id;

}

std::string Dog::get_breed() const
{
	return breed;
}

std::string Dog::get_name() const
{
	return name;
}

int Dog::get_age() const
{
	return age;
}

std::string Dog::get_photo() const
{
	return photo;
}

int Dog::get_id() const
{
	return id;
}

void Dog::set_new_age(int new_age) 
{
	age = new_age;
}

void Dog::set_new_photo(std::string new_photo)
{
	photo = new_photo;
}

std::string Dog::toString() const {
	return breed + " "  + name + " " + to_string(age) + " " + photo + " " + to_string(id);
}