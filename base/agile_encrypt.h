#ifndef agile_encrypt_header
#define agile_encrypt_header

typedef unsigned long Huge;

typedef struct agile_rsa_pub_key_ {
	Huge e;
	Huge n;
} agile_rsa_pub_key;

typedef struct agile_rsa_pri_key_ {
	Huge d;
	Huge n;
} agile_rsa_pri_key;

void agile_des_encipher(const unsigned char* plaintext, unsigned char* ciphertext, const unsigned char* key);
void agile_des_decipher(const unsigned char* ciphertext, unsigned char* plaintext, const unsigned char* key);

void agile_rsa_encipher(Huge plaintext, Huge* ciphertext, agile_rsa_pub_key pubkey);
void agile_rsa_decipher(Huge ciphertext, Huge* plaintext, agile_rsa_pri_key prikey);

void test_agile_encrypt();

#endif
