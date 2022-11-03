#include <iostream>
#include <fstream> 
#include <math.h>
#include <vector>
#include <stdlib.h>     	/* srand, rand */
#include <time.h>       	/* time */
#include "parameters.h"         //input parameters, which are shared with ROOT file that draws graph
using namespace std;
int aScenario(int N);           //a scenario of N males taking part in reproduction
int aSimulation(int N);         //a simulation that writes at which generation Muller's ratchet clicks
int initializing(int N);        //to select N females and N males from the first equilibrium state
int daughterBorn(int N, int M);	//from N mothers and N fathers to M daughters
int sonBorn(int N, int M);     	//from N mothers and N fathers to M sons
int female[10000];              //to store up to 10000 female genotype; when female[i]=1/2, genotype is XX/Xx
int male[10000];                //to store up to 10000 male genotype;   when male[i]=3/4/5, genotype is XY/Xy/xY
int daughter[10000];           	//to temporarily hold daughter's genotypes
int son[10000];                	//to temporarily hold son's genotypes
ofstream myfile;                //to write to file for ROOT file to read for drawing
int check(int N);		//to write to file for ROOT file to read for drawing
float r; 			//a random number 
int main(){
        //srand(time(NULL)+clock()); 
	for(int i = 0; i!=sizeof(N)/sizeof(N[0]); i++){
		aScenario(N[i]);
	}
}

int aScenario(int N){
	string filename="probabilities-"+to_string(mu)+"-"+to_string(NumberOfGenerationLimit)+"-"+to_string(numberOfSimulations)+"-"+to_string(N)+".txt";
	myfile.open(filename);
	for(int i=0; i<numberOfSimulations; i++){
		srand(N*49+i);
		int theGeneration=0;
                while (theGeneration==0) theGeneration=aSimulation(N);
		cout<<"Muller's ratchet clicks at "<<theGeneration<<endl;
	}
	myfile.close();
	return 1;
}

int aSimulation(int N){
	initializing(N);	
	int generation=0; 
	while(generation<NumberOfGenerationLimit){
		bool anyY=false;
        	for (int i=0; i<N; i++){
        	        if ((male[i]==3)||(male[i]==5)) anyY=true;
        	}
		if (!anyY) return generation;
		daughterBorn(N, N);
		sonBorn(N,N);
		for (int i=0; i<N; i++){
			female[i]=daughter[i];
			male[i]=son[i];
		}
	 	generation++;	
		check(N);
	}
	return generation;
}

int initializing(int N){ // 1:XX; 2:Xx; 3:XY; 4:Xy; 5:xY
	for(int i=0;i<N;i++){ 
		float aboutmu=(sqrt(mu)-mu)/(1-mu);//The formula from the article
  		r=(float)rand()/(float)RAND_MAX;
  		female[i]=1; if (r<2*aboutmu) female[i]=2;
		r=(float)rand()/(float)RAND_MAX;
  		male[i]=3; if (r<2*aboutmu) male[i]=4; if (r<aboutmu) male[i]=5;
 	}
	return 1;
}

int daughterBorn(int N, int M){
        int i=0;
        int j=0;
        while(j<M){ 
                bool X1isLong=true; //X1 is from mother
                bool X2isLong=true; //X2 is from father
		i=rand()%N;
                if ((female[i]==2)&&(rand()%2==1)) {
                        X1isLong=false;
                }else {
                        r=(float)rand()/(float)RAND_MAX;
                        if (r<mu) X1isLong=false; // mutation happens
                }
		i=rand()%N;
                if (male[i]==5) {
                        X2isLong=false;
                } else {
                        r=(float)rand()/(float)RAND_MAX;
                        if (r<mu) X2isLong=false; // mutation happens
                }
                if(X1isLong&&X2isLong) {
                        daughter[j]=1;
                        j++;
                } else if(X1isLong||X2isLong) {
                        daughter[j]=2;
                        j++;
                }
	}
        return 1;
}

int sonBorn(int N, int M){
        int i;
        int k=0;
        while(k<M){
                bool XisLong=true; 
                bool YisLong=true; 
                i=rand()%N;
                if ((female[i]==2)&&(rand()%2==1)) {
                        XisLong=false;
                }else {
                        r=(float)rand()/(float)RAND_MAX;
                        if (r<mu) XisLong=false; // mutation happens
                }
                i=rand()%N;
        	if (male[i]==4) {
        	        YisLong=false;
        	} else {
        	        r=(float)rand()/(float)RAND_MAX;
        	        if (r<mu) YisLong=false; // mutation happens
        	}
        	if(XisLong&&YisLong) {
        	        son[k]=3;
        	        k++;
        	} else if(XisLong&&!YisLong) {
        	        son[k]=4;
        	        k++;
        	} else if(!XisLong&&YisLong){
        	        son[k]=5;
        	        k++;
        	}
        }
        return 1;
}

int check(int N){
		long female1=0;
		long female2=0;
		long male3=0;
		long male4=0;
		long male5=0;
	for (int i=0; i<N; i++){
		if (female[i]==1) female1++;
		if (female[i]==2) female2++;
		if (male[i]==3) male3++;
		if (male[i]==4) male4++;
		if (male[i]==5) male5++;
	}
	myfile<<male3+male5<<endl;
	return 1;
}

