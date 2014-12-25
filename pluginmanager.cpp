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
#include "plugins/pluginversion1.h"
#include "plugins/pluginversion2.h"

// Including cstring for speed in dirent operations
#include <cstring>         
#include <dlfcn.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <sstream>

PluginManager::PluginManager(string pluginDir): pluginDir(pluginDir)
{
  pluginScan();
}

PluginManager::~PluginManager()
{
  pluginFree();
}
// Gets filename full name
char* PluginManager::getFullName(char *path, struct dirent *ent)
{
  char *fullname;
  int tmp;

  tmp=strlen(path);
  fullname=(char*)malloc(tmp+strlen(ent->d_name)+2); /* Sumamos 2, por el \0 y la barra de directorios (/) no sabemos si falta */
  if (path[tmp-1]=='/')
    sprintf(fullname,"%s%s", path, ent->d_name);
  else
    sprintf(fullname,"%s/%s", path, ent->d_name);
 
  return fullname;
}

// Scan and add plugins
void PluginManager::pluginScan()
{
  struct dirent *ent;
  char *path=(char*)pluginDir.c_str();
  char *fullFileName;

  DIR *dir = opendir(path);

  pluginFree();

  if (dir==NULL)
    throw new PluginManagerException(1, "Couldn't open plugin directory");
 
  while ((ent = readdir (dir)) != NULL)
    {
      if ( (strcmp(ent->d_name, ".")!=0)
       && (strcmp(ent->d_name, "..")!=0)
       && (strcmp(this->getExtension(ent->d_name), ".so")==0)
       && (ent->d_type==DT_REG) )
    {
      cout << "Opening plugin "<<ent->d_name<<"...";
      fullFileName=this->getFullName(path, ent);
      try
        {
          addPlugin(fullFileName);
          cout << "OK"<<endl;
        }
      catch (PluginManagerException* e)
        {
          cout << "Failed loading plugin: "<<e->what()<<endl;
        }
      free(fullFileName);
        }
    }
  closedir (dir);
}

// Gets filename extension
char* PluginManager::getExtension(char *filename)
{
  return strrchr(filename, '.');
}

// Gets version 1 plugin advanced information (function advancedInfo)
void PluginManager::pluginGetVersion1Information(Plugin &p)
{
  PluginVersion1Info *moreinfo;
  getPluginVersion1Info gai;

  gai=(getPluginVersion1Info)dlsym(p.dlhandle, "advancedInfo");
  if (dlerror()!=NULL)
      throw new PluginManagerException(5, "Could not load advanced information");

  moreinfo=new PluginVersion1Info;
  gai(moreinfo);
  p.moreinfo=(void*)moreinfo;
}

// Gets version 2 plugin advanced information (function advancedInfo)
void PluginManager::pluginGetVersion2Information(Plugin &p)
{
  PluginVersion2Info *moreinfo;
  getPluginVersion2Info gai;

  gai=(getPluginVersion2Info)dlsym(p.dlhandle, "advancedInfo");
  if (dlerror()!=NULL)
      throw new PluginManagerException(5, "Could not load advanced information");

  moreinfo=new PluginVersion2Info;
  gai(moreinfo);
  p.moreinfo=(void*)moreinfo;
}

// Gets information for version 1 or 2 plugins
void PluginManager::pluginGetMoreInformation(Plugin &p)
{
  switch (p.info.client_version)
    {
    case 1: this->pluginGetVersion1Information(p);
      break;
    case 2: this->pluginGetVersion2Information(p);
      break;
    default:
      throw new PluginManagerException(4, "Unknown plugin version");
    }
}

// Adds a plugin to the list
void PluginManager::addPlugin(char *filename)
{
  Plugin info;
  getPluginBasicInfo gbi;

  info.dlhandle=dlopen(filename, RTLD_LAZY);
  if (info.dlhandle==NULL)
      throw new PluginManagerException(2, "Could not load file");

  gbi=(getPluginBasicInfo)dlsym(info.dlhandle, "basicInfo");
  if (dlerror()!=NULL)
      throw new PluginManagerException(3, "Could not load symbol");

  gbi(&info.info);
  info.initialized=false;
  this->pluginGetMoreInformation(info);

  loadedPlugins.push_back(info);
  //  dlclose(info.dlhandle);
}

