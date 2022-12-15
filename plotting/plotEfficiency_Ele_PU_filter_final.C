#include "TGraphAsymmErrors.h"
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TRatioPlot.h>
#include <stdio.h>
#include <iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TMultiGraph.h>
using namespace std;
void plotEfficiency_Ele_PU_filter_final(TString rootfileName, TString Output,TString filterName){

//TFile *f1 = TFile::Open("filterEff_TT_PU30to80_efficiency_tightid_nominal.root");
TFile *f1 = TFile::Open(rootfileName);
std::cout<<" input file ="<<rootfileName<<std::endl;
f1->Print();
   TH1F *h_total_Run2_2018_PU,*h_total_Run2_2018_pt,*h_total_Run2_2018_eta, *h_total_Run2_2018_pt_eta; 
   TH1F *h_pass_Run2_2018_PU,*h_pass_Run2_2018_pt,*h_pass_Run2_2018_eta, *h_pass_Run2_2018_pt_eta; 
  

  h_total_Run2_2018_PU = (TH1F*)f1->Get("PU_total");
  h_total_Run2_2018_pt = (TH1F*)f1->Get("pt_total");
  h_total_Run2_2018_eta = (TH1F*)f1->Get("eta_total");

  h_pass_Run2_2018_PU = (TH1F*)f1->Get("PU_pass");
  h_pass_Run2_2018_pt = (TH1F*)f1->Get("pt_pass");
  h_pass_Run2_2018_eta = (TH1F*)f1->Get("eta_pass");


 TH1F* graph_Run2_2018_pt=(TH1F*)h_pass_Run2_2018_pt->Clone("temp");
 TH1F* graph_Run2_2018_PU=(TH1F*)h_pass_Run2_2018_PU->Clone("temp");
 TH1F* graph_Run2_2018_eta=(TH1F*)h_pass_Run2_2018_eta->Clone("temp");
 graph_Run2_2018_pt->Divide(h_total_Run2_2018_pt);
 graph_Run2_2018_PU->Divide(h_total_Run2_2018_PU);
 graph_Run2_2018_eta->Divide(h_total_Run2_2018_eta);


   graph_Run2_2018_pt->GetXaxis()->SetTitle("p_T");
   graph_Run2_2018_PU->GetXaxis()->SetTitle("N_PV");
   graph_Run2_2018_eta->GetXaxis()->SetTitle("#eta");

   graph_Run2_2018_pt->GetYaxis()->SetTitle("Efficiency");
   graph_Run2_2018_PU->GetYaxis()->SetTitle("Efficiency");
   graph_Run2_2018_eta->GetYaxis()->SetTitle("Efficiency");

   graph_Run2_2018_pt->SetTitle(filterName);
   graph_Run2_2018_PU->SetTitle(filterName);
   graph_Run2_2018_eta->SetTitle(filterName);

// TLegend *legend = new TLegend(0.4,0.3,0.8,0.5);
//  legend->AddEntry(graph_Run2_2018_PU,"2018","p");
//  legend->AddEntry(graph_Run3_PU,"2021","p");

   gStyle->SetOptStat(0);
  TCanvas *c = new TCanvas("c","Efficiency",1800,600);
////////////////////////////
   c->cd();
   TPad *pad1 = new TPad("pad1", "pad1", 0.0, 0.35, 0.313, 1.0);
  // pad1->SetBottomMargin(0); // Upper and lower plot are joined
   pad1->Draw();             // Draw the upper pad: pad1
   pad1->cd();               // pad1 becomes the current pad
   graph_Run2_2018_PU->SetMaximum(1.1);
   graph_Run2_2018_PU->SetMinimum(0.0);
   graph_Run2_2018_PU->SetMarkerStyle(20);
   graph_Run2_2018_PU->SetMarkerColor(kBlue);
   graph_Run2_2018_PU->Draw("E");    

//////////////////////////////////////////////////   
   c->cd();
   TPad *pad2 = new TPad("pad2", "pad2", 0.343, 0.35, 0.656, 1.0);
   //pad2->SetBottomMargin(0); // Upper and lower plot are joined
   pad2->Draw();             // Draw the upper pad: pad1
   pad2->cd();               // pad1 becomes the current pad
   graph_Run2_2018_pt->SetMaximum(1.1);
   graph_Run2_2018_pt->SetMinimum(0.0);
   graph_Run2_2018_pt->SetMarkerStyle(20);
   graph_Run2_2018_pt->SetMarkerColor(kBlue);
   graph_Run2_2018_pt->Draw("E");    
///////////////////////////////////
   c->cd();
   TPad *pad3 = new TPad("pad3", "pad3", 0.686, 0.35, 1.0, 1.0);
  // pad3->SetBottomMargin(0); // Upper and lower plot are joined
   pad3->Draw();             // Draw the upper pad: pad1
   pad3->cd();               // pad1 becomes the current pad

   graph_Run2_2018_eta->SetMaximum(1.1);
   graph_Run2_2018_eta->SetMinimum(0.0);
   graph_Run2_2018_eta->SetMarkerStyle(20);
   graph_Run2_2018_eta->SetMarkerColor(kBlue);
   graph_Run2_2018_eta->Draw("E");    

  c->Print("/eos/user/a/aldas/www/HLTEfficiency/Egamma_nanoAod/efficiency_" + Output + "_" + filterName + ".png");
  c->Clear();
  delete c;

}// end of program
int main(int ac, char** av){
gROOT->SetBatch(true);
TString filtername,rootfile,output;
rootfile=av[1];
output=av[2];
filtername=av[3];
plotEfficiency_Ele_PU_filter_final(rootfile,output,filtername);
return 0;
}

