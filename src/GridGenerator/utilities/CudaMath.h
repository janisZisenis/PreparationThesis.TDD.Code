#ifndef CudaMath_H
#define CudaMath_H

#include <cmath>

#define EPSILON 1.0E-7f

class CudaMath
{
public:


   inline static bool equalZero(const doubflo& val1)
   {
       return std::fabs(val1) < EPSILON;
   }
  
   inline static bool unequalZero(const doubflo& val1)
   {
       return std::fabs(val1) >= EPSILON;
   }


   inline static bool equal(const doubflo& val1, const doubflo& val2)
   {
       float i = std::fabs(val1 - val2);
      return std::fabs( val1 - val2 ) < EPSILON;
   }

   inline static bool unequal(const doubflo& val1, const doubflo& val2)
   {
      return std::fabs( val1 - val2 ) >= EPSILON;
   }


   inline static doubflo sqrt(const doubflo& val)
   {
       return sqrtf(val);
   }

   inline static doubflo acos(const doubflo& val)
   {
       return acosf(val);
   }

};

#endif
