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
	string keyInput = argv[2];		// Encryption key
	string encDec = argv[3];			// Determine encrypt or decrypt
	string inputFile = argv[4];		// File to read input
	string outputFile = argv[5];	// File to write output


	///// Reading the input file /////

	//Open input and output files
	ifstream in(inputFile);
	ofstream out;
	out.open(outputFile);

	//Text from input file
	string input;

	//Check if input file can be found
	if(in.is_open())
	{
		//Read text from input file
		getline(in, input);
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

	//Size of ENC/DEC blocks
	int blockSize = 0;

	//Determine which cipher is chosen
	//AES Cipher
	if(cipherName == "AES")
	{
		cipher = new AES();
		blockSize = 16;

		//Check if key is exactly 32 characters long
		if(keyInput.length() != 32)
		{
			cout << "Key \'" << keyInput << "\" Must be exactly 32 characters long.\n";
			exit(-1);
		}

		//Add byte in beggining of key
		if(encDec == "ENC")
			keyInput = "00" + keyInput;
		else
			keyInput = "11" + keyInput;

		const unsigned char* key = reinterpret_cast<const unsigned char*>(keyInput.c_str());

		//Set key for cipher
		if(!cipher->setKey(key))
		{
			cout << "Key \'" << key << "\' not a vaild key for cipher \"" << cipherName << "\".\n";
			exit(-1);
		}
	}

	//DES Cipher
 if(cipherName == "DES")
	{
		cipher = new DES();
		blockSize = 8;

		const unsigned char* key = reinterpret_cast<const unsigned char*>(keyInput.c_str());

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
	}

	//Unknown Cipher
	else
	{
		cout << "The cipher \"" << cipherName << "\" is unknown.\n";
		exit(-1);
	}

	///// Performing Cryptographic Process /////

	//Perfrom encryption
	if(encDec == "ENC")
	{
		string plaintext;
		int index = 0;
		while(index < input.length())
		{
			plaintext = input.substr(index, blockSize);
			const unsigned char* inputText = reinterpret_cast<const unsigned char*>(plaintext.c_str());

			unsigned char * ciphertext = cipher->encrypt(inputText);
			out << ciphertext;

			index += blockSize;
		}

		out << endl;
	}
	//Perform decryption
	else if(encDec == "DEC")
	{
		string ciphertext;
		int index = 0;
		while(index < input.length())
		{
			ciphertext = input.substr(index, blockSize);
			const unsigned char* inputText = reinterpret_cast<const unsigned char*>(ciphertext.c_str());

			unsigned char * plaintext = cipher->decrypt(inputText);
			out << plaintext;

			index += blockSize;
		}

		out << endl;
	}
	//ERROR: Unknown process
	else
	{
		cout << "Unknown Process: \"" << encDec << "\"\n";
		exit(-1);
	}

	//// Close files ////

	in.close();
	out.close();

	return 0;
}
