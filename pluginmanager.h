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
#ifndef _PLUGINMANAGER_H
#define _PLUGINMANAGER_H 1

#include "plugins/basicplugin.h"
#include "pluginmanagerexception.h"
#include <string>
#include <dirent.h>
#include <vector>

using namespace std;
class PluginManager
{
 public:
  PluginManager(string pluginDir);
  ~PluginManager();

  /* Scan plugins in the plugins directory */
  void pluginScan();
  /* Lists loaded plugins */
  string pluginList();
  /* Get information about a plugin */
  string getInfo(string plugin);
  /* Call a plugin with an argument */
  string pluginCall(string plugin, string argument);
  /* Free plugins from memory */
  void pluginFree();

 private:
  struct Plugin
  {
    void *dlhandle;
    PluginBasicInfo info;
    void *moreinfo;
    bool initialized;
  };
  string pluginDir;
  vector<Plugin> loadedPlugins;
 
  void pluginInit(Plugin &plugin);
  bool pluginDestroy(Plugin &plugin);
  void addPlugin(char *filename);

  /* Call a plugin */
  string pluginCall(Plugin &plugin, string argument);

  /* Information related methods */
  string getInfo(Plugin plugin);
  string getVersion1Info(Plugin plugin);
  string getVersion2Info(Plugin plugin);

  void pluginGetMoreInformation(Plugin &p);
  void pluginGetVersion1Information(Plugin &p);
  void pluginGetVersion2Information(Plugin &p);

  /* Maybe these two methods must be separated in another .h. They are so */
  /* general purpose. */
  char *getFullName(char *path, struct dirent *ent);
  char *getExtension(char *filename);
};

#endif /* _PLUGINMANAGER_H */
