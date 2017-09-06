

void RunOverlayAnalysis()
{
	Int_t errorCode = TInterpreter::kNoError;
	gROOT->ProcessLine(".L OverlayAnalysis.C+", &errorCode);

	if(errorCode != TInterpreter::kNoError)
	{
		std::cerr << "Coulnd't compile OverlayAnalysis.C !" << std::endl;
		return;
	}

	IntVector neutralEnergies;
	neutralEnergies.push_back(10);

	IntVector chargedEnergies;
	chargedEnergies.push_back(10);
	chargedEnergies.push_back(30);

	DataTypeVector dataTypes;
	dataTypes.push_back(TB_SPS_AUG_2012);
	dataTypes.push_back(FTF_BIC);

	OverlayAnalysis analysis(neutralEnergies, chargedEnergies);
	analysis.SetFileParameters("/home/rete/soft/SDHCALArborPFA/output/v01-04-00/Paper/Separation/");
//	analysis.SetFileParameters("/home/rete/soft/SDHCALArborPFA/output/v01-04-00/Separation/");
	analysis.SetDataTypes(dataTypes);
	// analysis.SetComputeSystematics(false);
	analysis.SetComputeSystematics(true);
//	analysis.SetTextLabel("Preliminary");
	analysis.SetTextLabel("CALICE SDHCAL");
	analysis.Run();

	// OverlayCheckPlotAnalysis checkPlot;
	// checkPlot.SetFileParameters("/home/rete/soft/SDHCALArborPFA/output/v01-04-00/Separation/");
	// checkPlot.SetTextLabel("CALICE SDHCAL");
	// checkPlot.SetParameters(TB_SPS_AUG_2012, 10, 10, 5, 30);

	// checkPlot.Run();

	while(1)
	{
		gSystem->ProcessEvents();
		gSystem->Sleep(10);
	}

	delete pCanvas;
}


