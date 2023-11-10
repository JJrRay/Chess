#pragma once
#include<iostream>

class kingInstanceError :public std::runtime_error {
	using runtime_error::runtime_error;
};
