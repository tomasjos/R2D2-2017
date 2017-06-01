/**
 * \file	  encryption.hh
 * \brief     Class that applys simple non safe encryption
 * \author    Rik Honcoop
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#ifndef ENCRYPTION_HH
#define ENCRYPTION_HH

#include <string>

class Encryption{
public:
    
    /**
     * \brief Constructor for it using your own key code.
     */
	Encryption();


	/*
	 * Contructor for if your using fixed key
	 *
	 * \param[in] Key that will be used by the object for standaart encryption
	 */
	Encryption(int encryptionKey);
    
   /**
     * \brief Can encrypt a string, with a give keycode.
     * 
     * \param[in,out] Input string that will be encrypted
     * \param[in,out] keyCode that will be used the encrypt the string with a specific key
     * \return string
     */
    std::string Encrypt(std::string input, int keyCode);
    
   /**
     * \brief can encrypt a string if the enqryption key is given with the constuctor.
     * 
     * \param[in,out] Input string that will be encrypted with a give encryption key in constructor or later set with setEncryptionKey().
     * \return string
     */
    std::string Encrypt(std::string input);
    
    /**
     * \brief Can solve the previously encrypted string
     * 
     * \param[in,out] Input string that will be decrypted
     * \param[in,out] keyCode that will be used the decrypt the string with a specific key
     * \return Returns a Decrypted string if the keyCode is the same as applyd in the encryption.
     */
    std::string Decrypt(std::string input, int keyCode);
    
    /**
     * \brief Can solve the previously encrypted string
     * 
     * \param[in,out] Input string that will be decrypted
     * \return Returns a Decrypted string.
     */
    std::string Decrypt(std::string input);
    
    /**
     * \brief Set the encryption key if not given in constructor
     *
     * \param[in,out] Input string that will be decrypt with a give encryption key in constructor or later set with setEncryptionKey().
     */
    void setEncryptionKey(int encryptionKey);

private:
    int encryptKey;
};

#endif /* ENCRYPTION_HH */
