//Robert Humble
//rh1269@txstate.edu

// This is the server application that will be used to requests requests from the client.
// It takes 3 arguments, server IP (this machines ip) , desired port, backlog size.

// List of includes
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
 #include <unistd.h>
 #include <time.h>

#define MAXBUF 1024




int main (int argc,char* argv[]) {




//pass this ip
//pass desired port
//pass backlog number


  char myIP[40];
  char cPort[6];
  //char cFile [200];
  int nPort;
  int backlog;
  
  if (argc < 4)
    {
      printf ("Usage: server_ip server_port backlog_size \r\n");
      return(0);
    }
    
  printf("1\n");
  sprintf(myIP,"%s",argv[1]);
 printf("myIP %s \n", myIP);
//****************************
printf("2\n");
  sprintf(cPort,"%s",argv[2]);
  nPort = atoi(cPort);
printf("nport: %i \n", nPort);  
  
//**************************  
  
printf("3\n");
  //sprintf(backlog,"%i",argv[3]);
  backlog=atoi(argv[3]);
printf("backlog: %i\n", backlog);
  
  printf("4\n");
  //struct sockaddr_in name;
  //struct hostent *hent;
  //int sd;
  
  
  
  
  //start server here
  
 //create socket 
  
  int sockfd=socket(AF_INET,SOCK_STREAM,0);
  
  if(sockfd>0)
  {
    printf("socket created: %i \n", sockfd);
  }
  else
  {
       printf("socket error: %i \n", sockfd);
       exit(-1);
  }
  
  
  // start bind
 
 

  
  
  struct sockaddr_in mainSAddr;
 
 
  mainSAddr.sin_family = AF_INET;
  mainSAddr.sin_port = htons (nPort);
 
  inet_pton(AF_INET,myIP,(&mainSAddr.sin_addr));

  
if(bind(sockfd,(struct sockaddr *)&mainSAddr,sizeof(mainSAddr)) < 0) {
    perror("server: bind() error error");
    exit (-1);
  }

printf("Binded!! \n");  


//start listening

if (listen(sockfd,backlog)<0){
    perror("server: listen() super error");
    exit (-1);
  }


printf("listening !!!\n");










//OPEN LOG

FILE *logFile;
logFile=fopen("logFILE.txt","a+");
fprintf(logFile, "START LOG\n");
fclose(logFile);


//timing
time_t currentTime=time(NULL)*1000;
printf("time: %i \n",(int)currentTime );
time_t startTime,endTime;

logFile=fopen("logFILE.txt","a+");
fprintf(logFile, "START LOG time:\n",(int)currentTime);
fclose(logFile);




//accept

struct sockaddr_in clientAddr;
socklen_t addrlen;

addrlen=sizeof clientAddr;
int newSockfd;
char stringtime[INET_ADDRSTRLEN];

//open big while
while(1){

if( (newSockfd=accept(sockfd, (struct sockaddr *)&clientAddr,/*(socklen_t *)sizeof(struct sockaddr_in)*/&addrlen))<0){
    perror("server: accept() super error");
    exit (-1);
  }
  
  
  printf("accepted !!!!\n  newsockfd is: %i \n\n", newSockfd);
  
  
  
  
  //printf("take another step i dare you\n");
 logFile=fopen("logFILE.txt","a+");
fprintf(logFile, "\n NEW REQUEST********************************\n");
fclose(logFile);
 printf("\n\nclient ip: %s" , inet_ntop(AF_INET,&(clientAddr.sin_addr),stringtime, INET_ADDRSTRLEN));
logFile=fopen("logFILE.txt","a+");
fprintf(logFile, "client ip: %s\n",inet_ntop(AF_INET,&(clientAddr.sin_addr),stringtime, INET_ADDRSTRLEN));
fclose(logFile);


startTime=time(NULL)*1000;
logFile=fopen("logFILE.txt","a+");
fprintf(logFile, "Start time: %i\n",(int) startTime);
fclose(logFile);


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //read time
  //
  
  int goodread=0;
  char inReqBuffer[MAXBUF];
  //strcpy(inReqBuffer, "This is String 1.");
  int bytes_read = 0;
  int total_bytes_read = 0;

bytes_read = read(newSockfd, (void *)inReqBuffer, MAXBUF-1);

printf("\n bytes read = %i \n", bytes_read);



    
   printf("read!!!!! \n buffer shows: %s", inReqBuffer);

logFile=fopen("logFILE.txt","a+");
fprintf(logFile, "\n requested file: %s\n",inReqBuffer);
fclose(logFile);

 
 
 
FILE *targetfile;
 
int found;

if( access( inReqBuffer, F_OK ) != -1 ) {
    
if((targetfile=fopen(inReqBuffer,"r"))==NULL){
    printf("and its null\n\n");                                       
    perror("server: fileopen() super error");
    exit (-1);
  }
}
else
{ printf("\n FILE NOT FOUND \n\n"); 
logFile=fopen("logFILE.txt","a+");
fprintf(logFile, "\n FILE NOT FOUND \n\n %s\n");
fclose(logFile);
exit(-1); }
 



 char testmsg[MAXBUF];
 int bytesSent=0;
 int bytestoSend=0;
 int totalSent=0;
 
 
 //printf("\n bytes to send %i\n", bytestoSend);
 
 void *ptr=testmsg;
int fileSIZE=0;
 
fseek (targetfile, 0, SEEK_END);
printf("\nsize of target file: %i\n",fileSIZE=(ftell(targetfile)));
rewind(targetfile);


logFile=fopen("logFILE.txt","a+");
fprintf(logFile, "size of target file: %i\n",fileSIZE);
fclose(logFile);

 
int loopCount=0;

 while((bytestoSend=fread(testmsg,1,MAXBUF,targetfile))>0)
 {	
   printf("bytestoSend size is : %i \n", bytestoSend);
	loopCount++;
			
           totalSent+=write(newSockfd,testmsg,/*(size_t)sizeof testmsg//(size_t)MAXBUF*/ bytestoSend);

 }

endTime=time(NULL)*1000;
int timeTaken=(int) (endTime-startTime);

logFile=fopen("logFILE.txt","a+");
fprintf(logFile, "FILE SENT\n End Time: %i\n",(int) endTime);
fprintf(logFile, "Time Taken : %i ms\n",timeTaken);
fprintf(logFile, "Transfer Rate : ",(int) (timeTaken/totalSent));
fclose(logFile);


 
 
 printf("testmsg size is : %i \n", (size_t)sizeof testmsg);
    
  fclose(targetfile);
  
  printf("totalsent shows: %i\n", totalSent);
  logFile=fopen("logFILE.txt","a+");
fprintf(logFile, "totalsent: %i\n",totalSent);
fclose(logFile);
  

  printf("loopcount shows: %i\n", loopCount);

//end big while
close(newSockfd);

}

 

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
 
 
  close(sockfd);
//  close(newSockfd);

  return 0;
}
