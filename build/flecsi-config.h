#pragma once

#if defined (SINGULARITY_ENABLE_KOKKOS)
    #define PORTABILITY_STATEGY_KOKKOS
    #if defined(SINGULARITY_ENABLE_KOKKOSKERNELS)
        #define(SINGULARITY_USE_KOKKOSKERNELS)
    #endif
#endif

#define fastmathorder 4
