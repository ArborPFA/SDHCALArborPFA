#include "OverlayAnalysis.h"

// -- root headers
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TPaveText.h>
#include <TLegend.h>

// -- std headers
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <sstream>

//--------------------------------------------------------------------------------------------------------------------

std::string DataTypeToDrawableString(DataType dataType)
{
	switch(dataType)
	{
		case TB_SPS_AUG_2012:
			return "CERN SPS H6";
		case FTFP_BERT_HP:
			return "FTFP_BERT_HP";
		case FTF_BIC:
			return "FTF_BIC";
		default:
			return "UNKNOWN";
	}
}

//--------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------

DrawAttributeMapping::DrawAttributeMapping(DataType dataType) :
		m_dataType(dataType)
{
	switch(dataType)
	{
		case FTFP_BERT_HP:
			m_drawAttributeMap[MARKER_COLOR] = kRed;
			m_drawAttributeMap[MARKER_STYLE] = 23;
			m_drawAttributeMap[LINE_COLOR] = kRed;
			break;
		case FTF_BIC:
			m_drawAttributeMap[MARKER_STYLE] = 29;
			m_drawAttributeMap[MARKER_COLOR] = kBlue;
			m_drawAttributeMap[LINE_COLOR] = kBlue;
			break;
		default:
			m_drawAttributeMap[MARKER_STYLE] = 21;
			m_drawAttributeMap[MARKER_COLOR] = kBlack;
			m_drawAttributeMap[LINE_COLOR] = kBlack;
	}

	m_drawAttributeMap[LINE_STYLE] = 0;
	m_drawAttributeMap[LINE_WIDTH] = 1;
	m_drawAttributeMap[MARKER_SIZE] = 1.6;
	m_drawAttributeMap[FILL_COLOR] = 0;
	m_drawAttributeMap[FILL_STYLE] = 0;
}

//--------------------------------------------------------------------------------------------------------------------

float DrawAttributeMapping::GetAttribute(DrawAttribute attribute) const
{
	DrawAttributeMap::const_iterator findIter = m_drawAttributeMap.find(attribute);

	if(findIter == m_drawAttributeMap.end())
		return 1;

	return findIter->second;
}

//--------------------------------------------------------------------------------------------------------------------

TGraphErrors *DrawAttributeMapping::ConfigureGraph(TGraphErrors *pGraph)
{
	if(NULL == pGraph)
		return NULL;

	pGraph->SetName(DataTypeToDrawableString(m_dataType).c_str());

	pGraph->SetMarkerStyle(this->GetAttribute(MARKER_STYLE));
	pGraph->SetMarkerColor(this->GetAttribute(MARKER_COLOR));
	pGraph->SetMarkerSize(this->GetAttribute(MARKER_SIZE));
	pGraph->SetLineColor(this->GetAttribute(LINE_COLOR));
	pGraph->SetLineStyle(this->GetAttribute(LINE_STYLE));
	pGraph->SetLineWidth(this->GetAttribute(LINE_WIDTH));
	pGraph->SetFillColor(this->GetAttribute(FILL_COLOR));
	pGraph->SetFillStyle(this->GetAttribute(FILL_STYLE));

	return pGraph;
}

//--------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------

TreeAnalyzer::TreeAnalyzer(TTree *pTree) :
	m_pTree(0),
	m_energy(0),
	m_momentum(0),
	m_nTracks(0),
	m_nClusters(0),
	m_charge(0),
	m_mass(0),
	m_pid(0),
	m_nHit(0),
	m_nHit1(0),
	m_nHit2(0),
	m_nHit3(0),
	m_mcParticleEnergy1(0),
	m_mcParticleEnergy2(0),
	m_lcioFlagType1(0),
	m_lcioFlagType2(0),
	m_lcioFlagType3(0)
{
	if (pTree == 0)
		throw std::invalid_argument("Tree is NULL !");

	Init(pTree);
}

//--------------------------------------------------------------------------------------------------------------------

TreeAnalyzer::~TreeAnalyzer()
{
	if (!m_pTree)
		return;

	delete m_pTree->GetCurrentFile();
}

//--------------------------------------------------------------------------------------------------------------------

Int_t TreeAnalyzer::GetEntry(Long64_t entry)
{
	if (!m_pTree)
		return 0;

	return m_pTree->GetEntry(entry);
}

//--------------------------------------------------------------------------------------------------------------------

