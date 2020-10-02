/*
	Program which accept directory name from user and create hole in file if size is less than 1kb & if it is greater than 1kb then truncate the remaining data.
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("Invalid Arguments\n");
		printf("Usage: exe_name Directory_name\n");
	}

	DIR *dir;
	struct stat statf;
	struct dirent *statd;
	int fd=0,ret=0;
	//char lnname[10];
	char path[60];

	char *pdir=getcwd(NULL,0);

	chdir(argv[1]);

	dir=opendir(argv[1]);
	if(dir==NULL)
	{
		perror("opendir");
		return -1;
	}

	while((statd=readdir(dir))!=NULL)
	{
		if(statd->d_type==DT_DIR)
		{
			continue;
		}
		else if((statd->d_type)==DT_LNK)
		{
			printf("%s\n",statd->d_name);
			if(realpath(statd->d_name,path)==NULL)
			{
				perror("realpath");
				return -1;
			}
			ret=lstat(path,&statf);
			if(ret==-1)
			{
				perror("lstat");
				return -1;	
			}
			printf("%s:%ld\n",statd->d_name,statf.st_size);
	
			if(statf.st_size<1024)
			{
				fd=open(statd->d_name,O_WRONLY);
				if(fd==-1)
				{
					perror("open");	
					printf("symb\n");
					return -1;
				}
				lseek(fd,0,1023);
				ret=write(fd,"c",1);
				if(ret==-1)
				{
					perror("write");
					return -1;
				}
				printf("%s:%ld\n",statd->d_name,statf.st_size);
				printf("The current file offset is %ld",lseek(fd,0,SEEK_CUR));
				close(fd);
			}
			else if(statf.st_size>1024)
			{
				truncate(statd->d_name,1024);
				printf("%s:%ld\n",statd->d_name,statf.st_size);
			}
			/*readlink(statd->d_name,lnname,sizeof(lnname));
			strcpy(path,getcwd(NULL,0));
			strcat(path,lnname);
			printf("%s\n",lnname);*/
		}
		else if((statd->d_type)==DT_REG)
		{
			ret=stat(statd->d_name,&statf);
			if(ret==-1)
			{
				perror("stat");
				//printf("%s\n",statd->d_name);
				return -1;
			}
			

			if(statf.st_size<1024)
			{
				fd=open(statd->d_name,O_WRONLY);
				if(fd==-1)
				{
					perror("open");
					return -1;
				}
				lseek(fd,1023,SEEK_SET);
				ret=write(fd,"c",1);
				if(ret==-1)
				{
					perror("write");
					return -1;
				}
				printf("%s\n",statd->d_name);
				printf("The current file offset is %ld\n",lseek(fd,0,SEEK_CUR));
				close(fd);
			}
			else if(statf.st_size>1024)
			{
				fd=open(statd->d_name,O_WRONLY);
				if(fd==-1)
				{
					perror("open");
					return -1;
				}
				ftruncate(fd,1024);
				lseek(fd,0,SEEK_END);
				printf("%s\n",statd->d_name);
				printf("The current file offset is %ld\n",lseek(fd,0,SEEK_CUR));
				close(fd);
			}

		}
		
		
	}
	
	closedir(dir);
	chdir(pdir);
	printf("%s\n",getcwd(NULL,0));
	return 0;
}

