#include <iostream>
using namespace std;

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

typedef void (*CFPTR)(char*, char*, int);

typedef void (*XORFPTR)(char*, char*, char);

typedef void (*BFFPTR)(char*, char*, int, int);

int main()
{
    int iCount = 0;
    int iChoice = 0;

    HINSTANCE hdll = LoadLibrary(L"EncryptDecryptServer.dll");
    if (hdll == NULL)
    {
        std::cout << "Unable to load library\n";
        return -1;
    }

    cout << "Select the operation that you want to perform\n";
    cout << " 1 : Encrypt file\n";
    cout << " 2 : Decrypt file\n";

    cin >> iCount;

    while (iCount != 0)
    {
        if (iCount == 1) // Encryption
        {
            cout << "Select the Encryption algorithm\n";
            cout << " 1 : Encrypt using XOR operation\n";
            cout << " 2 : Encrypt using Caesar cipher\n";
            cout << " 3 : Encrypt using Blowfish\n";
            cin >> iChoice;

            char source[50], dest[50];
            int ikey = 0, key1 = 0, key2 = 0;
            char key = '\0';

            cout << "Enter the source file name\n";
            cin >> source;
            cout << "Enter the destination file name\n";
            cin >> dest;

            if (iChoice == 1)
            {
                cout << "Enter the key (char)\n";
                cin >> key;
                XORFPTR xorfptr = (XORFPTR)GetProcAddress(hdll, "Encrypt_XOR_Cipher");
                if (!xorfptr) { cout << "Unable to get function\n"; return -1; }
                xorfptr(source, dest, key);
            }
            else if (iChoice == 2)
            {
                cout << "Enter the key (int)\n";
                cin >> ikey;
                CFPTR cfptr = (CFPTR)GetProcAddress(hdll, "Encrypt_Caeser_Cipher");
                if (!cfptr) { cout << "Unable to get function\n"; return -1; }
                cfptr(source, dest, ikey);
            }
            else if (iChoice == 3)
            {
                cout << "Enter first key (int)\n";
                cin >> key1;
                cout << "Enter second key (int)\n";
                cin >> key2;
                BFFPTR bffptr = (BFFPTR)GetProcAddress(hdll, "Encrypt_Blowfish_File");
                if (!bffptr) { cout << "Unable to get function\n"; return -1; }
                bffptr(source, dest, key1, key2);
            }
            else
            {
                cout << "Invalid choice\n";
            }
        }
        else if (iCount == 2) // Decryption
        {
            cout << "Select the Decryption algorithm\n";
            cout << " 1 : Decrypt using XOR operation\n";
            cout << " 2 : Decrypt using Caesar cipher\n";
            cout << " 3 : Decrypt using Blowfish\n";
            cin >> iChoice;

            char source[50], dest[50];
            int ikey = 0, key1 = 0, key2 = 0;
            char key = '\0';

            cout << "Enter the source file name\n";
            cin >> source;
            cout << "Enter the destination file name\n";
            cin >> dest;

            if (iChoice == 1)
            {
                cout << "Enter the key (char)\n";
                cin >> key;
                XORFPTR xorfptr = (XORFPTR)GetProcAddress(hdll, "Decrypt_XOR_Cipher");
                if (!xorfptr) { cout << "Unable to get function\n"; return -1; }
                xorfptr(source, dest, key);
            }
            else if (iChoice == 2)
            {
                cout << "Enter the key (int)\n";
                cin >> ikey;
                CFPTR cfptr = (CFPTR)GetProcAddress(hdll, "Decrypt_Caeser_Cipher");
                if (!cfptr) { cout << "Unable to get function\n"; return -1; }
                cfptr(source, dest, ikey);
            }
            else if (iChoice == 3)
            {
                cout << "Enter first key (int)\n";
                cin >> key1;
                cout << "Enter second key (int)\n";
                cin >> key2;
                BFFPTR bffptr = (BFFPTR)GetProcAddress(hdll, "Decrypt_Blowfish_File");
                if (!bffptr) { cout << "Unable to get function\n"; return -1; }
                bffptr(source, dest, key1, key2);
            }
            else
            {
                cout << "Invalid choice\n";
            }
        }
        else
        {
            cout << "Invalid choice\n";
        }

        cout << "\nSelect next operation:\n";
        cout << " 1 : Encrypt file\n";
        cout << " 2 : Decrypt file\n";
        cout << " 0 : Exit\n";
        cin >> iCount;
    }

    FreeLibrary(hdll);
    return 0;
}