Long64_t TreeAnalyzer::LoadTree(Long64_t entry)
{
   if (!m_pTree)
	   return -5;

   return m_pTree->LoadTree(entry);
}

//--------------------------------------------------------------------------------------------------------------------

void TreeAnalyzer::Init(TTree *pTree)
{
	m_pTree = pTree;

	m_pTree->SetBranchAddress("nPfos", &m_nPfos, &b_nPfos);
	m_pTree->SetBranchAddress("nNeutralPfos", &m_nNeutralPfos, &b_nNeutralPfos);
	m_pTree->SetBranchAddress("nChargedPfos", &m_nChargedPfos, &b_nChargedPfos);
	m_pTree->SetBranchAddress("neutralEnergy", &m_neutralEnergy, &b_neutralEnergy);
	m_pTree->SetBranchAddress("chargedEnergy", &m_chargedEnergy, &b_chargedEnergy);
	m_pTree->SetBranchAddress("energy", &m_energy, &b_energy);
	m_pTree->SetBranchAddress("momentum", &m_momentum, &b_momentum);
	m_pTree->SetBranchAddress("nTracks", &m_nTracks, &b_nTracks);
	m_pTree->SetBranchAddress("nClusters", &m_nClusters, &b_nClusters);
	m_pTree->SetBranchAddress("charge", &m_charge, &b_charge);
	m_pTree->SetBranchAddress("mass", &m_mass, &b_mass);
	m_pTree->SetBranchAddress("pid", &m_pid, &b_pid);
	m_pTree->SetBranchAddress("nHit", &m_nHit, &b_nHit);
	m_pTree->SetBranchAddress("nHit1", &m_nHit1, &b_nHit1);
	m_pTree->SetBranchAddress("nHit2", &m_nHit2, &b_nHit2);
	m_pTree->SetBranchAddress("nHit3", &m_nHit3, &b_nHit3);
	m_pTree->SetBranchAddress("mcParticleEnergy1", &m_mcParticleEnergy1, &b_mcParticleEnergy1);
	m_pTree->SetBranchAddress("mcParticleEnergy2", &m_mcParticleEnergy2, &b_mcParticleEnergy2);
	m_pTree->SetBranchAddress("lcioFlagType1", &m_lcioFlagType1, &b_lcioFlagType1);
	m_pTree->SetBranchAddress("lcioFlagType2", &m_lcioFlagType2, &b_lcioFlagType2);
	m_pTree->SetBranchAddress("lcioFlagType3", &m_lcioFlagType3, &b_lcioFlagType3);
}

//--------------------------------------------------------------------------------------------------------------------

