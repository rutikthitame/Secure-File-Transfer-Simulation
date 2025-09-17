//=======================================================================
//
//  File Name   : EncrypDecrypt.cpp
//  Description : This DLL provides multiple encryption/decryption 
//                algorithms (XOR Cipher, Caesar Cipher, Blowfish) 
//                for file-based operations. Each algorithm reads data 
//                from a source file, encrypts/decrypts the buffer, 
//                and writes the output to a destination file.
//
//  Author      : Rutik Shivaji Thitame
//  Date        : 16/09/2025
//
//=======================================================================

#include <windows.h>
#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <io.h>
#include <cstdint>
#include <algorithm> // for swap

#define MAX_SIZE 1024   // Buffer size for XOR/Caesar cipher
#define BF_BLOCK 8      // Block size for Blowfish (64 bits)

//=======================================================================
//  XOR CIPHER (Simple symmetric encryption)
//=======================================================================

/////////////////////////////////////////////////////////////////////////
//
//  Function Name   : Encrypt_XOR_Cipher
//  Parameters      : [IN] char* Src  -> Path of source file
//                    [IN] char* Dest -> Path of destination file
//                    [IN] char  Key  -> XOR key
//  Description     : Reads source file, applies XOR operation with Key 
//                    on each byte, and writes encrypted output.
//  Returns         : None
//
/////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) void Encrypt_XOR_Cipher(char* Src, char* Dest, char Key)
{
    int fdSrc = 0, fdDest = 0, iRet = 0, i = 0;
    char Buffer[MAX_SIZE] = { '\0' };

    fdSrc = _open(Src, O_RDONLY);
    if (fdSrc == -1)
    {
        printf("Unable to open Src file\n");
        return;
    }

    fdDest = _open(Dest, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fdSrc == -1)
    {
        printf("Unable to create Destination file\n");
        return;
    }

    while ((iRet = _read(fdSrc, Buffer, sizeof(Buffer))) > 0)
    {
        for (i = 0; i < iRet; i++)
        {
            Buffer[i] = Buffer[i] ^ Key; // XOR with key
        }
        _write(fdDest, Buffer, iRet);
    }

    _close(fdSrc);
    _close(fdDest);
}

/////////////////////////////////////////////////////////////////////////
//
//  Function Name   : Decrypt_XOR_Cipher
//  Parameters      : [IN] char* Src  -> Path of encrypted file
//                    [IN] char* Dest -> Path of destination file
//                    [IN] char  Key  -> XOR key
//  Description     : Reads encrypted file, applies XOR operation with Key 
//                    (same as encryption), and writes decrypted output.
//  Returns         : None
//
/////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) void Decrypt_XOR_Cipher(char* Src, char* Dest, char Key)
{
    int fdSrc = 0, fdDest = 0, iRet = 0, i = 0;
    char Buffer[MAX_SIZE] = { '\0' };

    fdSrc = _open(Src, O_RDONLY);
    if (fdSrc == -1)
    {
        printf("Unable to open Src file\n");
        return;
    }

    fdDest = _open(Dest, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fdDest == -1)
    {
        printf("Unable to create Destination file\n");
        return;
    }

    while ((iRet = _read(fdSrc, Buffer, sizeof(Buffer))) > 0)
    {
        for (i = 0; i < iRet; i++)
        {
            Buffer[i] = Buffer[i] ^ Key; // XOR with key (reverse)
        }
        _write(fdDest, Buffer, iRet);
    }

    _close(fdSrc);
    _close(fdDest);
}

//=======================================================================
//  CAESAR CIPHER (Shift-based encryption)
//=======================================================================

/////////////////////////////////////////////////////////////////////////
//
//  Function Name   : Encrypt_Caeser_Cipher
//  Parameters      : [IN] char* Src  -> Path of source file
//                    [IN] char* Dest -> Path of destination file
//                    [IN] int  Key   -> Shift value
//  Description     : Reads source file, shifts each byte by Key, and 
//                    writes encrypted output. Wraps around using mod 256.
//  Returns         : None
//
/////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) void Encrypt_Caeser_Cipher(char* Src, char* Dest, int Key)
{
    int fdSrc = 0, fdDest = 0, iRet = 0, i = 0;
    char Buffer[MAX_SIZE] = { '\0' };

    fdSrc = _open(Src, O_RDONLY);
    if (fdSrc == -1)
    {
        printf("Unable to open Src file\n");
        return;
    }

    fdDest = _open(Dest, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fdSrc == -1)
    {
        printf("Unable to create Destination file\n");
        return;
    }

    while ((iRet = _read(fdSrc, Buffer, sizeof(Buffer))) > 0)
    {
        for (i = 0; i < iRet; i++)
        {
            Buffer[i] = (Buffer[i] + Key) % 256; // shift right
        }
        _write(fdDest, Buffer, iRet);
    }

    _close(fdSrc);
    _close(fdDest);
}

