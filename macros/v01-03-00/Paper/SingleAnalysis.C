#include "SingleAnalysis.h"

// -- root headers
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TPaveText.h>
#include <TLegend.h>
#include <TSystemFile.h>
#include <TString.h>
//#include <TIter.h>
#include <TSystemDirectory.h>
#include <TSystem.h>
#include <TList.h>
#include <TLatex.h>

// -- std headers
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <fstream>

//--------------------------------------------------------------------------------------------------------------------

std::string DataTypeToDrawableString(DataType dataType)
{
  switch(dataType)
    {
    case TB_SPS_AUG_2012:
      return "CERN SPS H6";
    case TB_SPS_AUG_2012_NO_PFA:
      return "CERN SPS H6 - No PFA";
    case TB_SPS_AUG_2012_SPILL_CUT:
      return "CERN SPS H6 - spill cut";
    case TB_SPS_AUG_2012_SPILL_CUT_CALIB:
      return "CERN SPS H6 - spill cut - recalibrated";
    case FTFP_BERT_HP:
      return "FTFP_BERT_HP";
    case FTF_BIC:
      return "FTF_BIC";
    case FTFP_BERT_HP_NO_PFA:
      return "FTFP_BERT_HP - No PFA";
    case FTF_BIC_NO_PFA:
      return "FTF_BIC - No PFA";
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
    case TB_SPS_AUG_2012_SPILL_CUT:
      m_drawAttributeMap[MARKER_STYLE] = 22;
      m_drawAttributeMap[MARKER_COLOR] = kPink;
      m_drawAttributeMap[LINE_COLOR] = kPink;
      break;
    case TB_SPS_AUG_2012_SPILL_CUT_CALIB:
      m_drawAttributeMap[MARKER_STYLE] = 25;
      m_drawAttributeMap[MARKER_COLOR] = kGreen;
      m_drawAttributeMap[LINE_COLOR] = kGreen;
      break;
      
    case FTFP_BERT_HP_NO_PFA:
      m_drawAttributeMap[MARKER_STYLE] = 23;
      m_drawAttributeMap[MARKER_COLOR] = kOrange;
      m_drawAttributeMap[LINE_COLOR] = kOrange;
      break;
    case FTF_BIC_NO_PFA:
      m_drawAttributeMap[MARKER_STYLE] = 29;
      m_drawAttributeMap[MARKER_COLOR] = kGreen;
      m_drawAttributeMap[LINE_COLOR] = kGreen;
      break;
    case TB_SPS_AUG_2012_NO_PFA:
      m_drawAttributeMap[MARKER_STYLE] = 21;
      m_drawAttributeMap[MARKER_COLOR] = kPink;
      m_drawAttributeMap[LINE_COLOR] = kPink;
      break;
    case TB_SPS_AUG_2012:
    default:
      m_drawAttributeMap[MARKER_STYLE] = 21;
      m_drawAttributeMap[MARKER_COLOR] = kBlack;
      m_drawAttributeMap[LINE_COLOR] = kBlack;
      break;
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
	m_nHit3(0)
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
}

//--------------------------------------------------------------------------------------------------------------------

void TreeAnalyzer::Loop(int pointID, double xGraph, GraphMap &graphMap)
{
	if (m_pTree == 0)
		return;

	Long64_t nEntries = m_pTree->GetEntriesFast();

	unsigned int nProcessedEvents = 0;
	float meanNPfos = 0.f;
	float meanEfficiency = 0.f;

	TH1F *pEnergyDistribution = new TH1F("tmp_histo_single_erec", "", 121, 0, 120);

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
		int totalNHit = 0;
		int chargedNHit = 0;

		pEnergyDistribution->Fill(m_chargedEnergy);

		// analyze pfos and extract the purity/efficiency
		for(int p=0 ; p<m_nPfos ; p++)
		{
			totalNHit += m_nHit->at(p);

			// charged case
			if(m_charge->at(p) != 0)
			{
				chargedNHit += m_nHit->at(p);

			}
		}

		if(totalNHit != 0)
			meanEfficiency += static_cast<float>(chargedNHit) / static_cast<float>(totalNHit);

	} // end of loop

	meanEfficiency /= nProcessedEvents;
	meanNPfos /= nProcessedEvents;

	TF1 *pGaus = new TF1("gausFunc","gaus", 0, 120);
	pEnergyDistribution->Fit(pGaus, "NQ", "");
	pEnergyDistribution->Fit(pGaus, "NQ", "", pGaus->GetParameter(1)-1.5*pGaus->GetParameter(2), pGaus->GetParameter(1)+1.5*pGaus->GetParameter(2));

	// get mean charged energy from fit
	float meanChargedEnergy = pGaus->GetParameter(1);
	float meanChargedEnergyError = pGaus->GetParError(1);

	// compute energy deviation
	float chargedEnergyDeviation = ( meanChargedEnergy - static_cast<float>(xGraph) ) / static_cast<float>(xGraph);
	float chargedEnergyDeviationError = meanChargedEnergyError / static_cast<float>(xGraph);

	// get charged energy resolution from fit
	float chargedEnergyResolution = pGaus->GetParameter(2) / pGaus->GetParameter(1);
	float chargedEnergyResolutionError = std::sqrt(std::pow(pGaus->GetParError(2)/pGaus->GetParameter(1), 2)
		+ std::pow((pGaus->GetParameter(2)*pGaus->GetParError(1))/(pGaus->GetParameter(1)*pGaus->GetParameter(1)), 2));

	// no delete of TF1 since the distribution owns it. Deleted at next delete
	delete pEnergyDistribution;


	graphMap[EFFICIENCY]->SetPoint(pointID, xGraph, meanEfficiency);
	graphMap[EFFICIENCY]->SetPointError(pointID, 0, 1 / std::sqrt(nProcessedEvents));

	graphMap[E_REC]->SetPoint(pointID, xGraph, meanChargedEnergy);
	graphMap[E_REC]->SetPointError(pointID, 0, meanChargedEnergyError);

	graphMap[E_RESOL]->SetPoint(pointID, xGraph, chargedEnergyResolution);
	graphMap[E_RESOL]->SetPointError(pointID, 0, chargedEnergyResolutionError);

	graphMap[E_REC_DEVIATION]->SetPoint(pointID, xGraph, chargedEnergyDeviation);
	graphMap[E_REC_DEVIATION]->SetPointError(pointID, 0, chargedEnergyDeviationError);

	graphMap[N_PFOS]->SetPoint(pointID, xGraph, meanNPfos);
	graphMap[N_PFOS]->SetPointError(pointID, 0, 1 / std::sqrt(nProcessedEvents));
}

