// Kruskal.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include<fstream>
#include <string>
using namespace std;

class CGraf
{
public:
	CGraf(int aN);
	~CGraf(void);
	void dodajPovezavo(int aI, int aJ, int aUtez);
	bool jePovezava(int aI, int aJ);
	int odstraniPovezavo(int aI, int aJ);
	void izpisiMatriko();
	int vrniUtez(int aI, int aJ);
	int min(int &aJ);
	int max(int &aJ);
	CGraf* minVpetoDrevo();
	bool polno(int* aP);
	void spremeni(int aI, int  aJ, int* &aP);
	void izpis(int* aP);

private:
	int **matrika;
	int n;
};

CGraf::CGraf(int aN)
{
	n=aN;
	matrika=new int*[n];
	for(int i=0; i<n; i++)
		matrika[i]=new int[n];

	for(int i=0; i<n; i++) 
		for(int j=0; j<n; j++)
			matrika[i][j]=-1;	
}


CGraf::~CGraf(void)
{
	for(int i=0; i<n; i++) 
		delete[] matrika[i];
	delete[] matrika;
}

bool CGraf::jePovezava(int aI, int aJ) {
	if(matrika[aI][aJ]!=-1)
		return true;
	else
		return false;
}

void CGraf::dodajPovezavo(int aI, int aJ, int aUtez) {
	matrika[aI][aJ]=aUtez;
	matrika[aJ][aI]=aUtez;
}

int CGraf::odstraniPovezavo(int aI, int aJ)
{
	int aU = matrika[aI][aJ];
		matrika[aI][aJ] = -1;
		matrika[aJ][aI] = -1;
		return aU;
}

int CGraf::vrniUtez(int aI, int aJ)
{
	if(matrika[aI][aJ] != -1)
		return matrika[aI][aJ];
	else
		return -1;
}

void CGraf::izpisiMatriko() {
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			cout<<matrika[i][j]<<" ";
		}
		cout<<endl;
	}
}

int CGraf:: max(int &aJ)
{
	int aI = -1;
	int aM = vrniUtez(0,0);
	for(int i = 0; i< n; i++){
		for(int j = i+1; j < n; j++){
			if(aM < vrniUtez(i,j)){
				aM = vrniUtez(i,j);
				aI = i;
				aJ = j;
			}
		}
	}
	return aI;
}
int CGraf:: min(int &aJ)
{
	int aK = max(aJ);
	int aI = aK;
	int aMin = vrniUtez(aK, aJ);
	for(int i = 0; i< n; i++){
		for(int j = i+1; j <n; j++){
			if((jePovezava(i,j))&&(aMin > vrniUtez(i,j))){
				aI = i;
				aJ = j;
				aMin = vrniUtez(i,j);
			}
		}
	}
	return aI;
}
CGraf* CGraf:: minVpetoDrevo()
{
	CGraf* aS = new CGraf(n);
	int* aP = new int[n];
	for(int i = 0; i< n; i++){
		aP[i] = -(i+1);
	}
	//Izpis(aP);
	int k = 1;
	while(k < n){
			int aR = -1;
			int aT = min(aR);
			if(aP[aR] != aP[aT]){
				if(aP[aR] > aP[aT]){
					spremeni(aR,aT,aP);
					aP[aT] = aP[aR];
				}else{
					spremeni(aT,aR,aP);
					aP[aR] = aP[aT];
				}
				cout << "Dodajam " <<vrniUtez(aR,aT)<< endl;
				aS->dodajPovezavo(aR,aT, vrniUtez(aR,aT));
				int aU = odstraniPovezavo(aR,aT);
				k++;
			}else{
				int aU = odstraniPovezavo(aR,aT);
			}	
	}
	return aS;
}	

bool CGraf:: polno(int* aP)
{
	for(int i = 0; i< n; i++){
		if(aP[i] != -1){
			return false;
		}
	}
	return true;
}

void CGraf:: spremeni(int aI, int  aJ, int* &aP)
{
	for(int i = 0; i< n; i++){
		if(aP[aJ] == aP[i]){
			aP[i] = aP[aI];
		}
	}
}

void CGraf:: izpis(int* aP)
{
	for(int i = 0; i<n; i++){
		cout << aP[i]<<" ";
	}
	cout << endl;
}

CGraf* Preberi(char* ime){
 ifstream dat(ime);
 if (dat.is_open()){
	 int aN;
	 dat>>aN;
	 CGraf * aG = new CGraf(aN);	
	if(dat.good()){
		while(!dat.eof()){
			int x;
			int y; 
			int z;
			dat>>x>>y>>z;
			aG->dodajPovezavo(x,y,z);
		}
	}
		dat.close();
		return aG;
 }
 else{	
	 cout<<"Napaka pri odpiranju datoteke!";
	 return NULL;
 }
}



int _tmain(int argc, _TCHAR* argv[])
{

	CGraf* aG = Preberi("K.txt");
	aG->izpisiMatriko();
	CGraf* aMD = aG->minVpetoDrevo();
	aMD->izpisiMatriko();


	cin.ignore();
	cin.get();

	return 0;
}

