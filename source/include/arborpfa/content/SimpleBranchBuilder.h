  /// \file SimpleBranchBuilder.h
/*
 *
 * SimpleBranchBuilder.h header template automatically generated by a class generator
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


#ifndef SIMPLEBRANCHBUILDER_H
#define SIMPLEBRANCHBUILDER_H

#include "arborpfa/content/IBranchBuilder.h"

#include "Pandora/StatusCodes.h"

namespace arbor
{
class Tree;

/** 
 * @brief SimpleBranchBuilder class
 */ 
class SimpleBranchBuilder : public IBranchBuilder 
{
 protected:

 /**
  *
  */
 pandora::StatusCode Build(Tree *pTree);

}; 

} 

#endif  //  SIMPLEBRANCHBUILDER_H