#include<bits/stdc++.h>
using namespace std ;

int cost[100][100] , n  ; 

int getMin(int dist[] , bool visited[]){
    int key = 0 ; 
    int min = INT_MAX ; 
    for(int i=0;i < n ; i++){
        if(!visited[i] && dist[i]<min){
            min = dist[i] ; 
            key = i ; 
        }
    }
    return key ; 
}

void display(int dist[] , int par[] ){
   for(int i =0 ;i < n ;i++){
       int temp = par[i] ; 
       cout<<i << " <- " ;
       while(temp!=-1)
       {
           cout<< temp << " <- " ;
           temp = par[temp] ; 
       }
       cout<<endl;
       cout<<"Distance = " << dist[i]<<endl ;
       cout<<endl; 
   } 
}

void dijkstra(int src ){//1
    int par[100] , dist[100] ; //parent and Distance table
    bool visited[100] ={0} ; //Matrix for maintaining visited/unvisited
    fill(dist , dist+n  , INT_MAX ) ; //Initially taking distance from routers as infinity

    dist[src] =0 ; //Setting distance of source=0
    par[src] =-1 ;//Setting parent router as -1 for source
    
    for(int g = 0  ;g<n-1 ; g++){//traversing through n-1 routers
        int u = getMin( dist ,  visited )  ; //getting router with minimum distance
        visited[u] = true ;//making its visit state as true
        cout<< " min = " << u <<endl; //displaying minimum distance vertex
        for(int v =0 ; v< n ;v++){
            if((!visited[v]) && ((dist[u]+cost[u][v]) <  dist[v]) && cost[u][v]!=9999)
            {
                par[v] = u ; 
                dist[v] = dist[u] + cost[u][v] ; 
            }
        }
    }
    
    display(dist , par) ; 
}
int main(void) { 
    system("cls");
    cout<<"\t\t\tDijkstra Algorithm for shortest path routing\t\t\t\n";
    cout<<"Enter number of Routers : " ; 
    cin>>n ; 
    cout<<"Enter cost matrix : \n" ; 
    for(int i = 0 ;i < n ; i++){
        for(int j = 0 ; j< n ; j++)cin>>cost[i][j] ; 
    }
    int src ; 
    cout<<"\nEnter source : " ;  cin>>src ;
    dijkstra(src) ; 
}