//--------------------------------------------------------------------------------------------------------------------

void TreeAnalyzer::FillSpecificNPfosGraph(TGraphErrors *pGraphErrors)
{
	if (m_pTree == 0)
		return;

	Long64_t nEntries = m_pTree->GetEntriesFast();

	std::vector<double> nPfosVector(10, 0.f);
	int nProcessedEvents = 0;

	for (Long64_t jentry=0 ; jentry<nEntries ; jentry++)
	{
		Long64_t ientry = this->LoadTree(jentry);

		if (ientry < 0)
			break;

		m_pTree->GetEntry(jentry);

		if(static_cast<int>(nPfosVector.size())-1 < m_nPfos)
		{
			std::cout << "Too much pfos (" << m_nPfos << "). Skipping ..." << std::endl;
			continue;
		}

		nProcessedEvents++;
		nPfosVector[m_nPfos] ++;
	} // end of loop

	for(unsigned int i=0 ; i<nPfosVector.size() ; i++)
	{
		pGraphErrors->SetPoint(i, static_cast<double>(i), nPfosVector.at(i) / static_cast<double>(nProcessedEvents));
		pGraphErrors->SetPointError(i, 0, 0);
	}
}

//--------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------

SingleAnalysis::SingleAnalysis() :
		m_saveGraphs(false),
		m_rootFileDirectory("/home/remi/git/SDHCALArborPFA/output/v01-04-00/Separation/"),
		m_treeName("PfoMonitoring"),
		m_computeSystematics(false)
{
	// default list of data set to process
	m_dataTypeVector.push_back(TB_SPS_AUG_2012);
	m_dataTypeVector.push_back(FTFP_BERT_HP);
	m_dataTypeVector.push_back(FTF_BIC);

	// set to be read from a simple file
	m_dataSourceBitSet.set(TB_SPS_AUG_2012_NO_PFA, true);
	m_dataSourceBitSet.set(FTFP_BERT_HP_NO_PFA, true);
	m_dataSourceBitSet.set(FTF_BIC_NO_PFA, true);
}

//--------------------------------------------------------------------------------------------------------------------

