#ifndef agile_encrypt_header
#define agile_encrypt_header

typedef struct agile_rsa_pub_key_ {
	int e;
	int n;
} agile_rsa_pub_key;

typedef struct agile_rsa_pri_key_ {
	int d;
	int n;
} agile_rsa_pri_key;

void agile_des_encipher(const unsigned char* plaintext, unsigned char* ciphertext, const unsigned char* key);
void agile_des_decipher(const unsigned char* ciphertext, unsigned char* plaintext, const unsigned char* key);

void agile_cbc_encipher(const unsigned char* plaintext, unsigned char* ciphertext, const unsigned char* key, int size);
void agile_cbc_decipher(const unsigned char* ciphertext, unsigned char* plaintext, const unsigned char* key, int size);

void agile_rsa_encipher(int plaintext, long long* ciphertext, agile_rsa_pub_key pubkey);
void agile_rsa_decipher(long long ciphertext, int* plaintext, agile_rsa_pri_key prikey);

void test_agile_encrypt();

#endif
