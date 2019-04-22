#include <stdio.h>
#include <pthread.h>
#include "share_buf.h"
#define FLIE_NAME_SIZE 20
char file_path[FLIE_NAME_SIZE]
int main(int argc,char const *argv[])
{
	if(argc != 2){
		printf("please input file name");
		exit(0);
	}
	int ret;
	memcpy(file_path, argv[1], strlen(argv[1]));
	printf("file_path:%s  strlen:%d\n", file_path,strlen(argv[1]));	
	pthread_t read_pid,write_pid;
	/*创建读写线程*/
	ret = pthread_create(&write_pid,NULL,write_file_to_buf,NULL);
	if(ret != 0){
		perror("pthread_create1 failed!");
		exit(1);		
	}
	ret = pthread_create(&read_pid,NULL,read_file_from_buf,NULL);
	if(ret != 0){
		perror("pthread_create1 failed!");
		exit(1);	
	}
	/*以阻塞方式等待线程结束*/
	ret = pthread_join(write_pid,NULL);
	if(ret !=0)
	{
		perror("pthread_join1 failed!");
		exit(1);
	}

	ret = pthread_join(read_pid,NULL);
	if(ret !=0)
	{
		perror("pthread_join1 failed!");
		exit(1);
	}

}
