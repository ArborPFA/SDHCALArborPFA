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

   std::string graphYTitle = "N_{pfos}";
   std::string graphXTitle = "E_{beam} [GeV]";
   double rangeUserXMin = 0;
   double rangeUserXMax = 90;
   double rangeUserYMin = 0.5;
   double rangeUserYMax = 2;

   TMultiGraph *pMultiGraph = new TMultiGraph();

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
   
   TGraphErrors *gre =0;

   gre = new TGraphErrors(nPoints);
   // gre = new TGraphErrors(nPoints, energies, arborData, zero, zero);
   gre->SetName("Graph_arborTB");
   gre->SetTitle("");
   gre->SetLineColor(kBlack);
   gre->SetMarkerColor(kBlack);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.6);
   gre->SetPoint(0,10,1.069674);
   gre->SetPointError(0,0,0.006523975);
   gre->SetPoint(1,20,1.131904);
   gre->SetPointError(1,0,0.003026969);
   gre->SetPoint(2,30,1.190896);
   gre->SetPointError(2,0,0.005463584);
   gre->SetPoint(3,40,1.228494);
   gre->SetPointError(3,0,0.008698283);
   gre->SetPoint(4,50,1.277445);
   gre->SetPointError(4,0,0.007945271);
   gre->SetPoint(5,60,1.342656);
   gre->SetPointError(5,0,0.01222973);
   gre->SetPoint(6,70,1.392374);
   gre->SetPointError(6,0,0.009308873);
   gre->SetPoint(7,80,1.439882);
   gre->SetPointError(7,0,0.009935627);
   pMultiGraph->Add(gre);
   // gre->GetXaxis()->SetTitle(graphXTitle.c_str());
   // gre->GetXaxis()->SetLabelFont(42);
   // gre->GetXaxis()->SetTitleSize(0.05);
   // gre->GetXaxis()->SetTitleOffset(1.);
   // gre->GetXaxis()->SetTitleFont(42);
   // gre->GetXaxis()->SetRangeUser(rangeUserXMin, rangeUserXMax);
   // gre->GetYaxis()->SetTitle(graphYTitle.c_str());
   // gre->GetYaxis()->SetLabelFont(42);
   // gre->GetYaxis()->SetTitleSize(0.05);
   // gre->GetYaxis()->SetTitleOffset(1);
   // gre->GetYaxis()->SetTitleFont(42);
   // gre->GetYaxis()->SetRangeUser(rangeUserYMin, rangeUserYMax);


   gre = new TGraphErrors(nPoints);
   gre->SetName("Graph_arbor_FTFP_BERT_HP");
   gre->SetTitle("");
   gre->SetLineColor(TColor::GetColor("#ff0000"));
   gre->SetMarkerColor(TColor::GetColor("#ff0000"));
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.6);
   gre->SetPoint(0,10,1.043575);
   gre->SetPointError(0,0,0.009628747);
   gre->SetPoint(1,20,1.075343);
   gre->SetPointError(1,0,0.009289974);
   gre->SetPoint(2,30,1.097921);
   gre->SetPointError(2,0,0.009426415);
   gre->SetPoint(3,40,1.116805);
   gre->SetPointError(3,0,0.009643511);
   gre->SetPoint(4,50,1.128677);
   gre->SetPointError(4,0,0.00978841);
   gre->SetPoint(5,60,1.149009);
   gre->SetPointError(5,0,0.009881635);
   gre->SetPoint(6,70,1.17148);
   gre->SetPointError(6,0,0.01001403);
   gre->SetPoint(7,80,1.175433);
   gre->SetPointError(7,0,0.01015556);

   // gre->GetXaxis()->SetTitle(graphXTitle.c_str());
   // gre->GetXaxis()->SetLabelFont(42);
   // gre->GetXaxis()->SetTitleSize(0.05);
   // gre->GetXaxis()->SetTitleOffset(1.);
   // gre->GetXaxis()->SetTitleFont(42);
   // gre->GetXaxis()->SetRangeUser(rangeUserXMin, rangeUserXMax);
   // gre->GetYaxis()->SetTitle(graphYTitle.c_str());
   // gre->GetYaxis()->SetLabelFont(42);
   // gre->GetYaxis()->SetTitleSize(0.05);
   // gre->GetYaxis()->SetTitleOffset(1);
   // gre->GetYaxis()->SetTitleFont(42);
   // gre->GetYaxis()->SetRangeUser(rangeUserYMin, rangeUserYMax);
   pMultiGraph->Add(gre);

   gre = new TGraphErrors(nPoints);
   gre->SetName("Graph_arbor_FTF_BIC");
   gre->SetTitle("");
   gre->SetLineColor(TColor::GetColor("#0000ff"));
   gre->SetMarkerColor(TColor::GetColor("#0000ff"));
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(1.6);
   gre->SetPoint(0,10,1.061217);
   gre->SetPointError(0,0,0.01366151);
   gre->SetPoint(1,20,1.104496);
   gre->SetPointError(1,0,0.01341104);
   gre->SetPoint(2,30,1.148533);
   gre->SetPointError(2,0,0.01349996);
   gre->SetPoint(3,40,1.172017);
   gre->SetPointError(3,0,0.01374124);
   gre->SetPoint(4,50,1.196375);
   gre->SetPointError(4,0,0.01411253);
   gre->SetPoint(5,60,1.212563);
   gre->SetPointError(5,0,0.01423497);
   gre->SetPoint(6,70,1.236017);
   gre->SetPointError(6,0,0.01455556);
   gre->SetPoint(7,80,1.255615);
   gre->SetPointError(7,0,0.01462545);
   pMultiGraph->Add(gre);
   // gre->GetXaxis()->SetTitle(graphXTitle.c_str());
   // gre->GetXaxis()->SetLabelFont(42);
   // gre->GetXaxis()->SetTitleSize(0.05);
   // gre->GetXaxis()->SetTitleOffset(1.);
   // gre->GetXaxis()->SetTitleFont(42);
   // gre->GetXaxis()->SetRangeUser(rangeUserXMin, rangeUserXMax);
   // gre->GetYaxis()->SetTitle(graphYTitle.c_str());
   // gre->GetYaxis()->SetLabelFont(42);
   // gre->GetYaxis()->SetTitleSize(0.05);
   // gre->GetYaxis()->SetTitleOffset(1);
   // gre->GetYaxis()->SetTitleFont(42);
   // gre->GetYaxis()->SetRangeUser(rangeUserYMin, rangeUserYMax);

   pMultiGraph->Draw("ap");
   pMultiGraph->GetXaxis()->SetTitle("E_{beam} [GeV]");
   pMultiGraph->GetXaxis()->SetRange(0,101);
   pMultiGraph->GetXaxis()->SetLabelFont(42);
   pMultiGraph->GetXaxis()->SetTitleSize(0.05);
   pMultiGraph->GetXaxis()->SetTitleOffset(1);
   pMultiGraph->GetXaxis()->SetTitleFont(42);
   pMultiGraph->GetXaxis()->SetRangeUser(0, 90);
   pMultiGraph->GetYaxis()->SetTitle("N_{pfo}");
   pMultiGraph->GetYaxis()->SetLabelFont(42);
   pMultiGraph->GetYaxis()->SetTitleSize(0.05);
   pMultiGraph->GetYaxis()->SetTitleOffset(1);
   pMultiGraph->GetYaxis()->SetTitleFont(42);
   pMultiGraph->GetYaxis()->SetLabelSize(0.035);
   pMultiGraph->GetYaxis()->SetRangeUser(0.5, 2);

   TPaveText *pt = new TPaveText(0.3, 0.2, 0.93, 0.3, "tbNDC");
   pt->SetTextSize(0.05);
   pt->SetTextColor(kGray+2);
   pt->SetFillColor(0);
   pt->SetLineWidth(0);
   pt->SetBorderSize(0);
   pt->AddText("CALICE SDHCAL");
   pt->SetTextFont(62);
   pt->Draw();
   


   TLegend *leg = new TLegend(0.3,0.7,0.88,0.85,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(0);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   leg->SetTextSize(0.04);

   TLegendEntry *entry=0;
   entry=leg->AddEntry("Graph_arbor","ArborPFA - CERN SPS H6","p");
   entry->SetMarkerColor(kBlack);
   entry->SetMarkerStyle(21);

   entry->SetMarkerSize(1.6);

   entry=leg->AddEntry("Graph_FTFP_BERT_HP","ArborPFA - FTFP_BERT_HP","p");
   entry->SetMarkerColor(TColor::GetColor("#ff0000"));
   entry->SetMarkerStyle(23);
   entry->SetMarkerSize(1.6);

   entry=leg->AddEntry("Graph_FTF_BIC","ArborPFA - FTF_BIC","p");
   entry->SetMarkerColor(TColor::GetColor("#0000ff"));
   entry->SetMarkerStyle(29);
   entry->SetMarkerSize(1.6);

   leg->Draw();

   pCanvas->Modified();
   pCanvas->cd();
   pCanvas->SetSelected(pCanvas);
}
