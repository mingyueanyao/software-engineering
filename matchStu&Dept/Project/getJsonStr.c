#include "getJsonStr.h"

char *getJsonStr(char *filepath)
{
	FILE *fp;
	/* ���ö����Ʒ�ʽ�� */
	fp = fopen(filepath, "rb");
	/*��ȡ�ļ���С*/
	long fSize;
	fseek(fp, 0L, SEEK_END);
	fSize = ftell(fp);
	rewind(fp);
	/*�����ڴ�洢�����ļ�*/
	char *jsonStr;
	jsonStr = (char *)malloc(sizeof(char) * fSize);
	/*��ȡ�����ļ�*/
	size_t result;
	result = fread(jsonStr, 1, fSize, fp);
	
	fclose(fp);
	return jsonStr;
}
