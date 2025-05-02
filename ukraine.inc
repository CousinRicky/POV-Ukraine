/* ukraine.inc
 * Persistence of Vision Raytracer include file
 *
 * Ukrainian symbols.
 *
 * Copyright © 2025 Richard Callwood III.  Some rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Vers  Date         Notes
 * ----  ----         -----
 * 1.0   2025-Apr-24  A first version of the small coat of arms is created.
 * 1.1   2025-Apr-27  The small arms object is made uniform depth.
 */
#ifndef (Ukraine_Inc_Temp) #declare Ukraine_Inc_Temp = version;
#version max (3.5, min (3.8, version)); // Bracket the POV version.

#include "math.inc"

//================================ PARAMETER ===================================

#ifndef (Ukr_Gamma) #declare Ukr_Gamma = 1; #end

//============================== PRIVATE VALUES ================================

#local UKR_TMP_AZURE = <0, 87, 183> / 255; // approx. PMS 2935 C
#local UKR_TMP_OR = <255, 215, 0> / 255;   // approx. PMS Yellow 012 C
#local UKR_MORE = 1.1;  // to avoid coincident CSG surfaces
#local UKR_TINY = 1e-6; // to avoid coincident pigment surfaces
#local UKR_ZMORE = UKR_MORE * z;
//side tine, outer
#local ukr_outerCtr = <9, 13, 0>;
#local ukr_Router = vlength (ukr_outerCtr - <6, 18.5, 0>);
//side tine, S-curve
#local ukr_Ctr1 = <1.75, 5, 0>;
#local ukr_Ctr2 = <2.5, 8.5, 0>;
#local ukr_R1 = 1.75;
#local ukr_R2 = 1.5;
#local ukr_SAngleD = 90 + degrees
(  atan2 (ukr_Ctr2.y - ukr_Ctr1.y, ukr_Ctr2.x - ukr_Ctr1.x)
 - asin (ukr_R1 / (vlength (ukr_Ctr2 - ukr_Ctr1) * ukr_R1 / (ukr_R1 + ukr_R2)))
);
//side tine, upper inner
#local ukr_Rmid = ukr_Router - 0.5;
#local ukr_Bottom = <2.25, 5, 0>;
#local ukr_outerDist = vlength (ukr_outerCtr - ukr_Bottom);
#local ukr_innerDist = sqrt (pow (ukr_outerDist, 2) - pow (ukr_Rmid, 2));
#local ukr_sideRot = degrees
(  atan2 (ukr_outerCtr.y - ukr_Bottom.y, ukr_outerCtr.x - ukr_Bottom.x)
  + asin (ukr_Rmid / ukr_outerDist)
);
//shield border
#local ukr_shieldPt = -1.5 * y;
#local ukr_shSideCtr = <5, 4, 0>;
#local ukr_shieldR = 3;
#local ukr_shieldL = vlength (ukr_shSideCtr - ukr_shieldPt);
#local ukr_shLowerL = sqrt (pow (ukr_shieldL, 2) - pow (ukr_shieldR, 2));
#local ukr_shieldAngleD = degrees
( atan2
  ( ukr_shSideCtr.y - ukr_shieldPt.y,
    ukr_shSideCtr.x) - asin (ukr_shieldR / ukr_shieldL
  )
);
#local ukr_shLcorner =
  ukr_shSideCtr + vrotate (-(ukr_shieldR + 1/4) * y, ukr_shieldAngleD * z);

//============================= PUBLIC CONSTANTS ===============================

#if (version >= 3.7)
  #declare UKR_C_AZURE = srgb UKR_TMP_AZURE;
  #declare UKR_C_GOLD = srgb UKR_TMP_OR;
#else
  #declare UKR_C_AZURE = rgb VPow (UKR_TMP_AZURE, 2.2 / Ukr_Gamma);
  #declare UKR_C_GOLD = rgb VPow (UKR_TMP_OR, 2.2 / Ukr_Gamma);
