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
#ifndef _PLUGINVERSION1_H
#define _PLUGINVERSION1_H 1

#include <string>

struct PluginVersion1Info
{
  std::string description;
  std::string author;
};

typedef void (*getPluginVersion1Info)(PluginVersion1Info*);

#endif /* _PLUGINVERSION1_H */
