#  Secure-File-Transfer-Simulation

##  Project Overview
`EncryptDecryptServer` is a **C++ DLL-based encryption and decryption library** with a console-based client program.  
The project demonstrates the implementation of **multiple encryption algorithms** (XOR Cipher, Caesar Cipher, and Blowfish) and integrates them into a **menu-driven application** that allows encrypting/decrypting files dynamically using a loaded DLL.  

The DLL exposes encryption/decryption functions, and the client interacts with these using **`LoadLibrary`** and **`GetProcAddress`**, showcasing real-world usage of **dynamic linking** in Windows.  

---

##  Key Features
-  **XOR Cipher** → Simple symmetric bitwise encryption with a single key.  
-  **Caesar Cipher** → Classical shift-based substitution cipher using an integer key.  
-  **Blowfish Cipher** → Block cipher (64-bit block size) with Feistel structure.  
-  **File-based operations** → Works directly on source and destination files.  
-  **Menu-driven console client** → User-friendly interface for selecting algorithms.  
-  **Dynamic DLL loading** → Functions are called via function pointers using `GetProcAddress`.  

---

##  Learning Outcomes
By working with this project, you will learn:  
-  How to create and export functions in a **Windows DLL** (`__declspec(dllexport)`).  
-  How to **load DLLs dynamically** in C++ using `LoadLibrary` and `GetProcAddress`.  
-  Implementation of **basic (XOR, Caesar)** and **advanced (Blowfish)** encryption algorithms.  
-  File handling in C++ using **low-level I/O (`_open`, `_read`, `_write`)**.  
-  Working with **function pointers** to call DLL functions at runtime.  

---

##  Example Usage

### 1. Run the Client
```bash
g++ EncrypDecryptClient.cpp -o EncryptClient
EncryptClient.exe
```

Select the operation that you want to perform
 1 : Encrypt file
 2 : Decrypt file

Select the Encryption algorithm
 1 : Encrypt using XOR operation
 2 : Encrypt using Caesar cipher
 3 : Encrypt using Blowfish

Enter the source file name
input.txt
Enter the destination file name
encrypted.txt
Enter the key (int)

Encryption complete!

