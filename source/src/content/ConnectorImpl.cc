/*
 *
 * ConnectorImpl.cc source template automatically generated by a class generator
 * Creation date : jeu. f�vr. 13 2014
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


// arborpfa
#include "arborpfa/content/ConnectorImpl.h"
#include "arborpfa/content/ArborObject.h"

// pandora
#include "Objects/CartesianVector.h"

using namespace pandora;

namespace arborpfa
{

ConnectorImpl::ConnectorImpl(ArborObject *pObject1, ArborObject *pObject2, const float weight)
{
	if(NULL == pObject1 || NULL == pObject2)
	{
		throw StatusCodeException(STATUS_CODE_INVALID_PARAMETER);
	}

	m_objectPair.first  = pObject1;
	m_objectPair.second = pObject2;
	m_weight = weight;
}

ConnectorImpl::~ConnectorImpl() 
{
	m_objectPair.first  = NULL;
	m_objectPair.second = NULL;
	m_weight = 0.0;
}



ArborObject *ConnectorImpl::GetFirst() const
{
	return m_objectPair.first;
}



ArborObject *ConnectorImpl::GetSecond() const
{
	return m_objectPair.second;
}



pandora::StatusCode ConnectorImpl::SetWeight(float weight)
{
	m_weight = weight;

	return STATUS_CODE_SUCCESS;
}



float ConnectorImpl::GetWeight() const
{
	return m_weight;
}



const ArborObjectPair &ConnectorImpl::GetObjects() const
{
	return m_objectPair;
}



bool ConnectorImpl::Contains(ArborObject *pObject) const
{
	return ( m_objectPair.first == pObject || m_objectPair.second == pObject ) ? true : false;
}



float ConnectorImpl::GetDistanceBetweenObjects() const
{
	return (m_objectPair.first->GetPosition() - m_objectPair.second->GetPosition()).GetMagnitude();
}



Connector::Type ConnectorImpl::GetType() const
{
	return m_type;
}



pandora::StatusCode ConnectorImpl::SetType(Connector::Type type)
{
	m_type = type;

	return STATUS_CODE_SUCCESS;
}

pandora::StatusCode ConnectorImpl::SwapObjects()
{
	ArborObject *pThird = m_objectPair.first;
	m_objectPair.first = m_objectPair.second;
	m_objectPair.second = pThird;
	pThird = NULL;

	return STATUS_CODE_SUCCESS;
}


} 

