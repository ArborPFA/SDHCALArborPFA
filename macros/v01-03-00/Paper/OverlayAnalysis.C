#include "OverlayAnalysis.h"

// -- root headers
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TPaveText.h>
#include <TLegend.h>
#include <TSystemDirectory.h>

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

std::string GetDataName(DataType dataType)
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

std::string GetFileName(int neutralEnergy, int chargedEnergy, unsigned int distance, DataType dataType)
{
	std::stringstream distanceStr;
	distanceStr << distance;

	std::string fileName =
			"OverlayEventReconstruction_"
		  + GetEnergyToString(dataType, neutralEnergy)
		  + "_neutral_"
		  + GetEnergyToString(dataType, chargedEnergy)
		  + "_charged_"
		  + distanceStr.str()
		  + "cm_cut_ArborPFA_"
		  + GetDataName(dataType)
		  + "_basic.root";

	return fileName;
}

//--------------------------------------------------------------------------------------------------------------------

std::string GetEnergyToString(DataType dataType, int energy)
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

TCanvas *CreateCanvas(const std::string &canvasName, const std::string &canvasTitle)
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

TMultiGraph *CreateMultiGraph()
{
	return new TMultiGraph();
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
			m_drawAttributeMap[LINE_STYLE] = 1;
			break;
		case FTF_BIC:
			m_drawAttributeMap[MARKER_STYLE] = 29;
			m_drawAttributeMap[MARKER_COLOR] = kBlue;
			m_drawAttributeMap[LINE_COLOR] = kBlue;
			m_drawAttributeMap[LINE_STYLE] = 1;
			break;
		default:
			m_drawAttributeMap[MARKER_STYLE] = 21;
			m_drawAttributeMap[MARKER_COLOR] = kBlack;
			m_drawAttributeMap[LINE_COLOR] = kBlack;
			m_drawAttributeMap[LINE_STYLE] = 7;
			break;
	}

	m_drawAttributeMap[LINE_WIDTH] = 2;
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

TGraphAsymmErrors *DrawAttributeMapping::ConfigureGraph(TGraphAsymmErrors *pGraph, int chargedEnergy)
{
	if(NULL == pGraph)
		return NULL;

	// charged energy is a multiple of 10
	int chID = chargedEnergy/10;

	std::stringstream ss;
	ss << DataTypeToDrawableString(m_dataType) << " - charged energy " << chargedEnergy << " GeV";
	pGraph->SetName(ss.str().c_str());

	pGraph->SetMarkerStyle(this->GetAttribute(MARKER_STYLE));
	pGraph->SetMarkerColor(this->GetAttribute(MARKER_COLOR));
	pGraph->SetMarkerSize(this->GetAttribute(MARKER_SIZE));
	pGraph->SetLineColor(this->GetAttribute(LINE_COLOR));
	pGraph->SetLineStyle(1);
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
	float meanEnergyDifference = 0.f;

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

		meanEnergyDifference += m_neutralEnergy - m_mcParticleEnergy1;
	} // end of loop

	meanNPfos /= nProcessedEvents;
	meanNeutralPurity /= nProcessedEvents;
	meanNeutralEfficiency /= nProcessedEvents;
	neutralRecPercentage /= nProcessedEvents;
	meanEnergyDifferenceEfficient /= nProcessedEvents;
	meanEnergyDifference /= nProcessedEvents;

	double nPfosError = 1 / std::sqrt(nProcessedEvents);
	double efficiencyError = std::sqrt( meanNeutralEfficiency*(1-meanNeutralEfficiency) / nProcessedEvents );
	double purityError = std::sqrt( meanNeutralPurity*(1-meanNeutralPurity) / nProcessedEvents );
	double neutralProbaError = std::sqrt( neutralRecPercentage*(1-neutralRecPercentage) / nProcessedEvents );
	double energyDifferenceError = 1 / std::sqrt(nProcessedEvents);

	graphMap[N_PFOS]->SetPoint(pointID, xGraph, meanNPfos);
	graphMap[N_PFOS]->SetPointError(pointID, 0, 0, nPfosError, nPfosError);

	graphMap[NEUTRAL_PURITY]->SetPoint(pointID, xGraph, meanNeutralPurity);
	graphMap[NEUTRAL_PURITY]->SetPointError(pointID, 0, 0, purityError, purityError);

	graphMap[NEUTRAL_EFFICIENCY]->SetPoint(pointID, xGraph, meanNeutralEfficiency);
	graphMap[NEUTRAL_EFFICIENCY]->SetPointError(pointID, 0, 0, efficiencyError, efficiencyError);

	graphMap[NEUTRAL_RECOVER_PROBA]->SetPoint(pointID, xGraph, neutralRecPercentage);
	graphMap[NEUTRAL_RECOVER_PROBA]->SetPointError(pointID, 0, 0, neutralProbaError, neutralProbaError);

	graphMap[NEUTRAL_ENERGY_DIFFERENCE]->SetPoint(pointID, xGraph, meanEnergyDifference);
	graphMap[NEUTRAL_ENERGY_DIFFERENCE]->SetPointError(pointID, 0, 0, energyDifferenceError, energyDifferenceError);

	graphMap[NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT]->SetPoint(pointID, xGraph, meanEnergyDifferenceEfficient);
	graphMap[NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT]->SetPointError(pointID, 0, 0, energyDifferenceError, energyDifferenceError);
}

