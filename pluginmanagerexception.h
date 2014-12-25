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
#ifndef _PLUGINMANAGEREXCEPTION_H
#define _PLUGINMANAGEREXCEPTION_H 1

#include <string>
#include <exception>

using namespace std;

class PluginManagerException : public exception {
 public:
  PluginManagerException(int code, string err);
  ~PluginManagerException() throw();

  string what();
  int getCode();

private:
  string error;
  int code;
};
#endif /* _PLUGINMANAGEREXCEPTION_H */
