//
//  taulop_sequence_hpp
//  TauLopCost
//
//  Created by jarico on 30/10/16.
//  Copyright © 2016 Juan A. Rico. All rights reserved.
//

#ifndef taulop_sequence_hpp
#define taulop_sequence_hpp

#include "transmission.hpp"

#include <list>
#include <iostream>

class TauLopSequence {
   
private:
   
   list<Transmission> l_seq;
   
public:
   
            TauLopSequence  ();
           ~TauLopSequence  ();
   
   void           add       (const Transmission &c);
   Transmission  &get       ();
   void           substract (double t_min, int tau);
   bool           empty     ();
   void           compact   ();
   
   // TBD ??
   //void   apply     (TaulopCost *tc);
   
   void  show ();
};

#endif /* taulop_sequence_hpp */
