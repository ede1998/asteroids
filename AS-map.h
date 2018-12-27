#pragma once

#define AS_MAP_LEFT -40
#define AS_MAP_RIGHT 40
#define AS_MAP_BOTTOM -30
#define AS_MAP_TOP 30
#define AS_MAP_WIDTH (std::abs(AS_MAP_RIGHT)+std::abs(AS_MAP_LEFT))
#define AS_MAP_HEIGHT (std::abs(AS_MAP_TOP)+std::abs(AS_MAP_BOTTOM))
#define AS_MAP_XYRATIO ((double)AS_MAP_HEIGHT/AS_MAP_WIDTH)

