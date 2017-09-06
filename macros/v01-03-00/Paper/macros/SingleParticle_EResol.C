#include "CommonTools.h"
#include "TH1F.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TPaveStats.h"
#include "TF1.h"

void SingleParticle_EResol()
{
   std::string canvasName = "canvas";
   std::string canvasTitle = "Canvas title";
   int canvasX1 = 200;
   int canvasY1 = 52;
   int canvasX2 = 700;
   int canvasY2 = 650;
   int nPoints = 8;

   double zero [] = {0, 0, 0, 0, 0, 0, 0, 0};
   double energies[] = {10, 20, 30, 40, 50, 60, 70, 80};

   double arborData[] = 
     {0.208067,
      0.165154,
      0.152197,
      0.137305,
      0.130617,
      0.111196,
      0.109463,
      0.101937};

   double arborDataError[] =
     {0.00223789,
      0.000939173,
      0.00139212,
      0.00211278,
      0.00194287,
      0.00248777,
      0.00190629,
      0.00178431};

   double noPFAData[] =
     {0.206694,
     0.1561,
     0.143164,
     0.129763,
     0.122156,
     0.10309,
     0.101744,
     0.0967555};

   double noPFADataError[] = 
     {0.0045529,
     0.00115861,
     0.00170988,
     0.0022871,
     0.00196874,
     0.00222291,
     0.0017071,
     0.00180287};

   double FTFP_BERT_HP_Data[] =
     {0.2053399,
      0.1428589,
      0.1283569,
      0.1230574,
      0.1184088,
      0.1155998,
      0.1122676,
      0.1048735};
 
   double FTFP_BERT_HP_DataError[] = 
     {0.003954651,
      0.00235069,
      0.002156589,
      0.002398154,
      0.002261617,
      0.002314047,
      0.002264068,
      0.002092942};

   double FTF_BIC_Data[] =
     {0.1969724,
      0.1408498,
      0.1256989,
      0.1253923,
      0.1230361,
      0.1163957,
      0.1196471,
      0.1098737};
 
   double FTF_BIC_DataError[] =
     {0.004175523,
      0.003611685,
      0.003133653,
      0.003561399,
      0.003547318,
      0.003138559,
      0.003878797,
      0.003713659};

   std::string graphXTitle = "E_{beam} [GeV]";
   std::string graphYTitle = "#sigma_{E}/E_{rec}";
   double rangeUserXMin = 0;
   double rangeUserXMax = 90;
   double rangeUserYMin = 0;
   double rangeUserYMax = 0.4;

   TCanvas *pCanvas = new TCanvas(canvasName.c_str(), canvasTitle.c_str(), canvasX1, canvasY1, canvasX2, canvasY2);
   pCanvas->SetFillColor(0);
   pCanvas->SetBorderMode(0);
   pCanvas->SetBorderSize(2);
   pCanvas->SetTickx(1);
   pCanvas->SetTicky(1);
   pCanvas->SetLeftMargin(0.15);
   pCanvas->SetRightMargin(0.03);
   pCanvas->SetTopMargin(0.05);
   pCanvas->SetBottomMargin(0.14);
   pCanvas->SetFrameBorderMode(0);
   pCanvas->SetFrameBorderMode(0);

   gStyle->SetOptStat(0);
   gStyle->SetOptFit(0);

   TH1F *pH = new TH1F("h", "", rangeUserXMax-rangeUserXMin, rangeUserXMin,rangeUserXMax );
   pH->Draw();
   pH->GetXaxis()->SetTitle(graphXTitle.c_str());
   pH->GetXaxis()->SetLabelFont(42);
   pH->GetXaxis()->SetTitleSize(0.05);
   pH->GetXaxis()->SetTitleOffset(1);
   pH->GetXaxis()->SetTitleFont(42);
   pH->GetXaxis()->SetRangeUser(rangeUserXMin, rangeUserXMax);
   pH->GetYaxis()->SetTitle(graphYTitle.c_str());
   pH->GetYaxis()->SetLabelFont(42);
   pH->GetYaxis()->SetTitleSize(0.055);
   pH->GetYaxis()->SetTitleOffset(1.2);
   pH->GetYaxis()->SetTitleFont(42);
   pH->GetYaxis()->SetRangeUser(rangeUserYMin, rangeUserYMax);

   TF1 *pResolFunc = new TF1("resolFunc", resolutionFunction, 0, 90, 2);
   
   TGraphErrors *gre = 0;
   TPaveStats *st = 0;

   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);

   gre = new TGraphErrors(nPoints, energies, arborData, zero, arborDataError);
   gre->SetName("Graph_arbor");
   gre->SetTitle("ArborPFA - CERN SPS H6");
   gre->SetLineColor(kRed);
   gre->SetMarkerColor(kRed);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.6);
   pResolFunc->SetLineColor(kRed);
   //gre->Fit(pResolFunc, "Q"); 
   gre->Draw("p same");
   pCanvas->Update();

   gre = new TGraphErrors(nPoints, energies, noPFAData, zero, noPFADataError);
   gre->SetName("Graph_nopfa");
   gre->SetTitle("No PFA - CERN SPS H6");
   gre->SetLineColor(kBlue);
   gre->SetMarkerColor(kBlue);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(1.6);
   pResolFunc->SetLineColor(kBlue);
   //gre->Fit(pResolFunc, "Q");
   gre->Draw("p same");
   pCanvas->Update();

   gre = new TGraphErrors(nPoints, energies, FTFP_BERT_HP_Data, zero, FTFP_BERT_HP_DataError);
   gre->SetName("Graph_FTFP_BERT_HP");
   gre->SetTitle("ArborPFA - FTFP_BERT_HP");
   gre->SetLineColor(kGreen+1);
   gre->SetMarkerColor(kGreen+1);
   gre->SetMarkerStyle(33);
   gre->SetMarkerSize(1.6);
   pResolFunc->SetLineColor(kGreen+1);
   //gre->Fit(pResolFunc, "Q");
   gre->Draw("p same");
   pCanvas->Update(); 

   gre = new TGraphErrors(nPoints, energies, FTF_BIC_Data, zero, FTF_BIC_DataError);
   gre->SetName("Graph_FTF_BIC");
   gre->SetTitle("ArborPFA - FTF_BIC");
   gre->SetLineColor(kBlack);
   gre->SetMarkerColor(kBlack);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.6);
   pResolFunc->SetLineColor(kBlack);
   //gre->Fit(pResolFunc, "Q");
   gre->Draw("p same");
   pCanvas->Update();  


   TPaveText *pt = new TPaveText(0.3, 0.2, 0.93, 0.3, "tbNDC");
   pt->SetTextSize(0.05);
   pt->SetTextColor(kGray+2);
   pt->SetFillColor(0);
   pt->SetLineWidth(0);
   pt->SetBorderSize(0);
   pt->AddText("CALICE SDHCAL");
   pt->SetTextFont(62);
   pt->Draw();
   
   TLegend *leg = new TLegend(0.3,0.67,0.88,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillStyle(0);
   leg->SetFillColor(0);
   leg->SetTextSize(0.04);

   TLegendEntry *entry=0;
   entry=leg->AddEntry("Graph_arbor","ArborPFA - CERN SPS H6","p");
   entry->SetFillStyle(1001);
   entry->SetMarkerColor(kRed);
   entry->SetMarkerStyle(23);
   entry->SetMarkerSize(2);

   entry=leg->AddEntry("Graph_nopfa","No PFA - CERN SPS H6","p");
   entry->SetFillStyle(1001);
   entry->SetMarkerColor(kBlue);
   entry->SetMarkerStyle(29);
   entry->SetMarkerSize(2);

   entry=leg->AddEntry("Graph_FTFP_BERT_HP","ArborPFA - FTFP_BERT_HP","p");
   entry->SetFillStyle(1001);
   entry->SetMarkerColor(kGreen+1);
   entry->SetMarkerStyle(33);
   entry->SetMarkerSize(2);

   entry=leg->AddEntry("Graph_FTF_BIC","ArborPFA - FTF_BIC","p");
   entry->SetFillStyle(1001);
   entry->SetMarkerColor(kBlack);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(2);

   leg->Draw();

   pCanvas->Modified();
   pCanvas->cd();
   pCanvas->SetSelected(pCanvas);
}
