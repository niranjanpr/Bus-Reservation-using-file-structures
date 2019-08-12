#include<process.h>
#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<string.h>
#include<stdio.h>
#include<graphics.h>
#include<dos.h>
#include<ctype.h>

fstream fp,fp1,fp2,fp3;

int getrecount(){
	int re;
	fp1.open("count.txt",ios::in);
	fp1>>re;
	fp1.close();
	remove("count.txt");
	return re;
}

void uploadrecount(int re){
	fp1.open("count.txt",ios::out);
	fp1<<re;
	fp1.close();
}
int recount=getrecount();

char fname[10]="inp.txt";

class bus
{

	private:char bid[15];
		char pas[15];
		 char cname[30];
		 char busid[4];
		 char date[20];
		 char src[20];
		 char dest[20];
		 char cost[6];
		 char phno[20];
	public:
		void pack(char[]);
	    void unpack(char[]);
		void display();
		void inser();
		void del();
		int search(char[]);
		void update();
	   
};

bus b;

struct memindex
{
	char k[15];
	int o;
};
memindex in[50];
void setmemindex(){
	char buffer[10];
	fp2.open("memindexes.txt",ios::out);
	fp3.open("offset.txt",ios::out);
	for(int i=1;i<=recount;i++){
		
		fp2<<in[i].k;
		fp2<<"\n";
		
		fp3<<in[i].o<<endl;
	}
	fp2.close();
	fp3.close();
}
void getmemindex(){
	char buffer[20];
	fp3.open("offset.txt",ios::in);
	fp2.open("memindex.txt",ios::in);
	for(int i=1;i<=recount;i++){
		fp2>>in[i].k;
		
		fp3>>in[i].o;
	}
	fp3.close();
	fp2.close();
	remove("offset.txt");
	remove("memindex.txt");
}



int isAlpha(char ch)
{
	if(isalpha(ch))
	    return 1;
	 else
	    return 0;
}

void bus::pack(char buffer[])
{	int valid=1;

	get_bid:
		cout<<endl<<"\t\t  Booking ID  \t\t: ";cin>>bid;
		valid=1;
		if(((strlen(bid)==10)&&isalpha(bid[0]))&&(isalpha(bid[1]))&&(isalpha(bid[2]))&&(isalpha(bid[3]))&&(isalpha(bid[4]))&&(isdigit(bid[5]))&&(isdigit(bid[6]))&&(isdigit(bid[7]))&&(isdigit(bid[8]))&&(isdigit(bid[9]))&&(bid[9]>=0)&&(bid[7]>=0))
			valid=1;
		else
			valid=0;
		if(valid==0){cout<<endl<<" INVALID bid"<<endl;goto get_bid;}


	get_pas:
		cout<<endl<<"\t\t  Name     \t\t: "; cin>>pas;
		valid=1;
		for(int i=0;i<strlen(pas);i++)
		if(isAlpha(pas[i])==0)
		{
			valid=0;
			break;
		}
	if(valid==0)
		{cout<<endl<<" INVALID NAME "<<endl;goto get_pas;}

	cout<<endl<<"\t\t  enter the Busid\t: ";
	cin>>busid;
	cout<<endl<<"\t\t  enter the date\t: ";
	cin>>date;
	cout<<endl<<"\t\t  enter source\t\t: ";
	cin>>src;
	cout<<endl<<"\t\t  enter destination\t: ";
	cin>>dest;
	cout<<endl<<"\t\t  enter cost\t\t: ";
	cin>>cost;

	get_phno:cout<<endl<<"\t\t  Phno  \t\t: ";cin>>phno;
	valid=1;
	if(strlen(phno)!=10)
	   valid=0;
	else
	     
	     if(isdigit(phno[1])==0)
	     {
	       valid=0;

	     }
   if(valid==0)
   {
     cout<<endl<<"Invalid Phone number"<<endl;
     goto get_phno;
   }
	strcpy(buffer,bid);
	strcat(buffer,"|");
	strcat(buffer,pas);
	strcat(buffer,"|");
	strcat(buffer,busid);
	strcat(buffer,"|");
	strcat(buffer,date);
	strcat(buffer,"|");
	strcat(buffer,src);
	strcat(buffer,"|");
	strcat(buffer,dest);
	strcat(buffer,"|");
	strcat(buffer,cost);
	strcat(buffer,"|");
	strcat(buffer,phno);


}

