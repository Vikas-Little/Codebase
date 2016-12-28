cmake_minimum_required (VERSION 2.6)
project (LightHTTPServer)
add_executable (bin/server src/LightHTTPServer.c src/Parse.c src/FileUtility.c src/WebPage.c) 
