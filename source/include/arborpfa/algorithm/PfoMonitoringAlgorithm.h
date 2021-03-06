  /// \file PfoMonitoringAlgorithm.h
/*
 *
 * PfoMonitoringAlgorithm.h header template automatically generated by a class generator
 * Creation date : jeu. oct. 16 2014
 *
 * This file is part of ArborPFA libraries.
 * 
 * ArborPFA is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 * 
 * ArborPFA is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with ArborPFA.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * @author Remi Ete
 * @copyright CNRS , IPNL
 */


#ifndef PFOMONITORINGALGORITHM_H
#define PFOMONITORINGALGORITHM_H

// arborpfa
#include "arborpfa/algorithm/ArborAlgorithm.h"
#include "arborpfa/algorithm/ArborAlgorithmFactory.h"

// pandora
#include "Pandora/PandoraInternal.h"

namespace arbor
{

/** 
 * @brief PfoMonitoringAlgorithm class
 */ 
class PfoMonitoringAlgorithm : public ArborAlgorithm 
{
public:

	/**
		* @brief Factory class for instantiating algorithm
		*/
	class Factory : public ArborAlgorithmFactory
	{
		public:
			ArborAlgorithm *CreateArborAlgorithm() const;
	};

	/**
		* @brief Destructor
		*/
	~PfoMonitoringAlgorithm();

	/**
		* @brief Run the algorithm
		*/
	pandora::StatusCode RunArborAlgorithm();

	/**
		* @brief Read settings from Xml handler
		*/
	pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

	/**
	 *
	 */
	pandora::StatusCode RunGlobalPfoMonitoring(const pandora::PfoList *const pPfoList);

	/**
	 *
	 */
	pandora::StatusCode RunSdhcalSinglePfoMonitoring(const pandora::PfoList *const pPfoList);

	/**
	 *
	 */
	pandora::StatusCode RunSdhcalOverlayPfoMonitoring(const pandora::PfoList *const pPfoList);

	/**
	 *
	 */
	pandora::StatusCode Reset();

protected:

	/**
	 * @brief AnalysisType enum
	 */
	enum AnalysisType
	{
		NO_ANALYSIS = 0,
		SDHCAL_SINGLE,
		SDHCAL_OVERLAY
	};

	// file parameters
 std::string      m_rootFileName;
 std::string      m_rootTreeName;
	std::string      m_rootFileOptions;

	std::string      m_energyFunctionName;
	FloatVector      m_energyThresholdValues;


	AnalysisType     m_analysisType;
	bool            m_shouldFillTree;
	unsigned int   m_nonFilledCounter;

	// global monitoring
	int         m_nPfos;
	int         m_nNeutralPfos;
	int         m_nChargedPfos;
	float       m_neutralEnergy;
	float       m_chargedEnergy;
	FloatVector m_pfoEnergies;
	FloatVector m_pfoMomentums;
	IntVector   m_pfoNTracks;
	IntVector   m_pfoNClusters;
	IntVector   m_pfoCharges;
	FloatVector m_pfoMasses;
	IntVector   m_pfoParticleIds;
	IntVector   m_pfoNHits;
	IntVector   m_pfoNHit1;
	IntVector   m_pfoNHit2;
	IntVector   m_pfoNHit3;

	// sdhcal single particle study
	unsigned int   m_nTrackMinimumCutForNoFill;

	// sdhcal overlay particles study
	float      m_mcParticleEnergy1;
	float      m_mcParticleEnergy2;
	IntVector   m_pfoFlagType1;
	IntVector   m_pfoFlagType2;
	IntVector   m_pfoFlagType3;
	float      m_chargedHitEfficiency;
	float      m_chargedHitPurity;
	float      m_neutralHitEfficiency;
	float      m_neutralHitPurity;


	std::string m_monitoringAlgorithmName;
}; 

//--------------------------------------------------------------------------------------------------------------------

inline ArborAlgorithm *PfoMonitoringAlgorithm::Factory::CreateArborAlgorithm() const
{
	return new PfoMonitoringAlgorithm();
}

//--------------------------------------------------------------------------------------------------------------------

} 

#endif  //  PFOMONITORINGALGORITHM_H
