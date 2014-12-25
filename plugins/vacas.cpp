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
#include "pluginversion1.h"
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

extern "C"
{
  void basicInfo(PluginBasicInfo* info)
  {
    info->name = "vacas";
    info->plugin_version=1.0;
    info->client_version=1;
  }
 
  void advancedInfo(PluginVersion1Info *info)
  {
    info->description="Just draw ASCII cows on screen";
    info->author="Gaspar Fernández";
  }
 
  void initialize()
  {
    cout << "Initializing cows plugin..."<<endl;
  }
 
  void destroy()
  {
    cout << "Destroying cows plugin..."<<endl;
  }

  string displayVaca1()
  {
    return "         (__)\n         (oo)\n  /-------\\/\n / |     ||\n*  ||----||\n   ^^    ^^";
  }

  string displayVaca2()
  {
    return "         (__)\n         (\\/)\n  /-------\\/\n / | 666 ||\n*  ||----||\n   ^^    ^^";
  }

  string displayVaca3()
  {
    return "         (__)    ^\n         (oo)   /\n     _____\\/___/\n    /  /\\ / /\n   ^  /  * /\n     / ___/\n*----/\\\n    /  \\\n   /   /\n  ^    ^\n";
  }

  string action(string argument)
  {
    int number = atoi(argument.c_str());

    switch (number)
      {
      case 1:
    return displayVaca1();
    break;

      case 2:
    return displayVaca2();
    break;

      case 3:
    return displayVaca3();
    break;
   
      default:
    return "Vaca not found";
      }
  }
}
