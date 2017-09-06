{
   std::string canvasName = "canvas";
   std::string canvasTitle = "Canvas title";
   int canvasX1 = 14;
   int canvasY1 = 48;
   int canvasX2 = 600;
   int canvasY2 = 741;
   int nPoints = 8;

   double zero [] = {0, 0, 0, 0, 0, 0, 0, 0};
   double energies[] = {10, 20, 30, 40, 50, 60, 70, 80};

   double arborData[] = 
     {10.246,
     19.9324,
      28.4116,
      38.8009,
      47.2327,
      61.0905,
      68.3314,
      73.6478};

   double arborDataError[] =
     {0.019234,
      0.0146414,
      0.0332272,
      0.0664221,
      0.0732852,
      0.122841,
      0.103513,
      0.1091};

   double noPFAData[] = 
    {10.5116,
     20.5701,
     29.0285,
     39.634,
     48.1973,
     62.1095,
     69.4983,
     74.7649};

   double noPFADataError[] = 
    {0.0357198,
     0.0193659,
     0.0394093,
     0.07411,
     0.0753174,
     0.11351,
     0.0980916,
     0.110341};

   double FTFP_BERT_HP_Data[] =
     {9.992329,
      20.20013,
      29.92255,
      39.25561,
      47.89563,
      56.18078,
      63.46324,
      70.22595};

   double FTFP_BERT_HP_DataError[] =
     {0.02951871,
      0.03850629,
      0.05140743,
      0.07131807,
      0.08273342,
      0.0987248,
      0.110043,
      0.1148181};

   double FTF_BIC_Data[] =
     {10.51304,
      21.14527,
      31.27037,
      41.19224,
      49.99818,
      58.59739,
      66.09443,
      72.56016};

   double FTF_BIC_DataError[] =
     {0.03703696,
      0.05890614,
      0.07779753,
      0.1105619,
      0.1362508,
      0.1449815,
      0.1858119,
      0.1952935};

   std::string graphXTitle = "E_{beam} [GeV]";
   std::string graphYTitle = "E_{rec} [GeV]";
   double rangeUserXMin = 0;
   double rangeUserXMax = 89.9;
   double rangeUserYMin = 0;
   double rangeUserYMax = 90;

   gStyle->SetOptStat(0);

   TCanvas *pCanvas = new TCanvas(canvasName.c_str(), canvasTitle.c_str(), canvasX1, canvasY1, canvasX2, canvasY2);
   pCanvas->Range(0,0,1,1);
   pCanvas->SetFillColor(0);
   pCanvas->SetBorderMode(0);
   pCanvas->SetBorderSize(2);
   pCanvas->SetTickx(1);
   pCanvas->SetTicky(1);
   pCanvas->SetLeftMargin(0.1666667);
   pCanvas->SetRightMargin(0.05660377);
   pCanvas->SetTopMargin(0.0256917);
   pCanvas->SetBottomMargin(0.07692308);
   pCanvas->SetFrameLineWidth(1);

   // pCanvas->SetFillColor(0);
   // pCanvas->SetBorderMode(0);
   // pCanvas->SetBorderSize(2);
   // pCanvas->SetTickx(1);
   // pCanvas->SetTicky(1);
   // pCanvas->SetLeftMargin(0.15);
   // pCanvas->SetRightMargin(0.03);
   // pCanvas->SetTopMargin(0.05);
   // pCanvas->SetBottomMargin(0.14);
   // pCanvas->SetFrameBorderMode(0);
   // pCanvas->SetFrameBorderMode(0);

   TPad *r1_1 = new TPad("r1_1", "",0.02,0.37,0.95,0.99);
   r1_1->Draw();
   r1_1->cd();
   r1_1->Range(-19.23077,0.01,96.15385,1428.571);
   r1_1->SetFillColor(0);
   r1_1->SetBorderMode(0);
   r1_1->SetBorderSize(2);
   r1_1->SetTickx(1);
   r1_1->SetTicky(1);
   r1_1->SetLeftMargin(0.1666667);
   r1_1->SetRightMargin(0.01);
   r1_1->SetTopMargin(0.02);
   r1_1->SetBottomMargin(0.0);
   r1_1->SetFrameLineWidth(2);
   r1_1->SetFrameBorderMode(0);
   r1_1->SetFrameLineWidth(1);
   r1_1->SetFrameBorderMode(0);

   TH1F *pH = new TH1F("pouette", "", rangeUserXMax-rangeUserXMin, rangeUserXMin, rangeUserXMax);
   pH->SetMinimum(0.1);
   pH->SetMaximum(90);
   pH->Draw();
   pH->GetYaxis()->SetTitle(graphYTitle.c_str());
   pH->GetYaxis()->SetLabelFont(42);
   pH->GetYaxis()->SetTitleSize(0.07);
   pH->GetYaxis()->SetTitleOffset(0.8);
   pH->GetYaxis()->SetTitleFont(42);
   pH->GetYaxis()->SetLabelSize(0.045);
   
   TGraphErrors *gre=0;
   gre = new TGraphErrors(nPoints, energies, arborData, zero, arborDataError);
   gre->SetName("Graph_arbor");
   gre->SetTitle("ArborPFA - CERN SPS H6");
   gre->SetLineColor(kRed);
   gre->SetMarkerColor(kRed);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.6);
   gre->Draw("p same");

   gre = new TGraphErrors(nPoints, energies, noPFAData, zero, noPFADataError);
   gre->SetName("Graph_nopfa");
   gre->SetTitle("No PFA - CERN SPS H6");
   gre->SetLineColor(kBlue);
   gre->SetMarkerColor(kBlue);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(1.6);
   gre->Draw("p same");

   gre = new TGraphErrors(nPoints, energies, FTFP_BERT_HP_Data, zero, FTFP_BERT_HP_DataError);
   gre->SetName("Graph_FTFP_BERT_HP");
   gre->SetTitle("ArborPFA - FTFP_BERT_HP");
   gre->SetLineColor(kGreen+1);
   gre->SetMarkerColor(kGreen+1);
   gre->SetMarkerStyle(33);
   gre->SetMarkerSize(1.6);
   gre->Draw("p same");

   gre = new TGraphErrors(nPoints, energies, FTF_BIC_Data, zero, FTF_BIC_DataError);
   gre->SetName("Graph_FTF_BIC");
   gre->SetTitle("ArborPFA - FTF_BIC");
   gre->SetLineColor(kBlack);
   gre->SetMarkerColor(kBlack);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.6);
   gre->Draw("p same");

   TF1 *pLin = new TF1("lin", "x", 0, 90);
   pLin->SetLineColor(kBlack);
   pLin->SetLineWidth(1);
   pLin->SetLineStyle(2);
   pLin->Draw("same");

   TPaveText *pt = new TPaveText(0.55, 0.2, 0.93, 0.3, "tbNDC");
   pt->SetTextSize(0.05);
   pt->SetTextColor(kGray+2);
   pt->SetFillColor(0);
   pt->SetLineWidth(0);
   pt->SetBorderSize(0);
   pt->AddText("CALICE SDHCAL");
   pt->SetTextFont(62);
   pt->Draw();
   
   TLegend *leg = new TLegend(0.15,0.67,0.73,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillStyle(0);
   leg->SetFillColor(0);
   leg->SetTextSize(0.05);

   TLegendEntry *entry=0;
   entry=leg->AddEntry("Graph_arbor","ArborPFA - CERN SPS H6","p");
   entry->SetFillStyle(1001);
   entry->SetMarkerColor(kRed);
   entry->SetMarkerStyle(23);
   entry->SetMarkerSize(1);

   entry=leg->AddEntry("Graph_nopfa","No PFA - CERN SPS H6","p");
   entry->SetFillStyle(1001);
   entry->SetMarkerColor(kBlue);
   entry->SetMarkerStyle(29);
   entry->SetMarkerSize(1);

   entry=leg->AddEntry("Graph_FTFP_BERT_HP","ArborPFA - FTFP_BERT_HP","p");
   entry->SetFillStyle(1001);
   entry->SetMarkerColor(kGreen+1);
   entry->SetMarkerStyle(33);
   entry->SetMarkerSize(1);

   entry=leg->AddEntry("Graph_FTF_BIC","ArborPFA - FTF_BIC","p");
   entry->SetFillStyle(1001);
   entry->SetMarkerColor(kBlack);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(1);

   leg->Draw();

   r1_1->Modified();
   pCanvas->cd();

   TPad *r1_2 = new TPad("r1_2", "Energy_2",0.02,0,0.95,0.37);
   r1_2->Draw();
   r1_2->cd();
   r1_2->Range(-19.23077,-0.3993507,96.15385,0.25);
   r1_2->SetFillColor(0);
   r1_2->SetBorderMode(0);
   r1_2->SetBorderSize(2);
   r1_2->SetTickx(1);
   r1_2->SetTicky(1);
   r1_2->SetLeftMargin(0.1666667);
   r1_2->SetRightMargin(0.01);
   r1_2->SetTopMargin(0);
   r1_2->SetBottomMargin(0.23);
   r1_2->SetFrameLineWidth(1);
   r1_2->SetFrameBorderMode(0);

   TH1F *pH = new TH1F("pouette2", "", rangeUserXMax-rangeUserXMin, rangeUserXMin, rangeUserXMax);
   pH->SetMinimum(-0.22);
   pH->SetMaximum(0.22);
   pH->Draw();
   pH->GetXaxis()->SetTitle(graphXTitle.c_str());
   pH->GetXaxis()->SetLabelFont(42);
   pH->GetXaxis()->SetLabelSize(0.07);
   pH->GetXaxis()->SetTitleSize(0.1);
   pH->GetXaxis()->SetTitleOffset(1);
   pH->GetXaxis()->SetTitleFont(42);
   pH->GetYaxis()->SetTitle("#DeltaE/E_{beam} ");
   pH->GetYaxis()->SetLabelFont(42);
   pH->GetYaxis()->SetTitleSize(0.12);
   pH->GetYaxis()->SetTitleOffset(0.5);
   pH->GetYaxis()->SetTitleFont(42);
   pH->GetYaxis()->SetLabelSize(0.07);
   


   gre = new TGraphErrors(nPoints);//, energies, arborData, zero, arborDataError);
   gre->SetName("Graph_arborDev");
   gre->SetTitle("ArborPFA - CERN SPS H6");
   gre->SetLineColor(kRed);
   gre->SetMarkerColor(kRed);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.6);

   for(int i=0 ; i<nPoints ; i++)
   {
     gre->SetPoint(i, energies[i], (arborData[i]-energies[i]) / energies[i]);
     gre->SetPointError(i, 0, arborDataError[i]/energies[i]);
   }

   gre->Draw("p same");




   gre = new TGraphErrors(nPoints);//, energies, noPFAData, zero, noPFADataError);
   gre->SetName("Graph_nopfaDev");
   gre->SetTitle("No PFA - CERN SPS H6");
   gre->SetLineColor(kBlue);
   gre->SetMarkerColor(kBlue);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(1.6);
 
   for(int i=0 ; i<nPoints ; i++)
   {
     gre->SetPoint(i, energies[i], (noPFAData[i]-energies[i]) / energies[i]);
     gre->SetPointError(i, 0, noPFADataError[i]/energies[i]);
   }
   
   gre->Draw("p same");


   gre = new TGraphErrors(nPoints);//, energies, noPFAData, zero, noPFADataError);
   gre->SetName("Graph_FTFP_BERT_HP_Dev");
   gre->SetTitle("ArborPFA - FTFP_BERT_HP");
   gre->SetLineColor(kGreen+1);
   gre->SetMarkerColor(kGreen+1);
   gre->SetMarkerStyle(33);
   gre->SetMarkerSize(1.6);
 
   for(int i=0 ; i<nPoints ; i++)
   {
     gre->SetPoint(i, energies[i], (FTFP_BERT_HP_Data[i]-energies[i]) / energies[i]);
     gre->SetPointError(i, 0, FTFP_BERT_HP_DataError[i]/energies[i]);
   }
   
   gre->Draw("p same");



   gre = new TGraphErrors(nPoints);//, energies, noPFAData, zero, noPFADataError);
   gre->SetName("Graph_FTF_BIC_Dev");
   gre->SetTitle("ArborPFA - FTF_BIC");
   gre->SetLineColor(kBlack);
   gre->SetMarkerColor(kBlack);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.6);
 
   for(int i=0 ; i<nPoints ; i++)
   {
     gre->SetPoint(i, energies[i], (FTF_BIC_Data[i]-energies[i]) / energies[i]);
     gre->SetPointError(i, 0, FTF_BIC_DataError[i]/energies[i]);
   }
   
   gre->Draw("p same");



   r1_2->Modified();
   pCanvas->cd();

   pCanvas->Modified();
   pCanvas->cd();
   pCanvas->SetSelected(pCanvas);
}