SingleAnalysis::~SingleAnalysis()
{
	m_dataTypeVector.clear();

	for(CanvasMultiGraphMap::iterator iter = m_canvasMultiGraphMap.begin(), endIter = m_canvasMultiGraphMap.end() ;
			endIter != iter ; ++iter)
	{
		delete iter->second.first;
		delete iter->second.second;
	}

	m_canvasMultiGraphMap.clear();

	delete m_pERecCanvas;
}

//--------------------------------------------------------------------------------------------------------------------

void SingleAnalysis::Run()
{
    std::cout << "SingleAnalysis::Run() !" << std::endl;
    
    this->ConfigureMultiGraphMap();
    this->FillGraphs();
    this->DrawGraphs();
    
    if(m_saveGraphs)
      this->SaveGraphs();
}

//--------------------------------------------------------------------------------------------------------------------

void SingleAnalysis::SetEnergies(const IntVector &energies)
{
	m_energies = energies;
}

//--------------------------------------------------------------------------------------------------------------------

void SingleAnalysis::SetFileParameters(const std::string &rootFileDirectory,
		const std::string &treeName)
{
	m_rootFileDirectory = rootFileDirectory;
	m_treeName = treeName;
}

//--------------------------------------------------------------------------------------------------------------------

void SingleAnalysis::SetSaveGraphs(bool save)
{
	m_saveGraphs = save;
}

//--------------------------------------------------------------------------------------------------------------------

void SingleAnalysis::SetDataTypeList(const DataTypeVector &dataTypeVector)
{
  if( ! dataTypeVector.empty() )
    m_dataTypeVector = dataTypeVector;
}

//--------------------------------------------------------------------------------------------------------------------

void SingleAnalysis::SetComputeSystematics(bool compute)
{
	m_computeSystematics = compute;
}

//--------------------------------------------------------------------------------------------------------------------

void SingleAnalysis::ConfigureMultiGraphMap()
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
	m_canvasMultiGraphMap[EFFICIENCY].first = this->CreateCanvas("SingleParticle_Efficiency", "Hit clustering efficiency");
	m_canvasMultiGraphMap[EFFICIENCY].second = this->CreateMultiGraph();

	m_canvasMultiGraphMap[E_REC].first = this->CreateCanvas("SingleParticle_ERec", "Reconstructed energy");
	m_canvasMultiGraphMap[E_REC].second = this->CreateMultiGraph();

	m_canvasMultiGraphMap[E_REC_DEVIATION].first = this->CreateCanvas("SingleParticle_ERecDeviation", "Deviation from the reconstructed energy");
	m_canvasMultiGraphMap[E_REC_DEVIATION].second = this->CreateMultiGraph();

	m_canvasMultiGraphMap[E_RESOL].first = this->CreateCanvas("SingleParticle_EResol", "Energy resolution");
	m_canvasMultiGraphMap[E_RESOL].second = this->CreateMultiGraph();

	m_canvasMultiGraphMap[N_PFOS].first = this->CreateCanvas("SingleParticle_NPfos", "Number of Pfos");
	m_canvasMultiGraphMap[N_PFOS].second = this->CreateMultiGraph();

	m_canvasMultiGraphMap[N_PFOS_20GEV].first = this->CreateCanvas("SingleParticle_NPfosAt20GeV", "Number of Pfos at 20 GeV");
	m_canvasMultiGraphMap[N_PFOS_20GEV].second = this->CreateMultiGraph();

	m_canvasMultiGraphMap[N_PFOS_70GEV].first = this->CreateCanvas("SingleParticle_NPfosAt70GeV", "Number of Pfos at 70 GeV");
	m_canvasMultiGraphMap[N_PFOS_70GEV].second = this->CreateMultiGraph();

	m_pERecCanvas = new TCanvas("SingleParticle_ERec_and_deviation", "ERec and its deviation", 14, 48, 600, 741);
	m_pERecCanvas->SetFillColor(0);
	m_pERecCanvas->SetBorderMode(0);
	m_pERecCanvas->SetBorderSize(2);
	m_pERecCanvas->SetTickx(1);
	m_pERecCanvas->SetTicky(1);
	m_pERecCanvas->SetLeftMargin(0.1666667);
	m_pERecCanvas->SetRightMargin(0.05660377);
	m_pERecCanvas->SetTopMargin(0.0256917);
	m_pERecCanvas->SetBottomMargin(0.07692308);
	m_pERecCanvas->SetFrameLineWidth(1);
}

//--------------------------------------------------------------------------------------------------------------------

