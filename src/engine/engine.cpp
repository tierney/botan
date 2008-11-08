/*************************************************
* Engine Source File                             *
* (C) 1999-2007 Jack Lloyd                       *
*************************************************/

#include <botan/engine.h>
#include <botan/libstate.h>
#include <botan/lookup.h>
#include <botan/look_add.h>

namespace Botan {

namespace Engine_Core {

#if defined(BOTAN_HAS_IF_PUBLIC_KEY_FAMILY)
/*************************************************
* Acquire an IF op                               *
*************************************************/
IF_Operation* if_op(const BigInt& e, const BigInt& n, const BigInt& d,
                    const BigInt& p, const BigInt& q, const BigInt& d1,
                    const BigInt& d2, const BigInt& c)
   {
   Library_State::Engine_Iterator i(global_state());

   while(const Engine* engine = i.next())
      {
      IF_Operation* op = engine->if_op(e, n, d, p, q, d1, d2, c);
      if(op)
         return op;
      }

   throw Lookup_Error("Engine_Core::if_op: Unable to find a working engine");
   }
#endif

#if defined(BOTAN_HAS_DSA)
/*************************************************
* Acquire a DSA op                               *
*************************************************/
DSA_Operation* dsa_op(const DL_Group& group, const BigInt& y, const BigInt& x)
   {
   Library_State::Engine_Iterator i(global_state());

   while(const Engine* engine = i.next())
      {
      DSA_Operation* op = engine->dsa_op(group, y, x);
      if(op)
         return op;
      }

   throw Lookup_Error("Engine_Core::dsa_op: Unable to find a working engine");
   }
#endif

#if defined(BOTAN_HAS_NYBERG_RUEPPEL)
/*************************************************
* Acquire a NR op                                *
*************************************************/
NR_Operation* nr_op(const DL_Group& group, const BigInt& y, const BigInt& x)
   {
   Library_State::Engine_Iterator i(global_state());

   while(const Engine* engine = i.next())
      {
      NR_Operation* op = engine->nr_op(group, y, x);
      if(op)
         return op;
      }

   throw Lookup_Error("Engine_Core::nr_op: Unable to find a working engine");
   }
#endif

#if defined(BOTAN_HAS_ELGAMAL)
/*************************************************
* Acquire an ElGamal op                          *
*************************************************/
ELG_Operation* elg_op(const DL_Group& group, const BigInt& y, const BigInt& x)
   {
   Library_State::Engine_Iterator i(global_state());

   while(const Engine* engine = i.next())
      {
      ELG_Operation* op = engine->elg_op(group, y, x);
      if(op)
         return op;
      }

   throw Lookup_Error("Engine_Core::elg_op: Unable to find a working engine");
   }
#endif

#if defined(BOTAN_HAS_DIFFIE_HELLMAN)
/*************************************************
* Acquire a DH op                                *
*************************************************/
DH_Operation* dh_op(const DL_Group& group, const BigInt& x)
   {
   Library_State::Engine_Iterator i(global_state());

   while(const Engine* engine = i.next())
      {
      DH_Operation* op = engine->dh_op(group, x);
      if(op)
         return op;
      }

   throw Lookup_Error("Engine_Core::dh_op: Unable to find a working engine");
   }
#endif

#if defined(BOTAN_HAS_ECDSA)
/*************************************************
* Acquire an ECDSA op                            *
*************************************************/
ECDSA_Operation* ecdsa_op(const EC_Domain_Params& dom_pars,
                          const BigInt& priv_key,
                          const PointGFp& pub_key)
   {
   Library_State::Engine_Iterator i(global_state());

   while(const Engine* engine = i.next())
      {
      ECDSA_Operation* op = engine->ecdsa_op(dom_pars, priv_key, pub_key);
      if(op)
         return op;
      }

   throw Lookup_Error("Engine_Core::ecdsa_op: Unable to find a working engine");
   }
#endif

#if defined(BOTAN_HAS_ECKAEG)
/*************************************************
* Acquire a ECKAEG op                            *
*************************************************/
ECKAEG_Operation* eckaeg_op(const EC_Domain_Params& dom_pars,
                            const BigInt& priv_key,
                            const PointGFp& pub_key)
   {
   Library_State::Engine_Iterator i(global_state());

   while(const Engine* engine = i.next())
      {
      ECKAEG_Operation* op = engine->eckaeg_op(dom_pars, priv_key, pub_key);
      if(op)
         return op;
      }

   throw Lookup_Error("Engine_Core::eckaeg_op: Unable to find a working engine");
   }
#endif

/*************************************************
* Acquire a modular exponentiator                *
*************************************************/
Modular_Exponentiator* mod_exp(const BigInt& n, Power_Mod::Usage_Hints hints)
   {
   Library_State::Engine_Iterator i(global_state());

   while(const Engine* engine = i.next())
      {
      Modular_Exponentiator* op = engine->mod_exp(n, hints);

      if(op)
         return op;
      }

   throw Lookup_Error("Engine_Core::mod_exp: Unable to find a working engine");
   }

}

/*************************************************
* Acquire a block cipher                         *
*************************************************/
const BlockCipher* retrieve_block_cipher(Library_State& libstate,
                                         const std::string& name)
   {
   Library_State::Engine_Iterator i(libstate);

   while(const Engine* engine = i.next())
      {
      const BlockCipher* algo = engine->block_cipher(name);
      if(algo)
         return algo;
      }

   return 0;
   }

/*************************************************
* Acquire a stream cipher                        *
*************************************************/
const StreamCipher* retrieve_stream_cipher(Library_State& libstate,
                                           const std::string& name)
   {
   Library_State::Engine_Iterator i(libstate);

   while(const Engine* engine = i.next())
      {
      const StreamCipher* algo = engine->stream_cipher(name);
      if(algo)
         return algo;
      }

   return 0;
   }

/*************************************************
* Acquire a hash function                        *
*************************************************/
const HashFunction* retrieve_hash(Library_State& libstate,
                                  const std::string& name)
   {
   Library_State::Engine_Iterator i(libstate);

   while(const Engine* engine = i.next())
      {
      const HashFunction* algo = engine->hash(name);
      if(algo)
         return algo;
      }

   return 0;
   }

/*************************************************
* Acquire an authentication code                 *
*************************************************/
const MessageAuthenticationCode* retrieve_mac(Library_State& libstate,
                                              const std::string& name)
   {
   Library_State::Engine_Iterator i(libstate);

   while(const Engine* engine = i.next())
      {
      const MessageAuthenticationCode* algo = engine->mac(name);
      if(algo)
         return algo;
      }

   return 0;
   }

/*************************************************
* Acquire a string-to-key algorithm              *
*************************************************/
const S2K* retrieve_s2k(Library_State& libstate,
                        const std::string& name)
   {
   Library_State::Engine_Iterator i(libstate);

   while(const Engine* engine = i.next())
      {
      const S2K* algo = engine->s2k(name);
      if(algo)
         return algo;
      }

   return 0;
   }

/*************************************************
* Retrieve a block cipher padding method         *
*************************************************/
const BlockCipherModePaddingMethod* retrieve_bc_pad(Library_State& libstate,
                                                    const std::string& name)
   {
   Library_State::Engine_Iterator i(libstate);

   while(const Engine* engine = i.next())
      {
      const BlockCipherModePaddingMethod* algo = engine->bc_pad(name);
      if(algo)
         return algo;
      }

   return 0;
   }

/*************************************************
* Add a new block cipher                         *
*************************************************/
void add_algorithm(Library_State& libstate, BlockCipher* algo)
   {
   Library_State::Engine_Iterator i(libstate);

   while(Engine* engine = i.next())
      {
      if(engine->can_add_algorithms())
         {
         engine->add_algorithm(algo);
         return;
         }
      }

   throw Invalid_State("add_algorithm: Couldn't find the Default_Engine");
   }

/*************************************************
* Add a new stream cipher                        *
*************************************************/
void add_algorithm(Library_State& libstate, StreamCipher* algo)
   {
   Library_State::Engine_Iterator i(libstate);

   while(Engine* engine = i.next())
      {
      if(engine->can_add_algorithms())
         {
         engine->add_algorithm(algo);
         return;
         }
      }

   throw Invalid_State("add_algorithm: Couldn't find the Default_Engine");
   }

/*************************************************
* Add a new hash function                        *
*************************************************/
void add_algorithm(Library_State& libstate, HashFunction* algo)
   {
   Library_State::Engine_Iterator i(libstate);

   while(Engine* engine = i.next())
      {
      if(engine->can_add_algorithms())
         {
         engine->add_algorithm(algo);
         return;
         }
      }

   throw Invalid_State("add_algorithm: Couldn't find the Default_Engine");
   }

/*************************************************
* Add a new authentication code                  *
*************************************************/
void add_algorithm(Library_State& libstate,
                   MessageAuthenticationCode* algo)
   {
   Library_State::Engine_Iterator i(libstate);

   while(Engine* engine = i.next())
      {
      if(engine->can_add_algorithms())
         {
         engine->add_algorithm(algo);
         return;
         }
      }

   throw Invalid_State("add_algorithm: Couldn't find the Default_Engine");
   }

/*************************************************
* Add a padding method to the lookup table       *
*************************************************/
void add_algorithm(Library_State& libstate,
                   BlockCipherModePaddingMethod* algo)
   {
   Library_State::Engine_Iterator i(libstate);

   while(Engine* engine = i.next())
      {
      if(engine->can_add_algorithms())
         {
         engine->add_algorithm(algo);
         return;
         }
      }

   throw Invalid_State("add_algorithm: Couldn't find the Default_Engine");
   }

/*************************************************
* Get a cipher object                            *
*************************************************/
Keyed_Filter* get_cipher(const std::string& algo_spec,
                         Cipher_Dir direction)
   {
   Library_State::Engine_Iterator i(global_state());

   while(Engine* engine = i.next())
      {
      Keyed_Filter* algo = engine->get_cipher(algo_spec, direction);
      if(algo)
         return algo;
      }

   throw Algorithm_Not_Found(algo_spec);
   }

/*************************************************
* Get a cipher object                            *
*************************************************/
Keyed_Filter* get_cipher(const std::string& algo_spec,
                         const SymmetricKey& key,
                         const InitializationVector& iv,
                         Cipher_Dir direction)
   {
   Keyed_Filter* cipher = get_cipher(algo_spec, direction);
   cipher->set_key(key);

   if(iv.length())
      cipher->set_iv(iv);

   return cipher;
   }

/*************************************************
* Get a cipher object                            *
*************************************************/
Keyed_Filter* get_cipher(const std::string& algo_spec,
                         const SymmetricKey& key,
                         Cipher_Dir direction)
   {
   return get_cipher(algo_spec,
                     key, InitializationVector(), direction);
   }

}