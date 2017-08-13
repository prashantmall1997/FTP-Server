//Program to implement FTP server to share files

//Header files used
#include <stdio.h>		//for printf and other functions
#include <stdlib.h>		//for exit and other functions
#include <string.h>		//for string manipulations
#include <signal.h>		//for handling signals
#include <netdb.h>		//for host information
#include <unistd.h>		//for close()
#include <netinet/in.h>	//for recv()
//#include <sys/socket.h>	//for socket creation
//#include <sys/types.h>

//Macro used
#define TRUE 1
#define FALSE 0
#define MAX 10
#define LENGTH 30

//Buffer size for file transfer(speed)
const int BUFFER = 512*1024;	//bytes

//Queue for maintaining file names for transfer
typedef struct queue
{
	char name[MAX][LENGTH];
	int front;
	int rear;
}queue;

queue q;

//Function to initialize queue
void init()
{
	q.front = -1;
	q.rear = -1;
}

//Function to check if queue is empty
int isEmpty()
{
	if((q.rear == -1) || (q.rear == -1) || (q.front > q.rear))
		return TRUE;
	else
		return FALSE;
}

//Function to check if queue is full
int isFull()
{
	if(q.rear == MAX - 1)
		return TRUE;
	else
		return FALSE;
}

//Inserting name in the queue
void Enqueue(char *Name)
{
	if(isFull() == TRUE)
		printf("Queue is full.\n");
	else
	{
		if((q.front == -1) && (q.rear == -1))
			q.front = 0;

		q.rear++;
		strcpy(q.name[q.rear], Name);
	}
}

//Removing from the queue
char *Dequeue()
{
	if(isEmpty() == TRUE)
	{
		printf("Queue is empty.\n");
		init();
		return NULL;
	}
	else
	{
		char *temp;
		temp = q.name[q.front];
		q.front++;
		return temp;
	}
}

//Display the queue items
void Display()
{
	int i = q.front;

	for(; i <= q.rear; i++)
		printf("File %d : %s \n", i + 1, q.name[i]);
}
//End of Queue

//Function to get exit from program if program
//is not called properly
void InitialCheck()
{
	printf("Instruction : Name (send / receive) fileName [host : port]\n");
	exit(1);
}

//Function to get IP address/Host name
unsigned long getHost( const char *name)
{
	//This data type is used to represent an entry
	//in the hosts database

	//gethostbyname(name) method returns information
	//about the host named "name"
	struct hostent *host = gethostbyname(name);
	/*
		h_addr is a member of hostent structure
		h_addr is a array of character
		h_addr is the first host Addres
	*/

	/*
		ntohl() converts unsigned integer netlong
		from network byte to host byte
	*/

	//host value is returned
	return ntohl(host ? *((unsigned long *)host->h_addr) : 0);
}