void SingleAnalysis::FillGraphs()
{
  std::cout << "Filling graphs" << std::endl;

	for(DataTypeVector::const_iterator dataIter = m_dataTypeVector.begin(), dataEndIter = m_dataTypeVector.end() ;
			dataEndIter != dataIter ; ++dataIter)
	{
		DataType dataType = *dataIter;

		if( m_dataSourceBitSet.test(dataType) )
		{
			this->FillFromFile(dataType);
		}
		else
		{
			this->FillFromTree(dataType);
		}
	}
}

//--------------------------------------------------------------------------------------------------------------------

void SingleAnalysis::FillFromTree(DataType dataType)
{
	DrawAttributeMapping drawAttributeMapping(dataType);

	GraphMap graphMap;
	graphMap[EFFICIENCY] = drawAttributeMapping.ConfigureGraph(new TGraphErrors());
	graphMap[E_REC] = drawAttributeMapping.ConfigureGraph(new TGraphErrors());
	graphMap[E_REC_DEVIATION] = drawAttributeMapping.ConfigureGraph(new TGraphErrors());
	graphMap[E_RESOL] = drawAttributeMapping.ConfigureGraph(new TGraphErrors());
	graphMap[N_PFOS] = drawAttributeMapping.ConfigureGraph(new TGraphErrors());
	graphMap[N_PFOS_20GEV] = drawAttributeMapping.ConfigureGraph(new TGraphErrors());
	graphMap[N_PFOS_70GEV] = drawAttributeMapping.ConfigureGraph(new TGraphErrors());

	int pointID = 0;

	for(IntVector::iterator iter = m_energies.begin(), endIter = m_energies.end() ;
			endIter != iter ; ++iter)
	{
		int energy = *iter;

		std::string completeFileName =
			m_rootFileDirectory
			+ this->GetDataName(dataType)
			+ "/"
			+ this->GetFileName(energy, dataType);

		TFile *pFile = TFile::Open(completeFileName.c_str());

		if(!pFile)
			throw std::runtime_error("Wrong file name !");

		TTree *pTree = (TTree *) pFile->Get(m_treeName.c_str());

		if(!pTree)
			throw std::runtime_error("Wrong tree name !");

		TreeAnalyzer treeAnalyzer(pTree);
		treeAnalyzer.Loop(pointID, static_cast<double>(energy), graphMap);

		if(energy == 20)
		{
			treeAnalyzer.FillSpecificNPfosGraph(graphMap[N_PFOS_20GEV]);
		}
		else if(energy == 70)
		{
			treeAnalyzer.FillSpecificNPfosGraph(graphMap[N_PFOS_70GEV]);
		}

		// compute systematic errors if required !
		if( m_computeSystematics )
			this->ComputeSystematics(pointID, energy, dataType, graphMap);

		pointID++;
	}

	// Add graphs in multi graph map
	for(GraphMap::const_iterator graphIter = graphMap.begin(), graphEndIter = graphMap.end() ;
			graphEndIter != graphIter ; ++graphIter)
	m_canvasMultiGraphMap[graphIter->first].second->Add(graphIter->second);
}

//--------------------------------------------------------------------------------------------------------------------

void SingleAnalysis::FillFromFile(DataType dataType)
{
	DrawAttributeMapping drawAttributeMapping(dataType);
	GraphMap graphMap;

	graphMap[E_REC] = drawAttributeMapping.ConfigureGraph(new TGraphErrors());
	graphMap[E_REC_DEVIATION] = drawAttributeMapping.ConfigureGraph(new TGraphErrors());
	graphMap[E_RESOL] = drawAttributeMapping.ConfigureGraph(new TGraphErrors());

	int pointID = 0;

	std::ifstream ifile;
	std::string completeFileName =
		m_rootFileDirectory
		+ this->GetDataName(dataType)
		+ "/"
		+ this->GetBasicFileName(dataType);

	std::cout << "File name is " << completeFileName << std::endl;

	ifile.open( completeFileName.c_str(), std::ios::in );

	if( ! ifile.is_open() || ! ifile.good() )
		throw std::runtime_error("Wrong file name !");

	unsigned int nEnergies = 0;
	ifile >> nEnergies;

	if( 0 == nEnergies )
		throw std::runtime_error("Invalid n energy points");

	for( unsigned int e=0 ; e<nEnergies ; e++ )
	{
		int energy = 0;
		ifile >> energy;

		std::cout << "Energy is " << energy << std::endl;

		float erec, erecError, eresol, eresolError, erecDev, erecDevError = 0.f;
		ifile >> erec >> erecError >> eresol >> eresolError;

		std::cout << "Erec " << erec << " , erecError " << erecError << " , eresol " << eresol << " , eresolError " << eresolError << std::endl;

		erecDev = (erec - energy) / energy;
		erecDevError = erecError / energy;

		graphMap[E_REC]->SetPoint(e, energy, erec);
		graphMap[E_REC]->SetPointError(e, 0, erecError);

		graphMap[E_REC_DEVIATION]->SetPoint(e, energy, erecDev);
		graphMap[E_REC_DEVIATION]->SetPointError(e, 0, erecDevError);

		graphMap[E_RESOL]->SetPoint(e, energy, eresol);
		graphMap[E_RESOL]->SetPointError(e, 0, eresolError);
	}

	// Add graphs in multi graph map
	for(GraphMap::const_iterator graphIter = graphMap.begin(), graphEndIter = graphMap.end() ;
			graphEndIter != graphIter ; ++graphIter)
		m_canvasMultiGraphMap[graphIter->first].second->Add(graphIter->second);
}

