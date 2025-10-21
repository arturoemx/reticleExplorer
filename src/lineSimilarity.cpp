#include <lineSimilarity.h>
#include <limits>
#include <math.h>
   
bool lineSimilarity(gfeat::line2D &line_a, gfeat::line2D &line_b, clipBox &clpB, float &d, float threshold=1)
{
   gfeat::point2D pl1, pl2;

   d =std::numeric_limits<float>::max();

   if (clpB.clipLine(line_a, pl1, pl2) == true)
   {
      gfeat::point2D pl3, pl4;

      if (clpB.clipLine(line_b, pl3, pl4) == true)
      {
         float mid1x, mid1y,mid2x, mid2y;
         
         mid1x = 0.5 * (pl1.cx + pl2.cx);
         mid1y = 0.5 * (pl1.cy + pl2.cy);
         mid2x = 0.5 * (pl3.cx + pl4.cx);
         mid2y = 0.5 * (pl3.cy + pl4.cy);

         d = pow(mid1x - mid2x, 2) + pow(mid1y - mid2y, 2);     
      }
    }
    return d < threshold * threshold;
}