#end
#declare UKR_SMALL_TOP = 21.25;
#declare UKR_SMALL_LEFT = -8.25;
#declare UKR_SMALL_RIGHT = 8.25;
#declare UKR_SMALL_BOTTOM = ukr_shieldPt.y - ukr_shieldL / ukr_shLowerL / 4;

//============================= PRIVATE FEATURES ===============================

#macro Ukr__Toroid (RMajor, rMinor, uv_Where)
  difference
  { cylinder { -z, z, RMajor + rMinor }
    cylinder { -UKR_ZMORE, UKR_ZMORE, RMajor - rMinor }
    translate uv_Where * <1,1,0>
  }
#end

#macro Ukr__Bar (uv_A, uv_B, Half_width)
  #local ukr_A = uv_A * <1,1,0>;
  #local ukr_B = uv_B * <1,1,0>;
  box
  { -<0, Half_width, 1>, <vlength (ukr_B - ukr_A), Half_width, 1>
    rotate degrees (atan2 (ukr_B.y - ukr_A.y, ukr_B.x - ukr_A.x)) * z
    translate ukr_A
  }
#end

#local ukr_Small_Side = union
{
  // center tine bulb upper
  intersection
  { Ukr__Toroid (11, 0.5, <11, 13>)
    box { <0, 6.5, -UKR_MORE>, <2.5, 13, UKR_MORE> }
  }
  // center tine bulb lower
  intersection
  { Ukr__Toroid (5, 0.5, <-2.75, 5>)
    box { <0, 0, -UKR_MORE>, <2.75, 6.5, UKR_MORE> }
  }
  //----- side tine, outer -----
  intersection
  {//cylinder { <5.5, 13, 0>, <5.5, 18.5, 0>, 0.5 }
    Ukr__Bar (<5.5, 13, 0>, <5.5, 18.5, 0>, 0.5)
    cylinder { -UKR_ZMORE, UKR_ZMORE, ukr_Router translate ukr_outerCtr }
  }
  //cylinder { <5.5, 5, 0>, <5.5, 13, 0>, 0.5 }
  //cylinder { <4, 8.5, 0>, <5, 8.5, 0>, 0.5 }
  Ukr__Bar (<5.5, 5, 0>, <5.5, 13, 0>, 0.5)
  Ukr__Bar (<4, 8.5, 0>, <5, 8.5, 0>, 0.5)
  //----- side tine, S-curve -----
  //upper
  intersection
  { Ukr__Toroid (ukr_R2, 0.5, 0)
    box { -<0, ukr_R2 + 0.5, UKR_MORE>, ukr_R2 + UKR_MORE }
    plane { <ukr_Ctr1.y - ukr_Ctr2.y, ukr_Ctr1.x - ukr_Ctr2.x, 0>, 0 }
    translate ukr_Ctr2
  }
  //lower
  intersection
  { Ukr__Toroid (ukr_R1, 0.5, ukr_Ctr1)
    box
    { <0, ukr_Ctr1.y, -UKR_MORE>,
      <ukr_R1, ukr_Ctr1.y + ukr_R1 + 0.5, UKR_MORE>
    }
  }
  //join
  Ukr__Bar
  ( ukr_Ctr1 + vrotate (ukr_R1 * x, ukr_SAngleD * z)
    ukr_Ctr2 + vrotate (-ukr_R2 * x, ukr_SAngleD * z),
    0.5
  )
  //----- side tine, upper inner -----
  //upper curve
  intersection
  { Ukr__Toroid (ukr_Rmid, 0.5, ukr_outerCtr)
    box { ukr_outerCtr - <ukr_Router, 0, UKR_MORE>, <5, 18.5, UKR_MORE> }
    plane { -x, 0 rotate ukr_sideRot * z translate ukr_outerCtr }
  }
  //mid straight
  difference
  { object
    { Ukr__Bar (ukr_innerDist * 0.4 * x, ukr_innerDist * x, 0.5)
      rotate ukr_sideRot * z
      translate ukr_Bottom
    }
    cylinder { -UKR_ZMORE, UKR_ZMORE, ukr_R2 - 0.5 translate ukr_Ctr2 }
  }
  //----- shield border -----
  object
  { Ukr__Bar (ukr_shSideCtr * y, (21.25 + UKR_TINY) * y, 1/8 + UKR_TINY)
    translate (8 + 1/8 + UKR_TINY) * x
  }
  intersection
  { Ukr__Toroid (ukr_shieldR + 1/8 + UKR_TINY, 1/8 + UKR_TINY, 0)
    box { <0, -ukr_shieldR, -UKR_MORE>, <ukr_shieldR + 1/4, 0, UKR_MORE> }
    plane { -x, 0 rotate ukr_shieldAngleD * z }
    translate ukr_shSideCtr
  }
  intersection
  { object
    { Ukr__Bar (<-1, -1/8, 0>, <ukr_shLowerL, -1/8, 0>, 1/8 + UKR_TINY)
      translate -UKR_TINY * y
      rotate ukr_shieldAngleD * z
      translate ukr_shieldPt
    }
    plane { -x, 0 }
  }
}