//Welcome Function
void Welcome()
{
	printf ("\e[37m\e[44m"); //Set Background Color
    printf("\e[H\e[2J"); // clear screen


    printf("\n");
    printf("\n");
    printf("\n");

    printf("\n  __          __  ______   _         _____    ____    __  __   ______  ");
    printf("\n  \\ \\        / / |  ____| | |       / ____|  / __ \\  |  \\/  | |  ____| ");
    printf("\n   \\ \\  /\\  / /  | |__    | |      | |      | |  | | | \\  / | | |__    ");
    printf("\n    \\ \\/  \\/ /   |  __|   | |      | |      | |  | | | |\\/| | |  __|   ");
    printf("\n     \\  /\\  /    | |____  | |____  | |____  | |__| | | |  | | | |____  ");
    printf("\n      \\/  \\/     |______| |______|  \\_____|  \\____/  |_|  |_| |______| ");
    printf("\n\n\n");
    sleep(1);
    system("clear");

    printf("\n");
    printf("\n");
    printf("\n");
    sleep(1);
    printf("\n  ______   _   _         ");
    printf("\n |  ____| (_) | |        ");
    printf("\n | |__     _  | |   ___  ");
    printf("\n |  __|   | | | |  / _ \\ ");
    printf("\n | |      | | | | |  __/ ");
    printf("\n |_|      |_| |_|  \\___| ");
    printf("\n\n\n");
    sleep(1);
    system("clear");

    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n  _______                                 __               ");
    printf("\n |__   __|                               / _|              ");
    printf("\n    | |     _ __    __ _   _ __    ___  | |_    ___   _ __ ");
    printf("\n    | |    | '__|  / _` | | '_ \\  / __| |  _|  / _ \\ | '__|");
    printf("\n    | |    | |    | (_| | | | | | \\__ \\ | |   |  __/ | |   ");
    printf("\n    |_|    |_|     \\__,_| |_| |_| |___/ |_|    \\___| |_|   ");
    printf("\n\n\n");
    sleep(1);
    system("clear");

    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n  _____                   _                            _ ");
    printf("\n |  __ \\                 | |                          | |");
    printf("\n | |__) |  _ __    ___   | |_    ___     ___    ___   | |");
    printf("\n |  ___/  | '__|  / _ \\  | __|  / _ \\   / __|  / _ \\  | |");
    printf("\n | |      | |    | (_) | | |_  | (_) | | (__  | (_) | | |");
    printf("\n |_|      |_|     \\___/   \\__|  \\___/   \\___|  \\___/  |_|");
    printf("\n\n\n");
    sleep(1);
    system("clear");

    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n   _____           _   _     _           _   _         _                     ");
    printf("\n  |_   _|         (_) | |   (_)         | | (_)       (_)                    ");
    printf("\n    | |    _ __    _  | |_   _    __ _  | |  _   ____  _   _ __     __ _     ");
    printf("\n    | |   | '_ \\  | | | __| | |  / _` | | | | | |_  / | | | '_ \\   / _` |    ");
    printf("\n   _| |_  | | | | | | | |_  | | | (_| | | | | |  / /  | | | | | | | (_| |  _ ");
    printf("\n  |_____| |_| |_| |_|  \\__| |_|  \\__,_| |_| |_| /___| |_| |_| |_|  \\__, | (_)");
    printf("\n                                                                    __/ |    ");
    printf("\n                                                                   |___/     ");
    printf("\n\n\n");
    sleep(1);
    system("clear");

    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n   _____           _   _     _           _   _         _                     ");
    printf("\n  |_   _|         (_) | |   (_)         | | (_)       (_)                    ");
    printf("\n    | |    _ __    _  | |_   _    __ _  | |  _   ____  _   _ __     __ _     ");
    printf("\n    | |   | '_ \\  | | | __| | |  / _` | | | | | |_  / | | | '_ \\   / _` |    ");
    printf("\n   _| |_  | | | | | | | |_  | | | (_| | | | | |  / /  | | | | | | | (_| |  _   _");
    printf("\n  |_____| |_| |_| |_|  \\__| |_|  \\__,_| |_| |_| /___| |_| |_| |_|  \\__, | (_) (_)");
    printf("\n                                                                    __/ |    ");
    printf("\n                                                                   |___/     ");
    printf("\n\n\n");
    sleep(1);
    system("clear");

    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n   _____           _   _     _           _   _         _                     ");
    printf("\n  |_   _|         (_) | |   (_)         | | (_)       (_)                    ");
    printf("\n    | |    _ __    _  | |_   _    __ _  | |  _   ____  _   _ __     __ _     ");
    printf("\n    | |   | '_ \\  | | | __| | |  / _` | | | | | |_  / | | | '_ \\   / _` |    ");
    printf("\n   _| |_  | | | | | | | |_  | | | (_| | | | | |  / /  | | | | | | | (_| |  _   _   _");
    printf("\n  |_____| |_| |_| |_|  \\__| |_|  \\__,_| |_| |_| /___| |_| |_| |_|  \\__, | (_) (_) (_)");
    printf("\n                                                                    __/ |    ");
    printf("\n                                                                   |___/     ");
    printf("\n\n\n");
    sleep(1);
    system("clear");
    system("clear");

    printf("*********************************************************************************");
    printf("\n|  FFFFFFFFFFFFFFFFFFFFFF     TTTTTTTTTTTTTTTTTTTTTTT     PPPPPPPPPPPPPPPPP     |");
    printf("\n|  F::::::::::::::::::::F     T:::::::::::::::::::::T     P::::::::::::::::P    |");
    printf("\n|  F::::::::::::::::::::F     T:::::::::::::::::::::T     P::::::PPPPPP:::::P   |");
    printf("\n|  FF::::::FFFFFFFFF::::F     T:::::TT:::::::TT:::::T     PP:::::P     P:::::P  |");
    printf("\n|    F:::::F       FFFFFF     TTTTTT  T:::::T  TTTTTT       P::::P     P:::::P  |");
    printf("\n|    F:::::F                          T:::::T               P::::P     P:::::P  |");
    printf("\n|    F::::::FFFFFFFFFF                T:::::T               P::::PPPPPP:::::P   |");
    printf("\n|    F:::::::::::::::F                T:::::T               P:::::::::::::PP    |");
    printf("\n|    F:::::::::::::::F                T:::::T               P::::PPPPPPPPP      |");
    printf("\n|    F::::::FFFFFFFFFF                T:::::T               P::::P              |");
    printf("\n|    F:::::F                          T:::::T               P::::P              |");
    printf("\n|    F:::::F                          T:::::T               P::::P              |");
    printf("\n|  FF:::::::FF                      TT:::::::TT           PP::::::PP            |");
    printf("\n|  F::::::::FF                      T:::::::::T           P::::::::P            |");
    printf("\n|  F::::::::FF                      T:::::::::T           P::::::::P            |");
    printf("\n|  FFFFFFFFFFF                      TTTTTTTTTTT           PPPPPPPPPP            |");
    printf("\n*********************************************************************************");

    printf("\n\n");

    printf("\n\033[33;5mINSTRUCTIONS:-\033[0m\n\n");

    printf ("\e[37m\e[44m"); //Set Background Color


	printf("A. For Client Side\n");
	printf("\n\t1. Enter mode : [receive]");
	printf("\n\t2. Enter the port number : 9999");
	printf("\n\t3. Enter file names (stop - stop input)");
	printf("\n--------------------------------------------------");
	printf("\n\nB. For Server Side\n");
	printf("\n\t1. Enter mode : [send]");
	printf("\n\t2. Enter receiver IP");
	printf("\n-----------------------END------------------------");
	printf("\n");

}

