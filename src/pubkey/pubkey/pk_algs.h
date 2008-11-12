/*************************************************
* PK Key Factory Header File                     *
* (C) 1999-2007 Jack Lloyd                       *
*************************************************/

#ifndef BOTAN_PK_KEY_FACTORY_H__
#define BOTAN_PK_KEY_FACTORY_H__

#include <botan/x509_key.h>
#include <botan/pkcs8.h>

namespace Botan {

/**
* Get an empty public key object.
* @param name the name of the desired public key algorithm
* @return the public key object
*/
BOTAN_DLL Public_Key*  get_public_key(const std::string&);

/**
* Get an empty private key object.
* @param name the name of the desired public key algorithm
* @return the private key object
*/
BOTAN_DLL Private_Key* get_private_key(const std::string&);

}

#endif