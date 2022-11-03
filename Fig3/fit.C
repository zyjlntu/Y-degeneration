// run this by CERN ROOT from a terminal with command: root fit.C
#include <fstream>
#include <iostream>
#include "parameters.h"
void fit()
{
   	TCanvas *c1 = new TCanvas("c1","Graph Draw Options", 200,10,600,400);
	c1->SetLeftMargin(0.15);
        c1->SetBottomMargin(0.16);

	ifstream file;
	int n=NumberOfGenerationLimit;
	double x[n],y[n];
        for(int i=0; i<n; i++){
                x[i]=i;
		y[i]=0;
	}
        TGraph *gr1  = new TGraph(n,x,y);
	string title = "";
	gr1->SetTitle(title.c_str());
	gr1->GetXaxis()->CenterTitle(true);
	gr1->GetYaxis()->CenterTitle(true);
	gr1->GetXaxis()->SetTitle("Generations");
	gr1->GetYaxis()->SetTitle("N_{XY}+N_{xY}");
 	gr1->GetXaxis()->SetLabelSize(.050);
	gr1->GetYaxis()->SetLabelSize(.050);
 	gr1->GetXaxis()->SetTitleSize(.055);
 	gr1->GetYaxis()->SetTitleSize(.055);
        gr1->GetXaxis()->SetLabelOffset(0.02);
        gr1->GetYaxis()->SetLabelOffset(0.02);
        gr1->GetXaxis()->SetTitleOffset(1.5);
        gr1->GetYaxis()->SetTitleOffset(1.5);
	gr1->GetXaxis()->SetMaxDigits(3);

	gr1->GetYaxis()->SetRangeUser(0,N[0]*1.05); 
	gr1->GetXaxis()->SetRangeUser(0,NumberOfGenerationLimit);
   	gr1->Draw("AC");
	
	TLegend *leg = new TLegend(0.6,0.52,0.89,0.71);
	leg->SetTextSize(0.050);
	leg->SetBorderSize(0);
	leg->Draw();

	TGraph gr[sizeof(N)/sizeof(N[0])];
	for(int i = 0; i!=sizeof(N)/sizeof(N[0]); i++){
        	string filename="probabilities-"+to_string(mu)+"-"+to_string(NumberOfGenerationLimit)+"-"+to_string(numberOfSimulations)+"-"+to_string(N[i])+".txt";
       		file.open(filename,ios::in);
        	for(int i=0; i<NumberOfGenerationLimit; i++){
			float temp;
                	file >> temp;
                        y[i]=temp;
                        x[i]=i;
        	}
        	file.close();
        	TGraph *g  = new TGraph(n,x,y);
		g->SetLineColor(i+1);
		//g->SetLineStyle(i+1);
		g->Draw("L");
		string astring = to_string(N[i])+" males";
		leg->AddEntry(g,astring.c_str(),"l");
	}
	c1->SaveAs("c1.eps");
}
