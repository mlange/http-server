#include <moca.h>

#include <stdio.h>
#include <stdlib.h>

#include <mocagendef.h>
#include <mocaerr.h>
#include <oslib.h>


int main(int argc, char *argv[])
{
    long status,
         nbytes;

    char buffer[1024];

    SOCKET fd,
           newfd;

    /* Set up a socket for listening on port 80. */
    status = osTCPListen(&fd, 9900, 10, TRUE);
    if (status != eOK)
    {
	fprintf(stderr, "osTCPListen: %s\n", osSockError( ));
	exit(1);
    }

    /* Accept an incoming connection. */
    status = osSockAccept(fd, &newfd, 0);
    if (status != eOK)
    {
	fprintf(stderr, "osSockAccept: %s\n", osSockError( ));
	exit(1);
    }

    while (1)
    {
        nbytes = osSockRecv(newfd, buffer, sizeof(buffer)-1, 0);
	if (nbytes == 0)
	{
	    break;
	}
	else if (nbytes < 0)
        {
	    fprintf(stderr, "osSockRecv: %s\n", osSockError( ));
	    exit(1);
        }

	buffer[nbytes] = '\0';

        printf("%s", buffer);
    }

    /* Close the socket. */
    osSockClose(newfd);

    exit(0);
}
