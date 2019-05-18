#include<process.h>
#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<string.h>
#include<stdio.h>
#include<graphics.h>
#include<dos.h>
#include<ctype.h>

fstream fp,fp1;
int recount=0,ud=0;
char fname[10]="inp.txt";

class bus
{

	private:char bid[15];
		char pas[15];
		 char cname[30];
		 char busid[4];
		 char date[10];
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


struct secondaryindex
{
char sk[15];
char k[15];
};
secondaryindex sin[50];


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
		cout<<endl<<"\tBooking ID :\t\t";cin>>bid;
		valid=1;
		if(((strlen(bid)==10)&&isalpha(bid[0]))&&(isalpha(bid[1]))&&(isalpha(bid[2]))&&(isalpha(bid[3]))&&(isalpha(bid[4]))&&(isdigit(bid[5]))&&(isdigit(bid[6]))&&(isdigit(bid[7]))&&(isdigit(bid[8]))&&(isdigit(bid[9]))&&(bid[9]>=0)&&(bid[7]>=0))
			valid=1;
		else
			valid=0;
		if(valid==0){cout<<endl<<" INVALID bid"<<endl;goto get_bid;}


	get_pas:
		cout<<endl<<"\tName:\t\t\t"; cin>>pas;
		valid=1;
		for(int i=0;i<strlen(pas);i++)
		if(isAlpha(pas[i])==0)
		{
			valid=0;
			break;
		}
	if(valid==0)
		{cout<<endl<<" INVALID NAME "<<endl;goto get_pas;}

	cout<<endl<<"\tenter Busid:\t\t";
	cin>>busid;
	cout<<endl<<"\tenter the date:\t\t";
	cin>>date;
	cout<<endl<<"\tenter source:\t\t";
	cin>>src;
	cout<<endl<<"\tenter destination:\t";
	cin>>dest;
	cout<<endl<<"\tenter cost:\t\t";
	cin>>cost;

