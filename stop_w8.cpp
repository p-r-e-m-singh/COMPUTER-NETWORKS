#include<iostream>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
// #include"protocol.h>
using namespace std;
typedef unsigned int seq_nr; //sequence or ack numbers
typedef enum{data,ack,nak} frame_kind; //frame kind definition
typedef enum{frame_arrival,wait} event_type; //type of event
class packet //structure of a packet
{    public:
        char data[5];
} *p;
class frame //structure of a frame
{
    public:
    frame_kind kind; //what kind of a frame is it?
    seq_nr seq; //sequence number
    seq_nr ack; //acknowledgemenmt number
    packet * info; //the network layer packet
}*s,*r;
int a=-1,q=-1;
int wait_for_event(event_type event) //wait for an event to happen;return its type in event
    { 
        if(event==frame_arrival)
        { return 1 ;}
        else return 0;
    }
void showkind(frame_kind t) //display the event type
{       switch(t)
        { case data : cout<<"data"; break;
            case ack : cout<<"ack"; break;
            case nak : cout<<"nak"; break;
        }
}
void from_network_layer(packet *i) //fetch packet from network layer
{   
    s=new frame;
    cout<<"\n\tConverting packet into frame.....";
    s->seq=++a;
    s->kind=data;
    s->info=i;
}
void to_physical_layer(frame *s) //transfer frame to physical layer
{
    if(s->kind==data)
    { 
        cout<<"\n\tSending frame to physical layer with following details:";
        cout<<"\n\t\tKind= ";
        showkind(s->kind);
        cout<<", Sequence Number= "<<s->seq;
        cout<<"\n\t\tData= ";
        for(int i=0;i<5;i++)
        { cout<<s->info->data[i];}
    }
    else
    { 
        cout<<"\n\tSending feedback frame to physical layer : ";
        cout<<"\n\t\tKind= ";
        showkind(s->kind);
        cout<<", Ack= "<<s->ack;
    }
}
void from_physical_layer(frame *s) //fetch frame from physical layer
{ 
    cout<<"\n\tReceived frame from receiver with details : ";
    cout<<"\n\t\tKind= ";
    showkind(s->kind);
    cout<<", Sequence Number= "<<s->seq;
    cout<<"\n\t\tData= ";
    for(int i=0;i<5;i++)
    { cout<<s->info->data[i];}
    cout<<"\n\tChecking Sequence number....... ";
    if(q!=s->seq)
    {cout<<"\n\tSeparating data packet from the frame...........";}
    else
    { cout<<"\n\tDuplicate frame identified....\n\tDiscarding frame.....";}
}
void to_network_layer(packet *p) //transfer packet to network layer
{ 
    cout<<"\n\tSending packet to network layer......";
    q=s->seq;
    cout<<"\n\tData received : ";
    for(int i=0;i<5;i++)
    { cout<<p->data[i];}
    r=new frame;
    r->kind=ack;
    r->seq=(seq_nr)NULL;
    r->ack=s->seq;
}

class stop_and_wait
{ 
    char buf[50];
    event_type event;
    public:
    stop_and_wait()
    { 
        for(int i=0;i<50;i++)
        { buf[i]=(char)NULL;}
    }
    void sender();
    void receiver();
};

int k=0,count=0,len=0,lim=10000,flag=0;
void stop_and_wait::sender()
{ cout<<"\n\n\t\t\t**********Sender Side**********";
    if(count>0)
    { 
        if(count%2==0)
        { cout<<"\n\n\tTimeout Expired!!!!!!!";
        flag=1;
        }
        else
        { 
            cout<<"\n\tFeedback frame received : ";
            cout<<"\n\tKind = ";
            showkind(r->kind);
            cout<<" Ack = "<<r->ack;
            if(flag==1)
            {count--;
            flag=0;
            }
        }
        if(r->kind==nak || flag==1)
        { 
            cout<<"\n\tResending the previous frame......";
            --count;
            flag=1;
        }
  }
if(count==lim)
 { 
    cout<<"\n\n\tData Sent Successfully";
    cout<<"\n\tData :";
    puts(buf);
    exit(0);
 }
if(k==0)
 { 
    cout<<"\n\tEnter data to be sent :";
    gets(buf);
    len=strlen(buf);
    if(len%5==0)
    { lim=len/5;}
    else
    { lim=len/5+1;}
    cout<<"\n\tDividing data into groups(5-bit each).....";
    k++;
 }
 while(count<lim)
{ while(event!=wait)
{
if(flag==0)
{ cout<<"\n\tPutting data D"<<count+1<<" in a packet....";
 p=new packet;
for(int i=0;i<5;i++)
{ p->data[i]=buf[i+count*5]; }
cout<<"\n\tPassing data to datalink layer......";
event=frame_arrival;
}
 if(wait_for_event(event))
{ if(flag==0)
{from_network_layer(p); }
to_physical_layer(s);
event=wait;
}
 receiver();
}
}
}
void stop_and_wait::receiver()
{ cout<<"\n\n\t\t\t**********Receiver Side**********";
if(event==wait)
 { from_physical_layer(s);
 if(flag==0)
{to_network_layer(p);
count++;
}
else
{count=count+2;}
to_physical_layer(r);
event=frame_arrival;
sender();
 }
}
int main()
{ stop_and_wait ob;
ob.sender();
return 0;
}