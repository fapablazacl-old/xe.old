
/**
 * @file Metaprog.hpp
 * @brief Metaprogramming facilities.
 */ 

#pragma once

#ifndef __xe_metaprog_hpp__
#define __xe_metaprog_hpp__

namespace xe {
    template<bool, class True, class False>
    struct meta_if {};
    
    template<class True, class False>
    struct meta_if<true> {
        typedef True result;
    };
    
    template<class True, class False>
    struct meta_if<false> {
        typedef False result;
    };
}

#endif