//--------------------------------------------------------------------------------------------------------------------

void TreeAnalyzer::FillNeutralMCEnergy(TH1 *pHistogram)
{
	if (m_pTree == 0)
		return;

	Long64_t nEntries = m_pTree->GetEntriesFast();

	for (Long64_t jentry=0 ; jentry<nEntries ; jentry++)
	{
		Long64_t ientry = this->LoadTree(jentry);

		if (ientry < 0)
			break;

		m_pTree->GetEntry(jentry);

		pHistogram->Fill(m_mcParticleEnergy1);
	}
}

//--------------------------------------------------------------------------------------------------------------------

void TreeAnalyzer::FillChargedMCEnergy(TH1 *pHistogram)
{
	if (m_pTree == 0)
		return;

	Long64_t nEntries = m_pTree->GetEntriesFast();

	for (Long64_t jentry=0 ; jentry<nEntries ; jentry++)
	{
		Long64_t ientry = this->LoadTree(jentry);

		if (ientry < 0)
			break;

		m_pTree->GetEntry(jentry);

		pHistogram->Fill(m_mcParticleEnergy2);
	}
}

//--------------------------------------------------------------------------------------------------------------------

void TreeAnalyzer::FillNOverlaidHits(TGraphAsymmErrors *pGraph)
{
	if (m_pTree == 0)
		return;

	Long64_t nEntries = m_pTree->GetEntriesFast();

	unsigned int nProcessedEvents = 0;
	std::vector<int> nOverlaidHits(200, 0);

	for (Long64_t jentry=0 ; jentry<nEntries ; jentry++)
	{
		Long64_t ientry = this->LoadTree(jentry);

		if (ientry < 0)
			break;

		m_pTree->GetEntry(jentry);

		unsigned int totalHitType3 = 0;

		// analyze pfos and extract the purity/efficiency
		for(int p=0 ; p<m_nPfos ; p++)
		{
			totalHitType3 += m_lcioFlagType3->at(p);
		}

		if(totalHitType3 < nOverlaidHits.size())
			nOverlaidHits.at(totalHitType3)++;

		nProcessedEvents++;
	}

	for(unsigned int i=0 ; i<nOverlaidHits.size() ; i++)
	{
		pGraph->SetPoint(i, i, nOverlaidHits.at(i) / static_cast<double>(nProcessedEvents));
		pGraph->SetPointError(i, 0, 0, 0, 0);
	}
}

//--------------------------------------------------------------------------------------------------------------------

