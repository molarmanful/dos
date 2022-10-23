#ifndef _deps_h
#define _deps_h

#define __ATMEGA__ 1

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <ustd_array.h>
#include <ustd_functional.h>
#include <ustd_map.h>

#define UA ustd::array
#define UM ustd::map
#define ADD(xs, x) xs[xs.length()] = x

#endif