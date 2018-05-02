#include "mdp.h"
#include <stdio.h>
#include "utilities.h"

#include <stdio.h> // for error message only

  double
calc_eu ( const mdp *  p_mdp, unsigned int state, const double * utilities,
	const unsigned int action)
{
  if (p_mdp->numAvailableActions[state] == 0) {
	return 0;
  }
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
	double * meu, unsigned int * action ) {
  if (p_mdp->numAvailableActions[state] == 0) 
	return ;
  *action = 0;
  double eu = calc_eu(p_mdp, state, utilities, *action);
  *meu = eu;
  for (int i = 1; i < p_mdp->numAvailableActions[state]; i++) {
	eu = calc_eu(p_mdp, state, utilities, i);
	if (eu > *meu) {
	  *action = i;
	  *meu = eu;
	}
  }
}

