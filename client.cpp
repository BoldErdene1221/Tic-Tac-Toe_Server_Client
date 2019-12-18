#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "tictac.h"
#define  PORT "9987"

using namespace std;

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, port_no, n, connectfd, bytes_sent, bytes_recvd;
	char cbuffer[512], sname[64], cname[64];
	char *ptr = &cbuffer[0];
	char *ptr_port = (char *)&PORT;
	struct sockaddr_in serv_addr;
	struct hostent *he;
	
	int count = 0, inp, x, y, ni, inp_true = 0, toss;
	char serv_choice, cli_choice, nc;
	char choice_buffer[2], co_ordinates_buffer[2], toss_buffer;

	system("clear");

	if (argc != 2)
	{
		perror("Buruu utga awlaa IP address ee shalgana uu!");
		return 1;
	}
	port_no = atoi(ptr_port);
	he = gethostbyname(argv[1]);
	if (he == NULL)
	{
		perror("Server bolon Host uusegui bna!");
		return 1;
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{	
		perror("Socket uusegui bna!");
		return 1;
	}

    memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr = *((struct in_addr *)he->h_addr);  

	connectfd = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (connectfd == -1)
	{	
		perror("Server-tei holbogdoj chadsangui.");
		return 1;
	}
		
	cout<<"Neree oruulna uu : ";
	cin>>cname;
	do
	{
		static int flag = 0;
		bytes_sent = send(sockfd, &cname, sizeof(cname), 0);
		if (bytes_sent == -1 && flag == 0)
		{
			cout<<"Toglogchiin medeelel shiljuulhed aldaa garlaa!"<<endl<<"Dahin oroldnuu...";  
			continue;
		}
		else
		{		cli_choice = 'X';
	    	
			flag = 1;
			memset(&sname, 0, sizeof(sname));
			bytes_recvd = recv(sockfd, &sname, sizeof(sname), 0);
			if (bytes_recvd == -1)
				cout<<"Toglogchiin medeelel awch chadsangui!"<<endl<<"Dahin oroldnuu..."<<endl; 
			else
				cout<<"Ta amjilttai holbogdloo "<<sname<<" Tic-Tac-Toe."<<endl;
		}
	}while(bytes_sent == -1 || bytes_recvd == -1);
	
	cout<<"Togloom uusgej bna tur huleene uu..."<<endl;

	cout<<endl<<"Togloom uuslee "<<endl<<endl<<"Hen n ehlel eshiig shiidej bna";
	
	bytes_recvd = recv(sockfd, &toss_buffer, sizeof(toss_buffer), 0);
	if (bytes_recvd == -1)
	{
		perror("shidelt bolsongui");
		return 1;
	}

	toss = toss_buffer - '0';
	if (toss == 0)		
	{
		cout<<endl<<sname<<" songoh bolloo."<<endl;
		cout<<sname<<" songoj bna tur huleene uu..."<<endl<<endl;
		memset(&choice_buffer, 0, sizeof(choice_buffer));
		bytes_recvd = recv(sockfd, &choice_buffer, sizeof(choice_buffer), 0);
		if (bytes_recvd == -1)
		{
			perror("songolt amjiltgui");
			return 1;
		}
		else
		{
			serv_choice = choice_buffer[0];
			cli_choice = choice_buffer[1];
			cout<<sname<<" songoson "<<serv_choice<<endl<<endl<<"Ta enuugeer togolno"<<cli_choice<<endl;
			cout<<endl<<"Amjilt husie!"<<endl<<endl;
		}
	}
	else
	{
		cout<<endl<<"Songoltod ta hojloo"<<endl;
		do
    	{
    		cout<<cname<<" (X O) ali negiig songon uu: ";
			cin>>cli_choice;
			if (cli_choice == 'X' || cli_choice == 'x')
			{	
	    		serv_choice = 'O';
	    		cli_choice = 'X';
	    		inp_true = 1;
				cout<<endl<<sname<<"O songoloo."<<endl<<endl<<"Togloom ehellee!"<<endl<<endl;
			}
			else if (cli_choice == 'O' || cli_choice == 'o' || cli_choice == '0')
			{
			    serv_choice = 'X';
        		cli_choice = 'O';
	    		inp_true = 1;
	    		cout<<endl<<sname<<"X songoloo."<<endl<<endl<<"Togloom ehellee!"<<endl<<endl;
			}	
			else
			{
	    		cout<<"\nBuruu songolt bna dahij songonuu..."<<endl;
	    		inp_true == 0;
			}
    	}while(inp_true == 0);

		memset(&choice_buffer, 0, sizeof(choice_buffer));
		choice_buffer[0] = serv_choice;
		choice_buffer[1] = cli_choice;

		bytes_sent = send(sockfd, &choice_buffer, sizeof(choice_buffer), 0);
		if (bytes_sent == -1)
		{
			perror("Songolt ilgeegdsengui.");
			return 1;
		}

	}

	if (serv_choice == 'X')
	{
		inp = 1;
		cout<<sname<<" ene toglogch ehelne."<<endl<<endl;
	
	}
	else
	{
		inp = 2;
		cout<<"Ta ehelj togolno."<<endl<<endl;
	}

	
	init();
	cout<<endl<<"Togloom ehellee..."<<endl;
	sleep(2);
	display();
	
	while (count < 9)
	{
		memset(&co_ordinates_buffer, 0, sizeof(co_ordinates_buffer));
		
		if (inp % 2 != 0 )
		{
			cout<<endl<<sname<<"-hunii eelj. Tur huleene uu..."<<endl;
			bytes_recvd = recv(sockfd, &co_ordinates_buffer, sizeof(co_ordinates_buffer), 0);
			if (bytes_recvd == -1)
			{
				perror("coordinate huleej awch chadsangui");
				return 1;
			}
			x = co_ordinates_buffer[0] - '0';
			y = co_ordinates_buffer[1] - '0';
			ni = input(serv_choice, x, y);
			if (ni == 0)
			{	
				inp ++;
				cout<<endl<<sname<<"-hun togolloo. Matrix shinchilj bna..."<<endl;
			}
		}
		else 
		{
			cout<<endl<<"Tanii eelj matrix iin nudeer darna uu : ";
			cin>>x>>y;
			ni = input(cli_choice, x, y);
			if (ni == 0)
			{
				inp ++;
				sprintf(&co_ordinates_buffer[0], "%d", x);
				sprintf(&co_ordinates_buffer[1], "%d", y);
				cout<<endl<<"Matrix shinchelj bna..."<<endl;
				
				bytes_sent = send(sockfd, &co_ordinates_buffer, sizeof(co_ordinates_buffer), 0);
				if (bytes_sent == -1)
				{
					perror("coordinate ilgeej chadsangui");
					return 1;
				}
			}
		}
		
		count ++;
		system("clear");
		display();

		if (count >=5)
		{	
			nc = check();
			if (nc == 'f')
				continue;
			else if (serv_choice == nc)
			{	
				cout<<endl<<"Ta hojigdloo."<<endl<<sname<<" hojloo."<<endl;	
				break;
			}
			else if (cli_choice == nc)
			{
				cout<<endl<<"Bayar hurgie ta hojloo!!!"<<endl<<sname<<" suljee tasarlaa."<<endl;
				break;
			}
		}

	}
	
	if (nc == 'f')
		cout<<endl<<"Ta 2 tentslee."<<endl;

	cout<<endl<<"Tic-tac-Toe togloom duuslaa"<<endl;
	
	return 0;
}
	