//--------------------------------------------------------------------------------------------------------------------

void SingleAnalysis::ComputeSystematics(int pointID, int energy, DataType dataType, GraphMap &graphMapAtNominalValues)
{
	TSystemDirectory directory((m_rootFileDirectory + this->GetDataName(dataType)
			+ "/SYSTEMATICS/").c_str(), (m_rootFileDirectory + this->GetDataName(dataType)
					+ "/SYSTEMATICS/").c_str());
	TList *pFileList = directory.GetListOfFiles();

	if( ! pFileList )
	{
		std::cout << "No systematics study performed. Directory '" << m_rootFileDirectory + this->GetDataName(dataType)
					+ "/SYSTEMATICS/" << "' doesn't exists" << std::endl;
		return;
	}

	std::vector<std::string> pm;
	pm.push_back("+");
	pm.push_back("-");

	GraphSystErrorMap upperErrorMap;
	GraphSystErrorMap lowerErrorMap;

	upperErrorMap[EFFICIENCY] = 0.d;
	upperErrorMap[E_REC] = 0.d;
	upperErrorMap[E_REC_DEVIATION] = 0.d;
	upperErrorMap[E_RESOL] = 0.d;
	upperErrorMap[N_PFOS] = 0.d;

	lowerErrorMap[EFFICIENCY] = 0.d;
	lowerErrorMap[E_REC] = 0.d;
	lowerErrorMap[E_REC_DEVIATION] = 0.d;
	lowerErrorMap[E_RESOL] = 0.d;
	lowerErrorMap[N_PFOS] = 0.d;

	for(unsigned int sp=DISTANCE_1 ; sp<N_SYSTEMATIC_PARAMETERS ; sp++)
	{
		unsigned int parameterID = sp+1;

		for(unsigned int signID=0 ; signID<pm.size() ; signID++)
		{
			std::string sign = pm.at( signID );

			TString fileName =
					"SingleParticleReconstruction_"
					+ this->GetEnergyToString(dataType, energy)
					+ "_cut_ArborPFA_"
					+ this->GetDataName(dataType)
					+ "_P"
					+ TString::UItoa(parameterID, 10)
					+ "_S" + sign + "_basic.root";

			std::cout << "File name is " << fileName << " !!!!!" << std::endl;

			TString completeFileName = m_rootFileDirectory + this->GetDataName(dataType)
					+ "/SYSTEMATICS/" + fileName;

			TFile *pFile = TFile::Open(completeFileName.Data());

			if( ! pFile )
			{
				std::cerr << "Wrong sys file name !" << std::endl;
				continue;
			}

			TTree *pTree = (TTree *) pFile->Get(m_treeName.c_str());

			if(!pTree)
			{
				std::cerr << "Wrong sys tree name !" << std::endl;
				continue;
			}

			GraphMap graphMap;
			graphMap[EFFICIENCY] = new TGraphErrors();
			graphMap[E_REC] = new TGraphErrors();
			graphMap[E_REC_DEVIATION] = new TGraphErrors();
			graphMap[E_RESOL] = new TGraphErrors();
			graphMap[N_PFOS] = new TGraphErrors();

			TreeAnalyzer treeAnalyzer(pTree);
			treeAnalyzer.Loop(pointID, static_cast<double>(energy), graphMap);

			this->ComputeSystematics(pointID, graphMapAtNominalValues, graphMap,
					EFFICIENCY, upperErrorMap, lowerErrorMap);

			this->ComputeSystematics(pointID, graphMapAtNominalValues, graphMap,
					E_REC, upperErrorMap, lowerErrorMap);

			this->ComputeSystematics(pointID, graphMapAtNominalValues, graphMap,
					E_REC_DEVIATION, upperErrorMap, lowerErrorMap);

			this->ComputeSystematics(pointID, graphMapAtNominalValues, graphMap,
					E_RESOL, upperErrorMap, lowerErrorMap);

			this->ComputeSystematics(pointID, graphMapAtNominalValues, graphMap,
					N_PFOS, upperErrorMap, lowerErrorMap);
		}
	}

	delete pFileList;

	// First try : combine upper and lower values for efficiency
	graphMapAtNominalValues[EFFICIENCY]->SetPointError(pointID, 0,
			graphMapAtNominalValues[EFFICIENCY]->GetEY()[pointID]
		+ std::sqrt( upperErrorMap[EFFICIENCY] + lowerErrorMap[EFFICIENCY] ) );

	graphMapAtNominalValues[E_REC]->SetPointError(pointID, 0,
			graphMapAtNominalValues[E_REC]->GetEY()[pointID]
		+ std::sqrt( upperErrorMap[E_REC] + lowerErrorMap[E_REC] ) );

	graphMapAtNominalValues[E_REC_DEVIATION]->SetPointError(pointID, 0,
			graphMapAtNominalValues[E_REC_DEVIATION]->GetEY()[pointID]
		+ std::sqrt( upperErrorMap[E_REC_DEVIATION] + lowerErrorMap[E_REC_DEVIATION] ) );

	graphMapAtNominalValues[E_RESOL]->SetPointError(pointID, 0,
			graphMapAtNominalValues[E_RESOL]->GetEY()[pointID]
		+ std::sqrt( upperErrorMap[E_RESOL] + lowerErrorMap[E_RESOL] ) );

	graphMapAtNominalValues[N_PFOS]->SetPointError(pointID, 0,
			graphMapAtNominalValues[N_PFOS]->GetEY()[pointID]
		+ std::sqrt( upperErrorMap[N_PFOS] + lowerErrorMap[N_PFOS] ) );
}

