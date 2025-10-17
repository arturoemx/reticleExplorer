#include <lineSimilarity.h>
#include <limits>
#include <math.h>


clipBox::clipBox(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
{
   corners[0] = gfeat::vec2D(x0, y0, z0);
   corners[1] = gfeat::vec2D(x1, y1, z1);
   corners[2] = gfeat::vec2D(x2, y2, z2);
   corners[3] = gfeat::vec2D(x3, y3, z3);
   
   sides[0].cross(corners[0], corners[1]);
   sides[1].cross(corners[1], corners[2]);
   sides[2].cross(corners[2], corners[3]);
   sides[3].cross(corners[3], corners[0]);
}

clipBox::clipBox(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3)
{
   corners[0] = gfeat::vec2D(x0, y0, 1.);
   corners[1] = gfeat::vec2D(x1, y1, 1.);
   corners[2] = gfeat::vec2D(x2, y2, 1.);
   corners[3] = gfeat::vec2D(x3, y3, 1.);
   
   sides[0].cross(corners[0], corners[1]);
   sides[1].cross(corners[1], corners[2]);
   sides[2].cross(corners[2], corners[3]);
   sides[3].cross(corners[3], corners[0]);
}

bool clipBox::clipLines(gfeat::line2D &l, gfeat::point2D &p1, gfeat::point2D &p2)
{
   gfeat::vec2D intersections[4];
   gfeat::vec2D ln(l);
   bool where[4] = {false, false, false, false};
   int i, j, idx[4];
   
   intersections[0].cross(ln, sides[0]); //Top
   intersections[1].cross(ln, sides[1]); //Right
   intersections[2].cross(ln, sides[2]); //Bottom
   intersections[3].cross(ln, sides[3]); //Left
   

   for (i=0;i<4;++i)
      if (intersections[i][2] != 0.)
         intersections[i] /= intersections[i][2];
      
   if (intersections[0][0] >= corners[0][0] && intersections[0][0] < corners[0][1])
      where[0] = true; // TOP
   if (intersections[1][1] >= corners[1][1] && intersections[1][1] < corners[1][2])
      where[1] = true; // RIGHT
   if (intersections[0][2] > corners[0][3] && intersections[0][2] <= corners[0][2])
      where[2] = true; // BOTTOM
   if (intersections[1][3] > corners[1][0] && intersections[1][3] <= corners[1][3])
      where[3] = true; // LEFT

   for (i = j = 0; i < 4; ++i)
      if (where[i])
         idx[j++] = i;

   if (j < 2)
   {
      p1 = p2 = gfeat::point2D(0,0,0);
      return false;
   }
   
   p1 = gfeat::point2D(intersections[idx[0]][0], intersections[idx[0]][1], intersections[idx[0]][2]);
   p2 = gfeat::point2D(intersections[idx[1]][0], intersections[idx[1]][1], intersections[idx[1]][2]);
   
   return true;
}
   
bool line_similarity(gfeat::line2D &line_a, gfeat::line2D &line_b, clipBox &clpB, float threshold=1, float d=std::numeric_limits<double>::max())
{
   gfeat::point2D pl1, pl2;

   if (clpB.clipLines(line_a, pl1, pl2) == true)
   {
      gfeat::point2D pl3, pl4;

      if (clpB.clipLines(line_b, pl3, pl4) == true)
      {
         float mid1x, mid1y,mid2x, mid2y;
         
         mid1x = 0.5 * (pl1.cx + pl2.cx);
         mid1y = 0.5 * (pl1.cy + pl2.cy);
         mid2x = 0.5 * (pl3.cx + pl4.cx);
         mid2y = 0.5 * (pl3.cy + pl4.cy);

         d = pow(mid1x - mid1x, 2) + pow(mid1y - mid1y, 2);     
      }
    }
    return d < threshold * threshold;
}