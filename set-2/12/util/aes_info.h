#ifndef AES_INFO_H
#define AES_INFO_H

#define KEYSIZE		128
#define BLOCKSIZE	16
#define BLOCK(A)	((A >= BLOCKSIZE) ? (A % BLOCKSIZE) : A)

#endif /* AES_INFO_H */

