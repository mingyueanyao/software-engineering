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

/*按符合度从小到大插入*/
void insert(int k, struct Student *tmpStu)
{
	sp1 = department[k].next;
	sp2 = sp1;
    /*移动sp1,sp2,tmpStu最终插入二者之间*/
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
	/*特殊情况*/ 
	if(sp1 == NULL)
	{
		/*插入第一个元素*/
		if(sp2 == NULL)
		{
			department[k].next = tmpStu;
		}
        /*插入最后一个*/ 
		else
		{
			sp2->next = tmpStu;
		}
	}
	else
	{
		/*插入表头*/ 
		if(sp1 == sp2)
		{
			department[k].next = tmpStu;
			tmpStu->next = sp1;
		}
		/*插入表间*/ 
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
	/*从输入文件获取json字符串*/
	jsonStr = getJsonStr("./input_data.txt");
	/*解析json字符串成json对象*/
	cJSON *root = cJSON_Parse(jsonStr);

	/*获取学生和部门数组*/
	cJSON *students = cJSON_GetObjectItem(root, "students");
	cJSON *departments = cJSON_GetObjectItem(root, "departments");

    int i;
	char *jsonStrD;
	cJSON *dItem, *rootD;
	cJSON *timeD[20], *numberD[20], *tagsD[20], *limit;
	/*提取保存需要的部门信息*/
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
	/*遍历学生数组开始匹配*/
	for(i = 0; i < 300; i++)
	{
		/*将每个学生解析为json对象*/
		sItem = cJSON_GetArrayItem(students, i);
		jsonStrS = cJSON_PrintUnformatted(sItem);
		rootS = cJSON_Parse(jsonStrS);

		timeS = cJSON_GetObjectItem(rootS, "free_time");
		numberS = cJSON_GetObjectItem(rootS, "student_no");
		wantedD = cJSON_GetObjectItem(rootS, "applications_department");
		tagsS = cJSON_GetObjectItem(rootS, "tags");

		student[i] = numberS->valuestring;

		/*遍历学生的意愿部门*/
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
			/*遍历所有部门找当前的意愿部门*/
			for(k = 0; k < 20; k++)
			{
				int m, n;
				int cntSTime, cntDTime;
				dno = numberD[k]->valuestring;
				if(strcmp(wantedDno, dno) == 0)
				{
					/*匹配时间*/
					char *sTime, *dTime;
					cntSTime = cJSON_GetArraySize(timeS);//学生空闲时间段个数
					cntDTime = cJSON_GetArraySize(timeD[k]);//部门活动时间段个数
					for(m = 0; m < cntSTime; m++)//遍历学生free_time
					{
						tmpItem = cJSON_GetArrayItem(timeS, m);
						sTime = tmpItem->valuestring;
						for(n = 0; n < cntDTime; n++)//遍历部门活动时间
						{
							int p, q;
							int cntSame, cntSTags, cntDTags;
							tmpItem = cJSON_GetArrayItem(timeD[k], n);
							dTime = tmpItem->valuestring;
							if(cmpTime(sTime, dTime) == 1)//匹配成功
							{
								cntSame = 0;
								char *sTag, *dTag;
								/*统计和该部门相同的标签个数*/
								cntSTags = cJSON_GetArraySize(tagsS);//学生兴趣标签个数
								cntDTags = cJSON_GetArraySize(tagsD[k]);//部门特点标签个数
								for(p = 0; p < cntSTags; p++)//遍历学生兴趣标签
								{
									tmpItem = cJSON_GetArrayItem(tagsS, p);
									sTag = tmpItem->valuestring;
									for(q = 0; q < cntDTags; q++)//遍历部门特点便签
									{
										tmpItem = cJSON_GetArrayItem(tagsD[k], q);
										dTag = tmpItem->valuestring;
										if(strcmp(sTag, dTag) == 0)//发现相同标签
										{
											cntSame++;
										}
									}
								}

								/*检查部门是否已经收满*/
								if(department[k].cntIn < department[k].limit)//未收满，直接收入
								{
									inFlg = 1;    //标记已纳入该意愿部门
									department[k].cntIn++;

									tmpStu = (struct Student *)malloc(sizeof(struct Student));
									tmpStu->cnt = cntSame;
									tmpStu->order = i;
									tmpStu->next = NULL;

									insert(k, tmpStu);

								}
								else//收满，考虑淘汰
								{
									tmpStu = (struct Student *)malloc(sizeof(struct Student));
									tmpStu->cnt = cntSame;
									tmpStu->order = i;
									tmpStu->next = NULL;
									
									sp1 = department[k].next;
									sp2 = sp1;
                                    /*部门原纳入成员可以淘汰*/
									if(cntSame > sp1->cnt)
									{					
										inFlg = 1;
										/*删除第一个（符合度最小）成员*/
										department[k].next = sp1->next;
										sp1 = department[k].next;
										sp2 = sp1;
										/*纳入新成员*/ 
										insert(k, tmpStu);
									}
								}
							}
							/*匹配成功，无需遍历接下来的timeD*/ 
							if(inFlg)
							{
								break;
							}	
						}
						/*匹配成功，无需遍历接下来的timeS*/
						if(inFlg)
						{
							break;
						}
					}
					//遍历部门匹配到当前意愿部门，无需再遍历 
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
		/*生成unlucky_department*/
		if(sp1 == NULL)
		{
			cJSON_AddItemToArray(unluckyD, cJSON_CreateString(department[i].d_no));
		}
		else
		{
			/*生成admitted*/ 
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
			/*生成unlucky_student*/
			cJSON_AddItemToArray(unluckyS, cJSON_CreateString(student[i]));
		}
	}
	/*生成输出json字符串*/ 
	char *out = cJSON_Print(rootOut);
	
	FILE *f;
	/*输出到文件*/ 
	f = fopen("./output_data.txt", "w");
	fputs(out, f);
	fclose(f);

	cJSON_Delete(root);
	free(jsonStr);
	return 0;
}
