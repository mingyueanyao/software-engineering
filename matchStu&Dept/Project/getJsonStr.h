#ifndef GETJSONSTR_H
#define GETJSONSTR_H

#include <stdio.h>
#include <stdlib.h>

#include "cJSON.h"

/*输入json格式的文件路径*/
/*将整个文件输出成json字符串*/ 
char *getJsonStr(char *filepath);

#endif
