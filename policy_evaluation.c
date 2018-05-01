#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#include "utilities.h"
#include "mdp.h"

double max(double x, double y) {
  if (x > y) 
	return x;
  return y;
}

/*  Procedure
 *    policy_evaluation
 *
 *  Purpose
 *    Iteratively estimate state utilities under a fixed policy
 *
 *  Parameters
 *   policy
 *   p_mdp
 *   epsilon
 *   gamma
 *   utilities
 *
 *  Produces,
 *   [Nothing.]
 *
 *  Preconditions
 *    policy points to a valid array of length p_mdp->numStates
 *    Each policy entry respects 0 <= policy[s] < p_mdp->numActions
 *       and policy[s] is an entry in p_mdp->actions[s]
 *    p_mdp is a pointer to a valid, complete mdp
 *    epsilon > 0
 *    0 < gamma < 1
 *    utilities points to a valid array of length p_mdp->numStates
 *
 *  Postconditions
 *    utilities[s] has been updated according to the simplified Bellman update
 *    so that no update is larger than epsilon
 */
void policy_evaluation( const unsigned int* policy, const mdp* p_mdp,
	double epsilon, double gamma,
	double* utilities)
{
  unsigned int numStates = p_mdp->numStates;
  unsigned int arrSize = sizeof(double) * numStates;
  for (int state = 0; state < numStates; state++) {
	if (p_mdp->terminal[state]) {
	  utilities[state] = p_mdp->rewards[state];
	} else
	  utilities[state] = 0;
  } // initializes all utilities as 0, except for terminal states,
  // who we will initialize as their reward value here to avoid
  // having to ever touch them again
  double * utilitiesprime = malloc(arrSize);
  *memcpy(utilitiesprime,utilities,arrSize);
  double delta = epsilon + 1;
  while (delta > epsilon) {
	delta = 0;
	for (int state = 0; state < numStates; state++) {
	  if(!p_mdp->terminal[state]) {
		utilitiesprime[state] = 
		  p_mdp->rewards[state] + 
		  calc_eu(p_mdp, state, utilities, policy[state]);
		delta = max(fabs(utilities[state] - utilitiesprime[state]), delta);
	  }
	}
	*memcpy(utilities,utilitiesprime,arrSize);
  } free(utilitiesprime);
  return ;
}
