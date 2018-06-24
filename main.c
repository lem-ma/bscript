/*Author: lem-ma
bscript
Version 0.8beta
*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

double v[1000];

int keyvenues[1000];

char* substring(char* string, int init, int ending)
{
	if((init>ending)||(ending+1>strlen(string)))
	{
		puts("substring error!");
		return "\0";
	}
	int length=ending-init+1;
	char* newstr=(char*)malloc(sizeof(char)*(length+1));
	if(!newstr)
	{
		puts("RAM error!");
		return "\0";
	}
	newstr[length]='\0';
	for(int i=0;i<length;i++)
	{
		newstr[i]=string[init+i];
	}
	return newstr;
}

double getn(char* name)
{
	if(name[0]=='v'&&strlen(name)==4)
	{
		int k=atoi(substring(name,1,3));
		if(k)
		{
			return v[k];
		}
		else
		{
			puts("Variable name error!");
			return 1;
		}
	}
	else
	{
		printf("\n\n\nRendering |%s| error!\n", name);
		return 1;
	}
}

double parse(char* line)
{
	int length=strlen(line);
	int mode[2]={15,-1};
	for(int i=0;i<length;i++)
	{
		if(line[i]==line[i+1]&&line[i]=='|')
		{
			if((!line[i+2])||(i==0))
			{
				puts("ERROR: Invalid use of operator ||.");
				return 1;
			}
			else
			{
				return parse(substring(line,0,i-1))||parse(substring(line,i+2,length-1));
			}
		}
		else if(line[i]=='&'&&line[i+1]=='&')
		{
			if((!line[i+2])||(i==0))
			{
				puts("ERROR: Invalid use of operator &&.");
				return 1;
			}
			else
			{
				mode[0]=1;
				mode[1]=i;
			}
		}
		else if(line[i]=='=')
		{
			if(line[i+1]=='='&&line[i+2]!='\0'&&(i>0))
			{
				if(mode[0]>2)
				{
					mode[0]=2;
					mode[1]=i;
				}
			}
			else if((i>1)&&line[i-1]=='!'&&line[i+1]!=0)
			{
				if(mode[0]>3)
				{
					mode[0]=3;
					mode[1]=i;
				}
			}
			else if((i>1)&&line[i-1]=='>'&&line[i+1]!=0)
			{
				if(mode[0]>4)
				{
					mode[0]=4;
					mode[1]=i;
				}
			}
			else if((i>1)&&line[i-1]=='<'&&line[i+1]!=0)
			{
				if(mode[0]>5)
				{
					mode[0]=5;
					mode[1]=i;
				}
			}
			else if((i>0)&&(line[i-1]=='='))
			{

			}
			else if(i==0||line[i-1]=='=')
			{
				puts("ERROR: Invalid use of operator == or != or >= or <=.");
				return 1;
			}
		}
		else if(line[i]=='>')
		{
			if(i==0||i==(length-1))
			{
				puts("ERROR: Invalid use of operator >.");
				return 1;
			}
			else
			{
				if(mode[0]>6)
				{
					mode[0]=6;
					mode[1]=i;
				}
			}
		}
		else if(line[i]=='<')
		{
			if(i==0||i==(length-1))
			{
				puts("ERROR: Invalid use of operator <.");
				return 1;
			}
			else
			{
				if(mode[0]>7)
				{
					mode[0]=7;
					mode[1]=i;
				}
			}
		}
		else if(line[i]=='-')
		{
			if(i==0||i==(length-1))
			{
				puts("ERROR: Invalid use of operator(s).");
				return 1;
			}
			else
			{
				if(mode[0]>8)
				{
					mode[0]=8;
					mode[1]=i;
				}
			}
		}
		else if(line[i]=='+')
		{
			if(i==0||i==(length-1))
			{
				puts("ERROR: Invalid use of operator(s).");
				return 1;
			}
			else
			{
				if(mode[0]>9)
				{
					mode[0]=9;
					mode[1]=i;
				}
			}
		}
		else if(line[i]=='%')
		{
			if(i==0||i==(length-1))
			{
				puts("ERROR: Invalid use of operator %.");
				return 1;
			}
			else
			{
				if(mode[0]>10)
				{
					mode[0]=10;
					mode[1]=i;
				}
			}
		}
		else if(line[i]=='/')
		{
			if(i==0||i==(length-1))
			{
				puts("ERROR: Invalid use of operator(s).");
				return 1;
			}
			else
			{
				if(mode[0]>11)
				{
					mode[0]=11;
					mode[1]=i;
				}
			}
		}
		else if(line[i]=='*')
		{
			if(i==0||i==(length-1))
			{
				puts("ERROR: Invalid use of operator(s).");
				return 1;
			}
			else
			{
				if(mode[0]>12)
				{
					mode[0]=12;
					mode[1]=i;
				}
			}
		}
		else if(line[i]=='!'&&mode[0]>13)
		{
			if(i!=0)
			{
				puts("ERROR: Invalid use of operator(s).");
			}
			else
			{
				mode[0]=13;
			}
		}
		else if(line[i]=='v'&&mode[0]>14)
		{
			if(i!=0)
			{
				puts("ERROR: Invalid use of operator(s).");
				return 1;
			}
			else
			{
				mode[0]=14;
			}
		}
	}
	switch(mode[0])
	{
		case 1:
			return parse(substring(line,0,mode[1]-1))&&parse(substring(line,mode[1]+2,length-1));
			break;
		case 2:
			return parse(substring(line,0,mode[1]-1))==parse(substring(line,mode[1]+2,length-1));
			break;
		case 3:
			return parse(substring(line,0,mode[1]-2))!=parse(substring(line,mode[1]+1,length-1));
			break;
		case 4:
			return parse(substring(line,0,mode[1]-2))>=parse(substring(line,mode[1]+1,length-1));
			break;
		case 5:
			return parse(substring(line,0,mode[1]-2))<=parse(substring(line,mode[1]+1,length-1));
			break;
		case 6:
			return parse(substring(line,0,mode[1]-1))>parse(substring(line,mode[1]+1,length-1));
			break;
		case 7:
			return parse(substring(line,0,mode[1]-1))<parse(substring(line,mode[1]+1,length-1));
			break;
		case 8:
			return parse(substring(line,0,mode[1]-1))-parse(substring(line,mode[1]+1,length-1));
			break;
		case 9:
			return parse(substring(line,0,mode[1]-1))+parse(substring(line,mode[1]+1,length-1));
			break;
		case 10:
			return fmod(parse(substring(line,0,mode[1]-1)),parse(substring(line,mode[1]+1,length-1)));
			break;
		case 11:
			return parse(substring(line,0,mode[1]-1))/parse(substring(line,mode[1]+1,length-1));
			break;
		case 12:
			return parse(substring(line,0,mode[1]-1))*parse(substring(line,mode[1]+1,length-1));
			break;
		case 13:
			return !parse(substring(line,1,length-1));
			break;
		case 14:
			return getn(substring(line,0,3));
			break;
		default:
			return atof(line); 
	}
}

int handle(char* agcommand, int j)
{
	int length=strlen(agcommand);
	int blank=0;
	int mov;
	for(int i=0;i<length;i++)
	{
		if(agcommand[i]==' ')
		{
			blank=i;
			break;
		}
	}
	if(blank>1)
	{
		mov=atoi(substring(agcommand, 1, blank-1));
		if(mov>999||mov<1)
		{
			printf("Error occurs.\n\n%s",agcommand);
			return 0;
		}
		if(agcommand[0]=='a')
		{
			v[mov]=parse(substring(agcommand, blank+1, length-1));
			return 0;
		}
		else
		{
			if(parse(substring(agcommand, blank+1, length-1)))
			{
				return keyvenues[mov];
			}
			else
			{
				return j+1;
			}
		}
	}
	else
	{
		printf("Error occurs.\n\n%s",agcommand);
		return 0;
	}
}

int main(int argc, char* argv[])
{
	if(argc==1)
	{
		puts("FATAL ERROR: No input file.");
	}
	else
	{
		FILE *fp;
		long lSize;
		char *buffer;
		fp=fopen(argv[1], "rb");
		if(!fp) perror("error"),exit(1);
		fseek(fp, 0L, SEEK_END);
		lSize=ftell(fp);
		rewind(fp);
		buffer=calloc(1, lSize+1);
		if(!buffer) fclose(fp),fputs("memory alloc fails",stderr),exit(1);
		if(1!=fread(buffer, lSize, 1, fp))
			fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);
		buffer[lSize]='\n';
		fclose(fp);
		for(int i=0;i<1000;i++) {v[i]=0;} 
		for(int i=0;i<1000;i++) {keyvenues[i]=0;}
		char** commands=(char**)malloc(sizeof(char*)*1024);
		commands[0]="e"; 
		int mode=0;
		int one_plus_nol=1;
		int allocated_space=1024;
		int cache=0;
		int target;
		for(long i=0;i<=lSize;i++)
		{
			if(buffer[i]=='\n'&&!mode)
			{
				if(i&&buffer[i-1]!='\n')
				{
					commands[one_plus_nol]=substring(buffer, cache, i-1);
					one_plus_nol++;
					if(one_plus_nol%1024==0)
					{
						allocated_space+=1024;
						commands=(char**)realloc(commands, sizeof(char*)*allocated_space);
						if(!commands)
						{
							puts("Rendering error!");
							free(buffer);
							for(int i=0;i<one_plus_nol;i++)
							{
								free(commands[i]);
							}
							free(commands);
							return 1;
						}
					}
				}		
				cache=i+1;
				if(i<lSize)
				{
					if(buffer[i+1]=='t')
					{
						mode=1;
					}
					else if(buffer[i+1]=='#')
					{
						mode=2;
					}
				}
			}
			else if(mode==1)
			{
				if(buffer[i]=='\n')
				{
					target=atoi(substring(buffer, cache+1, i-1));					
					if(target<=0||target>=1000)
					{
						puts(substring(buffer, cache+1, i-1));
						printf("ERROR: go keys can only be integers from 1 to 999!");
						free(buffer);
						for(int i=0;i<one_plus_nol;i++)
						{
							free(commands[i]);
						}
						free(commands);
						return 1;
					}
					else
					{
						keyvenues[target]=one_plus_nol;
					}
					cache=i+1;
					if(i<lSize)
					{
						if(buffer[i+1]=='t')
						{
							mode=1;
						}
						else if(buffer[i+1]=='#')
						{
							mode=2;
						}
						else
						{
							mode=0;
						}
					}
				}
			}
			else if(mode==2)
			{
				if(buffer[i]=='\n')
				{
					cache=i+1;
					if(i<lSize)
					{
						if(buffer[i+1]=='t')
						{
							mode=1;
						}
						else if(buffer[i+1]=='#')
						{
							mode=2;
						}
						else
						{
							mode=0;
						}
					}
				}
			}
		}
		free(buffer);
		int length_of_commands;
		int variable;
		int i=0;
		while(i<one_plus_nol-1)
		{
			i++;
			length_of_commands=strlen(commands[i]);
			switch(commands[i][0])
			{
				case 'i':
					if(length_of_commands>1)
					{
						variable=atoi(substring(commands[i], 1, length_of_commands-1));
						if(variable<0)
						{
							variable=0;
						}
						if(variable>999)
						{
							variable=999;
						}
						scanf("%lf", v+variable);
					}
					else
					{
						printf("ERROR: Wrong input argument.\n\n%s",commands[i]);
						return 0;
					}
					break;
				case 'a':
					handle(commands[i], i);
					break;
				case 'g':
					i=handle(commands[i], i)-1;
					break;
				case 'o':
					if(length_of_commands>1)
					{
						variable=atoi(substring(commands[i], 1, length_of_commands-1));
						if(variable<0)
						{
							variable=0;
						}
						if(variable>999)
						{
							variable=999;
						}
						printf("%lf", v[variable]);
					}
					else
					{
						printf("ERROR: Wrong input argument.\n\n%s",commands[i]);
						return 0;
					}
					break;
				case 's':
					if(length_of_commands>2)
					{
						int iswin=(commands[i][length_of_commands-1]=='\r');
						printf("%s", substring(commands[i],2,length_of_commands-1-iswin));
					}
					else
					{
						printf("ERROR: Wrong input argument.\n\n%s",commands[i]);
					}
					break;
				case 'n':
					printf("\n");
					break;
				case 'e':
					return 0;
					break;
				default:
					printf("ERROR: Wrong syntax!\n\n%s", commands[i]);
			}
		}
		for(int i=1;i<one_plus_nol;i++)
		{
			free(commands[i]);
		}
		free(commands);
	}
	return 0;
}
