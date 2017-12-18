#pragma once
#include<iostream>
#include<vector>
#include<string>
using std::string;
using std::vector;
//making static class
//only one instance
//no need of multiple iomanager
namespace Bengine{
	class IOManager
	{
	public:
		static bool readFileToBuffer(string filePath, vector<unsigned char>&buffer);//passing by reference
	};
}
