#include "apue.h"
#include <sys/msg.h>


struct mymsg
{
    long mtype;
    char mtext[128];
};



int main(int argc, char* argv[]){
    int id;
    int idx;
    struct mymsg msg2snd;

    for(idx=0;idx<5;idx++){
        if((id = msgget(IPC_PRIVATE, 0400|0200)) == -1)
            err_quit("msgget error");
        printf("%dth msg has idx %d\n", idx, id);
        if(msgctl(id, IPC_RMID, NULL)==-1)
            err_sys("remove msg queue error\n");
    }

    for(idx=0;idx<5;idx++){
        if((id = msgget(IPC_PRIVATE, 0400|0200)) == -1)
            err_quit("msgget error");
        printf("%dth msg has idx %d\n", idx, id);

        msg2snd.mtype = id;
        snprintf(msg2snd.mtext, 128, "message queue with id %d", id);
        if(msgsnd(id, &msg2snd, sizeof(long)+strlen(msg2snd.mtext), 0)==-1)
            err_sys("msgsnd error");
    }

    printf("ready to exit\n");

}