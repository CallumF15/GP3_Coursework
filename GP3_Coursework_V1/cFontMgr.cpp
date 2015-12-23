/*
== == == == == == == == =
cFontMgr.h
- Header file for class definition - SPECIFICATION
- Header file for the cFontMgr class
== == == == == == == == =
*/

#include "cFontMgr.h"

cFontMgr* cFontMgr::pInstance = NULL;

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cFontMgr* cFontMgr::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cFontMgr(); //initialize font manager
	}
	return cFontMgr::pInstance;  //return instance of font manager
}

/*
=================================================================================
Constructor
=================================================================================
*/
cFontMgr::cFontMgr()
{

}

cFontMgr::~cFontMgr()							// Destructor.
{
	deleteFont();
}

void cFontMgr::addFont(LPCSTR fontName, LPCSTR fileName, int fontSize)  // add font to the Font collection
{
	if (!getFont(fontName))
	{
		cFont * newFont = new cFont(fileName, fontSize); //initialize new font
		gameFonts.insert(make_pair(fontName, newFont)); //add font to map
	}
}

cFont* cFontMgr::getFont(LPCSTR fontName)				// return the font for use
{
	map<LPCSTR, cFont*>::iterator theFont = gameFonts.find(fontName); //find font with specified name
	if (theFont != gameFonts.end()) //make sure not at end of iterator
	{
		return theFont->second; //return second value of map
	}
	else
	{
		return NULL;
	}
}

void cFontMgr::deleteFont()								// delete font.
{
	for (map<LPCSTR, cFont*>::const_iterator theFont = gameFonts.begin(); theFont != gameFonts.end(); theFont++) //iterate fonts 
	{
		delete theFont->second; //deletes font
	}
}
