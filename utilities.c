#include "mdp.h"
#include "utilities.h"

#include <stdio.h> // for error message only

double
calc_eu ( const mdp *  p_mdp, unsigned int state, const double * utilities,
          const unsigned int action)
{
  double eu = 0;   // Expected utility
  unsigned int numStates = p_mdp->numStates;

  for (int newstate = 0; newstate < numStates; newstate++) {
	eu += p_mdp->transitionProb[newstate][state][action] * utilities[newstate];
  }

  // Calculate expected utility: sum_{s'} P(s'|s,a)*U(s')
  
  return eu;
}

void
calc_meu ( const mdp * p_mdp, unsigned int state, const double * utilities,
           double * meu, unsigned int * action )
{
  // Calculated maximum expected utility (use calc_eu):
  fprintf (stderr,
           "WARNING! calc_meu not implemented. Results will be invalid!\n");
}