void TreeAnalyzer::Loop(int pointID, double xGraph, GraphMap &graphMap)
{
	if (m_pTree == 0)
		return;

	Long64_t nEntries = m_pTree->GetEntriesFast();

	unsigned int nProcessedEvents = 0;
	float neutralRecPercentage = 0.f;
	float meanNPfos = 0.f;
	float meanNeutralPurity = 0.f;
	float meanNeutralEfficiency = 0.f;
	float meanEnergyDifferenceEfficient = 0.f;

	for (Long64_t jentry=0 ; jentry<nEntries ; jentry++)
	{
		Long64_t ientry = this->LoadTree(jentry);

		if (ientry < 0)
			break;

		m_pTree->GetEntry(jentry);

		if(1 != m_nChargedPfos)
		{
			std::cout << "No charged particle in this event !" << std::endl;
			continue;
		}

		nProcessedEvents++;

		meanNPfos += m_nPfos;

		if(m_nNeutralPfos > 0)
			neutralRecPercentage++;

		unsigned int totalHitType1 = 0;
		unsigned int totalHitType2 = 0;
		unsigned int totalHitType3 = 0;
		float originalNHitNeutral = 0.f;
		float reconstructedNHitNeutral = 0.f;
		float reconstructedNHitGoodNeutral = 0.f;
		float reconstructedNHitBadNeutral = 0.f;

		bool neutralFound = false;

		// analyze pfos and extract the purity/efficiency
		for(int p=0 ; p<m_nPfos ; p++)
		{
			totalHitType1 += m_lcioFlagType1->at(p);
			totalHitType2 += m_lcioFlagType2->at(p);
			totalHitType3 += m_lcioFlagType3->at(p);

			// neutral case
			if(m_charge->at(p) == 0)
			{
				neutralFound = true;
				reconstructedNHitNeutral += m_lcioFlagType1->at(p) + m_lcioFlagType2->at(p) + m_lcioFlagType3->at(p);
				reconstructedNHitBadNeutral += m_lcioFlagType2->at(p) + m_lcioFlagType3->at(p)/2.f;
				reconstructedNHitGoodNeutral += m_lcioFlagType1->at(p) + m_lcioFlagType3->at(p)/2.f;
			}
		}

		originalNHitNeutral = totalHitType1 + totalHitType3/2.f;
		meanNeutralPurity += neutralFound ? reconstructedNHitGoodNeutral / (reconstructedNHitGoodNeutral + reconstructedNHitBadNeutral) : 0;
		meanNeutralEfficiency += neutralFound ? reconstructedNHitGoodNeutral/originalNHitNeutral : 0;

		if(neutralFound)
		{
			meanEnergyDifferenceEfficient += m_neutralEnergy - m_mcParticleEnergy1;
		}
	} // end of loop


	graphMap[N_PFOS]->SetPoint(pointID, xGraph, meanNPfos / nProcessedEvents);
	graphMap[N_PFOS]->SetPointError(pointID, 0, 1 / std::sqrt(nProcessedEvents));

	graphMap[NEUTRAL_PURITY]->SetPoint(pointID, xGraph, meanNeutralPurity / nProcessedEvents);
	graphMap[NEUTRAL_PURITY]->SetPointError(pointID, 0, 1 / std::sqrt(nProcessedEvents));

	graphMap[NEUTRAL_EFFICIENCY]->SetPoint(pointID, xGraph, meanNeutralEfficiency / nProcessedEvents);
	graphMap[NEUTRAL_EFFICIENCY]->SetPointError(pointID, 0, 1 / std::sqrt(nProcessedEvents));

	graphMap[NEUTRAL_RECOVER_PROBA]->SetPoint(pointID, xGraph, neutralRecPercentage / nProcessedEvents);
	graphMap[NEUTRAL_RECOVER_PROBA]->SetPointError(pointID, 0, 1 / std::sqrt(nProcessedEvents));

	graphMap[NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT]->SetPoint(pointID, xGraph, meanEnergyDifferenceEfficient / nProcessedEvents);
	graphMap[NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT]->SetPointError(pointID, 0, 1 / std::sqrt(nProcessedEvents));
}

//--------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------

OverlayAnalysis::OverlayAnalysis() :
		m_startDistance(5),
		m_endDistance(30),
		m_distanceStep(5),
		m_saveGraphs(false),
		m_rootFileDirectory("/home/remi/git/SDHCALArborPFA/output/v01-04-00/Separation/"),
		m_treeName("PfoMonitoring")
{
	m_dataTypeVector.push_back(TB_SPS_AUG_2012);
	m_dataTypeVector.push_back(FTFP_BERT_HP);
	m_dataTypeVector.push_back(FTF_BIC);

	m_neutralEnergies.push_back(10);
	m_chargedEnergies.push_back(10);
}

//--------------------------------------------------------------------------------------------------------------------

OverlayAnalysis::OverlayAnalysis(int neutralEnergy, int chargedEnergy) :
		m_startDistance(5),
		m_endDistance(30),
		m_distanceStep(5),
		m_saveGraphs(false),
		m_rootFileDirectory("/home/remi/soft/SDHCALArborPFA/output/v01-04-00/Separation/"),
		m_treeName("PfoMonitoring"),
		m_neutralEnergies(1, neutralEnergy),
		m_chargedEnergies(1, chargedEnergy)
{
	m_dataTypeVector.push_back(TB_SPS_AUG_2012);
	m_dataTypeVector.push_back(FTFP_BERT_HP);
	m_dataTypeVector.push_back(FTF_BIC);
}

//--------------------------------------------------------------------------------------------------------------------

OverlayAnalysis::OverlayAnalysis(const IntVector &neutralEnergies, const IntVector &chargedEnergies) :
		m_startDistance(5),
		m_endDistance(30),
		m_distanceStep(5),
		m_saveGraphs(false),
		m_rootFileDirectory("/home/remi/soft/SDHCALArborPFA/output/v01-04-00/Separation/"),
		m_treeName("PfoMonitoring"),
		m_neutralEnergies(neutralEnergies),
		m_chargedEnergies(chargedEnergies)
{
	m_dataTypeVector.push_back(TB_SPS_AUG_2012);
	m_dataTypeVector.push_back(FTFP_BERT_HP);
	m_dataTypeVector.push_back(FTF_BIC);
}

