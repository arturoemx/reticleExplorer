#include <lineSimilarity.h>
#include <limits>
#include <math.h>


clipBox::clipBox(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
{
   corners[0] = gfeat::point2D(x0, y0, z0);
   corners[1] = gfeat::point2D(x1, y1, z1);
   corners[2] = gfeat::point2D(x2, y2, z2);
   corners[3] = gfeat::point2D(x3, y3, z3);
   
   sides[0].join(corners[0], corners[1]);
   sides[1].join(corners[1], corners[2]);
   sides[2].join(corners[2], corners[3]);
   sides[3].join(corners[3], corners[0]);
}

clipBox::clipBox(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3)
{
   corners[0] = gfeat::point2D(x0, y0, 1.);
   corners[1] = gfeat::point2D(x1, y1, 1.);
   corners[2] = gfeat::point2D(x2, y2, 1.);
   corners[3] = gfeat::point2D(x3, y3, 1.);
   
   sides[0].join(corners[0], corners[1]);
   sides[1].join(corners[1], corners[2]);
   sides[2].join(corners[2], corners[3]);
   sides[3].join(corners[3], corners[0]);
}

bool clipBox::clipLine(gfeat::line2D &l, gfeat::point2D &p1, gfeat::point2D &p2)
{
   gfeat::point2D intersections[4];
   gfeat::line2D ln(l);
   bool where[4] = {false, false, false, false};
   int i, j, idx[4];
   
   intersections[0].intersect(ln, sides[0]); //Top
   intersections[1].intersect(ln, sides[1]); //Right
   intersections[2].intersect(ln, sides[2]); //Bottom
   intersections[3].intersect(ln, sides[3]); //Left
   

   for (i=0;i<4;++i)
      if (intersections[i][2] != 0.)
         intersections[i] /= intersections[i][2];
      
   if (intersections[0][0] >= corners[0][0] && intersections[0][0] < corners[1][0] && !intersections[0].infinity)
      where[0] = true; // TOP
   if (intersections[1][1] >= corners[1][1] && intersections[1][1] < corners[2][1] && !intersections[1].infinity)
      where[1] = true; // RIGHT
   if (intersections[2][0] > corners[3][0] && intersections[2][0] <= corners[2][0] && !intersections[2].infinity)
      where[2] = true; // BOTTOM
   if (intersections[3][1] > corners[0][1] && intersections[3][1] <= corners[3][1] && !intersections[3].infinity)
      where[3] = true; // LEFT

   for (i = j = 0; i < 4; ++i)
      if (where[i])
         idx[j++] = i;

   if (j < 2)
   {
      p1 = p2 = gfeat::point2D(0,0,0);
      return false;
   }
   
   p1 = intersections[idx[0]];
   p2 = intersections[idx[1]];
   return true;
}
   
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