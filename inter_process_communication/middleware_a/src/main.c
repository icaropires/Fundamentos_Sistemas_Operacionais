#include "middleware_a.h"

#define ARB_NUMBER 1
#define FLAG 0

int main() {
	int msqid = create_message_queue("/bin/ls", 'j');

	Message msg;
	
	fprintf(stdout, "Receiving message in MIDDLEWARE A...\n");
	is_error = receiving_message(msqid, &msg, ARB_NUMBER, FLAG);

	fprintf(stdout, "%s\n", msg.msg);

	return 0;
}