//--------------------------------------------------------------------------------------------------------------------

OverlayAnalysis::~OverlayAnalysis()
{
	m_dataTypeVector.clear();

	for(CanvasMultiGraphMap::iterator iter = m_canvasMultiGraphMap.begin(), endIter = m_canvasMultiGraphMap.end() ;
			endIter != iter ; ++iter)
	{
		delete iter->second.first;
		delete iter->second.second;
	}

	m_canvasMultiGraphMap.clear();
}

//--------------------------------------------------------------------------------------------------------------------

void OverlayAnalysis::Run()
{
	this->ConfigureMultiGraphMap();
	this->FillGraphs();
	this->DrawGraphs();

	if(m_saveGraphs)
		this->SaveGraphs();
}

//--------------------------------------------------------------------------------------------------------------------

void OverlayAnalysis::SetDistanceParameters(unsigned int startDistance, unsigned int endDistance, unsigned int distanceStep)
{
	m_startDistance = startDistance;
	m_endDistance = endDistance;
	m_distanceStep = distanceStep;
}

//--------------------------------------------------------------------------------------------------------------------

void OverlayAnalysis::SetFileParameters(const std::string &rootFileDirectory,
		const std::string &treeName)
{
	m_rootFileDirectory = rootFileDirectory;
	m_treeName = treeName;
}

//--------------------------------------------------------------------------------------------------------------------

void OverlayAnalysis::SetSaveGraphs(bool save)
{
	m_saveGraphs = save;
}

//--------------------------------------------------------------------------------------------------------------------

void OverlayAnalysis::ConfigureMultiGraphMap()
{
	std::cout << "Configuring multi graph map" << std::endl;

	std::cout << "  Clearing contents ..." << std::endl;
	// first clear it
	for(CanvasMultiGraphMap::iterator iter = m_canvasMultiGraphMap.begin(), endIter = m_canvasMultiGraphMap.end() ;
			endIter != iter ; ++iter)
	{
		delete iter->second.first;
		delete iter->second.second;
	}

	m_canvasMultiGraphMap.clear();

	std::cout << "  Creating graphs ..." << std::endl;

	// map each graph name with a canvas and a multi graph
	m_canvasMultiGraphMap[N_PFOS].first = this->CreateCanvas("OverlayEvent_NPfos", "Number of PFOs");
	m_canvasMultiGraphMap[N_PFOS].second = this->CreateMultiGraph();

	m_canvasMultiGraphMap[NEUTRAL_PURITY].first = this->CreateCanvas("OverlayEvent_NeutralPurity", "Neutral particle hit purity");
	m_canvasMultiGraphMap[NEUTRAL_PURITY].second = this->CreateMultiGraph();

	m_canvasMultiGraphMap[NEUTRAL_EFFICIENCY].first = this->CreateCanvas("OverlayEvent_NeutralEfficiency", "Neutral particle hit efficiency");
	m_canvasMultiGraphMap[NEUTRAL_EFFICIENCY].second = this->CreateMultiGraph();

	m_canvasMultiGraphMap[NEUTRAL_RECOVER_PROBA].first = this->CreateCanvas("OverlayEvent_NeutralRecoverProba", "Probability to recover at least one neutral particle");
	m_canvasMultiGraphMap[NEUTRAL_RECOVER_PROBA].second = this->CreateMultiGraph();

	m_canvasMultiGraphMap[NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT].first = this->CreateCanvas("OverlayEvent_NeutralEnergyDiff", "Ebeam - Erec when at least one neutral particle is recovered");
	m_canvasMultiGraphMap[NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT].second = this->CreateMultiGraph();
}

//--------------------------------------------------------------------------------------------------------------------

