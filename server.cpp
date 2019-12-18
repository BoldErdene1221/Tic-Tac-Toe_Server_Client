#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "tictac.h"
#define  PORT "9987";

using namespace std;

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, port_no, bindfd, listenfd, bytes_sent, bytes_recvd;
	char sbuffer[512], cli_ip[16], sname[64], cname[64]; 
	char *ptr_buff, *ptr_port;
	const char *ptr_cli_ip;
	struct sockaddr_in serv_addr, cli_addr;	
	socklen_t serv_size, cli_size;	

	int inp_true = 0, count = 0, inp, ni, x, y, toss;
	char serv_choice, cli_choice, nc;
	char choice_buffer[2], co_ordinates_buffer[2], toss_buffer;
	
	system("clear");
	ptr_buff = &sbuffer[0];
	ptr_port = (char *)&PORT;

	//socket uusgeh	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{	
		perror("Server taliing socket uussengui!");
		return 1;
	}

	memset(&serv_addr, 0, sizeof(serv_addr));	
	port_no = atoi(ptr_port);
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	
	//bind socket
	bindfd = bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (bindfd == -1)
	{	
		perror("Bind amjiltgui!");
		return 1;
	}
	
	cout<<"Neree oruulna uu : ";
	cin>>sname;
	cout<<"Server uuslee!"<<endl<<"Toglogch huleej bna..."<<endl; 

	listenfd = listen(sockfd, 5);
	if (listenfd == -1)
	{	
		perror("amjiltgui!");
		return 1;
	}

	serv_size = sizeof(serv_addr);
	cli_size = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_size);
		
	if (newsockfd == -1)
	{	
		perror("client zowshoorogdsongui!");
		return 1;
	}
		
	ptr_cli_ip = inet_ntop(AF_INET, &cli_addr.sin_addr, cli_ip, cli_size);
	cout<<"Server holbogdson "<<cli_ip<<endl;	

	memset(&cname, 0, sizeof(cname));
	do
	{	
		static int flag = 0;
		bytes_recvd = recv(newsockfd, &cname, sizeof(cname), 0);
		if (bytes_recvd == -1 && flag == 0)
		{
			memset(&cname, 0, sizeof(cname));
			cout<<"Toglogchiin medeelel awch chadsangui!"<<endl<<"Dahin oroldno uu..."<<endl; 
			continue;
		}
		else
		{	
			flag = 1;
			bytes_sent = send(newsockfd, &sname, sizeof(sname), 0);
			if (bytes_sent == -1)
				cout<<"Toglogchiin data ilgeej chadsangui!"<<"Dahin oroldno uu..."<<endl; 
			else
				cout<<cname<<"- togloomnd orloo."<<endl;
		}
	}while(bytes_recvd == -1 || bytes_sent == -1);

	cout<<"Togloom uusgej bna tur huleene uu..."<<endl;
	sleep(2);
	cout<<endl<<"Togloom uuslee!"<<endl<<endl<<"Hen n ehlehiig shiidej bna";
	srand(time(NULL));
	toss = rand() % 2;
	sleep(1);
	sprintf(&toss_buffer, "%d", toss);
	bytes_sent = send(newsockfd, &toss_buffer, sizeof(toss_buffer), 0);
	if (bytes_sent == -1)
	{
		perror("shiidelt bolsongui!");
		return 1;
	}

	if (toss == 0)
	{	
		cout<<endl<<"Ta songoh bolloo!"<<endl;
		do
    	{
    		cout<<sname<<"(X O) ali negiig songono uu: ";
			cin>>serv_choice;
			if (serv_choice == 'X' || serv_choice == 'x')
			{	
	    		serv_choice = 'X';
	    		cli_choice = 'O';
	    		inp_true = 1;
				cout<<endl<<cname<<" O songoloo."<<endl<<endl<<"Togloom ehellee!"<<endl<<endl;
			}
			else if (serv_choice == 'O' || serv_choice == 'o' || serv_choice == '0')
			{
			    serv_choice = 'O';
        		cli_choice = 'X';
	    		inp_true = 1;
	    		cout<<endl<<cname<<"X sognoloo."<<endl<<endl<<"Togloom ehellee!"<<endl<<endl;
			}	
			else
			{
	    		cout<<"\nBuruu songolt bna dahij songono uu..."<<endl;
	    		inp_true == 0;
			}
    	}while(inp_true == 0);

		memset(&choice_buffer, 0, sizeof(choice_buffer));
		choice_buffer[0] = serv_choice;
		choice_buffer[1] = cli_choice;

		bytes_sent = send(newsockfd, &choice_buffer, sizeof(choice_buffer), 0);
		if (bytes_sent == -1)
		{
			perror("songolt ilgeegdsengui");
			return 1;
		}
	}
	else
	{
		cout<<endl<<cname<<" songoh bolloo."<<endl;
		cout<<cname<<" songoj bna tur huleene uu..."<<endl<<endl;
	
		memset(&choice_buffer, 0, sizeof(choice_buffer));
		bytes_recvd = recv(newsockfd, &choice_buffer, sizeof(choice_buffer), 0);
		if (bytes_recvd == -1)
		{
			perror("songolt huleej awsangui");
			return 1;
		}
		else
		{
			serv_choice = choice_buffer[0];
			cli_choice = choice_buffer[1];
			cout<<sname<<" songoloo "<<serv_choice<<endl<<endl<<"ta enuugeer togolno "<<cli_choice<<endl;
			cout<<endl<<"Amjilt husie!"<<endl<<endl;
		}
	}

	if (serv_choice == 'X')
	{
		inp = 1;
		cout<<"Ta ehelj togolno."<<endl<<endl;
	}
	else
	{
		inp = 2;
		cout<<cname<<" ene hun ehelne."<<endl<<endl;
	}
	
	init();
	cout<<endl<<"Togloom ehellee..."<<endl;
	sleep(3);
	display();

	while (count < 9)
	{
		memset(&co_ordinates_buffer, 0, sizeof(co_ordinates_buffer));

		if (inp % 2 != 0 )
		{
			cout<<endl<<" (X O) ali negiig songon uu: ";
			cin>>x>>y;
			ni = input(serv_choice, x, y);
			if (ni == 0)
			{	
				inp ++;
				sprintf(&co_ordinates_buffer[0], "%d", x);
				sprintf(&co_ordinates_buffer[1], "%d", y);
				cout<<endl<<"Matrix shinchilj bna..."<<endl;
				
				bytes_sent = send(newsockfd, &co_ordinates_buffer, sizeof(co_ordinates_buffer), 0);
				if (bytes_sent == -1)
				{
					perror("coordinate ingeej chadsangui!");
					return 1;
				}
			}
		}
		else 
		{
			cout<<endl<<cname<<"'s turn. Please wait..."<<endl;
			bytes_recvd = recv(newsockfd, &co_ordinates_buffer, sizeof(co_ordinates_buffer), 0 );
			if (bytes_recvd == -1)
			{
				perror("coordinate huleej awch chadsangui!");
				return 1;
			}
			x = co_ordinates_buffer[0] - '0';
			y = co_ordinates_buffer[1] - '0';
			ni = input(cli_choice, x, y);
			if (ni == 0)
			{
				inp ++;
				cout<<endl<<cname<<" togolson. Matrix shinchilj bna..."<<endl;
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
				cout<<endl<<"Bayar hurgie ta hojloo!!!"<<endl<<cname<<" hojigdloo."<<endl;
				break;
			}
			else if (cli_choice == nc)
			{
				cout<<endl<<"Ta hojigdloo."<<endl<<cname<<" hojson."<<endl;						
				break;
			}
		}
	}
	
	if (nc == 'f')
		cout<<endl<<"Ta 2 tentslee."<<endl;
	
	cout<<endl<<"Tic-tac-Toe togloom duuslaa"<<endl;
	close(newsockfd);
	close(sockfd);
	return 0;
}

