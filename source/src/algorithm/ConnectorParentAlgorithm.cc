  /// \file ConnectorParentAlgorithm.cc
/*
 *
 * ConnectorParentAlgorithm.cc source template automatically generated by a class generator
 * Creation date : lun. sept. 22 2014
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


#include "arborpfa/algorithm/ConnectorParentAlgorithm.h"

// pandora
#include "Api/PandoraContentApi.h"

// arborpfa
#include "arborpfa/api/ArborContentApi.h"
#include "arborpfa/arbor/AlgorithmHeaders.h"

namespace arbor
{

//--------------------------------------------------------------------------------------------------------------------------

pandora::StatusCode ConnectorParentAlgorithm::RunArborAlgorithm()
{
 // Run connector related (seeding and cleaning) daughter algorithms
 for (StringVector::const_iterator iter = m_connectorAlgorithmList.begin(), iterEnd = m_connectorAlgorithmList.end(); iter != iterEnd; ++iter)
 {
  PANDORA_RETURN_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, PandoraContentApi::RunDaughterAlgorithm(*this, *iter));
 }


	return pandora::STATUS_CODE_SUCCESS;
}

//--------------------------------------------------------------------------------------------------------------------------

pandora::StatusCode ConnectorParentAlgorithm::ReadSettings(const pandora::TiXmlHandle xmlHandle)
{
 PANDORA_RETURN_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, pandora::XmlHelper::ProcessAlgorithmList(*this, xmlHandle, "connectorAlgorithms",
 		m_connectorAlgorithmList));

	return pandora::STATUS_CODE_SUCCESS;
}

//--------------------------------------------------------------------------------------------------------------------------

} 
