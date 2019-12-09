#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* Description:
 * dopo la creazione del primo processo, i successivi vengono istanziati
 * prima della terminazione di quest'ultimo. Non è noto a priori se la wait
 * viene eseguita quando ci sono 3,2,1 o 0 processi in esecuzione.
 */

int main() {
    pid_t child_pid, wpid;
    int status = 0;
    int id;
    /* Father code (before child processes start) */

    for (id=0; id<3; id++) {
        if ((child_pid = fork()) == 0) {
            /* child code */
            printf("Sono il figlio!\n");
            exit(0);
        }
    }

    /* this way, the father waits for all the child processes */
    while ((wpid = wait(&status)) > 0);
    /* Father code (After all child processes end) */
    printf("Sono il padre!\n");
    return 0;
}
