#include "Xml.h"

// Additional functions

/**
* Iterate childs until finding one child with an "id" attribute with value id
 mynotes
 this could be recursive sooooooo TO DO!
 */
TiXmlElement* XmlGetElementById(TiXmlElement* node, char* id) {
	return 0;
}

/**
* Return how many children has this node (or 0 if there are no children)
 This does not count children of children!!!
*/
unsigned int XmlGetChildCount(TiXmlElement* node) {
	unsigned int count = 0;
	if(node->NoChildren()) {
		return 0;
	} else {
		TiXmlElement* list = node->FirstChildElement();
		while(list) {
			count++;
			list = list->NextSiblingElement();
		}
	}
	return count;
}