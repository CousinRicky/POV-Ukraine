/* ukraine.pov version 1.1
 * Persistence of Vision Raytracer scene description file
 *
 * Ukrainian small coat of arms.
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
 * 1.1   2025-May-02  Created.
 */
#version 3.7;

global_settings { assumed_gamma 1 }
#default { finish { ambient 0 diffuse 0 emission 1 } }
background { rgb 1 }
#include "ukraine.inc"

#declare HEIGHT = 24;
camera
{ orthographic
  location <0, 9.75, -1>
  right HEIGHT * image_width / image_height * x
  up HEIGHT * y
}

object { Ukr_Small_Arms }
