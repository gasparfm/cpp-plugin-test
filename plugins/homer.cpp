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
    info->name = "homer";
    info->plugin_version=1.0;
    info->client_version=2;
  }
 
  void advancedInfo(PluginVersion2Info *info)
  {
    info->description="Several sizes homers on the screen";
    info->author="Gaspar Fernández";
    info->url="http://totaki.com/poesiabinaria/";
    info->date="2013-03-03";
  }

  void initialize()
  {
    cout << "Initializing homer plugin..."<<endl;
  }
 
  void destroy()
  {
    cout << "Destroying homer plugin..."<<endl;
  }

  string displayHomer1()
  {
    return "     /X \\\n"
      "   _------_\n"
      "  /        \\\n"
      " |          |\n"
      " |          |\n"
      " |     __  __)\n"
      " |    /  \\/  \\\n"
      "/\\/\\ (o   )o  )\n"
      "/c    \\__/ --.\n"
      "\\_   _-------'\n"
      " |  /         \\\n"
      " | | '\\_______)\n"
      " |  \\_____)\n"
      " |_____ |\n"
      "|_____/\\/\\\n"
      "/        \\\n";
  }

  string displayHomer2()
  {
    return " .'/,-Y\"     \"~-.\n"
      " l.Y             ^.\n"
      " /\\               _\\\n"
      "i            ___/\"   \"\\\n"
      "|          /\"   \"\\   o !\n"
      "l         ]     o !__./\n"
      " \\ _  _    \\.___./    \"~\\\n"
      "  X \\/ \\            ___./\n"
      " ( \\ ___.   _..--~~\"   ~`-.\n"
      "  ` Z,--   /               \\\n"
      "    \\__.  (   /       ______)\n"
      "      \\   l  /-----~~\" /\n"
      "       Y   \\          /\n"
      "       |    \"x______.^\n"
      "       |           \\\n"
      "       j            Y\n";
  }

  string displayHomer3()
  {
    return "               ___\n"
      "             _//_\\\\\n"
      "           ,\"    //\".\n"
      "          /          \\\n"
      "        _/           |\n"
      "       (.-,--.       |\n"
      "       /o/  o \\     /\n"
      "       \\_\\    /  /\\/\\\n"
      "       (__`--'   ._)\n"
      "       /  `-.     |\n"
      "      (     ,`-.  |\n"
      "       `-,--\\_  ) |-.\n"
      "        _`.__.'  ,-' \\\n"
      "       |\\ )  _.-'    |\n"
      "       i-\\.'\\     ,--+.\n"
      "     .' .'   \\,-'/     \\\n"
      "    / /         /       \\\n"
      "    7_|         |       |\n"
      "    |/          \"i.___.j\"\n"
      "    /            |     |\\\n"
      "   /             |     | \\\n"
      "  /              |     |  |\n"
      "  |              |     |  |\n"
      "  |____          |     |-i'\n"
      "   |   \"\"\"\"----\"\"|     | |\n"
      "   \\           ,-'     |/\n"
      "    `.         `-,     |\n"
      "     |`-._      / /| |\\ \\\n"
      "     |    `-.   `' | ||`-'\n"
      "     |      |      `-'|\n"
      "     |      |         |\n"
      "     |      |         |\n"
      "     |      |         |\n"
      "     |      |         |\n"
      "     |      |         |\n"
      "     |      |         |\n"
      "     )`-.___|         |\n"
      "   .'`-.____)`-.___.-'(\n"
      " .'        .'-._____.-i\n"
      "/        .'           |\n"
      "`-------/         .   |\n"
      "        `--------' \"--'\n";
  }

  string action(string argument)
  {
    int number = atoi(argument.c_str());

    switch (number)
      {
      case 1:
    return displayHomer1();
    break;

      case 2:
    return displayHomer2();
    break;

      case 3:
    return displayHomer3();
    break;
   
      default:
    return "Homer not found";
      }
  }

}
