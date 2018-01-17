/*
 mnftables Copyright (C) <2017> <matthias holl>

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>


 mnftables.c

 nftables front-end

 by mah00

 www.mahoosoft.com


Config:
----------------------------------------------
 
 you should have /etc/nftables.conf
 
 nftables.conf
 
 #!/usr/sbin/nft -f

flush ruleset

table inet filter {
	chain input {
		type filter hook input priority 0;
	}
	chain forward {
		type filter hook forward priority 0;
	}
	chain output {
		type filter hook output priority 0;
	}
}

----------------------------------------------
 
How-to
----------------------------------------------
 
 gcc -o mnftables mnftables.c
 sudo ./mnftables

---------------------------------------------- 

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum {
	startnftables,
	stopnftables,
	inportdr,
	outportdr,
	inportacc,
	outportacc,	
	www1,
	www2,
	www3,
	www4,	
	https1,
	https2,
	https3,
	https4,	
	invalid,	
	relatedports,
	dropall,
	listrules,
	deleterules,
	bye
};

void inportdrop() {	  
     char port[100];
     char command[100] = "sudo /usr/sbin/nft add rule inet filter input tcp dport {";
     char command_end[100] ="} drop";
     char command_exec[100];
     printf("port:");	
     scanf("%s",port);
	  strcat(command,port);
	  strcat(command,command_end);
	  strcpy(command_exec,command);	  
	  printf("%s \n",command_exec);
	  system(command_exec);


}

void outportdrop() {	  
     char port[100];
     char command[100] = "sudo /usr/sbin/nft add rule inet filter output tcp dport {";
     char command_end[100] ="} drop";
     char command_exec[100];
     printf("port:");	
     scanf("%s",port);
	  strcat(command,port);
	  strcat(command,command_end);
	  strcpy(command_exec,command);	  
	  printf("%s \n",command_exec);
	  system(command_exec);


}

void inportaccept() {	  
     char port[100];
     char command[100] = "sudo /usr/sbin/nft add rule inet filter input tcp dport {";
     char command_end[100] ="} accept";
     char command_exec[100];
     printf("port:");	
     scanf("%s",port);
	  strcat(command,port);
	  strcat(command,command_end);
	  strcpy(command_exec,command);	  
	  printf("%s \n",command_exec);
	  system(command_exec);


}

void outportaccept() {	  
     char port[100];
     char command[100] = "sudo /usr/sbin/nft add rule inet filter output tcp dport {";
     char command_end[100] ="} accept";
     char command_exec[100];
     printf("port:");	
     scanf("%s",port);
	  strcat(command,port);
	  strcat(command,command_end);
	  strcpy(command_exec,command);	  
	  printf("%s \n",command_exec);
	  system(command_exec);


}

int main(void) {
	int menu;
	do {

		printf("\n");
		printf("mnftables Copyright (C) 2017 by Matthias Holl \n");
		printf("\n");
		printf("-%d- start nftables.service\n", startnftables);
		printf("-%d- stop nftables.service\n", stopnftables);
		printf("-%d- port xy input drop\n", inportdr);
		printf("-%d- port xy output drop\n", outportdr);
		printf("-%d- port xy input access\n", inportacc);
		printf("-%d- port xy output access\n", outportacc);		
		printf("-%d- http (tcp) port 80 input drop\n", www1);
		printf("-%d- http (tcp) port 80 output drop\n", www2);
		printf("-%d- http (tcp) port 80 input accept\n", www3);
		printf("-%d- http (tcp) port 80 output accept\n", www4);		
		printf("-%d- https (tcp) port 443 input drop\n", https1);
		printf("-%d- https (tcp) port 443 output drop\n", https2);
		printf("-%d- https (tcp) port 443 input accept\n", https3);
		printf("-%d- https (tcp) port 443 output accept\n", https4);		
		printf("-%d- block all invalid connections\n", invalid);		
		printf("-%d- accept all established and related connections\n",
				relatedports);
		printf("-%d- drop all incoming connections\n", dropall);
		printf("-%d- show firewall rules\n", listrules);
		printf("-%d- delete all firewall rules\n", deleterules);
		printf("-%d- quit\n", bye);
		printf("--->");

		do {
			scanf("%d", &menu);
		} while (getchar() != '\n');

		switch (menu) {
			
		case startnftables:
			system("sudo systemctl start nftables.service");
			break;
		case stopnftables:
			system("sudo systemctl stop nftables.service");
			break;		
		case inportdr:
		   inportdrop();
			break;			
		case outportdr:
		   outportdrop();
			break;		
		case inportacc:
		   inportaccept();
			break;		
		case outportacc:
		   outportaccept();
			break;
		case www1:
			system(
					"sudo /usr/sbin/nft add rule inet filter input tcp dport {80} drop");
			break;
		case www2:
			system(
					"sudo /usr/sbin/nft add rule inet filter output tcp dport {80} drop");
			break;
		case www3:
			system(
					"sudo /usr/sbin/nft add rule inet filter input tcp dport {80} accept");
			break;
		case www4:
			system(
					"sudo /usr/sbin/nft add rule inet filter output tcp dport {80} accept");
			break;
		case https1:
			system(
					"sudo /usr/sbin/nft add rule inet filter input tcp dport {443} drop");
			break;
		case https2:
			system(
					"sudo /usr/sbin/nft add rule inet filter output tcp dport {443} drop");
			break;
		case https3:
			system(
					"sudo /usr/sbin/nft add rule inet filter input tcp dport {443} accept");
			break;
		case https4:
			system(
					"sudo /usr/sbin/nft add rule inet filter output tcp dport {443} accept");
			break;		
		case invalid:
			  system("sudo /usr/sbin/nft inet filter input ct state invalid drop");
			  break;			
		case relatedports:
			system(
					"sudo /usr/sbin/nft inet filter input ct state established,related accept && sudo /usr/sbin/nft inet filter output ct state established,related accept");
			break;
		case dropall:
			system("sudo systemctl stop nftables.service && sudo /usr/sbin/nft flush ruleset && sudo systemctl start nftables.service  && sudo /usr/sbin/nft inet filter input ct state established,related drop && sudo /usr/sbin/nft inet filter output ct state established,related drop");
			break;
		case listrules:
			system("sudo /usr/sbin/nft list table inet filter");
			sleep(20);
			break;
		case deleterules:
			system("sudo systemctl stop nftables.service && sudo /usr/sbin/nft flush ruleset && sudo systemctl start nftables.service ");
			break;
		}
	} while (menu != bye);
	printf("bye... mnftables\n");
	return EXIT_SUCCESS;
}

