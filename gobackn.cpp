#include<bits/stdc++.h>

// #include<ctime>

#define longint long long int
using namespace std;

void transmission(longint & i, longint & N/*Window Size*/, longint & tf/*Total No Frames*/, longint & tt/*Total frame sent/resent count*/) {
  while (i <= tf) { /*Limit for Sending/receive frames*/
    int z = 0;//To record no of times frame went undisturbed
    //For Loop working at Sender's end
    for (int k = i; k < i + N && k <= tf; k++) {
      cout << "\t\tSending Frame " << k << "..." << endl;
      tt++;
    }
    //For Loop working at receivers end
    for (int k = i; k < i + N && k <= tf; k++) {
      int f = rand() % 2; /*Random variable creating frame lost*/
      if (!f) {
        cout << "\t\tAcknowledgment for Frame " << k << "..." << endl;
        z++;//Updation to make window slide
      } else {
        cout << "\t\tTimeout!! Frame Number : " << k << " Not Received" << endl;
        cout << "\t\tRetransmitting Window..." << endl;
        break;
      }
    }
    cout << "\n";
    i = i + z;//i updated how much to slide window
  }
}

int main() {
    system("cls");
    cout<<"\t\t\tGo Back- N Sliding Window Protocol\t\t\t\n";

  longint tf, N, tt = 0;
  cout << "\tEnter the Total number of frames : ";
  cin >> tf;
  cout << "\tEnter the Window Size : ";
  cin >> N;
  longint i = 1;
  transmission(i, N, tf, tt);
  cout << "Total number of frames which were sent and resent are : " << tt <<
    endl;
  return 0;
}