void OverlayAnalysis::FillGraphs()
{
	std::cout << "Filling graphs" << std::endl;

	for(DataTypeVector::const_iterator dataIter = m_dataTypeVector.begin(), dataEndIter = m_dataTypeVector.end() ;
			dataEndIter != dataIter ; ++dataIter)
	{
		DataType dataType = *dataIter;
		DrawAttributeMapping drawAttributeMapping(dataType);

		GraphMap graphMap;
		graphMap[N_PFOS] = drawAttributeMapping.ConfigureGraph(new TGraphErrors());
		graphMap[NEUTRAL_PURITY] = drawAttributeMapping.ConfigureGraph(new TGraphErrors());
		graphMap[NEUTRAL_EFFICIENCY] = drawAttributeMapping.ConfigureGraph(new TGraphErrors());
		graphMap[NEUTRAL_RECOVER_PROBA] = drawAttributeMapping.ConfigureGraph(new TGraphErrors());
		graphMap[NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT] = drawAttributeMapping.ConfigureGraph(new TGraphErrors());

		for(IntVector::iterator nIter = m_neutralEnergies.begin(), nEndIter = m_neutralEnergies.end() ;
				nEndIter != nIter ; ++nIter)
		{
			int neutralEnergy = *nIter;

			for(IntVector::iterator cIter = m_chargedEnergies.begin(), cEndIter = m_chargedEnergies.end() ;
					cEndIter != cIter ; ++cIter)
			{
				int chargedEnergy = *cIter;
				int pointID = 0;

				for(unsigned int distance = m_startDistance ; distance <= m_endDistance ; distance += m_distanceStep)
				{
					std::string completeFileName =
							m_rootFileDirectory
						  + this->GetDataName(dataType)
						  + "/"
						  + this->GetFileName(neutralEnergy, chargedEnergy, distance, dataType);

					TFile *pFile = TFile::Open(completeFileName.c_str());

					if(!pFile)
						throw std::runtime_error("Wrong file name !");

					TTree *pTree = (TTree *) pFile->Get(m_treeName.c_str());

					if(!pTree)
						throw std::runtime_error("Wrong tree name !");

					TreeAnalyzer treeAnalyzer(pTree);
					treeAnalyzer.Loop(pointID, static_cast<double>(distance), graphMap);

					pointID++;
				}
			}
		}

		// Add graphs in multi graph map
		for(GraphMap::const_iterator graphIter = graphMap.begin(), graphEndIter = graphMap.end() ;
				graphEndIter != graphIter ; ++graphIter)
			m_canvasMultiGraphMap[graphIter->first].second->Add(graphIter->second);

	}
}

//--------------------------------------------------------------------------------------------------------------------

void OverlayAnalysis::DrawGraphs()
{
	std::cout << "Drawing graphs" << std::endl;

	for(CanvasMultiGraphMap::iterator graphIter = m_canvasMultiGraphMap.begin(), graphEndIter = m_canvasMultiGraphMap.end() ;
			graphEndIter != graphIter ; ++graphIter)
	{
		graphIter->second.first->cd();

		graphIter->second.second->Draw("ap");
		this->PostDrawMultiGraph(graphIter->first, graphIter->second.second);

		TLegend *pLegend = graphIter->second.first->BuildLegend();
		pLegend->SetBorderSize(0);
		pLegend->SetLineColor(0);
		pLegend->SetLineStyle(1);
		pLegend->SetLineWidth(1);
		pLegend->SetFillColor(0);
		pLegend->SetFillStyle(0);
		pLegend->SetTextSize(0.04);
	}
}

//--------------------------------------------------------------------------------------------------------------------

void OverlayAnalysis::SaveGraphs()
{
	std::cout << "Saving graphs" << std::endl;

	for(CanvasMultiGraphMap::iterator graphIter = m_canvasMultiGraphMap.begin(), graphEndIter = m_canvasMultiGraphMap.end() ;
			graphEndIter != graphIter ; ++graphIter)
	{
		std::stringstream fileName;
		fileName << graphIter->second.first->GetName() << ".pdf";

		graphIter->second.first->cd();
		graphIter->second.first->SaveAs(fileName.str().c_str());
	}
}

//--------------------------------------------------------------------------------------------------------------------

std::string OverlayAnalysis::GetDataName(DataType dataType) const
{
	switch(dataType)
	{
		case TB_SPS_AUG_2012:
			return "TEST_BEAM";
		case FTFP_BERT_HP:
			return "FTFP_BERT_HP";
		case FTF_BIC:
			return "FTF_BIC";
		default:
			return "UNKNOWN";
	}
}

//--------------------------------------------------------------------------------------------------------------------

std::string OverlayAnalysis::GetFileName(int neutralEnergy, int chargedEnergy, unsigned int distance, DataType dataType) const
{
	std::stringstream distanceStr;
	distanceStr << distance;

	std::string fileName =
			"OverlayEventReconstruction_"
		  + this->GetEnergyToString(dataType, neutralEnergy)
		  + "_neutral_"
		  + this->GetEnergyToString(dataType, chargedEnergy)
		  + "_charged_"
		  + distanceStr.str()
		  + "cm_cut_ArborPFA_"
		  + this->GetDataName(dataType)
		  + "_basic.root";

	return fileName;
}

