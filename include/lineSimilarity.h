#ifndef __LINE_SIMILARITY__
#define __LINE_SIMILARITY__

#include <clipBox.h>
   
bool lineSimilarity(gfeat::line2D &line_a, gfeat::line2D &line_b, clipBox &clpB, float &d, float threshold);

#endif