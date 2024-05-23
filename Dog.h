#ifndef DOG_ENTITY_H
#define DOG_ENTITY_H
#include <string>

class Dog
{

public:
	Dog();
	Dog(const std::string& breed, const std::string& name, int age, const std::string& photo,int id);
	std::string get_breed() const;
	std::string get_name() const;
	int get_age() const;
	std::string get_photo() const;
	int get_id() const;
	void set_new_age(int new_age);
	void set_new_photo(std::string new_photo);
	std::string toString() const;

private:
	std::string breed;
	std::string name;
	int age;
	std::string photo;
	int id;

};

#endif
