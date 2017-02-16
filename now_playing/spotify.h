#ifndef SPOTIFY_H
#define SPOTIFY_H

#include <iostream>
#include <string>
using namespace std;
#include <Windows.h>
#include <stdio.h>
#include "shared.h"
#include "ts3_functions.h"

int spotify(struct TrackInfo *info, struct TS3Functions ts3Functions);

#endif //#ifndef SPOTIFY_H