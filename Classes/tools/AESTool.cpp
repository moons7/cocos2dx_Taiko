#include "AESTool.h"
#include <memory>
#include "cocos2d.h"





void AESTool::encodeString(char *string, char* password, unsigned char*outString)
{
    aes_context aes_ctx;
    unsigned char key[32];
    unsigned char IV[16];
    memset(IV, 0, sizeof(IV));
    memset(key, 0, sizeof(key));
    memcpy(key, password, strlen(password));
    aes_setkey_enc(&aes_ctx, key, 256);
    aes_crypt_cbc(&aes_ctx, AES_ENCRYPT, strlen(string)*sizeof(char), IV, (unsigned char*)string, (unsigned char*)code);
}

void AESTool::decodeString(unsigned char *string, char* password)
{
    aes_context aes_ctx;
    unsigned char key[32];
    unsigned char IV[16];
    memset(IV, 0, sizeof(IV));
    memset(key, 0, sizeof(key));
    memcpy(key, password, strlen(password));
    aes_setkey_dec(&aes_ctx, key, 256);
    char *outString = new  char[4096];
    aes_crypt_cbc(&aes_ctx, AES_DECRYPT, strlen(code)*sizeof(char), IV, (unsigned char*)code, (unsigned char*)outString);
    CCLOG("buffer dec:%s", outString);
    delete[] outString;
}
