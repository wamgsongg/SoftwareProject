//
//  main.cpp
//  subway
//
//  Created by wangsong on 2019/10/14.
//  Copyright © 2019 wangsong. All rights reserved.
//
#include <bits/stdc++.h>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define MAX 9999
#define N 20
#define NUM 599

typedef struct{
    char station[N];
    int change;
} sta;
typedef struct{
    int weight;
    int L;
} G;
sta vertex[NUM];
G graph[NUM][NUM];
int Vsum;
pair<int,int> path[NUM];
int s[NUM];
int dis[NUM];
string linename[NUM];
int coutt[NUM];
int top=-1;

int search(char *s){
    int i;
    for (i=0; i<Vsum; i++) {
        if (!strcmp(vertex[i].station,s)) {
            return i;
        }
    }
    return -1;
}
bool empty(){
    if (top==-1) {
        return true;
    }
    else return false;
}
int pop(){
    if (!empty()) {
        return coutt[--top];
    }
    else return 0;
}
void print(int V1,int V2){
	string r="";
	path[V1].first=-1;
	int now=V2,nowL=path[V2].second,ttt;
	while(now!=V1&&now){
		//printf("%s\n",vertex[now].station);
		string ttr;
		if(nowL!=path[now].second&&path[now].second){
			r="\n<"+linename[nowL]+"> "+r;
			nowL=path[now].second;
			if(nowL)ttt=nowL;
		}
		ttr=vertex[now].station;
		r=ttr+" "+r;
		now=path[now].first;
	}
	char th[17];
	string ttr;
	ttr=vertex[V1].station;
	r=ttr+" "+r;
	r="<"+linename[nowL]+"> "+r;
	cout<<r<<endl; 
//    int last=V1;
//    int k=1;
//    int u=pop();
//    int L=graph[last][u].L;
//    printf("%s-%d(",vertex[V1].station,L);
//    last=u;
//    while (!empty()) {
//        u=pop();
//        if(L!=graph[last][u].L){
//            L=graph[last][u].L;
//            printf("%d)-%s-%d(",k,vertex[last].station,L);
//            k=0;
//        }
//        k++;
//        last=u;
//    }
//    printf("%d)-%s",k,vertex[V2].station);
}
void dijkstra(int V1,int V2){
    
    int i,j;
    s[V1]=1;
    for (i=0; i<Vsum; i++) {
        if (i==V1) {
            dis[i]=0;
        }
        dis[i]=graph[V1][i].weight;
    }
    while(1){
    	int min=MAX;
    	int v= -1;
        for (j=0; j<=Vsum; j++) {
            if (s[j]==0&&dis[j]<min) {
            	min=dis[j];
                v=j;
            } 
        }
		if(v==V2||v==-1){
			printf("%d\n",dis[V2]);
			return;
		} 
		s[v]=1; 
	    for (j=0; j<=Vsum; j++) {
	        if (!s[j]&&dis[j]>min+graph[v][j].weight) {
	            dis[j]=min+graph[v][j].weight;
	            path[j].first=v;
	            path[j].second=graph[v][j].L; 
	     	}
       	}
	}
	
    
} 

int main(int arg, char **args) {
	char name_start[N],name_end[N];
	
	for(int i=0;i<arg;i++){
		if(!strcmp(args[i],"-map")){
			freopen(args[++i], "r", stdin);
		}
		else if(!strcmp(args[i],"-b")){
			strcpy(name_start,args[++i]);
			strcpy(name_end,args[++i]);
		}
		else if(!strcmp(args[i],"-o")){
			freopen(args[++i], "w", stdout);
		}
		
	}

    // insert code here...
    
  
    int LINE;
    scanf("%d",&LINE);
	for(int k=1;k<=LINE;k++){
		cin>>linename[k];
	}
    int i,j,x,y;
    for(i=0;i<NUM;i++)
        for (j=0; j<NUM; j++) {
            graph[i][j].weight=graph[j][i].weight=MAX;
            graph[i][j].L=graph[j][i].L=0;
        }
    int no,sum,is,last;
    char name[N];
    Vsum=0;
    for(x=0;x<LINE;x++){
        scanf("%d %d",&no,&sum);
        
        last=-1;
        for (y=0; y<sum; y++) {
            scanf("%s %d",name,&is);
            int index=search(name);
            if (index==-1) {
                strcpy(vertex[Vsum].station, name);
                vertex[Vsum].change=is;
                if(last!=-1){
                    graph[last][Vsum].L=graph[Vsum][last].L=no;
                    graph[last][Vsum].weight=graph[Vsum][last].weight=1;
                }
                last=Vsum;
                Vsum++;
            }else{
                if (last!=-1) {
                    graph[last][index].L=graph[index][last].L=no;
                    graph[last][index].weight=graph[index][last].weight=1;
                }
                last=index;
            }
        }
    }
    //freopen("CON", "r", stdin);
    int V1,V2;
    V1=search(name_start);
    V2=search(name_end);
    dijkstra(V1,V2);
    print(V1,V2);
    return 0;
}
