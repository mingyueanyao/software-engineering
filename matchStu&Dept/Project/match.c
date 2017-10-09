#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cJSON.h"
#include "cmpTime.h"
#include "getJsonStr.h"

struct Student
{
	int cnt;
	int order;
	struct Student *next;
}*tmpStu, *sp1, *sp2;

struct Department
{
	int cntIn;
	int limit;
	char *d_no;
	struct Student *next;
} department[20];

char *student[300];

/*�����϶ȴ�С�������*/
void insert(int k, struct Student *tmpStu)
{
	sp1 = department[k].next;
	sp2 = sp1;
    /*�ƶ�sp1,sp2,tmpStu���ղ������֮��*/
	while(sp1 != NULL) 
	{
		if(sp1->cnt < tmpStu->cnt)
		{
			sp2 = sp1;
			sp1 = sp1->next;
		}
		else
		{
			break;
		}
	}
	/*�������*/ 
	if(sp1 == NULL)
	{
		/*�����һ��Ԫ��*/
		if(sp2 == NULL)
		{
			department[k].next = tmpStu;
		}
        /*�������һ��*/ 
		else
		{
			sp2->next = tmpStu;
		}
	}
	else
	{
		/*�����ͷ*/ 
		if(sp1 == sp2)
		{
			department[k].next = tmpStu;
			tmpStu->next = sp1;
		}
		/*������*/ 
		else
		{
			sp2->next = tmpStu;
			tmpStu->next = sp1;
		}
	}
}

