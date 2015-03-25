  /// \file Tree.cc
/*
 *
 * Tree.cc source template automatically generated by a class generator
 * Creation date : jeu. mai 29 2014
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


#include "arborpfa/content/Tree.h"

// arborpfa
#include "arborpfa/content/Branch.h"
#include "arborpfa/content/Object.h"
#include "arborpfa/content/Connector.h"

// std
#include <algorithm>

using namespace pandora;

namespace arbor
{

Tree::Tree(Object *pSeedObject) :
 m_pSeedObject(NULL),
 m_lastPseudoLayer(0)
{
	if(NULL == pSeedObject)
		throw StatusCodeException(STATUS_CODE_INVALID_PARAMETER);

	m_pSeedObject = pSeedObject;
	PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, this->BuildTree(m_pSeedObject));
}

//------------------------------------------------------------------------------------------------------

Tree::~Tree() 
{
	PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, this->ClearBranches());
	m_pSeedObject = NULL;
	m_objectList.clear();
}

//------------------------------------------------------------------------------------------------------

pandora::StatusCode Tree::BuildTree(Object *pSeedObject)
{
	if(NULL == pSeedObject)
		return STATUS_CODE_INVALID_PARAMETER;

	m_pSeedObject = pSeedObject;
	m_objectList.clear();
	m_objectList.insert(pSeedObject);
	m_lastPseudoLayer = m_pSeedObject->GetPseudoLayer();

	return this->RecursiveTreeBuilding(pSeedObject);
}

//------------------------------------------------------------------------------------------------------

pandora::StatusCode Tree::ClearBranches()
{
	for(BranchList::iterator iter = m_branchList.begin() , endIter = m_branchList.end() ; endIter != iter ; ++iter)
	{
		delete *iter;
	}

	m_branchList.clear();

	return pandora::STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------

const ObjectList &Tree::GetObjectList() const
{
	return m_objectList;
}

//------------------------------------------------------------------------------------------------------

const BranchList &Tree::GetBranchList() const
{
	return m_branchList;
}

//------------------------------------------------------------------------------------------------------

pandora::CaloHitList Tree::GetCaloHitList() const
{
	pandora::CaloHitList returnList;

	for(ObjectList::const_iterator iter = m_objectList.begin() , endIter = m_objectList.end() ; endIter != iter ; ++iter)
	{
		const pandora::CaloHitList &caloHitList((*iter)->GetCaloHitList());
		returnList.insert(caloHitList.begin(), caloHitList.end());
	}

	return returnList;
}

//------------------------------------------------------------------------------------------------------

pandora::StatusCode Tree::AddBranch(Branch *pBranch)
{
	if(NULL == pBranch)
	return STATUS_CODE_INVALID_PARAMETER;

	if(std::find(m_branchList.begin(), m_branchList.end(), pBranch) != m_branchList.end())
		return STATUS_CODE_ALREADY_PRESENT;

	if(!m_branchList.insert(pBranch).second)
		return STATUS_CODE_FAILURE;

	return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------

pandora::StatusCode Tree::RemoveBranch(Branch *pBranch)
{
	if(NULL == pBranch)
	return STATUS_CODE_INVALID_PARAMETER;

	if(std::find(m_branchList.begin(), m_branchList.end(), pBranch) == m_branchList.end())
		return STATUS_CODE_NOT_FOUND;

	if(1 != m_branchList.erase(pBranch))
		return STATUS_CODE_FAILURE;

	return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------

Object *Tree::GetSeedObject() const
{
	return m_pSeedObject;
}

//------------------------------------------------------------------------------------------------------

unsigned int Tree::GetNCaloHits() const
{
	unsigned int nCaloHits(0);

	for(ObjectList::const_iterator iter = m_objectList.begin() , endIter = m_objectList.end() ; endIter != iter ; ++iter)
	{
		Object *pObject = *iter;
		const CaloHitList &caloHitList(pObject->GetCaloHitList());
		nCaloHits += caloHitList.size();
	}

	return nCaloHits;
}

//------------------------------------------------------------------------------------------------------

pandora::StatusCode Tree::RecursiveTreeBuilding(Object *pCurrentObject)
{
	if(NULL == pCurrentObject)
		return pandora::STATUS_CODE_INVALID_PARAMETER;

	pandora::PseudoLayer pseudoLayer = pCurrentObject->GetPseudoLayer();

	if(pseudoLayer > m_lastPseudoLayer)
		m_lastPseudoLayer = pseudoLayer;

	const ConnectorList &forwardConnectors = pCurrentObject->GetForwardConnectorList();

	if(forwardConnectors.empty())
		return pandora::STATUS_CODE_SUCCESS;

	for(ConnectorList::const_iterator iter = forwardConnectors.begin() , endIter = forwardConnectors.end() ; endIter != iter ; ++iter)
	{
		Connector *pConnector = *iter;
		Object *pOtherObject = NULL;

		if(pConnector->GetFirst() == pCurrentObject)
			pOtherObject = pConnector->GetSecond();
		else
			pOtherObject = pConnector->GetFirst();

		if(!m_objectList.insert(pOtherObject).second)
			continue;

		PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, this->RecursiveTreeBuilding(pOtherObject));
	}

	return pandora::STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------

pandora::PseudoLayer Tree::GetFirstPseudoLayer() const
{
	return m_pSeedObject->GetPseudoLayer();
}

//------------------------------------------------------------------------------------------------------

pandora::PseudoLayer Tree::GetLastPseudoLayer() const
{
	return m_lastPseudoLayer;
}

//------------------------------------------------------------------------------------------------------

const pandora::CartesianVector &Tree::GetSeedPosition() const
{
	return m_pSeedObject->GetPosition();
}

//------------------------------------------------------------------------------------------------------

} 

