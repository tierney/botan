/*************************************************
* Hardware Timer Header File                     *
* (C) 1999-2007 Jack Lloyd                       *
*************************************************/

#ifndef BOTAN_TIMER_HARDWARE_H__
#define BOTAN_TIMER_HARDWARE_H__

#include <botan/timer.h>

namespace Botan {

/*************************************************
* Hardware Timer                                 *
*************************************************/
class BOTAN_DLL Hardware_Timer : public Timer
   {
   public:
      /*
      @todo: Add sync(Timer& wall_clock, bool milliseconds) which busy
      loops using wall_clock and tries to guess the tick rate of the
      hardware counter, allowing it to be used for benchmarks, etc
      */

      std::string name() const { return "Hardware Timer"; }
      u64bit clock() const;
   };

}

#endif