/**
 * @file  QdecUtilities.cxx
 * @brief Misc utilities
 *
 * A bunch of misc utilities for Qdec.
 */
/*
 * Original Author: Kevin Teich
 * CVS Revision Info:
 *    $Author: nicks $
 *    $Date: 2008/12/04 00:43:06 $
 *    $Revision: 1.2 $
 *
 * Copyright (C) 2007-2008,
 * The General Hospital Corporation (Boston, MA). 
 * All rights reserved.
 *
 * Distribution, usage and copying of this software is covered under the
 * terms found in the License Agreement file named 'COPYING' found in the
 * FreeSurfer source code root directory, and duplicated here:
 * https://surfer.nmr.mgh.harvard.edu/fswiki/FreeSurferOpenSourceLicense
 *
 * General inquiries: freesurfer@nmr.mgh.harvard.edu
 * Bug reports: analysis-bugs@nmr.mgh.harvard.edu
 *
 */

#include "QdecUtilities.h"

#include <string.h>
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

void
QdecUtilities::AssertFileIsReadable ( string const& ifn ) {
  
  if( !QdecUtilities::IsFileReadable( ifn ) )
    throw runtime_error( string("Couldn't find file ") + ifn );

}

bool
QdecUtilities::IsFileReadable ( string const& ifn ) {

  ifstream f( ifn.c_str(), ios::in );
  if( !f || f.bad() )
    return false;

  return true;
}

const char *
QdecUtilities::FileNamePath(const char *fname, const char *pathName)
{
  char *slash ;

  strcpy((char*)pathName, fname) ;
  slash = strrchr(pathName, '/') ;
  if (slash) *slash = 0 ; /* remove file name */
  else
#ifndef Linux
    getcwd((char*)pathName, MAXPATHLEN-1) ;  /* no path at all, must be cwd */
#else
#if 0
  getcwd(pathName, MAXPATHLEN-1) ;
#else
  sprintf((char*)pathName, ".") ;
#endif
#endif

  return(pathName) ;
}


const char *
QdecUtilities::GetResourceString(const char *key)
{
  // resource file ~/.Qdecrc contains key/value pairs
  if ( NULL == getenv("HOME") ) return NULL;
  string rcFile = getenv("HOME");
  rcFile += "/.Qdecrc";
  ifstream ifsFile;
  ifsFile.open(rcFile.c_str());
  if ( ifsFile.is_open())
  {
    size_t tmpstrMaxSize = 200000; // maximum size of one line in the file
    char *tmpstr = (char *)malloc( tmpstrMaxSize );
#define UNIX_EOL 0x0A
#define MAC_EOL  0x0D
    char eol_delim = UNIX_EOL;
    ifsFile.getline(tmpstr, tmpstrMaxSize, eol_delim);
    if (ifsFile.eof())
    {
      eol_delim =  MAC_EOL;
    }
    ifsFile.clear();
    ifsFile.seekg( 0 ); // rewind
#undef WHITESPC
#define WHITESPC " ,\"\t\n\r"
    int getLineRet = 0;
    while ( (getLineRet = 
             ifsFile.getline(tmpstr, tmpstrMaxSize, eol_delim).good()) ) 
    {
      char *token = strtok(tmpstr,WHITESPC);
      if ((token != NULL) && !strcmp(token,key))
      {
        // found our key
        token = strtok(NULL,WHITESPC); // get next token in this line
        if ((token != NULL) && !strcmp(token,"="))
        {
          // found the =, so return the value
          return strtok(NULL,WHITESPC);
        }
      }
      // else continue with next line
    }
  }
  ifsFile.close();
  return NULL;
}
