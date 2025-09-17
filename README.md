#  Secure File Transfer Simulation  

A *Windows-based simulation project* that demonstrates *cryptography* and *system-level programming* using the *Win32 SDK*.  
The project implements *Blowfish algorithm,Caesar Cipher* and *XOR Cipher* for secure file encryption/decryption and performs *low-level file handling* via Windows system calls instead of standard C library functions.  

The cryptographic logic is modularized into a *Dynamic Link Library (DLL)*, making the functionality reusable by multiple client applications.  

---

##  Project Overview  
This project showcases:  
- Low-level *Win32 API programming*  
- *DLL development* and integration  
- *File-based encryption & decryption*  
- Practical *cryptographic techniques*  

---

##  Features  

-  *File Encryption & Decryption*  
  - Encrypt and decrypt text files securely.  

-  *Multiple Algorithms*  
  - *Caesar Cipher* (character shift-based substitution)  
  - *XOR Cipher* (bitwise XOR with user-defined key)
  - *Blowfish algorithm*  

-  *System-Level File Handling*  
  - Uses *Win32 APIs* (CreateFile, ReadFile, WriteFile, CloseHandle)  
  - Avoids high-level C standard library functions.  

-  *DLL Integration*  
  - Cryptographic functions are modularized into a *custom DLL*.  
  - Client applications *dynamically load* and use the encryption/decryption services.  

-  *Low-Level Programming Practice*  
  - Worked extensively with *pointers, buffers, and string processing*.  
  - Debugging with *Visual Studio* and *Windows tools*.

---
