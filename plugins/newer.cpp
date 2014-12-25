/**
   Testing a plugin system in C++

   Copyright 2013 Gaspar Fernández <blakeyed@totaki.com>

   This file is part of cpp_plugin_test.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

 */
#include "basicplugin.h"
#include "pluginversion2.h"
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

extern "C"
{
  void basicInfo(PluginBasicInfo* info)
  {
    info->name = "newer";
    info->plugin_version=1.0;
    info->client_version=3;
  }
 
  void advancedInfo(PluginVersion2Info *info)
  {
    info->description="It's a plugin newer than the client";
    info->author="Gaspar Fernández";
    info->url="http://totaki.com/poesiabinaria/";
    info->date="2013-03-03";
  }

  void initialize()
  {
    cout << "Initializing newer plugin..."<<endl;
  }
 
  void destroy()
  {
    cout << "Destroying newer plugin..."<<endl;
  }

  string action(string argument)
  {
    return "Hello world";
  }

}
