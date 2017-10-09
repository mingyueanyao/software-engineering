#include "cmpTime.h"

/*比较部门时间和学生时间，如果传入的学生时间与部门时间不冲突则返回1，否则返回0*/
int cmpTime(char *stu ,char *dep)
{
	char time[9][3],time2[9],s_day[5],d_day[5];
	int k;
	for(k=0; k<strlen(stu); k++)
	{
		if(stu[k]=='.')
		{
			strncpy(s_day,stu,k);
//					printf("%s\n",s_day);
			if(stu[k+2]==':' && stu[k+7]==':')
			{
				strncpy(time[1],stu+k+1,1);
				strncpy(time[2],stu+k+3,2);
				strncpy(time[3],stu+k+6,1);
				strncpy(time[4],stu+k+8,2);
			}
			else if(stu[k+2]==':')
			{
				strncpy(time[1],stu+k+1,1);
				strncpy(time[2],stu+k+3,2);
				strncpy(time[3],stu+k+6,2);
				strncpy(time[4],stu+k+9,2);
			}
			else
			{
				strncpy(time[1],stu+k+1,2);
				strncpy(time[2],stu+k+4,2);
				strncpy(time[3],stu+k+7,2);
				strncpy(time[4],stu+k+10,2);
			}

			time2[1]=atoi(time[1]);
			time2[2]=atoi(time[2]);
			time2[3]=atoi(time[3]);
			time2[4]=atoi(time[4]);
//					printf("%d %d %d %d \n",time2[1],time2[2],time2[3],time2[4]);
			break;
		}
	}

	//提取部门时间
	for(k=0; k<strlen(dep); k++)
	{
		if(dep[k]=='.')
		{
			strncpy(d_day,dep,k);
//					printf("%s\n",d_day);
			if(dep[k+2]==':' && dep[k+7]==':')
			{
				strncpy(time[5],dep+k+1,1);
				strncpy(time[6],dep+k+3,2);
				strncpy(time[7],dep+k+6,1);
				strncpy(time[8],dep+k+8,2);
			}
			else if(dep[k+2]==':')
			{
				strncpy(time[5],dep+k+1,1);
				strncpy(time[6],dep+k+3,2);
				strncpy(time[7],dep+k+6,2);
				strncpy(time[8],dep+k+9,2);
			}
			else
			{
				strncpy(time[5],dep+k+1,2);
				strncpy(time[6],dep+k+4,2);
				strncpy(time[7],dep+k+7,2);
				strncpy(time[8],dep+k+10,2);
			}


			time2[5]=atoi(time[5]);
			time2[6]=atoi(time[6]);
			time2[7]=atoi(time[7]);
			time2[8]=atoi(time[8]);
//					printf("%s\n",d_day);
//					printf("%d %d %d %d\n",time2[5],time2[6],time2[7],time2[8]);
			break;
		}


	}

//		//两者时间相比较
	if(strcmp(s_day,d_day)==0)
	{
		if((time2[1]*60+time2[2]) <= (time2[5]*60+time2[6]) && (time2[3]*60+time2[4]) >= (time2[7]*60+time2[8]) )
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
