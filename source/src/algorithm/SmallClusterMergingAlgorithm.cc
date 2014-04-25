/*
 *
 * SmallClusterMergingAlgorithm.cc source template automatically generated by a class generator
 * Creation date : ven. mars 7 2014
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


#include "arborpfa/algorithm/SmallClusterMergingAlgorithm.h"
#include "arborpfa/arbor/AlgorithmHeaders.h"

using namespace pandora;

namespace arborpfa
{

pandora::StatusCode SmallClusterMergingAlgorithm::Run()
{

	const ClusterList *pClusterList = NULL;
	PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::GetCurrentClusterList(*this, pClusterList));

	if(pClusterList->empty())
		return STATUS_CODE_SUCCESS;

	ClusterList smallClusterList;
	ClusterList bigClusterList;

	for(ClusterList::const_iterator iter = pClusterList->begin() , endIter = pClusterList->end() ; endIter != iter ; ++iter)
	{
		Cluster *pCluster = *iter;

		if(m_minimumClusterSizeForMerging > pCluster->GetNCaloHits())
		{
			smallClusterList.insert(pCluster);
		}
		else
		{
			bigClusterList.insert(pCluster);
		}
	}

	// map for small cluster association
	ClusterToClusterMap smallToBigClusterMap;

	// loop and identify in which big cluster the small cluster has to be merged
	for(ClusterList::const_iterator smallIter = smallClusterList.begin() , smallEndIter = smallClusterList.end() ; smallEndIter != smallIter ; ++smallIter)
	{
		Cluster *pSmallCluster = *smallIter;

		float closestDistance(std::numeric_limits<float>::max());
		Cluster *pClosestCluster = NULL;

		for(ClusterList::const_iterator bigIter = bigClusterList.begin() , bigEndIter = bigClusterList.end() ; bigEndIter != bigIter ; ++bigIter)
		{
			Cluster *pBigCluster = *bigIter;

			float distance = 0.f;
			StatusCode statusCode;

			if(m_shouldUseCentroidForClusterDistance)
			{
				statusCode = this->GetCentroidDistanceBetweenClusters(pSmallCluster, pBigCluster, distance);
			}
			else
			{
				statusCode = this->GetClosestDistanceBetweenClusters(pSmallCluster, pBigCluster, distance);
			}

			if(STATUS_CODE_SUCCESS != statusCode)
				continue;

			if(m_largeDistanceClusterCut < distance)
				continue;

			if(closestDistance > distance)
			{
				closestDistance = distance;
				pClosestCluster = pBigCluster;
			}

		}

		if(NULL != pClosestCluster)
		{
			smallToBigClusterMap[pSmallCluster] = pClosestCluster;
		}

	}

	smallClusterList.clear();
	bigClusterList.clear();

	for(ClusterToClusterMap::iterator iter = smallToBigClusterMap.begin() , endIter = smallToBigClusterMap.end() ; endIter != iter ; ++iter)
	{
		Cluster *pSmallCluster = iter->first;
		Cluster *pBigCluster = iter->second;

		if(NULL == pSmallCluster || NULL == pBigCluster)
			continue;

		PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::MergeAndDeleteClusters(*this, pBigCluster, pSmallCluster));

	}

	smallToBigClusterMap.clear();

	return STATUS_CODE_SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------------------------

pandora::StatusCode SmallClusterMergingAlgorithm::GetClosestDistanceBetweenClusters(const Cluster *pCluster1, const Cluster *pCluster2, float &closestDistance)
{
	if(NULL == pCluster1 || NULL == pCluster2)
		return STATUS_CODE_INVALID_PARAMETER;

	if(0 == pCluster1->GetNCaloHits() || 0 == pCluster2->GetNCaloHits())
		return STATUS_CODE_FAILURE;

	CaloHitList caloHitList1;
	CaloHitList caloHitList2;
	pCluster1->GetOrderedCaloHitList().GetCaloHitList(caloHitList1);
	pCluster2->GetOrderedCaloHitList().GetCaloHitList(caloHitList2);

	closestDistance = std::numeric_limits<float>::max();

	for(CaloHitList::const_iterator iter1 = caloHitList1.begin() , endIter1 = caloHitList1.end() ; endIter1 != iter1 ; ++iter1)
	{
		CaloHit *pCaloHit1 = *iter1;

		for(CaloHitList::const_iterator iter2 = caloHitList2.begin() , endIter2 = caloHitList2.end() ; endIter2 != iter2 ; ++iter2)
		{
			CaloHit *pCaloHit2 = *iter2;

			float distance = (pCaloHit1->GetPositionVector() - pCaloHit2->GetPositionVector()).GetMagnitude();

			if(closestDistance > distance)
			{
				closestDistance = distance;
			}
		}
	}

	return STATUS_CODE_SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------------------------

pandora::StatusCode SmallClusterMergingAlgorithm::GetCentroidDistanceBetweenClusters(const Cluster *pCluster1, const Cluster *pCluster2, float &distance)
{

	if(NULL == pCluster1 || NULL == pCluster2)
		return STATUS_CODE_INVALID_PARAMETER;

	distance = std::numeric_limits<float>::max();

	CartesianVector centroid1(0.f, 0.f, 0.f);
	CartesianVector centroid2(0.f, 0.f, 0.f);

	CaloHitList caloHitList1;
	CaloHitList caloHitList2;
	pCluster1->GetOrderedCaloHitList().GetCaloHitList(caloHitList1);
	pCluster2->GetOrderedCaloHitList().GetCaloHitList(caloHitList2);

	PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, arborpfa::CaloHitHelper::GetCentroid(&caloHitList1, centroid1));
	PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, arborpfa::CaloHitHelper::GetCentroid(&caloHitList2, centroid2));

 distance = (centroid1 - centroid2).GetMagnitude();

	return STATUS_CODE_SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------------------------

pandora::StatusCode SmallClusterMergingAlgorithm::ReadSettings(const pandora::TiXmlHandle xmlHandle)
{

 PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::ReadValue(xmlHandle,
     "MinimumClusterSizeForMerging", m_minimumClusterSizeForMerging));

 PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::ReadValue(xmlHandle,
     "LargeDistanceClusterCut", m_largeDistanceClusterCut));

 m_shouldUseCentroidForClusterDistance = false;
 PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
     "ShouldUseCentroidForClusterDistance", m_shouldUseCentroidForClusterDistance));

	return STATUS_CODE_SUCCESS;
}


} 

