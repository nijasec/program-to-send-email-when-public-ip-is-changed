#include <stdio.h>
#include <unistd.h>
#include "smtp.h"
#include <string.h>

#define MAIL_SERVER              "smtp.gmail.com"
#define MAIL_PORT                "465"
#define MAIL_CONNECTION_SECURITY 1 //SMTP_SECURITY_STARTTLS
#define MAIL_FLAGS               (SMTP_DEBUG         | \
                                  SMTP_NO_CERT_VERIFY) /* Do not verify cert. */
#define MAIL_CAFILE              NULL
#define MAIL_AUTH                SMTP_AUTH_PLAIN
#define MAIL_USER                "xxx@gmail.com"
#define MAIL_PASS                "ccc"
#define MAIL_FROM                "xxx@gmail.com"
#define MAIL_FROM_NAME           "Cloud machine"
#define MAIL_SUBJECT             "System url  Changed"
#define MAIL_BODY                "Public url changed  "
#define MAIL_TO                  "ggg@gmail.com"
#define MAIL_TO_NAME             "bhnhnb"


struct mail_args{

char m_from[300];
char m_to[300];
char m_sub[300];
char m_msg[1000];
char m_path[1000];
char m_user[300];
char m_passwd[300];
char m_host[500];
char m_port[100];



};

int sendMail(struct mail_args *args);
int getMachine(char *ptr)
{
     FILE *fp;
  fp = popen("neofetch", "r");
  if (fp == NULL) {
    printf("Failed to run command\n" );
   return 1;
  }

  /* Read the output a line at a time - output it. */
  while (fgets(ptr, 65535, fp) != NULL) {
   // printf("%s", ptr);
  }
    /* close */
  pclose(fp);
  return 0;
}
int getIP(char *ptr)
{
    FILE *fp;
  fp = popen("dig +short myip.opendns.com @resolver1.opendns.com", "r");
  if (fp == NULL) {
    printf("Failed to run command\n" );
   return 1;
  }

  /* Read the output a line at a time - output it. */
  while (fgets(ptr, 1035, fp) != NULL) {
    printf("%s", ptr);
  }
    /* close */
  pclose(fp);
  return 0;
}
int main(int argc, char **argv)
{


  char ip[1035];
  char body[65535*2];
  char temp[1035];
  char md[65535];
  struct mail_args args;
  int option;

   while((option = getopt(argc, argv, ":f:t:s:m:u:p:a:h:i:")) != -1){ //get option from the getopt() method
      switch(option){
         //For option i, r, l, print that these are options


         case 'r':
            printf("Given Option: %c\n", option);
            break;
         case 'f': //here f is used for some file name

            strcpy(args.m_from,optarg);
            printf("Email from:%s\n", args.m_from);
            break;
        case 't':
            strcpy(args.m_to,optarg);
            printf("To address:%s",args.m_to);
            break;
          case 's':
            strcpy(args.m_sub,optarg);
            printf("\nSubject:%s",args.m_sub);
            break;
             case 'm':
             strcpy(args.m_msg,optarg);
            printf("\nMessage body:%s",args.m_msg);
            break;
         case 'u':

            strcpy(args.m_user,optarg);
            printf("\nUsername:%s",args.m_user);
            break;
        case 'p':
        strcpy(args.m_passwd,optarg);
        printf("\nPassword:%s",args.m_passwd);
        break;

        case 'a':
            strcpy(args.m_path,optarg);
            printf("\nattcah:%s",optarg);
            break;
        case 'h':
            strcpy(args.m_host,optarg);
            printf("\nhost address:%s",args.m_host);
            break;
        case 'i':
        strcpy(args.m_port,optarg);
             printf("\nhost port:%s",args.m_port);
          break;

         case ':':
            printf("option needs a value\n");
            break;
         case '?': //used for some unknown options
            printf("unknown option: %c\n", optopt);
            break;
      }
   }
   //return -1;

  sleep(6);
  //getIP(ip);
  //getMachine(md);
  //printf("%s",ip);
//   printf("%s",md);
 // bzero(temp);
  //strcpy(temp,ip);
 // sprintf(body,"System IP is %s \n",ip);
  //sendMail(body);

//while(1){
//sleep(20*3);
  /* Open the command for reading. */

//getIP(ip);
 //getMachine(md);
 //printf("%s,,,,",md);

//sprintf(body,"System IP is %s",ip);

//if(strcmp(ip,temp)!=0){
  //  printf("\n IP has changed");

sendMail(&args);
 //strcpy(temp,ip);



//}


	return 0;
}
int sendMail(struct mail_args *args)
{
        struct smtp *smtp;
  int rc;

    rc = smtp_open(args->m_host,
                 args->m_port,
                 MAIL_CONNECTION_SECURITY,
                 MAIL_FLAGS,
                 MAIL_CAFILE,
                 &smtp);
printf("\nSMTP connected ");

  rc = smtp_auth(smtp,
                 MAIL_AUTH,
                  args->m_user,
                 args->m_passwd);
    if(rc != SMTP_STATUS_OK)
fprintf(stderr,"smtp failed %s\n ",smtp_status_code_errstr(rc));

  rc = smtp_address_add(smtp,
                        SMTP_ADDRESS_FROM,
                        args->m_from,
                        args->m_from);
  rc = smtp_address_add(smtp,
                        SMTP_ADDRESS_TO,
                        args->m_to,
                        args->m_to);

                       /*  rc = smtp_address_add(smtp,
                        SMTP_ADDRESS_TO,
                        MAIL_TO_3,
                        MAIL_TO_NAME3);*/
  rc = smtp_header_add(smtp,
                       "Subject",
                       args->m_sub);
                       if(args->m_path!=NULL)
 rc = smtp_attachment_add_path(smtp,
                               "filename.txt",
                               args->m_path);
  rc = smtp_mail(smtp,
                 args->m_msg);
if(rc != SMTP_STATUS_OK)
fprintf(stderr,"smtp failed %s\n ",smtp_status_code_errstr(rc));

  rc = smtp_close(smtp);
  if(rc != SMTP_STATUS_OK){
    fprintf(stderr, "smtp failed: %s\n", smtp_status_code_errstr(rc));
    return 1;
  }
  return 0;
}
