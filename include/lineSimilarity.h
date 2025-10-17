#ifndef __LINE_SIMILARITY__
#define __LINE_SIMILARITY__

#include <geomFeatures.h>

/*!
\struct clipBox

\brief struct thatdefines a bounding box and provides a method to find the
        intersection points of an homogeneous line with it.

   tl:   A two-element list, tuple or array that contain the coordinates
         of the top-left corner of the bounding-box. The coordinate is
         expected to be column-wise, i.e. [column, row].
   wh: A two-element list, tuple or array that contain the width and height
         of the bounding-box, e.g. [width, height].

   """
*/
struct clipBox
{
   gfeat::vec2D corners[4];
   gfeat::vec2D sides[4];

   clipBox(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
   
   clipBox(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3);
   
   bool clipLines(gfeat::line2D &l, gfeat::point2D &p1, gfeat::point2D &p2);
   
};
   
bool line_similarity(gfeat::line2D &line_a, gfeat::line2D &line_b, clipBox &clpB, float threshold, float d);

#endif