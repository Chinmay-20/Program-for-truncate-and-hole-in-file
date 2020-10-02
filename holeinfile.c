#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("Invalid Argument\\n");
	}
	
 	int fd=0,ret=0;
 	
	fd=open(argv[1],O_RDONLY);
	if(fd==-1)
	{
		perror("read");
	}
		
 	ret=lseek(fd,0,SEEK_END);
	if(ret=-1)
	{
		perror("lseek");
	}
	printf("%ld\n",lseek(fd,0,SEEK_CUR));
	lseek(fd,1024,SEEK_CUR);
	printf("%ld\n",lseek(fd,0,SEEK_CUR));
 	close(fd);
	return 0;
}