int main()
{
	char *jsonStr;
	/*�������ļ���ȡjson�ַ���*/
	jsonStr = getJsonStr("./input_data.txt");
	/*����json�ַ�����json����*/
	cJSON *root = cJSON_Parse(jsonStr);

	/*��ȡѧ���Ͳ�������*/
	cJSON *students = cJSON_GetObjectItem(root, "students");
	cJSON *departments = cJSON_GetObjectItem(root, "departments");

    int i;
	char *jsonStrD;
	cJSON *dItem, *rootD;
	cJSON *timeD[20], *numberD[20], *tagsD[20], *limit;
	/*��ȡ������Ҫ�Ĳ�����Ϣ*/
	for (i = 0; i < 20; i++)
	{
		dItem = cJSON_GetArrayItem(departments, i);
		jsonStrD = cJSON_PrintUnformatted(dItem);
		rootD = cJSON_Parse(jsonStrD);

		timeD[i] = cJSON_GetObjectItem(rootD, "event_schedules");
		numberD[i] = cJSON_GetObjectItem(rootD, "department_no");
		tagsD[i] = cJSON_GetObjectItem(rootD, "tags");
		limit = cJSON_GetObjectItem(rootD, "member_limit");

		department[i].cntIn = 0;
		department[i].d_no = numberD[i]->valuestring;
		department[i].limit = limit->valueint;
		department[i].next = NULL;
	}

	char *jsonStrS;
	cJSON *sItem, *rootS, *tmpItem;
	cJSON *timeS, *numberS, *wantedD, *tagsS;
	/*����ѧ�����鿪ʼƥ��*/
	for(i = 0; i < 300; i++)
	{
		/*��ÿ��ѧ������Ϊjson����*/
		sItem = cJSON_GetArrayItem(students, i);
		jsonStrS = cJSON_PrintUnformatted(sItem);
		rootS = cJSON_Parse(jsonStrS);

		timeS = cJSON_GetObjectItem(rootS, "free_time");
		numberS = cJSON_GetObjectItem(rootS, "student_no");
		wantedD = cJSON_GetObjectItem(rootS, "applications_department");
		tagsS = cJSON_GetObjectItem(rootS, "tags");

		student[i] = numberS->valuestring;

		/*����ѧ������Ը����*/
		int j, inFlg, cntWantedD;
		char *dno, *wantedDno; 
		cntWantedD = cJSON_GetArraySize(wantedD);
		for(j = 0; j < cntWantedD; j++)
		{
			int k;
			char *dno;
			inFlg = 0;
			tmpItem = cJSON_GetArrayItem(wantedD, j);
			wantedDno = tmpItem->valuestring;
			/*�������в����ҵ�ǰ����Ը����*/
			for(k = 0; k < 20; k++)
			{
				int m, n;
				int cntSTime, cntDTime;
				dno = numberD[k]->valuestring;
				if(strcmp(wantedDno, dno) == 0)
				{
					/*ƥ��ʱ��*/
					char *sTime, *dTime;
					cntSTime = cJSON_GetArraySize(timeS);//ѧ������ʱ��θ���
					cntDTime = cJSON_GetArraySize(timeD[k]);//���Żʱ��θ���
					for(m = 0; m < cntSTime; m++)//����ѧ��free_time
					{
						tmpItem = cJSON_GetArrayItem(timeS, m);
						sTime = tmpItem->valuestring;
						for(n = 0; n < cntDTime; n++)//�������Żʱ��
						{
							int p, q;
							int cntSame, cntSTags, cntDTags;
							tmpItem = cJSON_GetArrayItem(timeD[k], n);
							dTime = tmpItem->valuestring;
							if(cmpTime(sTime, dTime) == 1)//ƥ��ɹ�
							{
								cntSame = 0;
								char *sTag, *dTag;
								/*ͳ�ƺ͸ò�����ͬ�ı�ǩ����*/
								cntSTags = cJSON_GetArraySize(tagsS);//ѧ����Ȥ��ǩ����
								cntDTags = cJSON_GetArraySize(tagsD[k]);//�����ص��ǩ����
								for(p = 0; p < cntSTags; p++)//����ѧ����Ȥ��ǩ
								{
									tmpItem = cJSON_GetArrayItem(tagsS, p);
									sTag = tmpItem->valuestring;
									for(q = 0; q < cntDTags; q++)//���������ص��ǩ
									{
										tmpItem = cJSON_GetArrayItem(tagsD[k], q);
										dTag = tmpItem->valuestring;
										if(strcmp(sTag, dTag) == 0)//������ͬ��ǩ
										{
											cntSame++;
										}
									}
								}

								/*��鲿���Ƿ��Ѿ�����*/
								if(department[k].cntIn < department[k].limit)//δ������ֱ������
								{
									inFlg = 1;    //������������Ը����
									department[k].cntIn++;

									tmpStu = (struct Student *)malloc(sizeof(struct Student));
									tmpStu->cnt = cntSame;
									tmpStu->order = i;
									tmpStu->next = NULL;

									insert(k, tmpStu);

								}
								else//������������̭
								{
									tmpStu = (struct Student *)malloc(sizeof(struct Student));
									tmpStu->cnt = cntSame;
									tmpStu->order = i;
									tmpStu->next = NULL;
									
									sp1 = department[k].next;
									sp2 = sp1;
                                    /*����ԭ�����Ա������̭*/
									if(cntSame > sp1->cnt)
									{					
										inFlg = 1;
										/*ɾ����һ�������϶���С����Ա*/
										department[k].next = sp1->next;
										sp1 = department[k].next;
										sp2 = sp1;
										/*�����³�Ա*/ 
										insert(k, tmpStu);
									}
								}
							}
							/*ƥ��ɹ������������������timeD*/ 
							if(inFlg)
							{
								break;
							}	
						}
						/*ƥ��ɹ������������������timeS*/
						if(inFlg)
						{
							break;
						}
					}
					//��������ƥ�䵽��ǰ��Ը���ţ������ٱ��� 
					break; 
				}
			}
		}
	}

	cJSON *rootOut, *unluckyS, *admitted, *unluckyD;
	rootOut = cJSON_CreateObject();
	unluckyS = cJSON_CreateArray();
	admitted = cJSON_CreateArray();
	unluckyD = cJSON_CreateArray();
	cJSON_AddItemToObject(rootOut, "unlucky_student", unluckyS);
	cJSON_AddItemToObject(rootOut, "admitted", admitted);
	cJSON_AddItemToObject(rootOut, "unlucky_department", unluckyD);

	int flg[300];
	memset(flg, 0, sizeof(int) * 300);
	for(i = 0; i < 20; i++)
	{
		sp1 = department[i].next;
		/*����unlucky_department*/
		if(sp1 == NULL)
		{
			cJSON_AddItemToArray(unluckyD, cJSON_CreateString(department[i].d_no));
		}
		else
		{
			/*����admitted*/ 
			cJSON *admittedDno, *admittedS;
			admittedDno = cJSON_CreateObject();
			admittedS = cJSON_CreateArray();
			cJSON_AddItemToObject(admittedDno, "member", admittedS);
			while(sp1 != NULL)
			{
				cJSON_AddItemToArray(admittedS, cJSON_CreateString(student[sp1->order]));
				flg[sp1->order] = 1;
				sp1 = sp1->next;
			}
			cJSON_AddStringToObject(admittedDno, "department_no", department[i].d_no);
			cJSON_AddItemToArray(admitted, admittedDno);
		}
	}
	for(i = 0; i < 300; i++)
	{
		if(!flg[i])
		{
			/*����unlucky_student*/
			cJSON_AddItemToArray(unluckyS, cJSON_CreateString(student[i]));
		}
	}
	/*�������json�ַ���*/ 
	char *out = cJSON_Print(rootOut);
	
	FILE *f;
	/*������ļ�*/ 
	f = fopen("./output_data.txt", "w");
	fputs(out, f);
	fclose(f);

	cJSON_Delete(root);
	free(jsonStr);
	return 0;
}
