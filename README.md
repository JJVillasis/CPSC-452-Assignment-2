# CPSC-452: Assignment 2

## Group Members:
Benjamin Ahn - benahn333@csu.fullerton.edu

Lyba Batla - lybabatla@csu.fullerton.edu

Nathaniel Marquez - nathanielmarquez@csu.fullerton.edu

Casey Thatsanaphonh - cthatsanaphonh@csu.fullerton.edu

Joshua Villasis - JJVillasis@csu.fullerton.edu

Evan Wu - Evanh.wu@csu.fullerton.edu

Po-Tyng (Peter) Wu - gaidepeter@csu.fullerton.edu

## Programming Language:
C++

## How to Execute:
Open a terminal and change the directory so that it is in the directory of the
the folder containing the cipher files.

Enter "make" into the terminal.

Next, enter the following into the terminal to execute:  
`./cipher <CIPHER NAME> <KEY> <ENC/DEC> <INPUT FILE> <OUTPUT FILE>`

Each parameter is defined as follows:
- `CIPHER NAME`: The name of the cipher:  
    - DES: indicates the DES cipher  
    - AES: indicates the AES cipher
- `KEY`: the encryption key to use
    - DES: Must be 16 characters representing a 64-bit hexadecimal number
    - AES: Must be 32 characters representing a 128-bit hexadecimal number
- `ENC/DEC`: whether to encrypt or decrypt, respectively
- `INPUT FILE`: the file from which to read the input
- `OUTPUT FILE`: the file to which to write the output

## Extra Credit:
Not implemented.

## Special Information
None.
