#include "../include/include.h"

int main(int argc, char **argv)
{
  int sockfd; /* Descriptor of socket */
  int n, len; /* Variables fo diffrent length and number of characters */
  char sendline[1000], recvline[1000]; /* Massive for send and recive string */
  struct sockaddr_in servaddr, cliaddr; /*struct for addresses and clients */
  /*  Checking the second argument in  
   *     command string. If there in no argument, 
   *     we are stop the workingу */
  if(argc != 2){
    printf("Usage: a.out <IP address>\n");
    exit(1);
  }
  /* Create UDP socket */
  if((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
    perror(NULL); /* Print message of error */
    exit(1);
  }

  /* Filling of struct for addresses of client: family of 
   *    protocols TCP/IP, network interface – any, number of port 
   *         at you look OS. */

  bzero(&cliaddr, sizeof(cliaddr)); /* Reset of struct */
  cliaddr.sin_family = AF_INET;
  cliaddr.sin_port = htons(0);
  cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  /* Customize address of socket */
  if(bind(sockfd, (struct sockaddr *) &cliaddr, 
        sizeof(cliaddr)) < 0){
    perror(NULL);
    close(sockfd); /* Close descriptor of socket */
    exit(1);
  }
  bzero(&servaddr, sizeof(servaddr)); /* Reset of struct*/
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERVER_PORT);
  if(inet_aton(argv[1], &servaddr.sin_addr) == 0){
    printf("Invalid IP address\n");
    close(sockfd); /* Close the descriptor */
    exit(1);
  }
  /* Enter the string, which we will send to the serverу */
  printf("String => ");
  fgets(sendline, 1000, stdin);
  /* To send the datagram */
  if(sendto(sockfd, sendline, strlen(sendline)+1, 
        0, (struct sockaddr *) &servaddr, 
        sizeof(servaddr)) < 0){
    perror(NULL);
    close(sockfd);
    exit(1);
  }
  /* We are expect an answer and read it. 
   * Max length of datagram – 1000 symbols, 
    We do not need the sender address */
  if((n = recvfrom(sockfd, recvline, 1000, 0, 
          (struct sockaddr *) NULL, NULL)) < 0){
            perror(NULL);
                    close(sockfd);
                            exit(1);
                                
  }
      /* Print the answer that came and close socket */
      printf("%s\n", recvline);
          close(sockfd);
              return 0;
}
