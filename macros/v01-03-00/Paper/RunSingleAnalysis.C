void RunSingleAnalysis()
{
  Int_t errorCode = TInterpreter::kNoError;
  gROOT->ProcessLine(".L SingleAnalysis.C+", &errorCode);

  if(errorCode != TInterpreter::kNoError)
    {
      std::cerr << "Coulnd't compile SingleAnalysis.C !" << std::endl;
      return;
    }

  std::vector<int> energies;
  energies.push_back(10);
  energies.push_back(20);
  energies.push_back(30);
  energies.push_back(40);
  energies.push_back(50);
  energies.push_back(60);
  energies.push_back(70);
  energies.push_back(80);

  DataTypeVector dataTypeVector;

  // for TB comparison (No PFA vs ArborPFA)
  // dataTypeVector.push_back(TB_SPS_AUG_2012_NO_PFA);
  // dataTypeVector.push_back(TB_SPS_AUG_2012);

  // for simulation comparison (No PFA vs ArborPFA)
  dataTypeVector.push_back(FTFP_BERT_HP_NO_PFA);
  dataTypeVector.push_back(FTFP_BERT_HP);
  dataTypeVector.push_back(FTF_BIC_NO_PFA);
  dataTypeVector.push_back(FTF_BIC);

  // for PFA only comparison (default)
  // dataTypeVector.push_back(TB_SPS_AUG_2012);
  // dataTypeVector.push_back(FTFP_BERT_HP);
  // dataTypeVector.push_back(FTF_BIC); 
  
	
 
  SingleAnalysis analysis;
  
  analysis.SetFileParameters("/home/rete/soft/SDHCALArborPFA/output/v01-04-00/SingleParticle/");
  analysis.SetEnergies(energies);
  
    std::cout << "pouette !" << std::endl;
  analysis.SetDataTypeList(dataTypeVector);
    std::cout << "pouette 2 !" << std::endl;
  
  //	analysis.SetSaveGraphs();
  analysis.Run();

  while(1)
    {
      gSystem->ProcessEvents();
      gSystem->Sleep(10);
    }
}


