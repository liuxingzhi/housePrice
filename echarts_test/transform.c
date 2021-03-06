#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h> 
#define MAX_BUFFER_SIZE 100

FILE* SkipLine(FILE *pfile);
bool isComma(char ch);
bool isEnter(char ch);
char* Get_Attr_Char(FILE *pfile);
float Get_Attr_Float(FILE *pfile);
int Get_Attr_Int(FILE *pfile);

int main(void)
{
	FILE* src_all_attr, *src_ln_and_lat, *des;
	//Attributes
	char* name, *landmark, *district, *address;
	float floor_area, ln, lat;
	int   price;
	
	char* Record_Buf;
	
	src_all_attr   =   fopen("lianjia.csv", "r");
	src_ln_and_lat =   fopen("ln_lat.txt","r");
	des = fopen("houseprice.js","w+");
	//skip the 1st line
	src_all_attr   =   SkipLine(src_all_attr);	
	//get attributes
	fputs("var myData = [\n",des);
	while(!feof(src_all_attr) && !feof(src_ln_and_lat))
	{
		src_all_attr    =    SkipLine(src_all_attr);
		ln              =    Get_Attr_Float(src_ln_and_lat);
		lat             =    Get_Attr_Float(src_ln_and_lat);
		if(ln == 0.0 && lat == 0.0)
		{
			src_all_attr  =  SkipLine(src_all_attr);
			continue;
		}
		address     =   Get_Attr_Char(src_all_attr);
		district    =   Get_Attr_Char(src_all_attr);
		floor_area  =   Get_Attr_Float(src_all_attr);
		landmark    =   Get_Attr_Char(src_all_attr);
		name        =   Get_Attr_Char(src_all_attr);
		price       =   Get_Attr_Int(src_all_attr);
		/*
		sprintf(Record_Buf,
				"{name:{\"name\":\"%s\",\"landmark\":\"%s\",\"floor_area\":%f,\"district\":\"%s\",\"address\":\"%s\"},value:[%f,%f,%d]}",
				name, landmark, floor_area, district, address, ln, lat, price);
		*/
		
		fprintf(des,
 				"{name:{\"name\":\"%s\",\"landmark\":\"%s\",\"floor_area\":%f,\"district\":\"%s\",\"address\":\"%s\"},value:[%f,%f,%d]}",
				name, landmark, floor_area, district, address, ln, lat, price);
		
		/*
		fwrite(Record_Buf,strlen(Record_Buf),2,des);
		*/
		if(!feof(src_all_attr) && !feof(src_ln_and_lat))
			fputs(",",des);
		fputs("\n",des);
		free(address);
		free(district);
		free(landmark);
		free(name);
	}
	//fprintf(des,"{name:{\"name\":\"end\",\"landmark\":\"end\",\"floor_area\":0,\"district\":\"end\",address:\"end\"},value:{0,0,0};}\n");
	fputs("]",des);
	//fprintf(des, "]");
	fclose(src_ln_and_lat);
	fclose(src_all_attr);
	fclose(des);
	return 0;
} 

FILE* SkipLine(FILE *pfile)
{
	while(fgetc(pfile)!='\n');
	return pfile;
}

bool isComma(char ch)
{
	if(ch == ',')
		return true;
	return false;
}

bool isEnter(char ch)
{
	if(ch == '\n')
		return true;
	return false;
}

char* Get_Attr_Char(FILE *pfile)
{
	char* buf = (char*)malloc(sizeof(char)*MAX_BUFFER_SIZE);
	if(buf == NULL)
	{
		printf("Memory Full!\n");
		exit(0);
	}
	char ch = fgetc(pfile);
	int num = 0;
	memset(buf, 0, sizeof(char)*MAX_BUFFER_SIZE);
	while(!isComma(ch) && !isEnter(ch) && !feof(pfile))
	{
		buf[num++] = ch;
		ch = fgetc(pfile);
	}
	return buf;
}

float Get_Attr_Float(FILE *pfile)
{
	char buf[MAX_BUFFER_SIZE];
	char ch = fgetc(pfile);
	int num = 0;
	memset(buf, 0, sizeof(char)*MAX_BUFFER_SIZE);
	while(!isComma(ch) && !isEnter(ch) && !feof(pfile))
	{
		buf[num++] = ch;
		ch = fgetc(pfile);
	}
	return atof(buf);
}

int Get_Attr_Int(FILE *pfile)
{
	char buf[MAX_BUFFER_SIZE];
	char ch = fgetc(pfile);
	int num = 0;
	memset(buf, 0, sizeof(char)*MAX_BUFFER_SIZE);
	while(!isComma(ch) && !isEnter(ch) && !feof(pfile))
	{
		buf[num++] = ch;
		ch = fgetc(pfile);
	}
	return atoi(buf);
}
