#include <iostream>
#include <fstream>
#include <string>
#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"

using namespace std;

int main(int argc, char** argv)
{
	///// Parsing command line arguments /////

	string cipherName = argv[1];	// Name of the cipher (AES/DES)
	const unsigned char* key = reinterpret_cast<const unsigned char*>(argv[2]);		// Encryption key; 16 characters long (DES: 64-bit / AES: 128-bit)
	//const unsigned char * key = reinterpret_cast<const unsigned char*>(keyStr.c_str());
	string encDec = argv[3];	// Determine encrypt or decrypt
	string inputFile = argv[4];	// File to read input
	string outputFile = argv[5];	// File to write output


	///// Reading the input file /////

	//Open input and output files
	ifstream in(inputFile);
	ofstream out;
	out.open(outputFile);

	//Text from input file
	string input;
	const unsigned char* inputText;

	//Check if input file can be found
	if(in.is_open())
	{
		//Read text from input file
		getline(in, input);
		inputText = reinterpret_cast<const unsigned char*>(input.c_str());
	}
	//Input cannot be found
	else
	{
		cout << "Unable to open file \"" << inputFile << "\". File does not exist.\n";
		exit(-1);
	}


	///// Handling Cipher Interface /////

	//Create an instance of a cipher
	CipherInterface* cipher = NULL;

	//Determine which cipher is chosen
	//AES Cipher
	if(cipherName == "AES")
	{
		cipher = new AES();
	}
	//DES Cipher
	else if(cipherName == "DES")
	{
		cipher = new DES();
	}
	//Unknown Cipher
	else
	{
		cout << "The cipher \"" << cipherName << "\" is unknown.\n";
		exit(-1);
	}


	///// Performing Cryptographic Process /////

	//Check if key is exactly 16 characters long
	if(strlen((char*) key) != 16)
	{
		cout << "Key \'" << key << "\" Must be exactly 16 characters long.\n";
		exit(-1);
	}

	//Set key for cipher
	if(!cipher->setKey(key))
	{
		cout << "Key \'" << key << "\' not a vaild key for cipher \"" << cipherName << "\".\n";
		exit(-1);
	}

	//Perfrom encryption
	if(encDec == "ENC")
	{
		unsigned char * ciphertext = cipher->encrypt(inputText);
		out << ciphertext << endl;
	}
	//Perform decryption
	else if(encDec == "DEC")
	{
		unsigned char * plaintext = cipher->decrypt(inputText);
		out << plaintext << endl;
	}
	//ERROR: Unknown process
	else
	{
		cout << "Unknown Process: \"" << encDec << "\"\n";
		exit(-1);
	}

	return 0;
}