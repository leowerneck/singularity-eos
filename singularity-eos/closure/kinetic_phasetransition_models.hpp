//------------------------------------------------------------------------------
// © 2024. Triad National Security, LLC. All rights reserved.  This
// program was produced under U.S. Government contract 89233218CNA000001
// for Los Alamos National Laboratory (LANL), which is operated by Triad
// National Security, LLC for the U.S.  Department of Energy/National
// Nuclear Security Administration. All rights in the program are
// reserved by Triad National Security, LLC, and the U.S. Department of
// Energy/National Nuclear Security Administration. The Government is
// granted for itself and others acting on its behalf a nonexclusive,
// paid-up, irrevocable worldwide license in this material to reproduce,
// prepare derivative works, distribute copies to the public, perform
// publicly and display publicly, and to permit others to do so.
//------------------------------------------------------------------------------

#ifndef _SINGULARITY_EOS_CLOSURE_KINETIC_PHSETRANSITION_MODELS_
#define _SINGULARITY_EOS_CLOSURE_KINETIC_PHSETRANSITION_MODELS_

#include <ports-of-call/portability.hpp>
#include <ports-of-call/portable_errors.hpp>
#include <singularity-eos/base/fast-math/logs.hpp>
#include <singularity-eos/base/robust_utils.hpp>
#include <singularity-eos/eos/eos.hpp>

#include <cmath>

#ifdef SINGULARITY_USE_KOKKOSKERNELS
#include <KokkosBatched_ApplyQ_Decl.hpp>
#include <KokkosBatched_QR_Decl.hpp>
#include <KokkosBatched_Trsv_Decl.hpp>
#else
#include <Eigen/Dense>
#endif // SINGULARITY_USE_KOKKOSKERNELS

namespace singularity {


PORTABLE_INLINE_FUNCTION void LogRatesCGModel(const Real *w, const Real *b,
    const int num_phases, const Real *gibbs, const int *gibbsorder, Real *logRjk, int *fromto) {

// begin the calculation of logRik
    int jk = 0;
    for (int j = 0; j < num_phases-1; j++){       
        // from high Gibb phase to low
        for (int k = num_phases-1; k > j; k--){ 
	  // from low Gibb phase to high, k>j always, gibbs_j > gibbs_k always
          // always mass transport from j->k
          Real hgj=gibbs[gibbsorder[j]];
          Real hgk=gibbs[gibbsorder[k]];
// calc phase dx from hgi to hgk
          Real dgdb=(hgj-hgk)/(b[gibbsorder[j]*num_phases + gibbsorder[k]]);
	  // First is highest level to levels below, largest gibbs energy diff first. Then follows 2nd highest to levels below.
          logRjk[jk] = log(w[gibbsorder[j]*num_phases + gibbsorder[k]]*dgdb)+dgdb*dgdb;
	  fromto[jk] = gibbsorder[j]*10+gibbsorder[k];
	  jk++;
        }
    }
    return; 
}

} // namespace singularity

#endif // _SINGULARITY_EOS_CLOSURE_KINETIC_PHSETRANSITION_MODELS_
