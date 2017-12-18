#include "IOManager.h"
#include<fstream>
namespace Bengine{
	bool IOManager::readFileToBuffer(string filePath, vector<unsigned char>&buffer){
		std::ifstream file(filePath, std::ios::binary);//reading in binary
		if (file.fail()){
			perror(filePath.c_str());
			return false;
		}
		//how big is the file?

		//seek to the end
		file.seekg(0, std::ios::end);

		//get file size
		int fileSize = file.tellg();

		//seek back to begining
		file.seekg(0, std::ios::beg);

		fileSize -= file.tellg();

		//resizing the buffer
		buffer.resize(fileSize);

		file.read((char*)&(buffer[0]), fileSize);

		file.close();

	}

}
	