/////////////////////////////////////////////////////////////////////////
//
//  Function Name   : Decrypt_Caeser_Cipher
//  Parameters      : [IN] char* Src  -> Path of encrypted file
//                    [IN] char* Dest -> Path of destination file
//                    [IN] int  Key   -> Shift value
//  Description     : Reads encrypted file, shifts each byte back by Key, 
//                    and writes decrypted output. Wraps around using mod 256.
//  Returns         : None
//
/////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) void Decrypt_Caeser_Cipher(char* Src, char* Dest, int Key)
{
    int fdSrc = 0, fdDest = 0, iRet = 0, i = 0;
    char Buffer[MAX_SIZE] = { '\0' };

    fdSrc = _open(Src, O_RDONLY);
    if (fdSrc == -1)
    {
        printf("Unable to open Src file\n");
        return;
    }

    fdDest = _open(Dest, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fdDest == -1)
    {
        printf("Unable to create Destination file\n");
        return;
    }

    while ((iRet = _read(fdSrc, Buffer, sizeof(Buffer))) > 0)
    {
        for (i = 0; i < iRet; i++)
        {
            Buffer[i] = (Buffer[i] - Key) % 256; // shift left
        }
        _write(fdDest, Buffer, iRet);
    }

    _close(fdSrc);
    _close(fdDest);
}

//=======================================================================
//  BLOWFISH CIPHER (Block cipher, 64-bit block size)
//=======================================================================

/////////////////////////////////////////////////////////////////////////
//
//  Class Name      : Encrypt_Blowfish
//  Description     : Implements simplified Blowfish encryption algorithm 
//                    with key expansion, Feistel function, and 
//                    Encrypt/Decrypt routines for 64-bit blocks.
//  Author          : Rutik Shivaji Thitame
//
/////////////////////////////////////////////////////////////////////////
class Encrypt_Blowfish
{
private:
    uint32_t P[18];       // P-array
    uint32_t S[4][256];   // S-boxes
    int key1, key2;       // Two integer keys

public:

    ///////////////////////////////////////////////////////////////////////
    //  Constructor : Encrypt_Blowfish(int a, int b)
    //  Description : Initializes keys and calls Key schedule function
    ///////////////////////////////////////////////////////////////////////
    Encrypt_Blowfish(int a, int b)
    {
        key1 = a;
        key2 = b;
        Key(key1, key2);
    }

