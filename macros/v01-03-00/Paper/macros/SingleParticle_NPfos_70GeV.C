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

  TCanvas *cc5 = new TCanvas("cc5", "N pfo at 70 GeV", 200, 52, 700, 650);
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
   
   TH1F *npfo70GeV_TEST_BEAM__1 = new TH1F("npfo70GeV_TEST_BEAM","",11,0,10);
   npfo70GeV_TEST_BEAM__1->SetBinContent(2,0.6761699);
   npfo70GeV_TEST_BEAM__1->SetBinContent(3,0.2633449);
   npfo70GeV_TEST_BEAM__1->SetBinContent(4,0.05311958);
   npfo70GeV_TEST_BEAM__1->SetBinContent(5,0.006759099);
   npfo70GeV_TEST_BEAM__1->SetBinContent(6,0.0005199307);
   npfo70GeV_TEST_BEAM__1->SetBinContent(7,8.665511e-05);
   npfo70GeV_TEST_BEAM__1->SetBinContent(2,0.8777167);
   npfo70GeV_TEST_BEAM__1->SetBinContent(3,0.1131574);
   npfo70GeV_TEST_BEAM__1->SetBinContent(4,0.008640278);
   npfo70GeV_TEST_BEAM__1->SetBinContent(5,0.0004764523);
   npfo70GeV_TEST_BEAM__1->SetBinContent(6,9.162543e-06);
   npfo70GeV_TEST_BEAM__1->SetMinimum(0);
   npfo70GeV_TEST_BEAM__1->SetMaximum(1);
   npfo70GeV_TEST_BEAM__1->SetEntries(11540);
   npfo70GeV_TEST_BEAM__1->SetDirectory(0);
   npfo70GeV_TEST_BEAM__1->SetLineWidth(2);
   npfo70GeV_TEST_BEAM__1->GetXaxis()->SetLabelFont(42);
   npfo70GeV_TEST_BEAM__1->GetXaxis()->SetTitleSize(0.05);
   npfo70GeV_TEST_BEAM__1->GetXaxis()->SetTitleOffset(1);
   npfo70GeV_TEST_BEAM__1->GetXaxis()->SetTitleFont(42);
   npfo70GeV_TEST_BEAM__1->GetXaxis()->SetTitle("N_{pfos}");
   npfo70GeV_TEST_BEAM__1->GetYaxis()->SetLabelFont(42);
   npfo70GeV_TEST_BEAM__1->GetYaxis()->SetTitleSize(0.05);
   npfo70GeV_TEST_BEAM__1->GetYaxis()->SetTitleOffset(1);
   npfo70GeV_TEST_BEAM__1->GetYaxis()->SetTitleFont(42);
   npfo70GeV_TEST_BEAM__1->GetYaxis()->SetLabelSize(0.035);
   npfo70GeV_TEST_BEAM__1->GetYaxis()->SetTitle("# events (normalized to unity)");
   npfo70GeV_TEST_BEAM__1->GetZaxis()->SetLabelFont(42);
   npfo70GeV_TEST_BEAM__1->GetZaxis()->SetTitleSize(0.035);
   npfo70GeV_TEST_BEAM__1->GetZaxis()->SetTitleFont(42);
   npfo70GeV_TEST_BEAM__1->Draw("");
   
   TH1F *npfo70GeV_FTFP_BERT_HP__2 = new TH1F("npfo70GeV_FTFP_BERT_HP","",11,0,10);
   npfo70GeV_FTFP_BERT_HP__2->SetBinContent(2,0.8459687);
   npfo70GeV_FTFP_BERT_HP__2->SetBinContent(3,0.1377858);
   npfo70GeV_FTFP_BERT_HP__2->SetBinContent(4,0.01504212);
   npfo70GeV_FTFP_BERT_HP__2->SetBinContent(5,0.001203369);
   npfo70GeV_FTFP_BERT_HP__2->SetEntries(9972);
   npfo70GeV_FTFP_BERT_HP__2->SetDirectory(0);
   npfo70GeV_FTFP_BERT_HP__2->SetLineColor(2);
   npfo70GeV_FTFP_BERT_HP__2->SetLineWidth(2);
   npfo70GeV_FTFP_BERT_HP__2->GetXaxis()->SetLabelFont(42);
   npfo70GeV_FTFP_BERT_HP__2->GetXaxis()->SetTitleSize(0.035);
   npfo70GeV_FTFP_BERT_HP__2->GetXaxis()->SetTitleOffset(1.5);
   npfo70GeV_FTFP_BERT_HP__2->GetXaxis()->SetTitleFont(42);
   npfo70GeV_FTFP_BERT_HP__2->GetYaxis()->SetLabelFont(42);
   npfo70GeV_FTFP_BERT_HP__2->GetYaxis()->SetTitleSize(0.035);
   npfo70GeV_FTFP_BERT_HP__2->GetYaxis()->SetTitleOffset(1.5);
   npfo70GeV_FTFP_BERT_HP__2->GetYaxis()->SetTitleFont(42);
   npfo70GeV_FTFP_BERT_HP__2->GetZaxis()->SetLabelFont(42);
   npfo70GeV_FTFP_BERT_HP__2->GetZaxis()->SetTitleSize(0.035);
   npfo70GeV_FTFP_BERT_HP__2->GetZaxis()->SetTitleFont(42);
   npfo70GeV_FTFP_BERT_HP__2->Draw("same");
   
   TH1F *npfo70GeV_FTF_BIC__3 = new TH1F("npfo70GeV_FTF_BIC","",11,0,10);
   npfo70GeV_FTF_BIC__3->SetBinContent(2,0.9021583);
   npfo70GeV_FTF_BIC__3->SetBinContent(3,0.09136691);
   npfo70GeV_FTF_BIC__3->SetBinContent(4,0.006294964);
   npfo70GeV_FTF_BIC__3->SetBinContent(5,0.0001798561);
   npfo70GeV_FTF_BIC__3->SetEntries(5560);
   npfo70GeV_FTF_BIC__3->SetDirectory(0);
   npfo70GeV_FTF_BIC__3->SetLineColor(3);
   npfo70GeV_FTF_BIC__3->SetLineWidth(2);
   npfo70GeV_FTF_BIC__3->GetXaxis()->SetLabelFont(42);
   npfo70GeV_FTF_BIC__3->GetXaxis()->SetTitleSize(0.035);
   npfo70GeV_FTF_BIC__3->GetXaxis()->SetTitleOffset(1.5);
   npfo70GeV_FTF_BIC__3->GetXaxis()->SetTitleFont(42);
   npfo70GeV_FTF_BIC__3->GetYaxis()->SetLabelFont(42);
   npfo70GeV_FTF_BIC__3->GetYaxis()->SetTitleSize(0.035);
   npfo70GeV_FTF_BIC__3->GetYaxis()->SetTitleOffset(1.5);
   npfo70GeV_FTF_BIC__3->GetYaxis()->SetTitleFont(42);
   npfo70GeV_FTF_BIC__3->GetZaxis()->SetLabelFont(42);
   npfo70GeV_FTF_BIC__3->GetZaxis()->SetTitleSize(0.035);
   npfo70GeV_FTF_BIC__3->GetZaxis()->SetTitleFont(42);
   npfo70GeV_FTF_BIC__3->Draw("same");

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
   leg->SetHeader("Single pi- 70 GeV");
   leg->SetBorderSize(0);
   leg->SetLineColor(0);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   leg->SetTextSize(0.04);
   leg->SetMargin(0.15);
   
   TLegendEntry *entry=leg->AddEntry("npfo70GeV_TEST_BEAM","ArborPFA - CERN SPS H6","l");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);

   entry=leg->AddEntry("npfo70GeV_FTFP_BERT_HP","ArborPFA - FTFP_BERT_HP","l");
   entry->SetFillStyle(1001);
   entry->SetLineColor(2);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);

   entry=leg->AddEntry("npfo70GeV_FTF_BIC","ArborPFA - FTF_BIC","l");
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
