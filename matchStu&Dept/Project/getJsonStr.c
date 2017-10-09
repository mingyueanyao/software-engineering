#include "getJsonStr.h"

char *getJsonStr(char *filepath)
{
	FILE *fp;
	/* 采用二进制方式打开 */
	fp = fopen(filepath, "rb");
	/*获取文件大小*/
	long fSize;
	fseek(fp, 0L, SEEK_END);
	fSize = ftell(fp);
	rewind(fp);
	/*分配内存存储整个文件*/
	char *jsonStr;
	jsonStr = (char *)malloc(sizeof(char) * fSize);
	/*读取整个文件*/
	size_t result;
	result = fread(jsonStr, 1, fSize, fp);
	
	fclose(fp);
	return jsonStr;
}
