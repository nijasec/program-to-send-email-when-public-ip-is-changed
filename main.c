#include <stdio.h>
#include <unistd.h>
#include "smtp.h"
#include <string.h>

#define MAIL_SERVER              "smtp.gmail.com"
#define MAIL_PORT                "587"
#define MAIL_CONNECTION_SECURITY 0 //SMTP_SECURITY_STARTTLS
#define MAIL_FLAGS               (SMTP_DEBUG         | \
                                  SMTP_NO_CERT_VERIFY) /* Do not verify cert. */
#define MAIL_CAFILE              NULL
#define MAIL_AUTH                SMTP_AUTH_PLAIN
#define MAIL_USER                "8888888@gmail.com"
#define MAIL_PASS                "888888888"
#define MAIL_FROM                "888888@gmail.com"
#define MAIL_FROM_NAME           "Cloud machine"
#define MAIL_SUBJECT             "System IP Changed"
#define MAIL_BODY                "Public IP changed  "
#define MAIL_TO                  "888888@gmail.com"
#define MAIL_TO_NAME             "888"
#define MAIL_TO_1        "8888@gmail.com"
#define MAIL_TO_NAME2             "Niju"
#define MAIL_TO_3        "888888@gmail.com"
#define MAIL_TO_NAME3             "Rajesh"

int sendMail(char *body);
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

	printf(" writing email... \n");



  char ip[1035];
  char body[65535*2];
  char temp[1035];
  char md[65535];
  
  sleep(6);
  getIP(ip);
  //getMachine(md);
  //printf("%s",ip);
   printf("%s",md);
 // bzero(temp);
  strcpy(temp,ip);
  sprintf(body,"System IP is %s \n",ip);
  //sendMail(body);
  
while(1){
sleep(20*3);
  /* Open the command for reading. */
 
getIP(ip);
 //getMachine(md);
 //printf("%s,,,,",md);
  sprintf(body,"System Public IP is %s \n",ip);
//sprintf(body,"System IP is %s",ip);
printf("\nChecking ip with previous\n");
if(strcmp(ip,temp)!=0){
    printf("\n IP has changed");
        
//sendMail(body);
 strcpy(temp,ip);

}


}
  
	return 0;
}
int sendMail(char *body)
{
        struct smtp *smtp;
  int rc;
    rc = smtp_open(MAIL_SERVER,
                 MAIL_PORT,
                 MAIL_CONNECTION_SECURITY,
                 MAIL_FLAGS,
                 MAIL_CAFILE,
                 &smtp);
printf("\nopende");
  rc = smtp_auth(smtp,
                 MAIL_AUTH,
                 MAIL_USER,
                 MAIL_PASS);
  rc = smtp_address_add(smtp,
                        SMTP_ADDRESS_FROM,
                        MAIL_FROM,
                        MAIL_FROM_NAME);
  rc = smtp_address_add(smtp,
                        SMTP_ADDRESS_TO,
                        MAIL_TO,
                        MAIL_TO_NAME);
                         rc = smtp_address_add(smtp,
                        SMTP_ADDRESS_TO,
                        MAIL_TO_1,
                        MAIL_TO_NAME2);
                       
                         rc = smtp_address_add(smtp,
                        SMTP_ADDRESS_TO,
                        MAIL_TO_1,
                        MAIL_TO_NAME2);
                       /*  rc = smtp_address_add(smtp,
                        SMTP_ADDRESS_TO,
                        MAIL_TO_3,
                        MAIL_TO_NAME3);*/
  rc = smtp_header_add(smtp,
                       "Subject",
                       MAIL_SUBJECT);
 // rc = smtp_attachment_add_mem(smtp,
   //                            "test.txt",
     //                          "Test email attachment.",
       //    
                  //  -1);
  rc = smtp_mail(smtp,
                 body);
  rc = smtp_close(smtp);
  if(rc != SMTP_STATUS_OK){
    fprintf(stderr, "smtp failed: %s\n", smtp_status_code_errstr(rc));
    return 1;
  }
  return 0;
}
