#include "Repository.h"
#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;


std::ifstream fin;
std::ofstream fout;

void DogRepository::take_all_dogs_from_file()
{
		fin.open("dogs.txt");

		int id, age;
		std::string breed, name, photo;

		while (fin >> breed >> name >> age >> photo >> id)
		{
			Dog new_dog(breed, name, age, photo, id);
			add_new_dog(new_dog);
		}
		fin.close();
}

void DogRepository::take_all_adopted_dogs_from_file()
{
	fin.open("adopted_dogs.txt");

	int id, age;
	std::string breed, name, photo;

	while (fin >> breed >> name >> age >> photo >> id)
	{
		Dog new_dog(breed, name, age, photo, id);
		adopt_dog(new_dog);
	}
	fin.close();

}

void DogRepository::save_all_dogs_in_file()
{
		fout.open("dogs.txt");

		for (int i = 0; i < dogs.size(); i++)
		{
			fout << dogs[i].get_breed() << " " << dogs[i].get_name() << " " <<
				dogs[i].get_age() << " " << dogs[i].get_photo() << " " << dogs[i].get_id() << std::endl;
		}
		fout.close();
}

void DogRepository::save_all_adopted_dogs_in_file()
{
	fout.open("adopted_dogs.txt");

	for (int i = 0; i < adopted_dogs.size(); i++)
	{
		fout << adopted_dogs[i].get_breed() << " " << adopted_dogs[i].get_name() << " " <<
			adopted_dogs[i].get_age() << " " << adopted_dogs[i].get_photo() << " " << adopted_dogs[i].get_id() << std::endl;
	}
	fout.close();
}

void DogRepository::save_all_dogs_in_csv_file()
{
	take_all_adopted_dogs_from_file();
	std::ofstream file("adoption_list.csv");
	if (file.is_open()) {
		for (size_t i = 0; i < adopted_dogs.size(); ++i) {
			file << adopted_dogs[i].get_breed() << "," << adopted_dogs[i].get_name() << "," << adopted_dogs[i].get_age() << ","
				<< adopted_dogs[i].get_photo() << "," << adopted_dogs[i].get_id();
			}
			file << endl;
		}
		file.close();
}

void DogRepository::save_all_dogs_in_html_file() 
{
	take_all_adopted_dogs_from_file();
	std::ofstream file("adoption_list.html");
	if (file.is_open()) {
		file << "<html>\n<head>\n<title>Dog List</title>\n</head>\n<body>\n";
		file << "<table>\n<tr>\n<th>Breed</th>\n<th>Name</th>\n<th>Age</th>\n<th>Photo</th>\n<th>ID</th>\n</tr>\n";
		for (const Dog& dog : adopted_dogs) {
			file << "<tr>\n";
			file << "<td>" << dog.get_breed() << "</td>\n";
			file << "<td>" << dog.get_name() << "</td>\n";
			file << "<td>" << dog.get_age() << "</td>\n";
			file << "<td>" << dog.get_photo() << "</td>\n";
			file << "<td>" << dog.get_id() << "</td>\n";
			file << "</tr>\n";
		}
		file << "</table>\n</body>\n</html>";
		file.close();
	}
}

void DogRepository::add_new_dog(const Dog& new_dog)
{
	this->dogs.push_back(new_dog);
	save_all_dogs_in_file();
}

void DogRepository::delete_dog(const int dog_id)
{
	auto it = std::find_if(dogs.begin(), dogs.end(), [dog_id](const Dog& d) {
		return d.get_id() == dog_id;
		});

	if (it != dogs.end()) 
	{
		dogs.erase(it);

		save_all_dogs_in_file();
	}
}

void DogRepository::update_dog(const int dog_id, const int new_age, const std::string new_photo)
{
	auto it = std::find_if(dogs.begin(), dogs.end(), [dog_id](const Dog& d) {
		return d.get_id() == dog_id;
		});

	if (it != dogs.end()) 
	{
		it->set_new_age(new_age);
		it->set_new_photo(new_photo);
		save_all_dogs_in_file();
	}
}

void DogRepository::adopt_dog(const Dog& dog)
{
	this->adopted_dogs.push_back(dog);
	save_all_adopted_dogs_in_file();
}