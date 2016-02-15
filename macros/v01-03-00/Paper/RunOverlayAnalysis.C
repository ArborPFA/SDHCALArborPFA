

void RunOverlayAnalysis(int neutralEnergy = 10, int chargedEnergy = 10)
{
	Int_t errorCode = TInterpreter::kNoError;
	gROOT->ProcessLine(".L OverlayAnalysis.C+", &errorCode);

	if(errorCode != TInterpreter::kNoError)
	{
		std::cerr << "Coulnd't compile OverlayAnalysis.C !" << std::endl;
		return;
	}

	OverlayAnalysis analysis(neutralEnergy, chargedEnergy);
	analysis.SetFileParameters("/home/rete/soft/SDHCALArborPFA/output/v01-04-00/Separation/");
//	analysis.SetSaveGraphs();
	analysis.Run();

	while(1)
		gSystem->ProcessEvents();
}


