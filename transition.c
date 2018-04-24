/* start.c
 *
 * A small test program to load and print info on an MDP file
 *
 * Jerod Weinman
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <inttypes.h>

#include "mdp.h"



////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    fprintf(stderr,"Usage: %s mdpfile state action\n",argv[0]);
    exit(EXIT_FAILURE);
  }

  // Pointer for the MDP struct
  mdp *p_mdp;

  unsigned int state = (unsigned int)strtol(argv[2], NULL, 10);
  unsigned int action = (unsigned int)strtol(argv[3], NULL, 10);

  // Read the MDP file
  p_mdp = mdp_read(argv[1]);

  if (NULL == p_mdp)
    // mdp_read prints a message upon failure
    exit(EXIT_FAILURE);
    
	// Print information about the markov decision process (MDP)
  printf("MDP Info for %s\n",argv[1]);
  printf("Number of states: %u\n", p_mdp->numStates);
  printf("Number of actions: %u\n", p_mdp->numActions);

  printf("Available actions\n");  

  for (unsigned int t = 0; t < p_mdp->numStates ; t++)
	printf("%u  %.2lf\n", t, p_mdp->transitionProb[t][state][action]);

  // Clean up
  mdp_free(p_mdp);

}
