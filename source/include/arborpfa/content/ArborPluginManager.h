  /// \file ArborPluginManager.h
/*
 *
 * ArborPluginManager.h header template automatically generated by a class generator
 * Creation date : ven. mai 30 2014
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
 * @author Ete Remi
 * @copyright CNRS , IPNL
 */


#ifndef ARBORPLUGINMANAGER_H
#define ARBORPLUGINMANAGER_H

// arborpfa
#include "arborpfa/arbor/ArborTypes.h"

// pandora
#include "Pandora/StatusCodes.h"
#include "Helpers/XmlHelper.h"

namespace arbor
{
class Arbor;
/** 
 * @brief ArborPlugin class
 */ 
class ArborPluginManager
{
 protected:

	/**
	 * @brief Ctor
	 */
	ArborPluginManager(Arbor *pArbor);

	/**
	 * @brief Dtor
	 */
	virtual ~ArborPluginManager();

	/* Tree builder related methods */

	/**
	 * @brief Register a new function to build trees
	 */
	pandora::StatusCode RegisterTreeBuilder(const std::string &treeBuilderName, ITreeBuilder *pTreeBuilder);

	/**
	 * @brief Set the current tree builder by name. Tree builder should be registered before
	 */
	pandora::StatusCode SetCurrentTreeBuilder(const std::string &treeBuilder);

	/**
	 * @brief Get the current tree builder
	 */
	pandora::StatusCode GetCurrentTreeBuilder(ITreeBuilder *&pTreeBuilder);

	/**
	 * @brief Get the current tree builder name
	 */
	pandora::StatusCode GetCurrentTreeBuilderName(std::string &treeBuilderName);

	/* Branch builder related methods */

	/**
	 * @brief Register a new function to build branches
	 */
	pandora::StatusCode RegisterBranchBuilder(const std::string &branchBuilderName, IBranchBuilder *pBranchBuilder);

	/**
	 * @brief Set the current branch builder by name. Branch builder should be registered before
	 */
	pandora::StatusCode SetCurrentBranchBuilder(const std::string &branchBuilderName);

	/**
	 * @brief Get the current tree builder
	 */
	pandora::StatusCode GetCurrentBranchBuilder(IBranchBuilder *&pBranchBuilder);

	/**
	 * @brief Get the current branch builder name
	 */
	pandora::StatusCode GetCurrentBranchBuilderName(std::string &branchBuilderName);

	/* Energy estimator related methods */

	/**
	 * @brief Register a new function to estimate energy
	 */
	pandora::StatusCode RegisterEnergyEstimator(const std::string &energyEstimatorName, IEnergyEstimator *pEnergyEstimator);

	/**
	 * @brief Set the current energy estimator by name. Estimator should be registered before
	 */
	pandora::StatusCode SetCurrentEnergyEstimator(const std::string &energyEstimatorName);

	/**
	 * @brief Get the current energy estimator
	 */
	pandora::StatusCode GetCurrentEnergyEstimator(IEnergyEstimator *&pEnergyEstimator);

	/**
	 * @brief Get the current energy estimator name
	 */
	pandora::StatusCode GetCurrentEnergyEstimatorName(std::string &energyEstimatorName);

	/* Energy resolution related methods */

	/**
	 * @brief Register a new function for detector energy resolution
	 */
	pandora::StatusCode RegisterEnergyResolutionFunction(const std::string &energyResolutionFunctionName, IEnergyResolutionFunction *pEnergyResolutionFunction);

	/**
	 * @brief Set the current energy resolution function by name. Function should be registered before
	 */
	pandora::StatusCode SetCurrentEnergyResolutionFunction(const std::string &energyResolutionFunctionName);

	/**
	 * @brief Get the current energy resolution function
	 */
	pandora::StatusCode GetCurrentEnergyResolutionFunction(IEnergyResolutionFunction *&pEnergyResolutionFunction);

	/**
	 * @brief Get the current energy resolution function name
	 */
	pandora::StatusCode GetCurrentEnergyResolutionFunctionName(std::string &energyResolutionFunctionName);


	/**
	 * @brief Read the settings for all of the plugins
	 */
	static pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

	/**
	 * @brief Read the settings for all of the plugins
	 */
	pandora::StatusCode _ReadSettings(const pandora::TiXmlHandle xmlHandle);

	/**
	 *
	 */
	pandora::StatusCode ReadTreeBuilderSettings(const pandora::TiXmlHandle &xmlHandle);

	/**
	 *
	 */
	pandora::StatusCode ReadBranchBuilderSettings(const pandora::TiXmlHandle &xmlHandle);

	/**
	 *
	 */
	pandora::StatusCode ReadEnergyEstimatorSettings(const pandora::TiXmlHandle &xmlHandle);

	/**
	 *
	 */
	pandora::StatusCode ReadEnergyResolutionSettings(const pandora::TiXmlHandle &xmlHandle);


	// tree builder members
	std::string             m_currentTreeBuilderName;
	ITreeBuilder           *m_pCurrentTreeBuilder;
	TreeBuilderMap          m_treeBuilderMap;

	// branch builder members
	std::string             m_currentBranchBuilderName;
	IBranchBuilder         *m_pCurrentBranchBuilder;
	BranchBuilderMap        m_branchBuilderMap;

 // energy estimator members
	std::string             m_currentEnergyEstimatorName;
	IEnergyEstimator       *m_pCurrentEnergyEstimator;
	EnergyEstimatorMap      m_energyEstimatorMap;

	// energy resolution members
	std::string                      m_currentEnergyResolutionFunctionName;
	IEnergyResolutionFunction       *m_pCurrentEnergyResolutionFunction;
	EnergyResolutionFunctionMap      m_energyResolutionFunctionMap;

	static arbor::Arbor             *m_pArbor;

	// friendship
	friend class ArborContentApiImpl;
	friend class ArborApiImpl;
	friend class Arbor;
}; 

} 

#endif  //  ARBORPLUGINMANAGER_H
