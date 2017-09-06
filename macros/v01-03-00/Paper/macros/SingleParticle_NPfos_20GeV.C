{
//=========Macro generated from canvas: cc5/N pfo at 20 GeV
//=========  (Thu Dec 17 09:52:29 2015) by ROOT version5.34/05
   // TCanvas *cc5 = new TCanvas("cc5", "N pfo at 20 GeV",11,52,700,500);
   // cc5->Range(-1.829268,-0.1728395,10.36585,1.061728);
   // cc5->SetFillColor(0);
   // cc5->SetBorderMode(0);
   // cc5->SetBorderSize(2);
   // cc5->SetTickx(1);
   // cc5->SetTicky(1);
   // cc5->SetLeftMargin(0.15);
   // cc5->SetRightMargin(0.03);
   // cc5->SetTopMargin(0.05);
   // cc5->SetBottomMargin(0.14);
   // cc5->SetFrameBorderMode(0);
   // cc5->SetFrameBorderMode(0);

  TCanvas *cc5 = new TCanvas("cc5", "N pfo at 20 GeV", 200, 52, 700, 650);
   cc5->SetFillColor(0);
   cc5->SetBorderMode(0);
   cc5->SetBorderSize(2);
   cc5->SetTickx(1);
   cc5->SetTicky(1);
   cc5->SetLeftMargin(0.15);
   cc5->SetRightMargin(0.03);
   cc5->SetTopMargin(0.05);
   cc5->SetBottomMargin(0.14);
   cc5->SetFrameBorderMode(0);
   cc5->SetFrameBorderMode(0);
   gStyle->SetOptStat(0);
   
   TH1F *npfo20GeV_TEST_BEAM__4 = new TH1F("npfo20GeV_TEST_BEAM__4","",11,0,10);
   npfo20GeV_TEST_BEAM__4->SetBinContent(2,0.8777167);
   npfo20GeV_TEST_BEAM__4->SetBinContent(3,0.1131574);
   npfo20GeV_TEST_BEAM__4->SetBinContent(4,0.008640278);
   npfo20GeV_TEST_BEAM__4->SetBinContent(5,0.0004764523);
   npfo20GeV_TEST_BEAM__4->SetBinContent(6,9.162543e-06);
   npfo20GeV_TEST_BEAM__4->SetMinimum(0);
   npfo20GeV_TEST_BEAM__4->SetMaximum(1);
   npfo20GeV_TEST_BEAM__4->SetEntries(109140);
   npfo20GeV_TEST_BEAM__4->SetDirectory(0);
   npfo20GeV_TEST_BEAM__4->SetLineWidth(2);
   
   // text = ptstats->AddText("Mean  =  1.132");
   // text = ptstats->AddText("RMS   = 0.3671");

   npfo20GeV_TEST_BEAM__4->GetXaxis()->SetLabelFont(42);
   npfo20GeV_TEST_BEAM__4->GetXaxis()->SetTitleSize(0.05);
   npfo20GeV_TEST_BEAM__4->GetXaxis()->SetTitleOffset(1);
   npfo20GeV_TEST_BEAM__4->GetXaxis()->SetTitleFont(42);
   npfo20GeV_TEST_BEAM__4->GetXaxis()->SetTitle("N_{pfos}");
   npfo20GeV_TEST_BEAM__4->GetYaxis()->SetLabelFont(42);
   npfo20GeV_TEST_BEAM__4->GetYaxis()->SetTitleSize(0.05);
   npfo20GeV_TEST_BEAM__4->GetYaxis()->SetTitleOffset(1);
   npfo20GeV_TEST_BEAM__4->GetYaxis()->SetTitleFont(42);
   npfo20GeV_TEST_BEAM__4->GetYaxis()->SetLabelSize(0.035);
   npfo20GeV_TEST_BEAM__4->GetYaxis()->SetTitle("# events (normalized to unity)");

   npfo20GeV_TEST_BEAM__4->GetZaxis()->SetLabelFont(42);
   npfo20GeV_TEST_BEAM__4->GetZaxis()->SetTitleSize(0.035);
   npfo20GeV_TEST_BEAM__4->GetZaxis()->SetTitleFont(42);
   npfo20GeV_TEST_BEAM__4->Draw("");
   
   TH1F *npfo20GeV_FTFP_BERT_HP__5 = new TH1F("npfo20GeV_FTFP_BERT_HP__5","",11,0,10);
   npfo20GeV_FTFP_BERT_HP__5->SetBinContent(2,0.9288858);
   npfo20GeV_FTFP_BERT_HP__5->SetBinContent(3,0.0668853);
   npfo20GeV_FTFP_BERT_HP__5->SetBinContent(4,0.004228877);
   npfo20GeV_FTFP_BERT_HP__5->SetEntries(11587);
   npfo20GeV_FTFP_BERT_HP__5->SetDirectory(0);
   npfo20GeV_FTFP_BERT_HP__5->SetLineColor(2);
   npfo20GeV_FTFP_BERT_HP__5->SetLineWidth(2);
   npfo20GeV_FTFP_BERT_HP__5->GetXaxis()->SetLabelFont(42);
   npfo20GeV_FTFP_BERT_HP__5->GetXaxis()->SetTitleSize(0.035);
   npfo20GeV_FTFP_BERT_HP__5->GetXaxis()->SetTitleOffset(1.5);
   npfo20GeV_FTFP_BERT_HP__5->GetXaxis()->SetTitleFont(42);
   npfo20GeV_FTFP_BERT_HP__5->GetYaxis()->SetLabelFont(42);
   npfo20GeV_FTFP_BERT_HP__5->GetYaxis()->SetTitleSize(0.035);
   npfo20GeV_FTFP_BERT_HP__5->GetYaxis()->SetTitleOffset(1.5);
   npfo20GeV_FTFP_BERT_HP__5->GetYaxis()->SetTitleFont(42);
   npfo20GeV_FTFP_BERT_HP__5->GetZaxis()->SetLabelFont(42);
   npfo20GeV_FTFP_BERT_HP__5->GetZaxis()->SetTitleSize(0.035);
   npfo20GeV_FTFP_BERT_HP__5->GetZaxis()->SetTitleFont(42);
   npfo20GeV_FTFP_BERT_HP__5->Draw("same");
   
   TH1F *npfo20GeV_FTF_BIC__6 = new TH1F("npfo20GeV_FTF_BIC__6","",11,0,10);
   npfo20GeV_FTF_BIC__6->SetBinContent(2,0.9021583);
   npfo20GeV_FTF_BIC__6->SetBinContent(3,0.09136691);
   npfo20GeV_FTF_BIC__6->SetBinContent(4,0.006294964);
   npfo20GeV_FTF_BIC__6->SetBinContent(5,0.0001798561);
   npfo20GeV_FTF_BIC__6->SetEntries(5560);
   npfo20GeV_FTF_BIC__6->SetDirectory(0);
   npfo20GeV_FTF_BIC__6->SetLineColor(3);
   npfo20GeV_FTF_BIC__6->SetLineWidth(2);
   npfo20GeV_FTF_BIC__6->GetXaxis()->SetLabelFont(42);
   npfo20GeV_FTF_BIC__6->GetXaxis()->SetTitleSize(0.035);
   npfo20GeV_FTF_BIC__6->GetXaxis()->SetTitleOffset(1.5);
   npfo20GeV_FTF_BIC__6->GetXaxis()->SetTitleFont(42);
   npfo20GeV_FTF_BIC__6->GetYaxis()->SetLabelFont(42);
   npfo20GeV_FTF_BIC__6->GetYaxis()->SetTitleSize(0.035);
   npfo20GeV_FTF_BIC__6->GetYaxis()->SetTitleOffset(1.5);
   npfo20GeV_FTF_BIC__6->GetYaxis()->SetTitleFont(42);
   npfo20GeV_FTF_BIC__6->GetZaxis()->SetLabelFont(42);
   npfo20GeV_FTF_BIC__6->GetZaxis()->SetTitleSize(0.035);
   npfo20GeV_FTF_BIC__6->GetZaxis()->SetTitleFont(42);
   npfo20GeV_FTF_BIC__6->Draw("same");

   TPaveText *pt = new TPaveText(0.3, 0.3, 0.93, 0.4, "tbNDC");
   pt->SetTextSize(0.05);
   pt->SetTextColor(kGray+2);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetLineWidth(0);
   pt->SetBorderSize(0);
   pt->AddText("CALICE SDHCAL");
   pt->SetTextFont(62);
   pt->Draw();

   TLegend *leg = new TLegend(0.3,0.65,0.88,0.85,NULL,"brNDC");
   leg->SetHeader("Single pi- 20 GeV");
   leg->SetBorderSize(0);
   leg->SetLineColor(0);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   leg->SetTextSize(0.04);
   leg->SetMargin(0.15);
   
   TLegendEntry *entry=leg->AddEntry("npfo20GeV_TEST_BEAM","ArborPFA - CERN SPS H6","l");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);

   entry=leg->AddEntry("npfo20GeV_FTFP_BERT_HP","ArborPFA - FTFP_BERT_HP","l");
   entry->SetFillStyle(1001);
   entry->SetLineColor(2);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);

   entry=leg->AddEntry("npfo20GeV_FTF_BIC","ArborPFA - FTF_BIC","l");
   entry->SetFillStyle(1001);
   entry->SetLineColor(3);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);

   leg->Draw();


   cc5->Modified();
   cc5->cd();
   cc5->SetSelected(cc5);
}
