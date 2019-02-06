#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
char buf[10];
int r;
int z;
int main()

{
	int fd=0;
	//printf("cant open source ");
	printf("enter the file to be read from(0 or 1 or 2) \n");
	scanf  ("%d", &z);
	switch (z)
	{
	case 0:
	fd = open ("/dev/adxl_0",O_RDONLY);
	break;
	case 1:
	fd = open ("/dev/adxl_1",O_RDONLY);
	break;
	case 2:
	fd = open ("/dev/adxl_2",O_RDONLY);
	break;
	}


     if (fd==1)
	{
	printf("cant open source file\n");
	exit(1);}
read(fd,buf,10);
       for(r=0;r<10;r++)
{
	
	
	printf("%u",buf[r]);
	
}

}


