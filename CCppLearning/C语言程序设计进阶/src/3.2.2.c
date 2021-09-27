#include<stdio.h>
#include<stdbool.h>

struct date{
	int year;
	int month;
	int day;
};

bool isLeap(struct date d);
int numberOfDays(struct date d);

int main(int argc, int const *argv[])
{
	struct date today, tomorrow;
	printf("Please input the day of today as yyyy mm dd: ");
	scanf("%d %d %d",&today.year,&today.month,&today.day);
	if(today.day != numberOfDays(today))
	{//不是年份或者月份最后一天
		tomorrow.year = today.year;
		tomorrow.month = today.month;
		tomorrow.day = today.day + 1;
	}else if(today.month == 12){
		//年份最后一天
		tomorrow.year = today.year + 1;
		tomorrow.month = 1;
		tomorrow.day = 1;
	}else{
		//月份最后一天
		tomorrow.year = today.year;
		tomorrow.month = today.month + 1;
		tomorrow.day = 1;
	}
	printf("Tomorrow's date is %d-%d-%d\n",tomorrow.year,tomorrow.month,tomorrow.day);
	return 0;
}

//返回对应月份的天数
int numberOfDays(struct date d)
{
	int days;
	const int daysPerMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	if(d.month==2 && isLeap(d))
	{
		days = 29;
	}else{
		days = daysPerMonth[d.month-1];
	}
}

//判断是否为闰年
bool isLeap(struct date d)
{
	if((d.year%4==0 && d.year%100 != 0)||d.year%400==0)
	{
		return true;
	}else{
		return false;
	}

}