//--------------------------------------------------------------------------------------------------------------------

void SingleAnalysis::ComputeSystematics(int pointID, const GraphMap &nominalMap, const GraphMap &systGraphMap,
		GraphName graphName, GraphSystErrorMap &upperBoundErrorMap, GraphSystErrorMap &lowerBoundErrorMap)
{
	double systVar = 0.d;
	double nominalVar = 0.d;
	double systVarDiff = 0.d;

	nominalVar = nominalMap.find(graphName)->second->GetY()[pointID];
	systVar = systGraphMap.find(graphName)->second->GetY()[pointID];
	systVarDiff = systVar - nominalVar;

	std::cout << "Graph name : " << graphName << std::endl;
	std::cout << "syst error on point id " << pointID << " is " << systVarDiff << std::endl;

	if( systVarDiff > 0.d )
		upperBoundErrorMap[graphName] += systVarDiff*systVarDiff;
	else
		lowerBoundErrorMap[graphName] += systVarDiff*systVarDiff;
}

//--------------------------------------------------------------------------------------------------------------------

void SingleAnalysis::DrawGraphs()
{
	std::cout << "Drawing graphs" << std::endl;

	// special case for erec and deviation
	m_pERecCanvas->cd();

	TPad *pERecPad = new TPad("ERecPad", "ERecPad", 0.02, 0.37, 0.95, 0.99);
	pERecPad->Draw();
	pERecPad->cd();
	pERecPad->Range(-19.23077,0.01,96.15385,1428.571);
	pERecPad->SetFillColor(0);
	pERecPad->SetBorderMode(0);
	pERecPad->SetBorderSize(2);
	pERecPad->SetTickx(1);
	pERecPad->SetTicky(1);
	pERecPad->SetLeftMargin(0.1666667);
	pERecPad->SetRightMargin(0.01);
	pERecPad->SetTopMargin(0.02);
	pERecPad->SetBottomMargin(0.0);
	pERecPad->SetFrameLineWidth(1);
	pERecPad->SetFrameBorderMode(0);

	m_canvasMultiGraphMap[E_REC].second->Draw("ap");
	this->PostDrawMultiGraph(E_REC, m_canvasMultiGraphMap[E_REC].second);

	TLegend *pLegend = pERecPad->BuildLegend();
	pLegend->SetBorderSize(0);
	pLegend->SetLineColor(0);
	pLegend->SetLineStyle(0);
	pLegend->SetLineWidth(1);
	pLegend->SetFillColor(0);
	pLegend->SetFillStyle(0);
	pLegend->SetTextSize(0.04);

	pERecPad->Modified();

	m_pERecCanvas->cd();

	TPad *pERecDeviationPad = new TPad("ERecDeviationPad", "ERecDeviationPad", 0.02, 0, 0.95, 0.37);
	pERecDeviationPad->Draw();
	pERecDeviationPad->cd();
	pERecDeviationPad->Range(-19.23077,-0.3993507,96.15385,0.25);
	pERecDeviationPad->SetFillColor(0);
	pERecDeviationPad->SetBorderMode(0);
	pERecDeviationPad->SetBorderSize(2);
	pERecDeviationPad->SetTickx(1);
	pERecDeviationPad->SetTicky(1);
	pERecDeviationPad->SetLeftMargin(0.1666667);
	pERecDeviationPad->SetRightMargin(0.01);
	pERecDeviationPad->SetTopMargin(0);
	pERecDeviationPad->SetBottomMargin(0.23);
	pERecDeviationPad->SetFrameLineWidth(1);
	pERecDeviationPad->SetFrameBorderMode(0);

	m_canvasMultiGraphMap[E_REC_DEVIATION].second->Draw("ap");

	TF1 *pLin = new TF1("lin", "0", 0, 90);
	pLin->SetLineColor(kBlack);
	pLin->SetLineWidth(1);
	pLin->SetLineStyle(2);
	pLin->Draw("same");

	this->PostDrawMultiGraph(E_REC_DEVIATION, m_canvasMultiGraphMap[E_REC_DEVIATION].second);

	pERecDeviationPad->Modified();

	for(CanvasMultiGraphMap::iterator graphIter = m_canvasMultiGraphMap.begin(), graphEndIter = m_canvasMultiGraphMap.end() ;
			graphEndIter != graphIter ; ++graphIter)
	{
		if(graphIter->first == E_REC || graphIter->first == E_REC_DEVIATION)
			continue;

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

void SingleAnalysis::SaveGraphs()
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

std::string SingleAnalysis::GetDataName(DataType dataType) const
{
  switch(dataType)
    {
    case TB_SPS_AUG_2012_NO_PFA:
      return "TEST_BEAM";
    case TB_SPS_AUG_2012:
      return "TEST_BEAM";
    case TB_SPS_AUG_2012_SPILL_CUT:
      return "TEST_BEAM";
    case TB_SPS_AUG_2012_SPILL_CUT_CALIB:
      return "TEST_BEAM";
    case FTFP_BERT_HP:
      return "FTFP_BERT_HP";
    case FTFP_BERT_HP_NO_PFA:
      return "FTFP_BERT_HP";
    case FTF_BIC:
      return "FTF_BIC";
    case FTF_BIC_NO_PFA:
      return "FTF_BIC";
    default:
      return "UNKNOWN";
    }
}

//--------------------------------------------------------------------------------------------------------------------

std::string SingleAnalysis::GetFileName(int energy, DataType dataType) const
{
	std::string fileName =
			"SingleParticleReconstruction_"
		  + this->GetEnergyToString(dataType, energy)
		  + "_cut_";

	if(dataType == TB_SPS_AUG_2012_SPILL_CUT)
		fileName += "spillcut_";
	else if(dataType == TB_SPS_AUG_2012_SPILL_CUT_CALIB)
		fileName += "spillcut_calibrated_";

	fileName += "ArborPFA_"
		  + this->GetDataName(dataType)
		  + "_basic.root";

	return fileName;
}

//--------------------------------------------------------------------------------------------------------------------

std::string SingleAnalysis::GetBasicFileName(DataType dataType)
{
  std::string fileName =
    "NoPFAData_" + this->GetDataName(dataType) + ".txt";

  return fileName;
}

//--------------------------------------------------------------------------------------------------------------------

std::string SingleAnalysis::GetEnergyToString(DataType dataType, int energy) const
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

TCanvas *SingleAnalysis::CreateCanvas(const std::string &canvasName, const std::string &canvasTitle) const
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

TMultiGraph *SingleAnalysis::CreateMultiGraph() const
{
	return new TMultiGraph();
}

//--------------------------------------------------------------------------------------------------------------------

void SingleAnalysis::PostDrawMultiGraph(GraphName graphName, TMultiGraph *pMultiGraph) const
{
	if(NULL == pMultiGraph)
		return;


	switch(graphName)
	{
	case E_REC:
	{
		pMultiGraph->GetYaxis()->SetLabelFont(42);
		pMultiGraph->GetYaxis()->SetTitleSize(0.07);
		pMultiGraph->GetYaxis()->SetTitleOffset(0.8);
		pMultiGraph->GetYaxis()->SetTitleFont(42);
		pMultiGraph->GetYaxis()->SetLabelSize(0.045);
		break;
	}
	case E_REC_DEVIATION:
	{
		pMultiGraph->GetXaxis()->SetTitle("E_{beam} [GeV]");
		pMultiGraph->GetXaxis()->SetLabelFont(42);
		pMultiGraph->GetXaxis()->SetLabelSize(0.07);
		pMultiGraph->GetXaxis()->SetTitleSize(0.1);
		pMultiGraph->GetXaxis()->SetTitleOffset(1);
		pMultiGraph->GetXaxis()->SetTitleFont(42);

		pMultiGraph->GetYaxis()->SetLabelFont(42);
		pMultiGraph->GetYaxis()->SetTitleSize(0.12);
		pMultiGraph->GetYaxis()->SetTitleOffset(0.5);
		pMultiGraph->GetYaxis()->SetTitleFont(42);
		pMultiGraph->GetYaxis()->SetLabelSize(0.07);
		break;
	}
	default:
	{
		pMultiGraph->GetXaxis()->SetTitle("E_{beam} [GeV]");
		pMultiGraph->GetXaxis()->SetLabelFont(42);
		pMultiGraph->GetXaxis()->SetTitleSize(0.05);
		pMultiGraph->GetXaxis()->SetTitleOffset(1.);
		pMultiGraph->GetXaxis()->SetTitleFont(42);
		pMultiGraph->GetXaxis()->SetRangeUser(0, 90);

		pMultiGraph->GetYaxis()->SetTitle("");
		pMultiGraph->GetYaxis()->SetLabelFont(42);
		pMultiGraph->GetYaxis()->SetTitleSize(0.045);
		pMultiGraph->GetYaxis()->SetTitleOffset(1.3);
		pMultiGraph->GetYaxis()->SetTitleFont(42);
		pMultiGraph->GetYaxis()->SetLabelSize(0.035);
		break;
	}
	}

	if(graphName != E_REC_DEVIATION)
	{
		TPaveText *pt = new TPaveText(0.3, 0.2, 0.53, 0.3, "tbNDC");
		pt->SetTextSize(0.05);
		pt->SetTextColor(kGray+2);
		pt->SetFillColor(0);
		pt->SetLineWidth(0);
		pt->SetBorderSize(0);
		pt->AddText("CALICE SDHCAL");
		pt->SetTextFont(62);
		pt->Draw();
	}

	// plot per plot customize
	switch(graphName)
	{
	case E_REC:
		pMultiGraph->GetYaxis()->SetTitle("E_{rec}");
		pMultiGraph->GetYaxis()->SetRangeUser(1, 90);
		break;
	case E_REC_DEVIATION:
		pMultiGraph->GetYaxis()->SetTitle("#DeltaE/E_{beam}");
		pMultiGraph->GetYaxis()->SetRangeUser(-0.12, 0.12);
		break;
	case E_RESOL:
		pMultiGraph->GetYaxis()->SetTitle("#sigma_{E}/E_{rec}");
		pMultiGraph->GetYaxis()->SetRangeUser(0, 0.4);
		break;
	case N_PFOS:
		pMultiGraph->GetYaxis()->SetTitle("<N_{pfos}>");
		pMultiGraph->GetYaxis()->SetRangeUser(0, 2);
		break;
	case N_PFOS_20GEV:
	case N_PFOS_70GEV:
		pMultiGraph->GetYaxis()->SetTitle("# events (normalized to unity)");
		pMultiGraph->GetYaxis()->SetRangeUser(0, 1);
		pMultiGraph->GetXaxis()->SetRangeUser(-0.99, 5.99);
		break;
	case EFFICIENCY:
		pMultiGraph->GetYaxis()->SetTitle("Hit clustering efficiency #epsilon_{s}");
		pMultiGraph->GetYaxis()->SetRangeUser(0.8, 1.1);
		break;
	default:
		break;
	}
}


















