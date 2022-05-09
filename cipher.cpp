#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
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
 else if(cipherName == "DES")
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

	//Open input file
	FILE *inFile;
	unsigned char* input;
	long textSize;

	inFile = fopen(inputFile.c_str(), "rb");
	if(inFile == NULL)
	{
			cout << "Unable to open file \"" << inputFile << "\". File does not exist.\n";
			exit(-1);
	}

	input = (unsigned char*) malloc (sizeof(unsigned char)*blockSize);

	//Open output file
	FILE *outFile;
	outFile = fopen(outputFile.c_str(), "wb");


	///// Performing Cryptographic Process /////

	//Perfrom encryption
	if(encDec == "ENC")
	{
		while(textSize = fread(input, 1, blockSize, inFile) >= 1)
		{
			const unsigned char* inputText = reinterpret_cast<const unsigned char*>(input);

			unsigned char * ciphertext = cipher->encrypt(inputText);
			fwrite(ciphertext, 1, blockSize, outFile);
			memset(input, 0, blockSize);
		}
	}
	//Perform decryption
	else if(encDec == "DEC")
	{
		while(textSize = fread(input, 1, blockSize, inFile) >= 1)
		{
			const unsigned char* inputText = reinterpret_cast<const unsigned char*>(input);

			unsigned char * plaintext = cipher->decrypt(inputText);
			fwrite(plaintext, 1, blockSize, outFile);
			memset(input, 0, blockSize);
		}
	}
	//ERROR: Unknown process
	else
	{
		cout << "Unknown Process: \"" << encDec << "\"\n";
		exit(-1);
	}

	//// Close files ////

	fclose(inFile);
	fclose(outFile);

	return 0;
}
