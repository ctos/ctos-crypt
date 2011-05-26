#include<string.h>
#include <mcrypt.h>
#include <stdio.h>
#include <stdlib.h>
/* #include <mhash.h> */

int encrypt(char *password, char *plaintext, char *ciphertext)
{

	MCRYPT td;
	int i;
	char *key;
	char block_buffer;
	char *IV;
	int keysize=16; /* 128 bits */
	
	key=calloc(1, keysize);

/* Generate the key using the password */
/* mhash_keygen( KEYGEN_MCRYPT, MHASH_MD5, key, keysize, NULL, 0, password, strlen(password));
*/
	memmove( key, password, strlen(password));
	
	td = mcrypt_module_open("twofish", NULL, "cfb", NULL);
	if (td==MCRYPT_FAILED)
	{
		return 1;
	}
        IV = malloc(mcrypt_enc_get_iv_size(td));
       /* Put random data in IV. Note these are not real random data,
        * consider using /dev/random or /dev/urandom.
        */

         /*  srand(time(0)); */

	for (i=0; i< mcrypt_enc_get_iv_size( td); i++)
	{
        	IV[i]=rand();
        }

        i=mcrypt_generic_init( td, key, keysize, IV);
        if (i<0) 
	{
        	mcrypt_perror(i);
        	return 1;
        }
//	printf("%d",strlen(plaintext));
         /* Encryption in CFB is performed in bytes */
        for(i=0;i<=strlen(plaintext);i++)
	{
//		printf("%c",plaintext[i]);
		block_buffer=plaintext[i];
        	mcrypt_generic (td, &block_buffer, 1);
        	ciphertext[i]=block_buffer; 

       /* Comment above and uncomment this to decrypt */
       /*    mdecrypt_generic (td, &block_buffer, 1);  */
//		printf("%c",ciphertext[i]);
	}

       /* Deinit the encryption thread, and unload the module */
         mcrypt_generic_end(td);

         return 0;

       }
int dencrypt(char *password, char *ciphertext, char *plaintext)
{

	MCRYPT td;
	int i;
	char *key;
	char block_buffer;
	char *IV;
	int keysize=16; /* 128 bits */
	
	key=calloc(1, keysize);

/* Generate the key using the password */
/* mhash_keygen( KEYGEN_MCRYPT, MHASH_MD5, key, keysize, NULL, 0, password, strlen(password));
*/
	memmove( key, password, strlen(password));
	
	td = mcrypt_module_open("twofish", NULL, "cfb", NULL);
	if (td==MCRYPT_FAILED)
	{
		return 1;
	}
        IV = malloc(mcrypt_enc_get_iv_size(td));
       /* Put random data in IV. Note these are not real random data,
        * consider using /dev/random or /dev/urandom.
        */

         /*  srand(time(0)); */

	for (i=0; i< mcrypt_enc_get_iv_size( td); i++)
	{
        	IV[i]=rand();
        }

        i=mcrypt_generic_init( td, key, keysize, IV);
        if (i<0) 
	{
        	mcrypt_perror(i);
        	return 1;
        }
//	printf("%d",strlen(plaintext));
         /* Encryption in CFB is performed in bytes */
        for(i=0;i<=strlen(ciphertext);i++)
	{
//		printf("%c",plaintext[i]);
		block_buffer=ciphertext[i];
//        	mcrypt_generic (td, &block_buffer, 1);

       /* Comment above and uncomment this to decrypt */
       		mdecrypt_generic (td, &block_buffer, 1); 
        	plaintext[i]=block_buffer; 
//		printf("%c",ciphertext[i]);
	}

       /* Deinit the encryption thread, and unload the module */
         mcrypt_generic_end(td);

         return 0;

       }

