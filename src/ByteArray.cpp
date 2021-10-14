#include "include/ByteArray.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>


std::ostream& operator<<(std::ostream& os, const ByteArray& s) {
	return operator<<(os, s.recebeConteudoVetor());
}

std::ostream& operator<<(std::ostream& os, const std::vector<unsigned char>& s) {
	std::ios::fmtflags oldFlags = os.flags();
	os << std::hex;
	for (ByteArray::const_iterador i = s.begin(); i != s.end(); ++i) {
		os << "0x" << static_cast<unsigned int>(static_cast<unsigned char>(*i));
		if (i + 1 < s.end()) {
			os << " ";
		}
	}
	os << std::endl;
	os.flags(oldFlags);
	return os;
}

static const int BUFFER_SIZE = 4096;

ByteArray ByteArray::criaDeArquivo(const std::string& file)  {
	std::ifstream input(file.c_str(), std::ios_base::in|std::ios_base::binary);
	std::vector<unsigned char> data;
	while (input.good()) {
		size_t oldSize = data.size();
		data.resize(oldSize + BUFFER_SIZE);
		input.read(reinterpret_cast<char*>(&data[oldSize]), BUFFER_SIZE);
		data.resize(oldSize + input.gcount());
	}
	input.close();
	return ByteArray(data);
}

std::vector<unsigned char> ByteArray::cria(const std::string& s) {
	return std::vector<unsigned char>(s.begin(), s.end());
}

std::vector<unsigned char> ByteArray::cria(const char* c) {
	std::vector<unsigned char> data;
	while (*c) {
		data.push_back(static_cast<unsigned char>(*c));
		++c;
	}
	return data;
}

std::vector<unsigned char> ByteArray::cria(const char* c, size_t n) {
	std::vector<unsigned char> data;
	if (n > 0) {
		data.resize(n);
		memcpy(&data[0], c, n);
	}
	return data;
}

std::vector<unsigned char> ByteArray::cria(const unsigned char* c, size_t n) {
	std::vector<unsigned char> data;
	if (n > 0) {
		data.resize(n);
		memcpy(&data[0], c, n);
	}
	return data;
}

std::string ByteArray::toString() const {
	return std::string((const char *)recebeConteudoPonteiro(), size());
}

void ByteArray::salvaEmArquivo(const std::string& where) const
{
	FILE *toWrite = nullptr;
	if ((toWrite = fopen(where.c_str(), "wb")) == NULL)
		throw ("Não foi possível salvar o arquivo em " + where);
	fwrite(dado_.data(), dado_.size(), 1, toWrite);
	fclose(toWrite);
}

std::string ByteArray::praHex(bool isUpperCase) const {
	size_t size = this->size();
    char *hex_data = new char[size*2 +1];

    int j = 0;
    std::string formatter = isUpperCase ? "%02X" : "%02x";
    for(int i = 0; i < size; i++)
    {
		sprintf(&hex_data[j], formatter.c_str(), this->dado_[i]);
		j+=2;
    }
    hex_data[j] = '\0';
	std::string data(hex_data);
	delete[] hex_data;
    return data;
}

std::string ByteArray::praHex(char separator, bool isUpperCase) const {
	std::stringstream data;
    char* hex_data = new char[2];
    size_t size = this->size();
    std::string formatter = isUpperCase ? "%02X" : "%02x";
    for(int i = 0; i < size; i++)
    {
		sprintf(&hex_data[0], formatter.c_str(), this->dado_[i]);
		data << hex_data;
		if(i < size-1)
			data << separator;
    }
	delete[] hex_data;
    return data.str();
}
