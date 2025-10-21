#ifndef __CLIP_BOX__
#define __CLIP_BOX__

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
   gfeat::point2D corners[4];
   gfeat::line2D sides[4];

   clipBox(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
   
   clipBox(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3);
   
   bool clipLine(gfeat::line2D &l, gfeat::point2D &p1, gfeat::point2D &p2);
   
};

#endif