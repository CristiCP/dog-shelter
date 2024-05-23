#include "Validator.h"
#include "Exception.h"

bool UiValidator::valid_age(int age)
{
	if (age < 0)
		throw Exception("Age should be a valid number");
	return true;
	
}