void bus::inser()
{
	char tem[100],buffer[100];
	char *bno;
	int i,j,pos;
	fp.open(fname,ios::out|ios::ate);
	b.pack(buffer);

	strcpy(tem,buffer);
	bno=strtok(tem,"|");
	pos=search(bno);
	if(pos!=(-1))
	{
		cout<<"bid already exists"<<endl;
		fp.close();
		return;
	}
       
	recount++;
	strcpy(in[recount].k,bno);
	in[recount].o=fp.tellg();
	fp<<buffer;
	fp<<endl;
	memindex temp;
	for(i=1;i<recount;i++)
	{
		for(j=1;j<recount;j++)
		{
			if(strcmp(in[j].k,in[j+1].k)>0)
			{
				strcpy(temp.k,in[j].k);
				temp.o=in[j].o;
				strcpy(in[j].k,in[j+1].k);
				in[j].o=in[j+1].o;
				strcpy(in[j+1].k,temp.k);
				in[j+1].o=temp.o;
			}
		}
	}
  
	fp.close();
}
void bus::display()
{	textbackground(BLACK);
  
	char buffer[100];
	int i,j;
	if(recount==0)
	{
		cout<<endl<<endl<<"              NO TICKETS RESERVED"<<endl;
		return;
	}
	cout<<"\t............................"<<endl;
	cout<<"\tprimary index"<<endl;
	cout<<"\t............................"<<endl;
	cout<<"\tkey\t"<<"          offset"<<endl;
	cout<<"\t............................"<<endl;
	for(i=1;i<=recount;i++)
	{
		cout<<"\t"<<in[i].k<<"\t"<<in[i].o<<endl;
	}
	getch();

	fp.open(fname,ios::in);
	for(i=1;i<=recount;i++)
	{
		cout<<"\n*******************TICKETS RESERVED*********************";
		cout<<"\n********************************************************\n";

		fp.seekg(in[i].o,ios::beg);
		fp>>buffer;
		unpack(buffer);
		cout<<endl;
		cout<< "\n\t\t\t\t Press any key ...\n";
		cout<<"\n********************************************************\n\n";
		getch();
	}
	fp.close();
}
void bus::del()
{
	char bno[15],buffer[100];
	int pos;
	fp.open(fname,ios::out|ios::ate);

	cout<<endl<<"Enter the Booking Id:";
	cin>>bid;
	pos=search(bid);
	if(pos==(-1))
	{
		cout<<"Ticket with this booking id not found"<<endl;
		return;
	}
	else
	{
		fp.seekg(in[pos].o,ios::beg);
		fp<<"**********";
		
		fp.close();
		for(int i=pos;i<recount;i++)
		{
			strcpy(in[i].k,in[i+1].k);
			in[i].o=in[i+1].o;
		}
	       cout<<"Your ticket is cancelled successfully.."<<endl;
		recount--;
	}
}


void bus::unpack(char buffer[])
{

textbackground(BLACK);

	char *t;
	//t=strtok(buffer,"|");
	t=strtok(buffer,"|");
	cout<<"		\n\t\tBooking id		: "<<t<<endl;
	t=strtok(NULL,"|");
	cout<<"		\n\t\tPassenger name\t\t: "<<t<<endl;
	t=strtok(NULL,"|");
	cout<<"		\n\t\tBus id			: "<<t<<endl;
	t=strtok(NULL,"|");
	cout<<"		\n\t\tDate\t\t\t: "<<t<<endl;
	t=strtok(NULL,"|");
	cout<<"		\n\t\tsource			: "<<t<<endl;
	t=strtok(NULL,"|");
	cout<<"		\n\t\tdestination		: "<<t<<endl;
	t=strtok(NULL,"|");
	cout<<"		\n\t\tcost\t\t\t: "<<t<<endl;
	t=strtok(NULL,'\0');
	cout<<"		\n\t\tphonenumber		: "<<t<<endl;
}

int bus::search(char bid[])
{
	int low=1,high=recount,mid;
	while(low<=high)
	{
		mid=(low+high)/2;
		if(strcmpi(in[mid].k,bid)==0)
			return mid;
		if(strcmpi(in[mid].k,bid)>0)
			high=mid-1;
		else
			low=mid+1;
	}
	return -1;
}

void bus::update()
{
char bid[15];
int pos;
fp.open("inp.txt",ios::out|ios::ate);
cout<<"Enter the booking id"<<endl;
cin>>bid;
pos=search(bid);
if(pos==-1){
cout<<"Ticket with this booking id not found\n"<<endl;
return;
}
fp.seekg(in[pos].o,ios::beg);
fp<<"**********";
fp.close();
for(int i=pos;i<=recount;i++){
strcpy(in[i].k,in[i+1].k);
in[i].o=in[i+1].o;
}
recount--;
inser();
}