//Instructions function
/*void Instruction()
{
	printf("INSTRUCTIONS\n");
	printf("A. For Client Side\n");
	printf("\n\t1. Enter mode : [receive]");
	printf("\n\t2. Enter the host address : 9999");
	printf("\n\t3. Enter file names (stop - stop input)");
	printf("\n--------------------------------------------------");
	printf("\n\nB. For Server Side\n");
	printf("\n\t1. Enter mode : [send]");
	printf("\n\t2. Enter receiver IP");
	printf("\n-----------------------END------------------------");
}
*/
//Function to send single file
void SendFile(unsigned long ipAddress, unsigned short port, const char * fileName)
{
	int sock;		//Socket creation
	int connection;	//Socket connection

	//Opening file is read only mode
	FILE *file = fopen(fileName, "r");
	if(file)
	{
		/*
			socket() creates and endpoint for communication
			AF_INET (domain): IPv4 Internet protocols
			SOCK_STREAM (type): Provides bi-directional stream
			0 (protocol): Single protocol exists
		*/
		//It returns SOCK_ID if created, else -1
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if(sock >= 0)
		{
			//sockaddr_in deals with internet addresses
			struct sockaddr_in sockAddress;
			/*
				memset(s, c, n) fill the first n bytes of the
				memory area pointed to by s with constant
				byte c
			*/
			memset(&sockAddress, 0, sizeof(sockAddress));

			sockAddress.sin_family = AF_INET;
			sockAddress.sin_addr.s_addr = htonl(ipAddress);
			sockAddress.sin_port = htons(port);

			connection = connect(sock, (struct sockaddr *) &sockAddress, sizeof(sockAddress));
			if(connection == FALSE)
			{
				printf("Connected to the client.");
				printf("\nSending file : %s", fileName);

				//Creating buffer to send file
				char buffer[BUFFER];

				while(TRUE)
				{
					ssize_t bytesRead = fread(buffer, TRUE, sizeof(buffer), file);
					//If End of file reached
					if(bytesRead <= FALSE)
						break;

					//Sending packet to client
					printf("\nReading %i bytes from %s, sending...", (int)bytesRead, fileName);

					//If packet is sent is not of same size
					if(send(sock, buffer, bytesRead, 0) != bytesRead)
					{
						perror("Send");
						break;
					}
				}
			}
			else
				perror("Connection");

			if(isEmpty() == TRUE)
				close(sock);
		}
		else
			perror("Socket");
		fclose(file);
	}
	else
		printf("Cannot open file with name : %s\n", fileName);
}


