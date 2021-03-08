//===- SVF-Teaching Assignment 2-------------------------------------//
//
//     SVF: Static Value-Flow Analysis Framework for Source Code
//
// Copyright (C) <2013->
//

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//===-----------------------------------------------------------------------===//
/*
 // SVF-Teaching Assignment 2 : Source Sink ICFG DFS Traversal
 //
 // 
 */
#ifndef ASSIGNMENT_2_H_
#define ASSIGNMENT_2_H_

#include "SVF-FE/LLVMUtil.h"
#include "SVF-FE/PAGBuilder.h"
#include "Assignment-2.h"
using namespace SVF;

class ICFGTraversal
{

public:

    ICFGTraversal(PAG *p) : pag(p) {}

    /// TODO: to be implemented
    void printICFGPath(std::vector<const ICFGNode *> &path);

    /// TODO: to be implemented
    void DFS(std::set<const ICFGNode *> &visited, std::vector<const ICFGNode *> &path, const ICFGNode *src, const ICFGNode *dst);

    // Identify source nodes on ICFG (i.e., call instruction with its callee function named 'src')
    virtual std::set<const CallBlockNode *> &identifySources()
    {
        for (const CallBlockNode *cs : pag->getCallSiteSet())
        {
            const SVFFunction *fun = SVFUtil::getCallee(cs->getCallSite());
            if (fun->getName() == "source")
            {
                sources.insert(cs);
            }
        }
        return sources;
    }

    // Identify sink nodes on ICFG (i.e., call instruction with its callee function named 'sink')
    virtual std::set<const CallBlockNode *> &identifySinks()
    {
        for (const CallBlockNode *cs : pag->getCallSiteSet())
        {
            const SVFFunction *fun = SVFUtil::getCallee(cs->getCallSite());
            if (fun->getName() == "sink")
            {
                sinks.insert(cs);
            }
        }
        return sinks;
    }
    std::set<std::string>& getPaths(){
        return paths;
    }

protected:
    std::set<const CallBlockNode *> sources;
    std::set<const CallBlockNode *> sinks;
    std::set<std::string> paths;
    PAG *pag;
};

#endif
