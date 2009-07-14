//: src:Xml.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 29 july 2005  
// Works as a way of being able to add more possibilities to tinyxml functions [later]
#ifndef XML_H
#define XML_H

//#define TIXML_USE_STL
#include "tinyxml.h"


// Additional functions

/**
* Iterate childs until finding one child with an "id" attribute with value id
*/
TiXmlElement* XmlGetElementById(TiXmlElement* node, char* id);

/**
* Return how many children has this node (or 0 if there are no children)
 */
unsigned int XmlGetChildCount(TiXmlElement* node);

#endif