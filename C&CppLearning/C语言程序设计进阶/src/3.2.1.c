#include<stdio.h>
#include<stdlib.h>

struct date{
	int year;
	int month;
	int day;
};

int main(int argc, int const *argv[])
{
	struct date today;
	//结构体赋值	
	today = (struct date){2019,11,27};
	struct date day;
	day = today;//结构体整体赋值
	printf("Today is %d-%d-%d\n",today.year,today.month,today.day);
	printf("The day is %d-%d-%d\n",day.year,day.month,day.day);
	day.year = 2020;
	printf("The day is %d-%d-%d\n",day.year,day.month,day.day);
	return 0;
}
