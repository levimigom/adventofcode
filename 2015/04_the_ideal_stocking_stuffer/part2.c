/**
 *	author: levimigom
 *	created: 2025-08-26 14:47:06
 **/

// cc source.c -lcrypto
#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define LIM 32

void convert_to_md5(const char *data, int len, char *md5) {
  	EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
  	const EVP_MD *md = EVP_md5();
  	unsigned char md_value[EVP_MAX_MD_SIZE];
  	unsigned int md_len, i;
  
	EVP_DigestInit_ex(mdctx, md, NULL);
  	EVP_DigestUpdate(mdctx, data, len);
  	EVP_DigestFinal_ex(mdctx, md_value, &md_len);
  	EVP_MD_CTX_free(mdctx);
  	
	for (i = 0; i < md_len; i++) {
    		snprintf(&(md5[i * 2]), 16 * 2, "%02x", md_value[i]);
 	}
}

bool starts_with_six_zeroes(char *s){
	int i;

	for(i = 0; i < 6; i++){
		if(s[i] != '0'){
			return false;
		}
	}

	return true;
}

int main(){
	char key[LIM], md5[33];
	int i, key_length;
	
	scanf("%s", key);
	key_length = strlen(key);

	i = 0;
	do {
		snprintf(key + key_length, LIM - key_length, "%d", ++i); 
		convert_to_md5(key, strlen(key), md5);
	} while(!starts_with_six_zeroes(md5));

	printf("%d\n", i);

	return 0;
}
