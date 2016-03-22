#include "aes.h"

/**AES加密工具
@warning 貌似不怎么稳定
 */
class AESTool
{
public:
     void  encodeString(char *string, char* password, unsigned char*outString);
     void decodeString(unsigned char *string, char* password);
private:
      char code[8192*2*2];
};