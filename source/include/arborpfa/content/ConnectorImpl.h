/*
 *
 * ConnectorImpl.h header template automatically generated by a class generator
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


#ifndef CONNECTORIMPL_H
#define CONNECTORIMPL_H

#include "arborpfa/content/Connector.h"
#include "arborpfa/arbor/ArborTypes.h"

namespace arborpfa {

class ArborObject;

/** 
 * @brief ConnectorImpl class
 */ 
class ConnectorImpl : public Connector 
{
 public:

		/**
			* @brief Ctor
			*/
		ConnectorImpl(ArborObject *pObject1, ArborObject *pObject2, const float weight = 1.0);

		/**
			* @brief Dtor
			*/
		virtual ~ConnectorImpl();

		/**
			*
			*/
		virtual ArborObject *GetFirst() const;

		/**
			*
			*/
		virtual ArborObject *GetSecond() const;

		/**
			*
			*/
		virtual pandora::StatusCode SetWeight(float weight);

		/**
			*
			*/
		virtual float GetWeight() const;

		/**
			*
			*/
		virtual const ArborObjectPair &GetObjects() const;

		/**
			*
			*/
		virtual bool Contains(ArborObject *pObject) const;

		/**
			*
			*/
		virtual float GetDistanceBetweenObjects() const;

		/**
		 *
		 */
		virtual pandora::StatusCode SetType(Connector::Type type);

		/**
		 *
		 */
		virtual Connector::Type GetType() const;

 protected:

		/**
			*
			*/
		virtual pandora::StatusCode SwapObjects();

		//
		ArborObjectPair         m_objectPair;
		float                  m_weight;
		Connector::Type         m_type;


		friend class ArborObjectImpl;

};


} 

#endif  //  CONNECTORIMPL_H
