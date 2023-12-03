#pragma once

#include <mutex>
#include <string>

struct MyStruct
{
private:
	int field_0 = 1;
	int field_1 = 1;
	int field_2 = 1;

	mutable std::mutex mutex;
public:
	MyStruct() = default;

	void set(int index, int value);
	int get(int index) const;
	operator std::string() const;
};
