#include "utils.h"

int create_message_queue(char *file_path, char ch) {
	assert(file_path != NULL);

	key_t key = ftok(file_path, ch);

	int msqid = msgget(key, 0666 | IPC_CREAT);
	if(msqid != -1){
		return msqid;
	} else {
		perror("Couldn't create message queue");
		exit(1);
	}
}

void sending_message(int msqid, Message *msg, int flag) {
    assert(msg != NULL);
	assert(msg->mtype >= 0);

    if(msgsnd(msqid, msg, sizeof(Message), flag) != -1) {
        /* Nothing */
    } else {
        perror("Error while sending message");
    }
}

void delete_message_queue(int msqid){
	if(msgctl(msqid, IPC_RMID, NULL) == -1){
		perror("Couldn't delete queue");
	}
}

void invalid_exit_handling(int signal){
    fprintf(stdout, "\nPlease, send the message END to exit the program!\n");
}

int receiving_message(int msqid, Message *msg, int arb_number, int flag) {
    assert(msg != NULL);
	assert(msg->mtype >= 0);

	// Get out when there is any message on queue
	// Improve, idle waiting
    fprintf(stdout, "Waiting for messages...\n");
    struct msqid_ds buf;
    unsigned int amount_messages;
    do{
        if(!msgctl(msqid, IPC_STAT, &buf)){
            /* Nothing */
        } else {
            perror("Couldn't check this queue");
            exit(1);
        }
        amount_messages = buf.msg_qnum;
    }while(!amount_messages);

    // Receive message
    int bytes = msgrcv(msqid, msg, sizeof(Message), ARB_NUMBER, FLAG);

    // Check if message could be sent
    if(bytes != -1){
        return bytes;	
    } else {
        perror("Message couldn't be received");
    }
}

char *remove_last_from_path(char* str){
	int i;
	for(i = 0; str[i] != '\0'; ++i){
		int u = 0;
		if(str[i] == '/'){
			u = i;
		}
	}
	str[i] = '\0';
	return str;
}