// List plugins into a string
string PluginManager::pluginList()
{
  stringstream str;
  if (loadedPlugins.size()==0)
    return "No plugins to list";
 
  for (unsigned int i=0; i<loadedPlugins.size(); i++)
    {
      str<<loadedPlugins[i].info.name<<". Version ";
      str<<loadedPlugins[i].info.plugin_version;
      str<<"\n";
    }
 
  return str.str();
}

// Free all plugins
void PluginManager::pluginFree()
{
  cout << "Freeing plugins"<<endl;
 
  for (unsigned int i=0; i<loadedPlugins.size(); i++)
    {
      cout << "Freeing "<<loadedPlugins[i].info.name<<"... ";
      if (loadedPlugins[i].initialized)
    this->pluginDestroy(loadedPlugins[i]);

      if (dlclose(loadedPlugins[i].dlhandle)!=0)
    cout << "Error "<<endl;
      else
    cout << "OK"<<endl;
    }  

  loadedPlugins.clear();
}

// Gets information of a plugin
string PluginManager::getInfo(string plugin)
{
  for (unsigned int i=0; i<loadedPlugins.size(); i++)
    {
      if (plugin==loadedPlugins[i].info.name)
    return getInfo(loadedPlugins[i]);
    }  
  return "Plugin "+plugin+" not found.";
}

// Gets plugin version 1 information
string PluginManager::getVersion1Info(Plugin plugin)
{
  PluginVersion1Info *info=(PluginVersion1Info*)plugin.moreinfo;
  stringstream str;
  str<<"Description: "<<info->description<<endl;
  str<<"Author: "<<info->author<<endl;
  return str.str();
}

// Gets plugin version 2 information
string PluginManager::getVersion2Info(Plugin plugin)
{
  PluginVersion2Info *info=(PluginVersion2Info*)plugin.moreinfo;
  stringstream str;
  str<<"Description: "<<info->description<<endl;
  str<<"Author: "<<info->author<<endl;
  str<<"URL: "<<info->url<<endl;
  str<<"Date: "<<info->date<<endl;

  return str.str();
}

// Gets plugin information into a string
string PluginManager::getInfo(Plugin plugin)
{
  stringstream str;

  str<<"Name: "<<plugin.info.name<<endl;
  str<<"Version: "<<plugin.info.plugin_version<<endl;
  str<<"Client version: "<<plugin.info.client_version<<endl;
  switch (plugin.info.client_version)
    {
    case 1:
      str<<getVersion1Info(plugin);
      break;
    case 2:
      str<<getVersion2Info(plugin);
      break;
    default:    
      str<<"Unknown version."<<endl;
      break;
    }
  return str.str();
}

// Initialize plugin (funcion initialize)
void PluginManager::pluginInit(Plugin &plugin)
{
  initializePlugin pi;

  pi=(initializePlugin)dlsym(plugin.dlhandle, "initialize");
  if (dlerror()!=NULL)
      throw new PluginManagerException(5, "Could not initialize plugin");

  pi();
  plugin.initialized=true;
}

// Destroy plugin (function destroy
bool PluginManager::pluginDestroy(Plugin &plugin)
{
  destroyPlugin pd;

  pd=(destroyPlugin)dlsym(plugin.dlhandle, "destroy");
  if (dlerror()!=NULL)
      throw new PluginManagerException(5, "Could not destroy plugin");
 
  pd();
  plugin.initialized=false;
  return true;
}


string PluginManager::pluginCall(string plugin, string argument)
{
  for (unsigned int i=0; i<loadedPlugins.size(); i++)
    {
      if (plugin==loadedPlugins[i].info.name)
    return pluginCall(loadedPlugins[i], argument);
    }  
  return "Plugin "+plugin+" not found.";
}

string PluginManager::pluginCall(Plugin &plugin, string argument)
{
  if (!plugin.initialized)
    pluginInit(plugin);

  pluginAction pa;

  pa=(pluginAction)dlsym(plugin.dlhandle, "action");
  if (dlerror()!=NULL)
      throw new PluginManagerException(6, "Could not load action");

  return pa(argument);

}
