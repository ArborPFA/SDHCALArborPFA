/*
 *
 * Arbor.cc source template automatically generated by a class generator
 * Creation date : lun. f�vr. 10 2014
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
#include "arborpfa/arbor/Arbor.h"
#include "arborpfa/content/ObjectManager.h"
#include "arborpfa/content/ClusterManager.h"
#include "arborpfa/content/ArborPluginManager.h"
#include "arborpfa/arbor/ArborImpl.h"
#include "arborpfa/api/ArborApiImpl.h"
#include "arborpfa/api/ArborContentApiImpl.h"

// pandora
#include "Api/PandoraApi.h"

using namespace pandora;

namespace arbor
{

Arbor::Arbor()
{
 try
 {
 	m_pPandora = new Pandora();
  m_pArborApiImpl = new ArborApiImpl(this);
  m_pArborContentApiImpl = new ArborContentApiImpl(this);
  m_pArborImpl = new ArborImpl(this);
 	m_pObjectManager = new ObjectManager();
 	m_pClusterManager = new ClusterManager();
 	m_pArborPluginManager = new ArborPluginManager(this);

  PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, PandoraApi::RegisterSettingsFunction(*m_pPandora, "ArborPlugin",
  		&ArborPluginManager::ReadSettings));

 	PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, this->RegisterResetFunction());
 }
 catch(StatusCodeException &e)
 {
 	std::cout << "Failed to create arbor instance " << e.ToString() << std::endl;
 	delete this;
 	throw e;
 }
 catch(...)
 {
  std::cout << "Failed to create arbor instance " << std::endl;
  delete this;
  throw;
 }

}

//------------------------------------------------------------------------------------------------------------------------------------------

pandora::StatusCode Arbor::RegisterResetFunction()
{
	PANDORA_RETURN_RESULT_IF( STATUS_CODE_SUCCESS, !=, PandoraApi::RegisterResetFunction(*m_pPandora, &Arbor::Reset));

	return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

Arbor::~Arbor()
{
	delete m_pPandora;
	delete m_pObjectManager;
	delete m_pClusterManager;
 delete m_pArborApiImpl;
 delete m_pArborContentApiImpl;
 delete m_pArborImpl;
}

//------------------------------------------------------------------------------------------------------------------------------------------

void Arbor::Reset()
{
	// Find a way to call the ResetEvent() method to clean the framework
	return;
}

//------------------------------------------------------------------------------------------------------------------------------------------

pandora::StatusCode Arbor::PrepareEvent()
{
	return m_pArborImpl->PrepareEvent();
}

//------------------------------------------------------------------------------------------------------------------------------------------

pandora::StatusCode Arbor::ResetEvent()
{
 return m_pArborImpl->ResetEvent();
}

//------------------------------------------------------------------------------------------------------------------------------------------

ArborApiImpl *Arbor::GetArborApiImpl() const
{
	return m_pArborApiImpl;
}

//------------------------------------------------------------------------------------------------------------------------------------------

ArborContentApiImpl *Arbor::GetArborContentApiImpl() const
{
	return m_pArborContentApiImpl;
}

//------------------------------------------------------------------------------------------------------------------------------------------

Pandora *Arbor::GetPandora() const
{
	return m_pPandora;
}

} 

