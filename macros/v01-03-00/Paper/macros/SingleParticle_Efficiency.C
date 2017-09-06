{
//=========Macro generated from canvas: cc1/Mean Purity
//=========  (Wed Dec 16 11:16:26 2015) by ROOT version5.34/05
   Int_t ci;   // for color index setting

   
   Int_t lineWidth = 2;
   Int_t lineStyle = 2;

   TCanvas *cc1 = new TCanvas("cc1", "Mean Efficiency",200, 52, 700, 650);
   cc1->SetFillColor(0);
   cc1->SetBorderMode(0);
   cc1->SetBorderSize(2);
   cc1->SetTickx(1);
   cc1->SetTicky(1);
   cc1->SetLeftMargin(0.15);
   cc1->SetRightMargin(0.03);
   cc1->SetTopMargin(0.05);
   cc1->SetBottomMargin(0.14);
   cc1->SetFrameBorderMode(0);
   cc1->SetFrameBorderMode(0);

   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("MeanPurityChargedMultiGraph");
   
   TGraphErrors *graph = new TGraphErrors(8);
   graph->SetName("Graph");
   graph->SetTitle("ArborPFA - CERN SPS H6");
   graph->SetLineStyle(lineStyle);
   graph->SetLineWidth(lineWidth);
   graph->SetMarkerStyle(21);
   graph->SetMarkerSize(1.6);
   graph->SetPoint(0,10,0.9754074);
   graph->SetPointError(0,0,0.006523975);
   graph->SetPoint(1,20,0.9675912);
   graph->SetPointError(1,0,0.003026969);
   graph->SetPoint(2,30,0.962257);
   graph->SetPointError(2,0,0.005463584);
   graph->SetPoint(3,40,0.9673604);
   graph->SetPointError(3,0,0.008698283);
   graph->SetPoint(4,50,0.9629018);
   graph->SetPointError(4,0,0.007945271);
   graph->SetPoint(5,60,0.9695662);
   graph->SetPointError(5,0,0.01222973);
   graph->SetPoint(6,70,0.9704362);
   graph->SetPointError(6,0,0.009308873);
   graph->SetPoint(7,80,0.9619195);
   graph->SetPointError(7,0,0.009935627);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","ArborPFA - CERN SPS H6",100,3,87);
   Graph_Graph1->SetDirectory(0);
   Graph_Graph1->SetStats(0);
   Graph_Graph1->GetXaxis()->SetLabelFont(42);
   Graph_Graph1->GetXaxis()->SetTitleSize(0.05);
   Graph_Graph1->GetXaxis()->SetTitleOffset(1.);
   Graph_Graph1->GetXaxis()->SetTitleFont(42);
   Graph_Graph1->GetYaxis()->SetLabelFont(42);
   Graph_Graph1->GetYaxis()->SetTitleSize(0.045);
   Graph_Graph1->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph1->GetYaxis()->SetTitleFont(42);
   Graph_Graph1->GetYaxis()->SetLabelSize(0.035);
   graph->SetHistogram(Graph_Graph1);
   
   multigraph->Add(graph,"");
   

   graph = new TGraphErrors(8);
   graph->SetName("Graph");
   graph->SetTitle("ArborPFA - FTFP_BERT_HP");
   ci = TColor::GetColor("#ff0000");
   graph->SetLineColor(ci);
   graph->SetLineStyle(lineStyle);
   graph->SetLineWidth(lineWidth);
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(23);
   graph->SetMarkerSize(1.6);
   graph->SetPoint(0,10,0.9825791);
   graph->SetPointError(0,0,0.009628747);
   graph->SetPoint(1,20,0.9787323);
   graph->SetPointError(1,0,0.009289974);
   graph->SetPoint(2,30,0.9766448);
   graph->SetPointError(2,0,0.009426415);
   graph->SetPoint(3,40,0.9726438);
   graph->SetPointError(3,0,0.009643511);
   graph->SetPoint(4,50,0.9737476);
   graph->SetPointError(4,0,0.00978841);
   graph->SetPoint(5,60,0.9697505);
   graph->SetPointError(5,0,0.009881635);
   graph->SetPoint(6,70,0.9660373);
   graph->SetPointError(6,0,0.01001403);
   graph->SetPoint(7,80,0.9650254);
   graph->SetPointError(7,0,0.01015556);
   
   TH1F *Graph_Graph2 = new TH1F("Graph_Graph2","ArborPFA - FTFP_BERT_HP",100,3,87);
   Graph_Graph2->SetDirectory(0);
   Graph_Graph2->SetStats(0);
   Graph_Graph2->GetXaxis()->SetLabelFont(42);
   Graph_Graph2->GetXaxis()->SetTitleSize(0.05);
   Graph_Graph2->GetXaxis()->SetTitleOffset(1.);
   Graph_Graph2->GetXaxis()->SetTitleFont(42);
   Graph_Graph2->GetYaxis()->SetLabelFont(42);
   Graph_Graph2->GetYaxis()->SetTitleSize(0.045);
   Graph_Graph2->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph2->GetYaxis()->SetTitleFont(42);
   Graph_Graph2->GetYaxis()->SetLabelSize(0.035);
   graph->SetHistogram(Graph_Graph2);
   
   multigraph->Add(graph,"");
   


   graph = new TGraphErrors(8);
   graph->SetName("Graph");
   graph->SetTitle("ArborPFA - FTF_BIC");
   ci = TColor::GetColor("#0000ff");
   graph->SetLineColor(ci);
   graph->SetLineStyle(lineStyle);
   graph->SetLineWidth(lineWidth);
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(29);
   graph->SetMarkerSize(1.6);
   graph->SetPoint(0,10,0.977373);
   graph->SetPointError(0,0,0.01366151);
   graph->SetPoint(1,20,0.9710354);
   graph->SetPointError(1,0,0.01341104);
   graph->SetPoint(2,30,0.9655939);
   graph->SetPointError(2,0,0.01349996);
   graph->SetPoint(3,40,0.9636544);
   graph->SetPointError(3,0,0.01374124);
   graph->SetPoint(4,50,0.9591894);
   graph->SetPointError(4,0,0.01411253);
   graph->SetPoint(5,60,0.9588658);
   graph->SetPointError(5,0,0.01423497);
   graph->SetPoint(6,70,0.9547688);
   graph->SetPointError(6,0,0.01455556);
   graph->SetPoint(7,80,0.9526848);
   graph->SetPointError(7,0,0.01462545);
   
   TH1F *Graph_Graph3 = new TH1F("Graph_Graph3","ArborPFA - FTF_BIC",100,3,87);
   Graph_Graph3->SetDirectory(0);
   Graph_Graph3->SetStats(0);
   Graph_Graph3->GetXaxis()->SetLabelFont(42);
   Graph_Graph3->GetXaxis()->SetTitleSize(0.05);
   Graph_Graph3->GetXaxis()->SetTitleOffset(1.);
   Graph_Graph3->GetXaxis()->SetTitleFont(42);
   Graph_Graph3->GetYaxis()->SetLabelFont(42);
   Graph_Graph3->GetYaxis()->SetTitleSize(0.045);
   Graph_Graph3->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph3->GetYaxis()->SetTitleFont(42);
   Graph_Graph3->GetYaxis()->SetLabelSize(0.035);
   graph->SetHistogram(Graph_Graph3);

   multigraph->Add(graph,"");




   multigraph->Draw("ap");
   multigraph->GetXaxis()->SetTitle("E_{beam} [GeV]");
   multigraph->GetXaxis()->SetLabelFont(42);
   multigraph->GetXaxis()->SetTitleSize(0.05);
   multigraph->GetXaxis()->SetTitleOffset(1.);
   multigraph->GetXaxis()->SetTitleFont(42);
   multigraph->GetXaxis()->SetRangeUser(0,90);
   multigraph->GetYaxis()->SetTitle("Hit clustering efficiency #epsilon_{s}");
   multigraph->GetYaxis()->SetLabelFont(42);
   multigraph->GetYaxis()->SetTitleSize(0.045);
   multigraph->GetYaxis()->SetTitleOffset(1.3);
   multigraph->GetYaxis()->SetTitleFont(42);
   multigraph->GetYaxis()->SetLabelSize(0.035);
   multigraph->GetYaxis()->SetRangeUser(0.7,1);


   TPaveText *pt = new TPaveText(0.3, 0.2, 0.93, 0.3, "tbNDC");
   pt->SetTextSize(0.05);
   pt->SetTextColor(kGray+2);
   pt->SetFillColor(0);
   pt->SetLineWidth(0);
   pt->SetBorderSize(0);
   pt->AddText("CALICE SDHCAL");
   pt->SetTextFont(62);
   pt->Draw();



   TLegend *leg = new TLegend(0.3,0.3,0.88,0.5,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   leg->SetTextSize(0.04);

   TLegendEntry *entry=leg->AddEntry("Graph_Graph1","ArborPFA - CERN SPS H6","p");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineWidth(4);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1.6);

   entry=leg->AddEntry("Graph_Graph2","ArborPFA - FTFP_BERT_HP","p");
   entry->SetFillStyle(1001);
   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(23);
   entry->SetMarkerSize(1.6);

   entry=leg->AddEntry("Graph_Graph3","ArborPFA - FTF_BIC","p");
   entry->SetFillStyle(1001);
   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(29);
   entry->SetMarkerSize(1.6);

   leg->Draw();

   cc1->Modified();
   cc1->cd();
   cc1->SetSelected(cc1);
}
