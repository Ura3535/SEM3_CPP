#include "my_struct.h"

void MyStruct::set(int index, int value)
{
	mutex.lock();
	switch (index)
	{
	case 0:
		field_0 = value;
		break;
	case 1:
		field_1 = value;
		break;
	case 2:
		field_2 = value;
		break;
	default:
		mutex.unlock();
		throw std::out_of_range("MyStruct has only 3 fields");
	}
	mutex.unlock();
}

int MyStruct::get(int index) const
{
	mutex.lock();
	int res = 0;
	switch (index)
	{
	case 0:
		res = field_0;
		break;
	case 1:
		res = field_1;
		break;
	case 2:
		res = field_2;
		break;
	default:
		mutex.unlock();
		throw std::out_of_range("MyStruct has only 3 fields");
	}
	mutex.unlock();
	return res;
}

MyStruct::operator std::string() const
{
	mutex.lock();
	std::string res("field_0 = " + std::to_string(field_0) + ';' +
				   " field_1 = " + std::to_string(field_1) + ';' +
				   " field_2 = " + std::to_string(field_2) + ';');
	mutex.unlock();
	return res;
}