    ///////////////////////////////////////////////////////////////////////
    //  Function Name : Key
    //  Description   : Initializes P-array and S-boxes with key material
    ///////////////////////////////////////////////////////////////////////
    void Key(int key1, int key2)
    {
        for (int i = 0; i < 18; i++)
        {
            P[i] = key1 + i;
        }
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 256; j++)
            {
                S[i][j] = key2 + j;
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////
    //  Function Name : F
    //  Description   : Blowfish round function F
    ///////////////////////////////////////////////////////////////////////
    uint32_t F(uint32_t x)
    {
        uint8_t a = (x >> 24) & 0xff;
        uint8_t b = (x >> 16) & 0xff;
        uint8_t c = (x >> 8) & 0xff;
        uint8_t d = x & 0xff;

        return ((S[0][a] + S[1][b]) ^ S[2][c]) + S[3][d];
    }

    ///////////////////////////////////////////////////////////////////////
    //  Function Name : Encrypt
    //  Description   : Encrypts 64-bit block (L, R)
    ///////////////////////////////////////////////////////////////////////
    void Encrypt(uint32_t& L, uint32_t& R)
    {
        for (int i = 0; i < 16; i++)
        {
            L ^= P[i];
            R ^= F(L);
            std::swap(L, R);
        }
        std::swap(L, R);
        R ^= P[16];
        L ^= P[17];
    }

    ///////////////////////////////////////////////////////////////////////
    //  Function Name : Decrypt
    //  Description   : Decrypts 64-bit block (L, R)
    ///////////////////////////////////////////////////////////////////////
    void Decrypt(uint32_t& L, uint32_t& R)
    {
        for (int i = 17; i > 1; i--)
        {
            L ^= P[i];
            R ^= F(L);
            std::swap(L, R);
        }
        std::swap(L, R);
        R ^= P[1];
        L ^= P[0];
    }
};

//=======================================================================
//  DLL Exported Blowfish File Functions
//=======================================================================

/////////////////////////////////////////////////////////////////////////
//
//  Function Name   : Encrypt_Blowfish_File
//  Parameters      : [IN] char* Src   -> Path of source file
//                    [IN] char* Dest  -> Path of destination file
//                    [IN] int  Key1   -> First key
//                    [IN] int  Key2   -> Second key
//  Description     : Reads file in 8-byte blocks, applies Blowfish 
//                    encryption, and writes output.
//  Returns         : None
//
/////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) void Encrypt_Blowfish_File(char* Src, char* Dest, int Key1, int Key2)
{
    Encrypt_Blowfish bf(Key1, Key2);

    int fdSrc = _open(Src, O_RDONLY);
    if (fdSrc == -1) { printf("Unable to open Src file\n"); return; }

    int fdDest = _open(Dest, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fdDest == -1) { printf("Unable to create Dest file\n"); _close(fdSrc); return; }

    char Buffer[BF_BLOCK];
    int iRet = 0;

    while ((iRet = _read(fdSrc, Buffer, sizeof(Buffer))) > 0)
    {
        if (iRet < BF_BLOCK)
        {
            for (int i = iRet; i < BF_BLOCK; i++) Buffer[i] = 0; // pad with 0
        }

        // Split into 32-bit halves
        uint32_t L = (uint8_t)Buffer[0] << 24 | (uint8_t)Buffer[1] << 16 | (uint8_t)Buffer[2] << 8 | (uint8_t)Buffer[3];
        uint32_t R = (uint8_t)Buffer[4] << 24 | (uint8_t)Buffer[5] << 16 | (uint8_t)Buffer[6] << 8 | (uint8_t)Buffer[7];

        bf.Encrypt(L, R);

        // Pack back to buffer
        Buffer[0] = (L >> 24) & 0xff;
        Buffer[1] = (L >> 16) & 0xff;
        Buffer[2] = (L >> 8) & 0xff;
        Buffer[3] = L & 0xff;
        Buffer[4] = (R >> 24) & 0xff;
        Buffer[5] = (R >> 16) & 0xff;
        Buffer[6] = (R >> 8) & 0xff;
        Buffer[7] = R & 0xff;

        _write(fdDest, Buffer, BF_BLOCK);
    }

    _close(fdSrc);
    _close(fdDest);
}

/////////////////////////////////////////////////////////////////////////
//
//  Function Name   : Decrypt_Blowfish_File
//  Parameters      : [IN] char* Src   -> Path of encrypted file
//                    [IN] char* Dest  -> Path of destination file
//                    [IN] int  Key1   -> First key
//                    [IN] int  Key2   -> Second key
//  Description     : Reads file in 8-byte blocks, applies Blowfish 
//                    decryption, and writes output.
//  Returns         : None
//
/////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) void Decrypt_Blowfish_File(char* Src, char* Dest, int Key1, int Key2)
{
    Encrypt_Blowfish bf(Key1, Key2);

    int fdSrc = _open(Src, O_RDONLY);
    if (fdSrc == -1) { printf("Unable to open Src file\n"); return; }

    int fdDest = _open(Dest, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fdDest == -1) { printf("Unable to create Dest file\n"); _close(fdSrc); return; }

    char Buffer[BF_BLOCK];
    int iRet = 0;

    while ((iRet = _read(fdSrc, Buffer, sizeof(Buffer))) > 0)
    {
        if (iRet < BF_BLOCK)
        {
            for (int i = iRet; i < BF_BLOCK; i++) Buffer[i] = 0; // pad with 0
        }

        uint32_t L = (uint8_t)Buffer[0] << 24 | (uint8_t)Buffer[1] << 16 | (uint8_t)Buffer[2] << 8 | (uint8_t)Buffer[3];
        uint32_t R = (uint8_t)Buffer[4] << 24 | (uint8_t)Buffer[5] << 16 | (uint8_t)Buffer[6] << 8 | (uint8_t)Buffer[7];

        bf.Decrypt(L, R);

        Buffer[0] = (L >> 24) & 0xff;
        Buffer[1] = (L >> 16) & 0xff;
        Buffer[2] = (L >> 8) & 0xff;
        Buffer[3] = L & 0xff;
        Buffer[4] = (R >> 24) & 0xff;
        Buffer[5] = (R >> 16) & 0xff;
        Buffer[6] = (R >> 8) & 0xff;
        Buffer[7] = R & 0xff;

        _write(fdDest, Buffer, BF_BLOCK);
    }

    _close(fdSrc);
    _close(fdDest);
}