//Function to Receive single file
static void ReceiveFile(unsigned short port, const char *fileName)
{
	int binding;
	int listening;
	int connectSocket;

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock >= 0)
	{
		//Required for Linux based OS
		#ifndef WIN32
		const int trueValue = 1;
		(void) setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &trueValue, sizeof(trueValue));
		#endif

		//sockaddr_in deals with internet addresses
		struct sockaddr_in sockAddress;
		/*
			memset(s, c, n) fill the first n bytes of the
			memory area pointed to by s with constant
			byte c
		*/
		memset(&sockAddress, 0, sizeof(sockAddress));

		sockAddress.sin_family = AF_INET;
		sockAddress.sin_addr.s_addr = htonl(0);
		sockAddress.sin_port = htons(port);

		binding = bind(sock, (struct sockaddr *) &sockAddress, sizeof(sockAddress));
		listening = listen(sock, 10);

		if(binding == FALSE && listening == FALSE)
		{
			memset(&sockAddress, 0, sizeof(sockAddress));
			socklen_t length = sizeof(sockAddress);

			printf("Waiting for connection to receive file : %s", fileName);

			connectSocket = accept(sock, (struct sockaddr *) &sockAddress, &length);

			if(connectSocket >= FALSE)
			{
				//Opening file in write mode
				FILE *file = fopen(fileName, "w");

				if(file)
				{
					char buffer[BUFFER];

					while(TRUE)
					{
						ssize_t bytesWrite = recv(connectSocket, buffer, sizeof(buffer), 0);

						if(bytesWrite <FALSE)
							perror("Receive ");

						//If End of File is reached
						if(bytesWrite == FALSE)
							break;

						printf("\nReceiving %i bytes from :%s", (int)bytesWrite, fileName);

						if(fwrite(buffer, 1, bytesWrite, file) != (size_t) bytesWrite)
						{
							perror("Writing");
							break;
						}
					}

					fclose(file);
				}
				else
					printf("\nCannot found file : %s", fileName);

				if(isEmpty() == TRUE)
					close(connectSocket);
			}
		}
		else
			perror("Bind");

		//if(isEmpty() == TRUE)
			close(sock);
	}
	else
		perror("Socket");
}


//Main Function
int main( int argc, char ** argv)
{
	//Calling Welcome Function
	Welcome();

	//This part is required if running the service in Windows
	//Checking that WIN32 is currently defined
	#ifdef WIN32
		//Windows requires this to start up the networking API
		WORD versionNeed = MAKEWORD(1, 1);
		WSADATA wsaData;
		(void) WSAStartup(versionNeed, &wsaData);
	//This part is required if running the service in Linux/Unix
	#else
		//Avoid SIGPIPE signals caused by sending on a closed socket
		signal(SIGPIPE, SIG_IGN);
		//SIGPIPE :
		//SIG_IGN :	Ignore Signal - It ignores the signal
	#endif

	//Variables used
	char mode[10];			//Get the mode (send / receive)
	char fileName[50];		//Get file name to send / receive
	char hostAddress[20];	//Get address of host (IP)
	int isSend = FALSE;		//Activate send mode (FALSE = receive active)
	unsigned long ip;		//Store host name
	char *portColon;		//Store port in string form
	unsigned short port;	//Store port number
	char *sendFile;			//Dequeue file

	//Instruction();
	init();

	//Input of Mode (send/receive)
	printf("\n\nEnter Mode : ");
	scanf("%s", mode);

	//Input host address
	/*
		For same pc - 127.0.0.1:9999
		For different pcs - IP_Address:9999
	*/
	printf("Enter Host Address : ");
	scanf("%s", hostAddress);


	while(TRUE)
	{
		//Input file name
		printf("Enter File Name : ");
		scanf("%s", fileName);

		if(strcmp(fileName, "-1") == 0)
			break;

		Enqueue(fileName);
	}

/*
	//Input file name
	printf("Enter File Name : ");
	scanf("%s", fileName);

*/
	//Checking for send or receive option
	//if Send mode selected first then set isSend = TRUE
	if(strcmp(mode, "send") == FALSE)
		isSend = TRUE;
	//if Receive mode selected first then EXIT
	else if(strcmp(mode, "receive") == TRUE)
		InitialCheck();


	//If send = TRUE then set the ip value equal to host name
	ip = isSend ? getHost(hostAddress) : 0;

	//Setting up the port

	//Searching for ":" symbol
	portColon = strchr(hostAddress, ':');
	port = portColon ? atoi(portColon + 1) : 0;
	if(port == 0)
		port = 9999;


	printf("\n\nInitiating File Transfer.\n");
	sleep(1);
	//if isSend is TRUE then initiating SendFile()
	//else initiating ReceiveFile()

	while(TRUE)
	{
		if(isEmpty() == TRUE)
		{
			printf("\nTransfer complete.\n");
			exit(1);
		}
			sendFile = Dequeue();
			printf("\n\nInitiating File Transfer.");
			sleep(1);
			//if isSend is TRUE then initiating SendFile()
			//else initiating ReceiveFile()
			if(isSend)
				SendFile(ip, port, sendFile);
			else
				ReceiveFile(port, sendFile);

		isSend = FALSE;
	}
	/*
	if(isSend)
		SendFile(ip, port, fileName);
	else
		ReceiveFile(port, fileName);

*/
	printf("\n\nFile Transfer completed succesfully...\n");

	return 0;
}
