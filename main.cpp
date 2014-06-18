#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/uio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string>
int main( int argc, char *argv[] )
{
     
     int sockfd, newsockfd, portno;
     socklen_t   clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int  n;

     /* First call to socket() function */
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
     {
        perror("ERROR opening socket");
        exit(1);
      }
    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 3333;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
                                                 
    /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr,
                        sizeof(serv_addr)) < 0)
    {
        perror("ERROR on binding");
        exit(1);
     }
   
    /* Now start listening for the clients, here process will
     * go in sleep mode and will wait for the incoming connection
     */
     listen(sockfd,5);
     clilen = sizeof(cli_addr);

    /* Accept actual connection from the client */
     newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
     if (newsockfd < 0) 
     {
        perror("ERROR on accept");
        exit(1);
      }
    /* If connection is established then start communicating */
    bzero(buffer,256);
                                                                        
   
    while(1) {
        n = read(newsockfd,buffer,255 );
        printf("%d", n);
        if (n < 0)
        {
            perror("ERROR reading from socket");
            exit(1);
         }
	if (n == 0){
          listen(sockfd,5);

	  /* Accept actual connection from the client */
	  newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
	  if (newsockfd < 0)
	    {
	      perror("ERROR on accept");
	      exit(1);
	    }
	  /* If connection is established then start communicating */
	  bzero(buffer,256);
         }
        //printf("Here is the message: %s\n",buffer);
	if (n>0){
	  /* Write a response to the client */

	  std::time_t result = std::time(NULL);
	  std::string name = "data";
	  struct tm* localtm = std::localtime(&result);
	  localtm->tm_sec = 0;
	  localtm->tm_min = 0; 
	  localtm->tm_hour = 0;
	  name.append( std::asctime(localtm) );

	  FILE *fp = fopen(name.c_str(), "ab");
	  if (fp != NULL) {
	    fputs(buffer, fp);
	    fclose(fp);
	  }
	}
             }
    if (n < 0)
     {
        perror("ERROR writing to socket");
        exit(1);
      }
    return 0; 
}


