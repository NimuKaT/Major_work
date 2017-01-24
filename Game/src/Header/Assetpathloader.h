/*
 * Assetoathloader.h
 *
 *  Created on: 19Jan.,2017
 *      Author: ImuKaT
 */

#ifndef ASSETPATHLOADER_H_
#define ASSETPATHLOADER_H_

#include <fstream>

#include "Global.h"


class Asset_path_loader{
public:
	Asset_path_loader();

private:
	SDL_RWops* imageFile;
};



#endif /* ASSETOATHLOADER_H_ */