int main()
{
textbackground(BLACK);

char *t;
char bid[15],buffer[100];
int i,j,k,ch,pos,k1;

fp.open(fname,ios::out|ios::ate);
getmemindex();
fp.close();
char *key;
clrscr();

for(;;)
{	  clrscr();

	//cout<<recount;
	  gotoxy(18,2);
	  cout<<"******************************************";gotoxy(18,4);
	  cout<<"*";
	  gotoxy(32,4);
	  cout<<"MAIN MENU";gotoxy(59,4);cout<<"*";gotoxy(18,6);
	  cout<<"******************************************";gotoxy(18,8);
	  cout<<"* 1: Display reserved tickets";gotoxy(59,8);cout<<"*";gotoxy(18,10);
	  cout<<"* 2: Ticket reservation";gotoxy(59,10);cout<<"*";gotoxy(18,12);
	  cout<<"* 3: Search reserved ticket ";gotoxy(59,12);cout<<"*";gotoxy(18,14);
	  cout<<"* 4: Cancel reservation";gotoxy(59,14);cout<<"*";gotoxy(18,16);
	  cout<<"* 5: Update reservation details";gotoxy(59,16);cout<<"*";gotoxy(18,18);
	  cout<<"* 6: Quit ";gotoxy(59,18);cout<<"*";gotoxy(18,20);
	  cout<<"******************************************"<<endl;
	  cout<<endl<<" 		 Enter choice [1-6] : ";
	 cin>>ch;
	 switch(ch)
	  {

	 case 1:
	   clrscr();
	   gotoxy(20,2);
	   cout<<"******************************************";
	   gotoxy(20,4);
	   cout<<"*        DISPLAY RESERVED TICKETS        *";
	   gotoxy(20,6);
	   cout<<"******************************************"<<endl<<endl;

	   b.display();
	   break;
	 case 2:
	   clrscr();
	   gotoxy(22,2);
	   cout<<"***************************************************";
	   gotoxy(22,4);
	   cout<<"*                 TICKET RESERVATION              *";
	   gotoxy(22,6);
	   cout<<"***************************************************"<<endl<<endl;
	   b.inser();
	   break;
	 case 3:
		clrscr();
		gotoxy(22,2);
		cout<<"*********************************";
		gotoxy(22,4);
		cout<<"*        SEARCH RESERVATION     *";
		gotoxy(22,6);
		cout<<"*********************************"<<endl<<endl;
		cout<<"\n\t*\t1.\tSearch using Bus Registration number\t\t*\n";
					cout<<"\n\t*\t2.\tSearch using name of the Passenger\t\t*\n";
					cout<<"\n\t*\t3.\tSearch using source and destination\t\t*\n";
					cout<<"\n\n\tEnter the Required option:\t";
					char opt;
					cin>>opt;
					switch(opt)
					{		
						case '1':	
							cout<<endl<<" \n\t\tEnter the Id to search :";
							cin>>key;
							k1=b.search(key);
							if(k1==(-1)) cout<<"\n\t\tentered key not found";
							else {
									fp.open(fname,ios::in);
									fp.seekg(in[k1].o,ios::beg);
									fp>>buffer;
									b.unpack(buffer);
									fp.close();
								}
								break;

						case '2':int f1=0;
						char *n2;
								cout<<endl<<"\n\t\tEnter the name to search : ";
								cin>>key;
								fp.open(fname,ios::in);
								//for(i=1;i<=recount;i++)
								strcpy(buffer,"aa");

								while(!strcmp(buffer,"\0")==0)
								{
									char *n,buf[100];
									fp>>buffer;
									strcpy(buf,buffer);
									n2=strtok(buf,"|");
									n=strtok(NULL,"|");
									if(strcmpi(n,key)==0)
									{
										f1=1;
										int kk=b.search(n2);
										//cout<<kk;
										fp.seekg(in[kk].o,ios::beg);
										fp>>buffer;
										b.unpack(buffer);
										getch();
										break;
									}

								}
								if(f1==0)
									cout<<"\t\tentered name is not there!!\n";
								fp.close();
								break;

						case '3':	
								char s[15],d[15],*tem;
								char *t,*r,*m,*y,*z;
								int i,found=0;
								cout<<endl<<"\n\t*\tEnter source:		";
								cin>>s;
							    cout<<"\n\t*\tEnter destination:	";
								cin>>d;
								fp.open(fname,ios::in);
							//for(i=1;i<=recount;i++)
								strcpy(buffer,"aa");

								while(!strcmp(buffer,"\0")==0)
								{
									fp>>buffer;
									strcpy(tem,buffer);
									t=strtok(tem,"|");
									for(int i=1;i<5;i++)
										t=strtok(NULL,"|");
									r=strtok(NULL,"|");
									strcpy(z,t);
									strcat(z,r);							
									strcpy(y,s);
									strcat(y,d);
									
									if((strcmpi(s,t)==0)&&(strcmpi(d,r)==0))
									{
										cout<<"\n\tfounded passengers int this way are:\n\n";
										b.unpack(buffer);
										found=1;
										getch();
									}
								      
								}
								if(found==0) cout<<"passengers are not there in this way";
									fp.close();
								    break;
					}
					break;
	 case 4:
		clrscr();
		gotoxy(28,2);
		cout<<"*******************************";
		gotoxy(28,4);
		cout<<"*       CANCEL RESERVATION    *";
		gotoxy(28,6);
		cout<<"*******************************"<<endl<<endl;
		b.del();
		break;
	case 5:
		clrscr();
		gotoxy(28,2);
		cout<<"********************";
		gotoxy(28,4);
		cout<<"*  UPDATE DETAILS  *";
		gotoxy(28,6);
		cout<<"********************"<<endl<<endl;
		b.update();
		break;

	 default:uploadrecount(recount);
setmemindex();
fp.close();
exit(0);

cout<<endl<< "		!!! Invalid Choice. Press any key ... !!!";
	   }

		if(ch>1 && ch<7)
		cout << "\n\n\t Press any key to return to menu ... ";
		getch();
	}
}