//--------------------------------------------------------------------------------------------------------------------

std::string OverlayAnalysis::GetEnergyToString(DataType dataType, int energy) const
{
	if(FTFP_BERT_HP == dataType || FTF_BIC == dataType)
	{
		std::stringstream ss;
		ss << energy <<"GeV";
		return ss.str();
	}
	else
	{
		switch (energy)
		{
		 case 10:
		 	return "715693";
		 case 20:
		 	return "715675";
		 case 30:
		 	return "715747";
		 case 40:
		 	return "715748";
		 case 50:
		 	return "715751";
		 case 60:
		 	return "715753";
		 case 70:
		 	return "715754";
		 case 80:
		 	return "715756";
		 default:
		 	throw std::invalid_argument("Invalid energy");
		}
	}
}

//--------------------------------------------------------------------------------------------------------------------

TCanvas *OverlayAnalysis::CreateCanvas(const std::string &canvasName, const std::string &canvasTitle) const
{
	TCanvas *pCanvas = new TCanvas(canvasName.c_str(), canvasTitle.c_str(), 200, 52, 700, 650);

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

	return pCanvas;
}

//--------------------------------------------------------------------------------------------------------------------

TMultiGraph *OverlayAnalysis::CreateMultiGraph() const
{
	return new TMultiGraph();
}

//--------------------------------------------------------------------------------------------------------------------

void OverlayAnalysis::PostDrawMultiGraph(GraphName graphName, TMultiGraph *pMultiGraph) const
{
	if(NULL == pMultiGraph)
		return;

	// base customize
	pMultiGraph->GetXaxis()->SetTitle("Distance between showers [cm]");
	pMultiGraph->GetXaxis()->SetLabelFont(42);
	pMultiGraph->GetXaxis()->SetTitleSize(0.05);
	pMultiGraph->GetXaxis()->SetTitleOffset(1.);
	pMultiGraph->GetXaxis()->SetTitleFont(42);
	pMultiGraph->GetXaxis()->SetRangeUser(std::max(static_cast<int>(m_startDistance) - 5, 0), m_endDistance + 5);

	pMultiGraph->GetYaxis()->SetTitle("");
	pMultiGraph->GetYaxis()->SetLabelFont(42);
	pMultiGraph->GetYaxis()->SetTitleSize(0.045);
	pMultiGraph->GetYaxis()->SetTitleOffset(1.3);
	pMultiGraph->GetYaxis()->SetTitleFont(42);
	pMultiGraph->GetYaxis()->SetLabelSize(0.035);

	TPaveText *pt = new TPaveText(0.3, 0.2, 0.93, 0.3, "tbNDC");
	pt->SetTextSize(0.05);
	pt->SetTextColor(kGray+2);
	pt->SetFillColor(0);
	pt->SetLineWidth(0);
	pt->SetBorderSize(0);
	pt->AddText("CALICE SDHCAL");
	pt->SetTextFont(62);
	pt->Draw();

	// plot per plot customize
	switch(graphName)
	{
		case N_PFOS:
			pMultiGraph->GetYaxis()->SetTitle("<N_{pfos}>");
			pMultiGraph->GetYaxis()->SetRangeUser(1, 3);
			break;
		case NEUTRAL_PURITY:
			pMultiGraph->GetYaxis()->SetTitle("#rho_{neutral}");
			pMultiGraph->GetYaxis()->SetRangeUser(0, 1);
			break;
		case NEUTRAL_EFFICIENCY:
			pMultiGraph->GetYaxis()->SetTitle("#varepsilon_{neutral}");
			pMultiGraph->GetYaxis()->SetRangeUser(0, 1);
			break;
		case NEUTRAL_RECOVER_PROBA:
			pMultiGraph->GetYaxis()->SetTitle("P_{n>0}");
			pMultiGraph->GetYaxis()->SetRangeUser(0, 1);
			break;
		case NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT:
			pMultiGraph->GetYaxis()->SetTitle("<E_{n,rec} - E_{n,meas}>, n>0");
			pMultiGraph->GetYaxis()->SetRangeUser(-5, 5);
			break;
	}
}



















