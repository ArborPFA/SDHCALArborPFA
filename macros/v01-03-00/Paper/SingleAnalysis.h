#ifndef OverlayAnalysis_h
#define OverlayAnalysis_h 1

// -- root headers
#include <TChain.h>
#include <TFile.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TMultiGraph.h>

// -- std headers
#include <vector>
#include <map>
#include <bitset>

/**
 *  @brief  DrawAttribute enum
 */
enum DrawAttribute
{
  MARKER_STYLE,
  MARKER_COLOR,
  MARKER_SIZE,
  LINE_COLOR,
  LINE_STYLE,
  LINE_WIDTH,
  FILL_COLOR,
  FILL_STYLE
};

//--------------------------------------------------------------------------------------------------------------------

/**
 *  @brief  DataType enum
 */
enum DataType
{
  TB_SPS_AUG_2012_NO_PFA,
  FTFP_BERT_HP_NO_PFA,
  FTF_BIC_NO_PFA,
  TB_SPS_AUG_2012,
  TB_SPS_AUG_2012_SPILL_CUT,
  TB_SPS_AUG_2012_SPILL_CUT_CALIB,
  FTFP_BERT_HP,
  FTF_BIC,
  N_DATA_TYPES
};

//--------------------------------------------------------------------------------------------------------------------

/**
 *  @brief
 */
enum GraphName
{
  EFFICIENCY,
  E_REC,
  E_REC_DEVIATION,
  E_RESOL,
  N_PFOS,
  N_PFOS_20GEV,
  N_PFOS_70GEV
};

//--------------------------------------------------------------------------------------------------------------------

/**
 *  @brief  Convert data type to a drawable string.
 *          Typically used in root legends
 */
std::string DataTypeToDrawableString(DataType dataType);

//--------------------------------------------------------------------------------------------------------------------

typedef std::map<GraphName, TGraphErrors *> GraphMap;
typedef std::map<DrawAttribute, float> DrawAttributeMap;
typedef std::pair<TCanvas*, TMultiGraph*> CanvasMultiGraphPair;
typedef std::map<GraphName, CanvasMultiGraphPair> CanvasMultiGraphMap;
typedef std::vector<DataType> DataTypeVector;
typedef std::vector<int> IntVector;

#pragma link C++ class DataTypeVector;
#pragma link C++ class IntVector;

//--------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------

/**
 *  @brief  DrawAttributeMapping class
 */
class DrawAttributeMapping
{
public:
	/**
	 *  @brief  Constructor
	 */
	DrawAttributeMapping(DataType dataType);

	/**
	 *  @brief  Get attribute mapping
	 */
	float GetAttribute(DrawAttribute attribute) const;

	/**
	 *  @brief  Configure the graph
	 */
	TGraphErrors *ConfigureGraph(TGraphErrors *pGraph);

private:
	DrawAttributeMap    m_drawAttributeMap;
	DataType            m_dataType;
};

//--------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------

/**
 *  @brief  TreeAnalyzer class
 */
class TreeAnalyzer
{
public:
	/**
	 *  @brief  Constructor
	 */
	TreeAnalyzer(TTree *pTree);

	/**
	 *  @brief  Destructor
	 */
	~TreeAnalyzer();

	/**
	 *  @brief  Initialize the analysis with the given tree.
	 *          Called in contructor
	 */
	void Init(TTree *tree);

	/**
	 *  @brief Get tree entry
	 */
	Int_t GetEntry(Long64_t entry);

	/**
	 *  @brief  Load the entire tree for the given entry
	 */
	Long64_t LoadTree(Long64_t entry);

	/**
	 *  @brief  Loop over the tree entries and fill all the y values of
	 *          graphs at coordinate x in the graph map for the point 'pointID'
	 */
	void Loop(int pointID, double xGraph, GraphMap &graphMap);

	/**
	 *  @brief  Fill the graph with the distribution of number of pfos
	 */
	void FillSpecificNPfosGraph(TGraphErrors *pGraphErrors);

private:

   TTree          *m_pTree;

   // Declaration of leaf types
   Int_t                  m_nPfos;
   Int_t                  m_nNeutralPfos;
   Int_t                  m_nChargedPfos;
   Float_t                m_neutralEnergy;
   Float_t               m_chargedEnergy;
   std::vector<float>   *m_energy;
   std::vector<float>   *m_momentum;
   std::vector<int>     *m_nTracks;
   std::vector<int>     *m_nClusters;
   std::vector<int>     *m_charge;
   std::vector<float>   *m_mass;
   std::vector<int>     *m_pid;
   std::vector<int>     *m_nHit;
   std::vector<int>     *m_nHit1;
   std::vector<int>     *m_nHit2;
   std::vector<int>     *m_nHit3;