	get_phno:cout<<endl<<"\tPhno:\t\t";cin>>phno;
	valid=1;
	if(strlen(phno)!=10)
	   valid=0;
	else
	     //for(i=0;i<strlen(phno);i++)
	     if(isdigit(phno[1])==0)
	     {
	       valid=0;

	     }
   if(valid==0)
   {
     cout<<endl<<"\t\tInvalid Phone number"<<endl;
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

	strcpy(sin[recount].sk,pas);
	strcpy(sin[recount].k,bno);

	fp<<buffer;
	fp<<endl;
	memindex temp;
	for(i=1;i<recount;i++)
	{
		for(j=1;j<recount;j++)
		{
			if(strcmpi(in[j].k,in[j+1].k)>0)
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
    textcolor(LIGHTMAGENTA);
	char buffer[100];
	int i,j;
	if(recount==0)
	{
		cout<<"no records to display"<<endl;
		return;
	}
	cout<<"\t.................."<<endl;
	cout<<"\tprimary index"<<endl;
	cout<<"\t.................."<<endl;
	cout<<"\tkey\t"<<"offset"<<endl;
	cout<<"\t.................."<<endl;
	for(i=1;i<=recount;i++)
	{
		cout<<"\t"<<in[i].k<<"\t"<<in[i].o<<endl;
	}
	getch();
	clrscr();
	cout<<"\n\n\n\n\n\t----------------------"<<endl;
	cout<<"\t Secondary index"<<endl;
	cout<<"\t----------------------"<<endl;
	cout<<"\t sec-key\t"<<"pri-key"<<endl;
	cout<<"\t-----------------------"<<endl;
	for(i=1;i<=recount;i++)
	{
	cout<<"\t"<<sin[i].sk<<"\t\t"<<sin[i].k<<endl;
	}
	//cout<<"\t------------------------"<<endl;

	getch();
		cout<<"\n\n\t*******************file contents are********************";

	fp.open(fname,ios::in);
	for(i=1;i<=recount;i++)
	{
		cout<<"\n\t********************************************************\n";

		fp.seekg(in[i].o,ios::beg);
		fp>>buffer;
		
		b.unpack(buffer);
		cout<<endl;
		cout<< "\t\t\t Press any key ...\n";
		cout<<"\n\t********************************************************\n\n";
		getch();
	}
	fp.close();
}
void bus::del()
{
	char bno[15],buffer[100];
	int pos,j=0,i,k=0;
	fp.open(fname,ios::out|ios::ate);
	cout<<endl<<"Enter the Booking Id:	";
	cin>>bid;
	pos=search(bid);
	k=search(sin[1].sk);
	if(pos==(-1))
	{
		cout<<"record not found"<<endl;
		fp.close();
		return;
	}
	else
	{
		if(recount==1)
			if(strcmpi(bid,in[k].k)==0)
				fp.seekg((in[pos].o-2),ios::beg);

		fp.seekg(in[pos].o,ios::beg);
		fp<<"**********";
		fp.close();

	}	
		for(i=pos;i<recount;i++)
		{
			strcpy(in[i].k,in[i+1].k);
			in[i].o=in[i+1].o;
		}

		while(strcmpi(sin[j].k,bid)!=0)
		{
		j++;
		}

		for(i=j;i<recount;i++)
		{
		strcpy(sin[i].sk,sin[i+1].sk);
		strcpy(sin[i].k,sin[i+1].k);
		}

		cout<<"record deleted successfully"<<endl;
		recount--;
	return;
}


void bus::unpack(char buffer[])
{

textbackground(BLACK);
textcolor(LIGHTMAGENTA);
	char *t;
	t=strtok(buffer,"|");
	cout<<"		\n\t\tBooking id:		"<<t<<endl;
	t=strtok(NULL,"|");
	cout<<"		\n\t\tPassenger name:\t\t"<<t<<endl;
	t=strtok(NULL,"|");
	cout<<"		\n\t\tBus id:			"<<t<<endl;
	t=strtok(NULL,"|");
	cout<<"		\n\t\tDate:\t\t\t"<<t<<endl;
	t=strtok(NULL,"|");
	cout<<"		\n\t\tsource:			"<<t<<endl;
	t=strtok(NULL,"|");
	cout<<"		\n\t\tdestination:		"<<t<<endl;
	t=strtok(NULL,"|");
	cout<<"		\n\t\tcost:\t\t\t"<<t<<endl;
	t=strtok(NULL,'\0');
	cout<<"		\n\t\tphonenumber:		"<<t<<endl;
}

//search using binary search
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

char buffer[100],buffer1[100],buffer2[100],tem[100],zz[100];
	int j,k,f,valid=1;
	char *key,*bi;
	char upd;
	cout<<endl<<"	the Enter the bid to update : ";
	cin>>key;
	f=b.search(key);
	
	//////cout<<q<<"\t"<<q;
	if(f==(-1))	{cout<<endl<<"     Record not found...!"<<endl; return;}
	

	else
	{
			cout<<endl<<"		Record:";
			fp.open(fname,ios::in);
			fp.seekg(in[f].o,ios::beg);
			fp>>buffer1;
			strcpy(tem,buffer1);
			//char *o;
		//	o=strtok(tem,"|");
			fp.close();
			b.unpack(buffer1);
		    cout<<endl<<"		Confirm permanent updation:[Y/N] ";
			cin>>upd;
			if(upd=='Y' || upd=='y')
			{
				ud=1;
				get_pas:
					cout<<endl<<"\tName of passenger:\t"; cin>>pas;
					valid=1;
					for(int i=0;i<strlen(pas);i++)
					if(isalpha(pas[i])==0)
					{
						valid=0;
						break;
					}
				if(valid==0)
					{cout<<endl<<" INVALID NAME "<<endl;goto get_pas;}

	cout<<endl<<"\tenter Busid:\t\t";
	cin>>busid;
	cout<<endl<<"\tenter the date:\t\t";
	cin>>date;
	cout<<endl<<"\tenter source:\t\t";
	cin>>src;
	cout<<endl<<"\tenter destination:\t";
	cin>>dest;
	cout<<endl<<"\tenter cost:\t\t";
	cin>>cost;

				get_phno:cout<<endl<<"\tPhno:\t\t";cin>>phno;
					valid=1;
					if(strlen(phno)!=10)
					   valid=0;
					else
					     for(i=0;i<strlen(phno);i++)
					     if(isdigit(phno[i])==0)
					     {
					       valid=0;
					       break;
					     }
					if(valid==0)
					{
					cout<<endl<<"Invalid Phone number"<<endl;
					goto get_phno;
					}
				strcpy(buffer,key);
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

				fp.open(fname,ios::in);
				fp1.open("out.txt",ios::out);

				while(!fp.eof())
				{

					fp>>buffer2;
					strcpy(zz,buffer2);
					bi=strtok(zz,"|");


					//if(strcmpi(sin[i].k,o)==0)
					if(strcmpi(bi,key)==0)
					{
						fp1<<buffer<<"\n";
						
						//cout<<endl<<in[i].k<<"\t"<<o<<"\t"<<bi<<"\t"<<sin[i].k<<endl<<endl;
					}
					else{
						
						//cout<<in[i].k<<"\t"<<o<<endl;
						fp1<<buffer2<<"\n";
					}
					
				}
		}	
	fp.close();                                   	
	fp1.close();
	//cout<<recount<<endl;
	remove(fname);
	rename("out.txt",fname);
	}
	return;
}


void ind()
{
	char buffer[100],tem[100],*t,*r;
	recount=0;
	//cout<<"\t"<<recount<<endl;
	fp.open(fname,ios::in|ios::out);

	while(!fp.eof())
	{
		recount++;
		if(recount>1)
			in[recount].o=(fp.tellg()+2);
		else
			in[recount].o=fp.tellg();
		fp>>buffer;
		strcpy(tem,buffer);
		t=strtok(tem,"|");
		r=strtok(NULL,"|");
		if(strcmpi("**********",t)==0)
			recount--;
		else
		{	
			strcpy(in[recount].k,t);

			strcpy(sin[recount].sk,r);
			strcpy(sin[recount].k,t);
		}
	}
	//cout<<"\t"<<recount<<endl;
//if(recount>1)
		recount--;
	//cout<<"\t"<<recount<<endl;
	
	memindex temp;
	int i,j;
		for(i=1;i<recount;i++)
		{
			for(j=1;j<recount;j++)
			{
				if(strcmpi(in[j].k,in[j+1].k)>0)
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
	return;
} 


int main()
{
textbackground(BLACK);
textcolor(LIGHTMAGENTA);
char *t,ch;
char bid[15],buffer[100];
int i,j,k,pos,k1;
char *key;
clrscr();
ind();

	for(;;)
	{	  	
		clrscr();
		ud=0;
		gotoxy(18,2);
		cout<<"******************************************";gotoxy(18,4);
		cout<<"*";
		gotoxy(32,4);
		cout<<"MAIN MENU";gotoxy(59,4);cout<<"*";gotoxy(18,6);
		cout<<"******************************************";gotoxy(18,8);
		cout<<"* 1: Display all records";gotoxy(59,8);cout<<"*";gotoxy(18,10);
		cout<<"* 2: Add record into the file";gotoxy(59,10);cout<<"*";gotoxy(18,12);
		cout<<"* 3: Search for record ";gotoxy(59,12);cout<<"*";gotoxy(18,14);
		cout<<"* 4: Delete record";gotoxy(59,14);cout<<"*";gotoxy(18,16);
		cout<<"* 5: Update record";gotoxy(59,16);cout<<"*";gotoxy(18,18);
		//cout<<"* 6: Tree structure display";gotoxy(59,18);cout<<"*";gotoxy(18,20);
		cout<<"* 6: Quit program";//gotoxy(59,20);cout<<"*";
		gotoxy(18,20);
		cout<<"******************************************"<<endl;
		cout<<endl<<" 		 Enter choice [1-6] : ";
		cin>>ch;
		switch(ch)
		{

		 case '1':	clrscr();
					gotoxy(20,2);
					cout<<"*******************************************";
					gotoxy(20,4);
					cout<<" *  		DISPLAY ALL RECORDS  	*";
					gotoxy(20,6);
					cout<<"*******************************************"<<endl<<endl;
					b.display();
					break;

		case '2':	clrscr();
					gotoxy(22,2);
					cout<<"******************************";
					gotoxy(22,4);
					cout<<"*  ADD RECORD INTO THE FILE *";
					gotoxy(22,6);
					cout<<"******************************"<<endl<<endl;
					b.inser();
					break;
		case '3':
					clrscr();
					gotoxy(22,2);
					cout<<"************************************";
					gotoxy(22,4);
					cout<<"*	  	     SEARCH   		     *";
					gotoxy(22,6);
					cout<<"************************************"<<endl<<endl;
					gotoxy(24,8);
					cout<<"\n*\t1.\tSearch using Bus Registration number\t*\n";
					cout<<"\n*\t2.\tSearch using name of the Passenger\t*\n";
					cout<<"\n*\t3.\tSearch using source and destination\t*\n";
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
								cout<<endl<<"\n\t\tEnter the name to search : ";
								cin>>key;
								fp.open(fname,ios::in);
								for(i=1;i<=recount;i++)
								{
									if(strcmpi(sin[i].sk,key)==0)
									{
										f1=1;
										int kk=b.search(sin[i].k);
										fp.seekg(in[kk].o,ios::beg);
										fp>>buffer;
										b.unpack(buffer);
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
								for(i=1;i<=recount;i++)
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
									}
								      
								}
								if(found==0) cout<<"passengers are not there in this way";
									fp.close();
								    break;
					}
					break;
		 case '4':
			clrscr();
			gotoxy(28,2);
			cout<<"*******************";
			gotoxy(28,4);
			cout<<"*	DELETE RECORD  *";
			gotoxy(28,6);
			cout<<"*******************"<<endl<<endl;
			b.del();
			ind();
			break;
		case '5':
			clrscr();
			gotoxy(28,2);
			cout<<"*******************";
			gotoxy(28,4);
			cout<<"*  UPDATE RECORD  *";
			gotoxy(28,6);
			cout<<"*******************"<<endl<<endl;
			b.update();
			if(ud==1)
				ind();
			break;

		case '6':
		   exit(0);
		   break;
		   case '8':ind();
		   getch();
		   break;
		 default:	cout<<endl<< "		!!! Invalid Choice. Press any key ... !!!";
		 getch();
		}
			if(ch>1 && ch<7)
			cout << "\n\n\t Press any key to return to menu ... ";
			getch();
	}
}
