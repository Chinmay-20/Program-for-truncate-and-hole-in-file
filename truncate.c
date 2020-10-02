#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("Invalid Arguements\n");
	}
	int size=0,fd=0,ret=0;
	size=atoi(argv[2]);

	fd=open(argv[1],O_WRONLY);
	if(fd==-1)
	{
		perror("read");	
	}
	ret=ftruncate(fd,size);
	if(ret==-1)
	{
		perror("ftruncate");	
	}
	size=lseek(fd,0,SEEK_END);//SEEK_CUR
	printf("The current file size is %d\n",size);
	close(fd);
	return 0;
}
	
