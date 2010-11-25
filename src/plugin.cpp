/*
   Copyright (c) 2010, The Mineserver Project
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
 * Neither the name of the The Mineserver Project nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "plugin.h"
#include "blocks/basic.h"

Plugin &Plugin::get()
{
  static Plugin instance;
  return instance;
}

void Plugin::init()
{
   // Set default behaviours 
   Callback call;
   BlockBasic* block = new BlockBasic();
   call.add("onBroken", Function::from_method<BlockBasic, &BlockBasic::onBroken>(block));
   call.add("onPlace", Function::from_method<BlockBasic, &BlockBasic::onPlace>(block));
   setBlockCallback(BLOCK_STONE, call);
   setBlockCallback(BLOCK_GRASS, call);
   setBlockCallback(BLOCK_DIRT, call);
   setBlockCallback(BLOCK_COBBLESTONE, call);
   setBlockCallback(BLOCK_WOOD, call);
}

void Plugin::setBlockCallback(const int type, Callback call)
{
   removeBlockCallback(type);
   blockevents.insert(std::pair<int, Callback>(type, call));
}

Callback Plugin::getBlockCallback(const int type)
{
   for (Callbacks::iterator iter = blockevents.begin(); iter != blockevents.end(); iter++)
   {
      if ((*iter).first == type)
      {
         return (*iter).second;
      }
   }

   Callback call;
   return call;
}

bool Plugin::removeBlockCallback(const int type)
{
   for (Callbacks::iterator iter = blockevents.begin(); iter != blockevents.end(); ++iter)
   {
      if (iter->first == type)
      {
           delete &iter->first;
           blockevents.erase(iter);
           return true;
      }
   }
   return false;
}