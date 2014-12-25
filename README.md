cpp-plugin-test
===============

Trying to make a tiny plugin system in c++

To compile plugins:
$ g++ -fPIC -shared -o homer.so homer.cpp
$ g++ -fPIC -shared -o newer.so newer.cpp
$ g++ -fPIC -shared -o vacas.so vacas.cpp

To compile the plugin manager:
$ g++ -o main main.cpp pluginmanager.cpp pluginmanagerexception.cpp -ldl

The plugin newer has an invalid version on it's code so the main program
won't recognise it.

For more information, please visit: http://totaki.com/poesiabinaria/2013/03/enlazado-dinamico-en-c-dynamic-linking-iv-permitir-plug-ins-en-nuestra-aplicacion/
(sorry, this site is in Spanish only)