void TreeAnalyzer::FillOverlaidHitsPercentage(TGraphAsymmErrors *pGraph)
{
	if (m_pTree == 0)
		return;

	Long64_t nEntries = m_pTree->GetEntriesFast();

	unsigned int nProcessedEvents = 0;
	std::vector<int> overlaidHitsPercentage(100, 0);

	for (Long64_t jentry=0 ; jentry<nEntries ; jentry++)
	{
		Long64_t ientry = this->LoadTree(jentry);

		if (ientry < 0)
			break;

		m_pTree->GetEntry(jentry);

		unsigned int nHits = 0;
		unsigned int totalHitType3 = 0;

		// analyze pfos and extract the purity/efficiency
		for(int p=0 ; p<m_nPfos ; p++)
		{
			nHits += m_nHit->at(p);
			totalHitType3 += m_lcioFlagType3->at(p);
		}

		int percentage = round((static_cast<double>(totalHitType3) / nHits)*100);

		std::cout << "nHits : " << nHits << std::endl;
		std::cout << "totalHitType3 : " << totalHitType3 << std::endl;
		std::cout << "percentage : " << percentage << std::endl;

		overlaidHitsPercentage.at(percentage) ++;
		nProcessedEvents++;
	}

	for(unsigned int i=0 ; i<overlaidHitsPercentage.size() ; i++)
	{
		pGraph->SetPoint(i, i, overlaidHitsPercentage.at(i) / static_cast<double>(nProcessedEvents));
		pGraph->SetPointError(i, 0, 0, 0, 0);
	}
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
		m_chargedEnergies(1, chargedEnergy),
		m_textLabel("CALICE SDHCAL")
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
		m_chargedEnergies(chargedEnergies),
		m_textLabel("CALICE SDHCAL")
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

void OverlayAnalysis::SetDataTypes(const DataTypeVector &dataTypes)
{
	if(dataTypes.empty())
		return;

	m_dataTypeVector = dataTypes;
}

//--------------------------------------------------------------------------------------------------------------------

void OverlayAnalysis::SetComputeSystematics(bool compute)
{
	m_computeSystematics = compute;
}

//--------------------------------------------------------------------------------------------------------------------

void OverlayAnalysis::SetTextLabel(const std::string &text)
{
	m_textLabel = text;
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
	m_canvasMultiGraphMap[N_PFOS].first = CreateCanvas("OverlayEvent_NPfos", "Number of PFOs");
	m_canvasMultiGraphMap[N_PFOS].second = CreateMultiGraph();

	m_canvasMultiGraphMap[NEUTRAL_PURITY].first = CreateCanvas("OverlayEvent_NeutralPurity", "Neutral particle hit purity");
	m_canvasMultiGraphMap[NEUTRAL_PURITY].second = CreateMultiGraph();

	m_canvasMultiGraphMap[NEUTRAL_EFFICIENCY].first = CreateCanvas("OverlayEvent_NeutralEfficiency", "Neutral particle hit efficiency");
	m_canvasMultiGraphMap[NEUTRAL_EFFICIENCY].second = CreateMultiGraph();

	m_canvasMultiGraphMap[NEUTRAL_RECOVER_PROBA].first = CreateCanvas("OverlayEvent_NeutralRecoverProba", "Probability to recover at least one neutral particle");
	m_canvasMultiGraphMap[NEUTRAL_RECOVER_PROBA].second = CreateMultiGraph();

	m_canvasMultiGraphMap[NEUTRAL_ENERGY_DIFFERENCE].first = CreateCanvas("OverlayEvent_NeutralEnergyDiff", "Ebeam - Erec when at least one neutral particle is recovered");
	m_canvasMultiGraphMap[NEUTRAL_ENERGY_DIFFERENCE].second = CreateMultiGraph();

	m_canvasMultiGraphMap[NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT].first = CreateCanvas("OverlayEvent_NeutralEnergyDiffEfficient", "Ebeam - Erec when at least one neutral particle is recovered");
	m_canvasMultiGraphMap[NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT].second = CreateMultiGraph();

	m_canvasMultiGraphMap[N_OVERLAID_HITS].first = CreateCanvas("OverlayEvent_NOverlaidHits", "Number of overlaid hits");
	m_canvasMultiGraphMap[N_OVERLAID_HITS].second = CreateMultiGraph();

	m_canvasMultiGraphMap[OVERLAID_HITS_PERCENTAGE].first = CreateCanvas("OverlayEvent_OverlaidHitsPercentage", "Percentage of overlaid hits");
	m_canvasMultiGraphMap[OVERLAID_HITS_PERCENTAGE].second = CreateMultiGraph();
}

//--------------------------------------------------------------------------------------------------------------------

void OverlayAnalysis::FillGraphs()
{
	std::cout << "Filling graphs" << std::endl;

	int color(1);

	for(DataTypeVector::const_iterator dataIter = m_dataTypeVector.begin(), dataEndIter = m_dataTypeVector.end() ;
			dataEndIter != dataIter ; ++dataIter)
	{
		DataType dataType = *dataIter;
		DrawAttributeMapping drawAttributeMapping(dataType);

		std::cout << "Data type = " << dataType << std::endl;

		for(IntVector::iterator nIter = m_neutralEnergies.begin(), nEndIter = m_neutralEnergies.end() ;
				nEndIter != nIter ; ++nIter)
		{
			int neutralEnergy = *nIter;
			// int color = dataType+1;

			for(IntVector::iterator cIter = m_chargedEnergies.begin(), cEndIter = m_chargedEnergies.end() ;
					cEndIter != cIter ; ++cIter)
			{
				int chargedEnergy = *cIter;
				int pointID = 0;

				GraphMap graphMap;
				graphMap[N_PFOS] = drawAttributeMapping.ConfigureGraph(new TGraphAsymmErrors(), chargedEnergy);
				graphMap[NEUTRAL_PURITY] = drawAttributeMapping.ConfigureGraph(new TGraphAsymmErrors(), chargedEnergy);
				graphMap[NEUTRAL_EFFICIENCY] = drawAttributeMapping.ConfigureGraph(new TGraphAsymmErrors(), chargedEnergy);
				graphMap[NEUTRAL_RECOVER_PROBA] = drawAttributeMapping.ConfigureGraph(new TGraphAsymmErrors(), chargedEnergy);
				graphMap[NEUTRAL_ENERGY_DIFFERENCE] = drawAttributeMapping.ConfigureGraph(new TGraphAsymmErrors(), chargedEnergy);
				graphMap[NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT] = drawAttributeMapping.ConfigureGraph(new TGraphAsymmErrors(), chargedEnergy);

				for(unsigned int distance = m_startDistance ; distance <= m_endDistance ; distance += m_distanceStep)
				{
					std::string completeFileName =
							m_rootFileDirectory
						  + GetDataName(dataType)
						  + "/"
						  + GetFileName(neutralEnergy, chargedEnergy, distance, dataType);

					TFile *pFile = TFile::Open(completeFileName.c_str());

					if(!pFile)
						throw std::runtime_error("Wrong file name !");

					TTree *pTree = (TTree *) pFile->Get(m_treeName.c_str());

					if(!pTree)
						throw std::runtime_error("Wrong tree name !");

					TreeAnalyzer treeAnalyzer(pTree);
					treeAnalyzer.Loop(pointID, static_cast<double>(distance), graphMap);

					if(neutralEnergy == 10 && chargedEnergy == 30 && distance == 30)
					{
						graphMap[N_OVERLAID_HITS] = drawAttributeMapping.ConfigureGraph(new TGraphAsymmErrors(), chargedEnergy);
						graphMap[N_OVERLAID_HITS]->SetLineStyle(0);
						graphMap[N_OVERLAID_HITS]->SetLineWidth(0);
						treeAnalyzer.FillNOverlaidHits(graphMap[N_OVERLAID_HITS]);

						graphMap[OVERLAID_HITS_PERCENTAGE] = drawAttributeMapping.ConfigureGraph(new TGraphAsymmErrors(), chargedEnergy);
						graphMap[OVERLAID_HITS_PERCENTAGE]->SetLineStyle(0);
						graphMap[OVERLAID_HITS_PERCENTAGE]->SetLineWidth(0);
						treeAnalyzer.FillOverlaidHitsPercentage(graphMap[OVERLAID_HITS_PERCENTAGE]);
					}

					// compute systematic errors if required !
					if( m_computeSystematics )
						this->ComputeSystematics(pointID, neutralEnergy, chargedEnergy, distance, dataType, graphMap);

					pointID++;
				}

				// Add graphs in multi graph map
				for(GraphMap::const_iterator graphIter = graphMap.begin(), graphEndIter = graphMap.end() ;
						graphEndIter != graphIter ; ++graphIter)
				{
					graphIter->second->SetMarkerColor(color);
					graphIter->second->SetLineColor(color);
					m_canvasMultiGraphMap[graphIter->first].second->Add(graphIter->second);
				}

				color ++;
				// graphColor++;
			}
		}
	}
}

//--------------------------------------------------------------------------------------------------------------------

void OverlayAnalysis::ComputeSystematics(int pointID, int neutralEnergy, int chargedEnergy, int distance, DataType dataType, GraphMap &graphMapAtNominalValues)
{
	TSystemDirectory directory((m_rootFileDirectory + GetDataName(dataType)
			+ "/SYSTEMATICS/").c_str(), (m_rootFileDirectory + GetDataName(dataType)
					+ "/SYSTEMATICS/").c_str());
	TList *pFileList = directory.GetListOfFiles();

	if( ! pFileList )
	{
		std::cout << "No systematics study performed. Directory '" << m_rootFileDirectory + GetDataName(dataType)
					+ "/SYSTEMATICS/" << "' doesn't exists" << std::endl;
		return;
	}

	std::vector<std::string> pm;
	pm.push_back("+");
	pm.push_back("-");

	GraphSystErrorMap upperErrorMap;
	GraphSystErrorMap lowerErrorMap;

	upperErrorMap[N_PFOS] = 0.d;
	upperErrorMap[NEUTRAL_PURITY] = 0.d;
	upperErrorMap[NEUTRAL_EFFICIENCY] = 0.d;
	upperErrorMap[NEUTRAL_RECOVER_PROBA] = 0.d;
	upperErrorMap[NEUTRAL_ENERGY_DIFFERENCE] = 0.d;
	upperErrorMap[NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT] = 0.d;

	lowerErrorMap[N_PFOS] = 0.d;
	lowerErrorMap[NEUTRAL_PURITY] = 0.d;
	lowerErrorMap[NEUTRAL_EFFICIENCY] = 0.d;
	lowerErrorMap[NEUTRAL_RECOVER_PROBA] = 0.d;
	lowerErrorMap[NEUTRAL_ENERGY_DIFFERENCE] = 0.d;
	lowerErrorMap[NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT] = 0.d;

	for(unsigned int sp=DISTANCE_1 ; sp<N_SYSTEMATIC_PARAMETERS ; sp++)
	{
		unsigned int parameterID = sp+1;

		double errorP = 0;
		double errorM = 0;

		for(unsigned int signID=0 ; signID<pm.size() ; signID++)
		{
			std::string sign = pm.at( signID );

			std::stringstream distanceStr;
			distanceStr << distance;

			TString fileName =
					"OverlayEventReconstruction_"
					+ GetEnergyToString(dataType, neutralEnergy)
					+ "_neutral_"
					+ GetEnergyToString(dataType, chargedEnergy)
					+ "_charged_"
					+ distanceStr.str()
					+ "cm_cut_ArborPFA_"
					+ GetDataName(dataType)
					+ "_P"
					+ TString::UItoa(parameterID, 10)
					+ "_S" + sign + "_basic.root";

			TString completeFileName = m_rootFileDirectory + GetDataName(dataType)
					+ "/SYSTEMATICS/" + fileName;

			TFile *pFile = TFile::Open(completeFileName.Data());

			if( ! pFile )
			{
				std::cerr << "Wrong sys file name !" << std::endl;
				continue;
			}

			TTree *pTree = (TTree *) pFile->Get(m_treeName.c_str());

			if( ! pTree )
			{
				std::cerr << "Wrong sys tree name !" << std::endl;
				delete pFile;
				continue;
			}

			GraphMap graphMap;
			graphMap[N_PFOS] = new TGraphAsymmErrors();
			graphMap[NEUTRAL_PURITY] = new TGraphAsymmErrors();
			graphMap[NEUTRAL_EFFICIENCY] = new TGraphAsymmErrors();
			graphMap[NEUTRAL_RECOVER_PROBA] = new TGraphAsymmErrors();
			graphMap[NEUTRAL_ENERGY_DIFFERENCE] = new TGraphAsymmErrors();
			graphMap[NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT] = new TGraphAsymmErrors();

			TreeAnalyzer treeAnalyzer(pTree);
			treeAnalyzer.Loop(pointID, static_cast<double>(distance), graphMap);

			this->ComputeSystematics(pointID, graphMapAtNominalValues, graphMap,
					N_PFOS, upperErrorMap, lowerErrorMap);

			this->ComputeSystematics(pointID, graphMapAtNominalValues, graphMap,
					NEUTRAL_PURITY, upperErrorMap, lowerErrorMap);

			this->ComputeSystematics(pointID, graphMapAtNominalValues, graphMap,
					NEUTRAL_EFFICIENCY, upperErrorMap, lowerErrorMap);

			this->ComputeSystematics(pointID, graphMapAtNominalValues, graphMap,
					NEUTRAL_RECOVER_PROBA, upperErrorMap, lowerErrorMap);

			this->ComputeSystematics(pointID, graphMapAtNominalValues, graphMap,
					NEUTRAL_ENERGY_DIFFERENCE, upperErrorMap, lowerErrorMap);

			this->ComputeSystematics(pointID, graphMapAtNominalValues, graphMap,
					NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT, upperErrorMap, lowerErrorMap);

			double systVar = 0.d;
			double nominalVar = 0.d;
			double systVarDiff = 0.d;

			nominalVar = graphMapAtNominalValues.find(NEUTRAL_EFFICIENCY)->second->GetY()[pointID];
			systVar = graphMap.find(NEUTRAL_EFFICIENCY)->second->GetY()[pointID];
			systVarDiff = systVar - nominalVar;

			bool print = ( distance == 10 && dataType == TB_SPS_AUG_2012);

			if(print)
				std::cout << "Error (" << sign << ") for parameter " << sp << " (nom = " << nominalVar << ") is " << systVarDiff << std::endl;;

			if( systVarDiff > 0.d )
				errorP += systVarDiff*systVarDiff;
			else
				errorM += systVarDiff*systVarDiff;
		}
	}

	delete pFileList;
	double upperError = 0;
	double lowerError = 0;

	/* -------------------------------------------------- */
	upperError = std::sqrt(
				// squared stat error set before calling this method
				graphMapAtNominalValues[N_PFOS]->GetEYhigh()[pointID]*graphMapAtNominalValues[N_PFOS]->GetEYhigh()[pointID] +
				// squared upper syst error that we add now
				upperErrorMap[N_PFOS]
				);

	lowerError = std::sqrt(
				// squared stat error set before calling this method
				graphMapAtNominalValues[N_PFOS]->GetEYhigh()[pointID]*graphMapAtNominalValues[N_PFOS]->GetEYhigh()[pointID] +
				// squared upper syst error that we add now
				lowerErrorMap[N_PFOS]
				);

	graphMapAtNominalValues[N_PFOS]->SetPointError(pointID, 0, 0, lowerError, upperError );

	/* -------------------------------------------------- */
	upperError = std::sqrt(
				// squared stat error set before calling this method
				graphMapAtNominalValues[N_PFOS]->GetEYhigh()[pointID]*graphMapAtNominalValues[NEUTRAL_PURITY]->GetEYhigh()[pointID] +
				// squared upper syst error that we add now
				upperErrorMap[NEUTRAL_PURITY]
				);

	lowerError = std::sqrt(
				// squared stat error set before calling this method
				graphMapAtNominalValues[NEUTRAL_PURITY]->GetEYhigh()[pointID]*graphMapAtNominalValues[NEUTRAL_PURITY]->GetEYhigh()[pointID] +
				// squared upper syst error that we add now
				lowerErrorMap[NEUTRAL_PURITY]
				);

	graphMapAtNominalValues[NEUTRAL_PURITY]->SetPointError(pointID, 0, 0, lowerError, upperError );

	bool print = ( distance == 10 && dataType == TB_SPS_AUG_2012);

	if( print )
	{
		double systP = std::sqrt(upperErrorMap[NEUTRAL_EFFICIENCY]);
		double systM = std::sqrt(lowerErrorMap[NEUTRAL_EFFICIENCY]);
		double stat = graphMapAtNominalValues[NEUTRAL_EFFICIENCY]->GetEYhigh()[pointID];
		double totalP = std::sqrt( systP*systP + stat*stat );
		double totalM = std::sqrt( systM*systM + stat*stat );

		std::cout << "systP error = " << systP << std::endl;
		std::cout << "systM error = " << systM << std::endl;
		std::cout << "Stat error = " << stat << std::endl;
		std::cout << "totalP error = " << totalP << endl;
		std::cout << "totalM error = " << totalM << endl;
	}

	/* -------------------------------------------------- */
	upperError = std::sqrt(
				// squared stat error set before calling this method
				graphMapAtNominalValues[NEUTRAL_EFFICIENCY]->GetEYhigh()[pointID]*graphMapAtNominalValues[NEUTRAL_EFFICIENCY]->GetEYhigh()[pointID] +
				// squared upper syst error that we add now
				upperErrorMap[NEUTRAL_EFFICIENCY]
				);

	lowerError = std::sqrt(
				// squared stat error set before calling this method
				graphMapAtNominalValues[NEUTRAL_EFFICIENCY]->GetEYhigh()[pointID]*graphMapAtNominalValues[NEUTRAL_EFFICIENCY]->GetEYhigh()[pointID] +
				// squared upper syst error that we add now
				lowerErrorMap[NEUTRAL_EFFICIENCY]
				);

	graphMapAtNominalValues[NEUTRAL_EFFICIENCY]->SetPointError(pointID, 0, 0, lowerError, upperError );

	/* -------------------------------------------------- */
	upperError = std::sqrt(
				// squared stat error set before calling this method
				graphMapAtNominalValues[NEUTRAL_RECOVER_PROBA]->GetEYhigh()[pointID]*graphMapAtNominalValues[NEUTRAL_RECOVER_PROBA]->GetEYhigh()[pointID] +
				// squared upper syst error that we add now
				upperErrorMap[NEUTRAL_RECOVER_PROBA]
				);

	lowerError = std::sqrt(
				// squared stat error set before calling this method
				graphMapAtNominalValues[NEUTRAL_RECOVER_PROBA]->GetEYhigh()[pointID]*graphMapAtNominalValues[NEUTRAL_RECOVER_PROBA]->GetEYhigh()[pointID] +
				// squared upper syst error that we add now
				lowerErrorMap[NEUTRAL_RECOVER_PROBA]
				);

	graphMapAtNominalValues[NEUTRAL_RECOVER_PROBA]->SetPointError(pointID, 0, 0, lowerError, upperError );

	/* -------------------------------------------------- */
	upperError = std::sqrt(
				// squared stat error set before calling this method
				graphMapAtNominalValues[NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT]->GetEYhigh()[pointID]*graphMapAtNominalValues[NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT]->GetEYhigh()[pointID] +
				// squared upper syst error that we add now
				upperErrorMap[NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT]
				);

	lowerError = std::sqrt(
				// squared stat error set before calling this method
				graphMapAtNominalValues[NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT]->GetEYhigh()[pointID]*graphMapAtNominalValues[NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT]->GetEYhigh()[pointID] +
				// squared upper syst error that we add now
				lowerErrorMap[NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT]
				);

	graphMapAtNominalValues[NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT]->SetPointError(pointID, 0, 0, lowerError, upperError );

	/* -------------------------------------------------- */
	upperError = std::sqrt(
				// squared stat error set before calling this method
				graphMapAtNominalValues[NEUTRAL_ENERGY_DIFFERENCE]->GetEYhigh()[pointID]*graphMapAtNominalValues[NEUTRAL_ENERGY_DIFFERENCE]->GetEYhigh()[pointID] +
				// squared upper syst error that we add now
				upperErrorMap[NEUTRAL_ENERGY_DIFFERENCE]
				);

	lowerError = std::sqrt(
				// squared stat error set before calling this method
				graphMapAtNominalValues[NEUTRAL_ENERGY_DIFFERENCE]->GetEYhigh()[pointID]*graphMapAtNominalValues[NEUTRAL_ENERGY_DIFFERENCE]->GetEYhigh()[pointID] +
				// squared upper syst error that we add now
				lowerErrorMap[NEUTRAL_ENERGY_DIFFERENCE]
				);

	graphMapAtNominalValues[NEUTRAL_ENERGY_DIFFERENCE]->SetPointError(pointID, 0, 0, lowerError, upperError );
}

//--------------------------------------------------------------------------------------------------------------------

void OverlayAnalysis::ComputeSystematics(int pointID, const GraphMap &nominalMap, const GraphMap &systGraphMap,
		GraphName graphName, GraphSystErrorMap &upperBoundErrorMap, GraphSystErrorMap &lowerBoundErrorMap)
{
	double systVar = 0.d;
	double nominalVar = 0.d;
	double systVarDiff = 0.d;

	nominalVar = nominalMap.find(graphName)->second->GetY()[pointID];
	systVar = systGraphMap.find(graphName)->second->GetY()[pointID];
	systVarDiff = systVar - nominalVar;

	if( systVarDiff > 0.d )
		upperBoundErrorMap[graphName] += systVarDiff*systVarDiff;
	else
		lowerBoundErrorMap[graphName] += systVarDiff*systVarDiff;
}

//--------------------------------------------------------------------------------------------------------------------

void OverlayAnalysis::DrawGraphs()
{
	std::cout << "Drawing graphs" << std::endl;

	for(CanvasMultiGraphMap::iterator graphIter = m_canvasMultiGraphMap.begin(), graphEndIter = m_canvasMultiGraphMap.end() ;
			graphEndIter != graphIter ; ++graphIter)
	{
		graphIter->second.first->cd();

		if(graphIter->first != N_OVERLAID_HITS
				&& graphIter->first != OVERLAID_HITS_PERCENTAGE)
			graphIter->second.second->Draw("alp");
		else
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

	if( ! m_textLabel.empty() )
	{
		TPaveText *pt = new TPaveText(0.3, 0.2, 0.93, 0.3, "tbNDC");
		pt->SetTextSize(0.05);
		pt->SetTextColor(kGray+2);
		pt->SetFillColor(0);
		pt->SetLineWidth(0);
		pt->SetBorderSize(0);
		pt->AddText( m_textLabel.c_str() );
		pt->SetTextFont(62);
		pt->Draw();
	}

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
			pMultiGraph->GetYaxis()->SetRangeUser(0, 1.099);
			break;
		case NEUTRAL_ENERGY_DIFFERENCE:
		{
			pMultiGraph->GetYaxis()->SetTitle("<E_{n,rec} - E_{n,meas}> [GeV]");
			pMultiGraph->GetYaxis()->SetRangeUser(-10, 10);
			TF1 *pZero = new TF1("zero1", "0", 0, 35);
			pZero->SetLineStyle(1);
			pZero->SetLineColor(kBlack);
			pZero->SetLineWidth(1);
			pZero->Draw("same");
			break;
		}
		case NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT:
		{
			pMultiGraph->GetYaxis()->SetTitle("<E_{n,rec} - E_{n,meas}>, n>0 [GeV]");
			pMultiGraph->GetYaxis()->SetRangeUser(-10, 10);
			TF1 *pZero = new TF1("zero2", "0", 0, 35);
			pZero->SetLineStyle(1);
			pZero->SetLineColor(kBlack);
			pZero->SetLineWidth(1);
			pZero->Draw("same");
			break;
		}
		case N_OVERLAID_HITS:
		{
			pMultiGraph->GetYaxis()->SetTitle("# events (normalized to unity)");
			pMultiGraph->GetXaxis()->SetTitle("Number of overlaid hits");
			break;
		}
		case OVERLAID_HITS_PERCENTAGE:
		{
			pMultiGraph->GetYaxis()->SetTitle("# events (normalized to unity)");
			pMultiGraph->GetXaxis()->SetTitle("Percentage of overlaid hits");
			break;
		}
	}
}

//--------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------

OverlayCheckPlotAnalysis::OverlayCheckPlotAnalysis() :
		m_textLabel("CALICE SDHCAL"),
		m_treeName("PfoMonitoring")
{
	// set default parameters
	SetParameters(TB_SPS_AUG_2012);
}

//--------------------------------------------------------------------------------------------------------------------

void OverlayCheckPlotAnalysis::SetParameters(DataType dataType, unsigned int neutralEnergy, unsigned int chargedEnergy,
		unsigned int smallDistance, unsigned int wideDistance)
{
	m_dataType = dataType;
	m_neutralEnergy = neutralEnergy;
	m_chargedEnergy = chargedEnergy;
	m_smallDistance = smallDistance;
	m_wideDistance = wideDistance;
}

//--------------------------------------------------------------------------------------------------------------------

void OverlayCheckPlotAnalysis::SetFileParameters(const std::string &fileDirectory, const std::string &treeName)
{
	m_fileDirectory = fileDirectory;
	m_treeName = treeName;
}

//--------------------------------------------------------------------------------------------------------------------

void OverlayCheckPlotAnalysis::SetTextLabel(const std::string &text)
{
	m_textLabel = text;
}

//--------------------------------------------------------------------------------------------------------------------

void OverlayCheckPlotAnalysis::Run()
{
	// configure plots
	TH1F *pSmallDistanceNeutralEnergy = new TH1F("SmallDisNeuErj", "", 301, 0, 100);
	pSmallDistanceNeutralEnergy->SetLineColor(kRed);
	pSmallDistanceNeutralEnergy->SetLineWidth(2);
	pSmallDistanceNeutralEnergy->GetXaxis()->SetTitle("E_{rec} [GeV]");
	pSmallDistanceNeutralEnergy->GetXaxis()->SetTitleSize(0.045);
	pSmallDistanceNeutralEnergy->GetXaxis()->SetRangeUser(0, 30);
	pSmallDistanceNeutralEnergy->GetYaxis()->SetTitle("#entries");
	pSmallDistanceNeutralEnergy->GetYaxis()->SetTitleOffset(1.5);
	pSmallDistanceNeutralEnergy->GetYaxis()->SetTitleSize(0.045);

	TH1F *pWideDistanceNeutralEnergy = new TH1F("WideDisNeuErj", "", 301, 0, 100);
	pWideDistanceNeutralEnergy->SetLineColor(kBlack);
	pWideDistanceNeutralEnergy->SetLineWidth(2);

	TH1F *pChargedEnergy = new TH1F("ChErj", "", 91, 0, 30);
	pChargedEnergy->SetLineColor(kBlue);
	pChargedEnergy->SetLineWidth(2);
	pChargedEnergy->SetLineWidth(2);
	pChargedEnergy->GetXaxis()->SetTitle("E_{rec} [GeV]");
	pChargedEnergy->GetXaxis()->SetTitleSize(0.045);
	pChargedEnergy->GetXaxis()->SetRangeUser(0, 30);
	pChargedEnergy->GetYaxis()->SetTitle("#entries");
	pChargedEnergy->GetYaxis()->SetTitleOffset(1.5);
	pChargedEnergy->GetYaxis()->SetTitleSize(0.045);

	// construct and open files
	std::string completeSmallDistanceFileName =
			m_fileDirectory
		  + GetDataName(m_dataType)
		  + "/"
		  + GetFileName(m_neutralEnergy, m_chargedEnergy, m_smallDistance, m_dataType);

	std::string completeWideDistanceFileName =
			m_fileDirectory
		  + GetDataName(m_dataType)
		  + "/"
		  + GetFileName(m_neutralEnergy, m_chargedEnergy, m_wideDistance, m_dataType);

	TFile *pSmallFile = TFile::Open(completeSmallDistanceFileName.c_str());
	TFile *pWideFile  = TFile::Open(completeWideDistanceFileName.c_str());

	if( ! pSmallFile )
		throw std::runtime_error("Wrong file name (small distance) !");

	if( ! pWideFile )
		throw std::runtime_error("Wrong file name (wide distance) !");

	// perform tree analysis
	TTree *pSmallTree = (TTree *) pSmallFile->Get(m_treeName.c_str());
	TTree *pWideTree  = (TTree *) pWideFile->Get(m_treeName.c_str());

	if( ! pSmallTree || ! pWideTree )
		throw std::runtime_error("Wrong tree name !");

	TreeAnalyzer treeSmallAnalyzer(pSmallTree);
	TreeAnalyzer treeWideAnalyzer(pWideTree);

	treeSmallAnalyzer.FillNeutralMCEnergy(pSmallDistanceNeutralEnergy);
	treeWideAnalyzer.FillNeutralMCEnergy(pWideDistanceNeutralEnergy);
	treeWideAnalyzer.FillChargedMCEnergy(pChargedEnergy);

	// plot contents
	TCanvas *pCanvas = CreateCanvas("OverlayEvent_checkOverlayEnergy", "Overlay energy comparison");
	pCanvas->cd();

	gStyle->SetOptStat(0);

	pSmallDistanceNeutralEnergy->Draw();
	pWideDistanceNeutralEnergy->Draw("same");

	std::stringstream titleStr;
	std::stringstream meanStr;
	std::stringstream rmsStr;

	TPaveText *stats = new TPaveText(0.68,0.635,0.88,0.8,"nbNDC");
	stats->SetName("statsE1");
	stats->SetBorderSize(0);
	stats->SetFillColor(0);
	stats->SetLineColor(kRed);
	stats->SetLineWidth(1);
	stats->SetTextAlign(12);
	stats->SetTextFont(42);
	stats->SetTextColor(kRed);
	stats->SetTextSize(0.04);

	titleStr   << m_smallDistance << " cm distance";
	meanStr    << "Mean    = " << pSmallDistanceNeutralEnergy->GetMean();
	rmsStr     << "RMS     = " << pSmallDistanceNeutralEnergy->GetRMS();

	stats->AddText(titleStr.str().c_str());
	stats->AddText(meanStr.str().c_str());
	stats->AddText(rmsStr.str().c_str());
	stats->Draw();

	titleStr.str("");
	meanStr.str("");
	rmsStr.str("");

	stats = new TPaveText(0.68,0.635,0.88,0.8,"nbNDC");
	stats->SetName("statsE2");
	stats->SetBorderSize(0);
	stats->SetFillColor(0);
	stats->SetLineColor(kBlack);
	stats->SetLineWidth(1);
	stats->SetTextAlign(12);
	stats->SetTextFont(42);
	stats->SetTextColor(kBlack);
	stats->SetTextSize(0.04);

	titleStr   << m_wideDistance << " cm distance";
	meanStr    << "Mean    = " << pWideDistanceNeutralEnergy->GetMean();
	rmsStr     << "RMS     = " << pWideDistanceNeutralEnergy->GetRMS();

	stats->AddText(titleStr.str().c_str());
	stats->AddText(meanStr.str().c_str());
	stats->AddText(rmsStr.str().c_str());
	stats->Draw();

	if( ! m_textLabel.empty() )
	{
		TPaveText *pt = new TPaveText(0.3, 0.2, 0.93, 0.3, "tbNDC");
		pt->SetTextSize(0.05);
		pt->SetTextColor(kGray+2);
		pt->SetFillColor(0);
		pt->SetLineWidth(0);
		pt->SetBorderSize(0);
		pt->AddText( m_textLabel.c_str() );
		pt->SetTextFont(62);
		pt->Draw();
	}

//	pCanvas = CreateCanvas("OverlayEvent_checkOverlayChEnergy", "Charged energy before overlay");
//	pCanvas->cd();
//
//	gStyle->SetOptStat(0);

	pChargedEnergy->Draw("same");

	titleStr.str("");
	meanStr.str("");
	rmsStr.str("");

	stats = new TPaveText(0.68,0.635,0.88,0.8,"nbNDC");
	stats->SetName("statsChE");
	stats->SetBorderSize(0);
	stats->SetFillColor(0);
	stats->SetLineColor(kBlack);
	stats->SetLineWidth(1);
	stats->SetTextAlign(12);
	stats->SetTextFont(42);
	stats->SetTextColor(kBlue);
	stats->SetTextSize(0.04);

	titleStr   << "Before overlay";
	meanStr    << "Mean    = " << pChargedEnergy->GetMean();
	rmsStr     << "RMS     = " << pChargedEnergy->GetRMS();

	stats->AddText(titleStr.str().c_str());
	stats->AddText(meanStr.str().c_str());
	stats->AddText(rmsStr.str().c_str());
	stats->Draw();

//	if( ! m_textLabel.empty() )
//	{
//		TPaveText *pt = new TPaveText(0.3, 0.2, 0.93, 0.3, "tbNDC");
//		pt->SetTextSize(0.05);
//		pt->SetTextColor(kGray+2);
//		pt->SetFillColor(0);
//		pt->SetLineWidth(0);
//		pt->SetBorderSize(0);
//		pt->AddText( m_textLabel.c_str() );
//		pt->SetTextFont(62);
//		pt->Draw();
//	}


//	return pCanvas;
}