   // List of branches
   TBranch        *b_nPfos;
   TBranch        *b_nNeutralPfos;
   TBranch        *b_nChargedPfos;
   TBranch        *b_neutralEnergy;
   TBranch        *b_chargedEnergy;
   TBranch        *b_energy;
   TBranch        *b_momentum;
   TBranch        *b_nTracks;
   TBranch        *b_nClusters;
   TBranch        *b_charge;
   TBranch        *b_mass;
   TBranch        *b_pid;
   TBranch        *b_nHit;
   TBranch        *b_nHit1;
   TBranch        *b_nHit2;
   TBranch        *b_nHit3;
};

//--------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------

/**
 *  @brief  SingleAnalysis class
 */
class SingleAnalysis
{
public:
	/**
	 *  @brief  Default constructor
	 */
        SingleAnalysis();

	/**
	 *  @brief  Destructor
	 */
	~SingleAnalysis();

	/**
	 *  @brief  Run the whole analysis.
	 *          Fill the graph, customize them and plot them.
	 */
	void Run();

	/**
	 *  @brief Set file parameters
	 */
	void SetFileParameters(const std::string &rootFileDirectory = "/home/remi/git/SDHCALArborPFA/output/v01-04-00/SingleParticle/",
			const std::string &treeName = "PfoMonitoring");

	/**
	 *  @brief  Set whether to save graphs in files
	 */
	void SetSaveGraphs(bool save = true);

	/**
	 *  @brief  Set energies to process
	 */
	void SetEnergies(const IntVector &energies);

	/**
	 *  @brief  Set data type list to process
	 */
	void SetDataTypeList(const DataTypeVector &dataTypeVector);

private:
	/**
	 *  @brief  Configure all graphs before filling them (allocation + customize)
	 */
	void ConfigureMultiGraphMap();

	/**
	 *  @brief  Run the analysis and fill the graphs
	 */
	void FillGraphs();

	/**
	 *  @brief  Draw all graphs
	 */
	void DrawGraphs();

	/**
	 *  @brief  Save graphs in pdf files if SetSaveGraphs() has been called
	 */
	void SaveGraphs();

private:
	/**
	 *  @brief  Fill the graphs of the target data type from a root tree using a tree analyzer
	 */
	void FillFromTree(DataType dataType);

	/**
	 *  @brief  Fill the graphs of the target data type from a simple file
	 */
	void FillFromFile(DataType dataType);
	
	/**
	 *  @brief  Get the data type converted to string.
	 *          Used in concatenation in file name construction
	 */
	std::string GetDataName(DataType dataType) const;

	/**
	 *  @brief  Build a root file name from different parameters
	 */
	std::string GetFileName(int energy, DataType dataType) const;

	/**
	 *  @brief  Get the basic file name
	 */
	std::string GetBasicFileName(DataType dataType);

	/**
	 *  @brief  Get the energy converted converted to string.
	 *          Used in GetFileName() to convert energy in "EGeV" or run number for test beam data
	 */
	std::string GetEnergyToString(DataType dataType, int energy) const;

	/**
	 *  @brief  Create and configure a TCanvas
	 */
	TCanvas *CreateCanvas(const std::string &canvasName, const std::string &canvasTitle) const;

	/**
	 *  @brief  Create and configure a TMultiGraph
	 */
	TMultiGraph *CreateMultiGraph() const;

	/**
	 *  @brief  Configure multi graph axis. Called after TMultiGraph::Draw()
	 */
	void PostDrawMultiGraph(GraphName graphName, TMultiGraph *pMultiGraph) const;

private:
	IntVector                    m_energies;

	DataTypeVector               m_dataTypeVector;
	CanvasMultiGraphMap          m_canvasMultiGraphMap;
	TCanvas                     *m_pERecCanvas;        ///< Special canvas to combine ERec and its deviation
	std::bitset<N_DATA_TYPES>    m_dataSourceBitSet;

	bool                         m_saveGraphs;
	std::string                  m_rootFileDirectory;
	std::string                  m_treeName;
};




#endif
