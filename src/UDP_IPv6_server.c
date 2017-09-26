#include "../include/server_UDP_IPv6.h"

int main(){
  int sockfd; /* Descriptor of socket */
  int clilen, n; /* Variables for different lengths and numbers of characters*/
  char line[1000]; /* An array for the received and 
                      of the sent string */
  struct sockaddr_in servaddr, cliaddr; /* Structures 
                                           for addresses servers and clients */
  /* We are full struct for address of server: family of
   *     protocols TCP/IP, network interface – any, number of port  
   *         14888. */
  bzero(&servaddr, sizeof(servaddr)); /*Reset the struct */
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERVER_PORT);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  /* Create UDP socket */
  if((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
    perror(NULL); /* Print message of error */
    exit(1);

  }
  /* Tune address of socket */
  if(bind(sockfd, (struct sockaddr *) &servaddr, 
        sizeof(servaddr)) < 0){
    perror(NULL);
    close(sockfd);
    exit(1);

  }
  while(1) {
    /* Main cycle of service */
    /* In variables clilen write маx length
     *         for expect address of client */
    clilen = sizeof(cliaddr);
    /* We expect the arrival of the request from the client and read it. 
     *         Maximum allowed datagram length – 999 
     *                 symbols, send the sender's address to the structure 
     *                         cliaddr, Its real length will be recorded in 
     *                                 variable clilen */
    if((n = recvfrom(sockfd, line, 999, 0, 
            (struct sockaddr *) &cliaddr, &clilen)) < 0){
      perror(NULL);    
      close(sockfd);
      exit(1);
    }
  /* Print the recived text on the screen */
    printf("%s\n", line);
    /* We send the received text back to the sender's address  */
    if(sendto(sockfd, line, strlen(line), 0, 
          (struct sockaddr *) &cliaddr, clilen) < 0){
      perror(NULL);
      close(sockfd);
      exit(1);
    } /* We leave to expect a new datagram */

  }
  return 0;
}
