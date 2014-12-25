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

#include "pluginmanager.h"
#include <string>
#include <cstdlib>
#include <iostream>
#include <cstring>

#define MAX_CADENA 100
#define MAX_ARGS 10

using namespace std;

int extrae_argumentos(char *orig, char *delim, char args[][MAX_CADENA], int max_args)
{
  char *tmp;
  int num=0;

  if (strlen(orig)==0)
    return 0;

  char *str = (char*)malloc(strlen(orig)+1);
  strcpy(str, orig);

  tmp=strtok(str, delim);
  do
    {
      if (num==max_args)
    return max_args+1;  

      strcpy(args[num], tmp);  
      num++;

      tmp=strtok(NULL, delim);
    } while (tmp!=NULL);

  return num;
}


int main(int argc, char *argv[])
{
  bool fin=false;
  PluginManager pm("plugins/");
  string command;
  char args[MAX_ARGS][MAX_CADENA];

  cout << "Introduzca comandos que serán interpretados:"<<endl<<endl;
  while (!fin)
    {
      cout << "> ";
      getline(cin, command);
      int nargs = extrae_argumentos((char*)command.c_str(), (char*)" ", args, MAX_ARGS);
      try
    {
      if (nargs>0)
        {
          if (strcmp("fin", args[0])==0)
        fin=true;
          else if (strcmp("list", args[0])==0)
        cout<< pm.pluginList()<<endl;
          else if (strcmp("scan", args[0])==0)
        pm.pluginScan();
          else if (strcmp("info", args[0])==0)
        cout << pm.getInfo((string)args[1]) << endl;
          else if (strcmp("free", args[0])==0)
        pm.pluginFree();
          else if (nargs>1)
        cout << pm.pluginCall((string)args[0], (string)args[1]) << endl;
          else
        cout << "Need at least one argument"<<endl;
        }
    }
      catch (PluginManagerException* e)
    {
      cout << "There was an error: "<<e->what()<<endl;
    }
    }
  return EXIT_SUCCESS;
}