//============================= PUBLIC FEATURES ================================

#declare Ukr_o_Small_Arms = union
{ object { ukr_Small_Side }
  object { ukr_Small_Side scale <-1, 1, 1> }
  // center tine tip
  intersection
  { cylinder { -z, UKR_ZMORE, 3 translate -2.25 * x }
    cylinder { -UKR_ZMORE, z, 3 translate 2.25 * x }
    scale <1, 8 * sqrt(7) / 21, 1>
    translate 18 * y
  }
  // center tine shaft
  prism
  { bezier_spline -1, 1, 16
    <0.75, 18>, <0.75, 49/3>, <0.5, 44/3>, <0.5, 13>,
    <0.5, 13>, <0.17, 13>, <-0.17, 13>, <-0.5, 13>,
    <-0.5, 13>, <-0.5, 44/3>, <-0.75, 49/3>, <-0.75, 18>,
    <-0.75, 18>, <-0.25, 18>, <0.25, 18>, <0.75, 18>
    rotate -90 * x
  }
  // bottom shaft
  difference
  { Ukr__Bar (0, 4 * y, 0.5)
    cylinder { -UKR_ZMORE, UKR_ZMORE, 2 translate <-sqrt(3), -1, 0> }
    cylinder { -UKR_ZMORE, UKR_ZMORE, 2 translate <sqrt(3), -1, 0> }
  }
  // lower crossbar
  object { Ukr__Bar (-6 * x, 6 * x, 0.5) translate 4.5 * y }
  // top of shield
  object
  { Ukr__Bar (-8 * x, 8 * x, 1/8 + UKR_TINY)
    translate (21 + 1/8 + UKR_TINY) * y
  }
}

#declare Ukr_p_Small_Arms = pigment
{ object { Ukr_o_Small_Arms UKR_C_AZURE UKR_C_GOLD }
}

#declare Ukr_Small_Shield = union
{ cylinder { 0, z, ukr_shieldR + 1/4 translate ukr_shSideCtr }
  cylinder { 0, z, ukr_shieldR + 1/4 translate ukr_shSideCtr * <-1, 1, 1> }
  prism
  { -1, 0, 8,
    <8.25, 21.25>, <8.25, 4>, <ukr_shLcorner.x, ukr_shLcorner.y>,
    <0, UKR_SMALL_BOTTOM>, <-ukr_shLcorner.x, ukr_shLcorner.y>,
    <-8.25, 4>, <-8.25, 21.25>, <8.25, 21.25>
    rotate -90 * x
  }
}

#macro Ukr_Make_Small_Arms()
  object
  { Ukr_Small_Shield
    pigment { Ukr_p_Small_Arms translate 0.5 * z }
  }
#end

#declare Ukr_Small_Arms = Ukr_Make_Small_Arms()

#version Ukraine_Inc_Temp;
#end
// end of ukraine.inc
