#include <iostream>

#include "FourNetworking/FourNetworking.h"

int main(int argc, char* argv[])
{
	std::cout << "Hello Client!. enum is : " << static_cast<int>(four::net::testEnum::enum2) << "\n";
	return 0;
}