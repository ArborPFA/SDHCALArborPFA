#ifndef OverlayAnalysis_h
#define OverlayAnalysis_h 1

// -- root headers
#include <TChain.h>
#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TMultiGraph.h>

// -- std headers
#include <vector>
#include <map>

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
	TB_SPS_AUG_2012,
	FTF_BIC,
	FTFP_BERT_HP
};

//--------------------------------------------------------------------------------------------------------------------

/**
 *  @brief
 */
enum GraphName
{
	N_PFOS,
	NEUTRAL_PURITY,
	NEUTRAL_EFFICIENCY,
	NEUTRAL_RECOVER_PROBA,
	NEUTRAL_ENERGY_DIFFERENCE,
	NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT,
	N_OVERLAID_HITS,
	OVERLAID_HITS_PERCENTAGE
};

//--------------------------------------------------------------------------------------------------------------------

/**
 *  @brief  SystematicsParameters enum
 */
enum SystematicsParameters
{
	DISTANCE_1,
	DISTANCE_2,
	ANGLE,
	BCK_1,
	FWD_1,
	BCK_2,
	FWD_3,
	N_OBJECTS,
	N_SYSTEMATIC_PARAMETERS
};

//--------------------------------------------------------------------------------------------------------------------

/**
 *  @brief  Convert data type to a drawable string.
 *          Typically used in root legends
 */
std::string DataTypeToDrawableString(DataType dataType);

/**
 *  @brief  Get the data type converted to string.
 *          Used in concatenation in file name construction
 */
std::string GetDataName(DataType dataType);

/**
 *  @brief  Build a root file name from different parameters
 */
std::string GetFileName(int neutralEnergy, int chargedEnergy, unsigned int distance, DataType dataType);

/**
 *  @brief  Get the energy converted converted to string.
 *          Used in GetFileName() to convert energy in "EGeV" or run number for test beam data
 */
std::string GetEnergyToString(DataType dataType, int energy);

/**
 *  @brief  Create and configure a TCanvas
 */
TCanvas *CreateCanvas(const std::string &canvasName, const std::string &canvasTitle);

/**
 *  @brief  Create and configure a TMultiGraph
 */
TMultiGraph *CreateMultiGraph();

//--------------------------------------------------------------------------------------------------------------------

typedef std::map<GraphName, TGraphAsymmErrors *> GraphMap;
typedef std::map<GraphName, double> GraphSystErrorMap;
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
	TGraphAsymmErrors *ConfigureGraph(TGraphAsymmErrors *pGraph, int chargedEnergy);

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
	 *
	 */
	void FillNeutralMCEnergy(TH1 *pHistogram);

	/**
	 *
	 */
	void FillChargedMCEnergy(TH1 *pHistogram);

	/**
	 *
	 */
	void FillNOverlaidHits(TGraphAsymmErrors *pGraph);

	/**
	 *
	 */
	void FillOverlaidHitsPercentage(TGraphAsymmErrors *pGraph);

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
   Float_t               m_mcParticleEnergy1;
   Float_t               m_mcParticleEnergy2;
   std::vector<int>     *m_lcioFlagType1;
   std::vector<int>     *m_lcioFlagType2;
   std::vector<int>     *m_lcioFlagType3;

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
   TBranch        *b_mcParticleEnergy1;
   TBranch        *b_mcParticleEnergy2;
   TBranch        *b_lcioFlagType1;
   TBranch        *b_lcioFlagType2;
   TBranch        *b_lcioFlagType3;
};

//--------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------

/**
 *  @brief  OverlayAnalysis class
 */
class OverlayAnalysis
{
public:
	/**
	 *  @brief  Default constructor.
	 *          Initialize the energies :
	 *            * neutral : 10 GeV
	 *            * charged : 10 GeV
	 */
	OverlayAnalysis();

	/**
	 *  @brief  Constructor with neutral and charged energy
	 */
	OverlayAnalysis(int neutralEnergy, int chargedEnergy);

	/**
	 *  @brief  Constructor with neutral and charged energies
	 */
	OverlayAnalysis(const IntVector &neutralEnergies, const IntVector &chargedEnergies);

	/**
	 *  @brief  Destructor
	 */
	~OverlayAnalysis();

	/**
	 *  @brief  Run the whole analysis.
	 *          Fill the graph, customize them and plot them.
	 */
	void Run();

	/**
	 *  @brief  Set parameters related to analyzed separation distances
	 */
	void SetDistanceParameters(unsigned int startDistance = 5, unsigned int endDistance = 30, unsigned int distanceStep = 5);

	/**
	 *  @brief Set file parameters
	 */
	void SetFileParameters(const std::string &rootFileDirectory = "/home/remi/git/SDHCALArborPFA/output/v01-04-00/Separation/",
			const std::string &treeName = "PfoMonitoring");

	/**
	 *  @brief  Set whether to save graphs in files
	 */
	void SetSaveGraphs(bool save = true);

	/**
	 * @brief  Set data types to treat
	 */
	void SetDataTypes(const DataTypeVector &dataTypes);

	/**
	 *  @brief  Whether to compute the systematic errors.
	 *          Requires additional files. Default is false
	 */
	void SetComputeSystematics(bool compute = true);

	/**
	 *  @brief  Set the pave text to draw on top of each plot. Not drawn if empty
	 */
	void SetTextLabel(const std::string &text);

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
	 *  @brief  Configure multi graph axis. Called after TMultiGraph::Draw()
	 */
	void PostDrawMultiGraph(GraphName graphName, TMultiGraph *pMultiGraph) const;

	/**
	 *  @brief  Compute systematics for a given point
	 */
	void ComputeSystematics(int pointID, int neutralEnergy, int chargedEnergy, int distance, DataType dataType, GraphMap &graphMapAtNominalValues);

	/**
	 *
	 */
	void ComputeSystematics(int pointID, const GraphMap &nominalMap, const GraphMap &systGraphMap,
			GraphName graphName, GraphSystErrorMap &upperBoundErrorMap, GraphSystErrorMap &lowerBoundErrorMap);

private:

	DataTypeVector              m_dataTypeVector;
	CanvasMultiGraphMap         m_canvasMultiGraphMap;

	unsigned int                m_startDistance;
	unsigned int                m_endDistance;
	unsigned int                m_distanceStep;
	bool                        m_saveGraphs;
	std::string                 m_rootFileDirectory;
	std::string                 m_treeName;

	IntVector                   m_neutralEnergies;
	IntVector                   m_chargedEnergies;

	bool                        m_computeSystematics;

	std::string                 m_textLabel;
};

/**
 *
 */
class OverlayCheckPlotAnalysis
{
public:
	/**
	 *
	 */
	OverlayCheckPlotAnalysis();

	/**
	 *
	 */
	void SetParameters(DataType dataType, unsigned int neutralEnergy = 10, unsigned int chargedEnergy = 30,
			unsigned int smallDistance = 5, unsigned int wideDistance = 30);

	/**
	 *
	 */
	void SetTextLabel(const std::string &text);

	/**
	 *
	 */
	void SetFileParameters(const std::string &fileDirectory, const std::string &treeName = "PfoMonitoring");

	/**
	 *
	 */
	void Run();

private:
	std::string                 m_fileDirectory;
	std::string                 m_treeName;

	DataType                    m_dataType;

	unsigned int                m_neutralEnergy;
	unsigned int                m_chargedEnergy;
	unsigned int                m_smallDistance;
	unsigned int                m_wideDistance;

	std::string                 m_textLabel;
};


#endif
