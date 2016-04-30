#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"

#define NUM_ITERATIONS 1000

#ifdef VERBOSE
#define VERBOSE_PRINT(S, ...) printf (S, ##__VA_ARGS__);
#else
#define VERBOSE_PRINT(S, ...) ;
#endif

int has_match = 0; 
int has_paper = 0; 
int has_tobacco = 0; 

struct Agent {
  uthread_mutex_t mutex;
  uthread_cond_t  match;
  uthread_cond_t  paper;
  uthread_cond_t  tobacco;
  uthread_cond_t  smoke;
};

struct Agent* createAgent() {
  struct Agent* agent = malloc (sizeof (struct Agent));
  agent->mutex   = uthread_mutex_create();
  agent->paper   = uthread_cond_create (agent->mutex);
  agent->match   = uthread_cond_create (agent->mutex);
  agent->tobacco = uthread_cond_create (agent->mutex);
  agent->smoke   = uthread_cond_create (agent->mutex);
  return agent;
}

/**
 * You might find these declarations helpful.
 *   Note that Resource enum had values 1, 2 and 4 so you can combine resources;
 *   e.g., having a MATCH and PAPER is the value MATCH | PAPER == 1 | 2 == 3
 */
enum Resource            {    MATCH = 1, PAPER = 2,   TOBACCO = 4};
char* resource_name [] = {"", "match",   "paper", "", "tobacco"};

int signal_count [5];  // # of times resource signalled
int smoke_count  [5];  // # of times smoker with resource smoked

struct Smoker{
  uthread_cond_t t_smoker; 
  uthread_cond_t m_smoker; 
  uthread_cond_t p_smoker; 
  uthread_cond_t done_smoking;
  struct Agent* agent;
}; 

struct Smoker* createSmoker(struct Agent* agent){
  struct Smoker* smoker = malloc(sizeof (struct Smoker)); 
  smoker->t_smoker = uthread_cond_create(agent->mutex);
  smoker->m_smoker = uthread_cond_create(agent->mutex);
  smoker->p_smoker = uthread_cond_create(agent->mutex);
  smoker->done_smoking = uthread_cond_create(agent->mutex);
  smoker->agent = agent;
}

void* match_watcher(void* av){
  struct Smoker* s = av; 
  uthread_mutex_lock(s->agent->mutex);
  while(1){

    uthread_cond_wait(s->agent->match); 
    has_match ++; 
    if(has_tobacco >= 1){
      has_tobacco--; 
      has_match--; 
      uthread_cond_signal(s->p_smoker);
    }
    if(has_paper >= 1){
      has_paper--;
      has_match--; 
      uthread_cond_signal(s->t_smoker); 
    }
  }
  uthread_mutex_unlock(s->agent->mutex);
}

void* paper_watcher(void* av){
  struct Smoker* s = av; 
  uthread_mutex_lock(s->agent->mutex);
  while(1){
    
    uthread_cond_wait(s->agent->paper); 
    has_paper ++; 
    if(has_tobacco >= 1){
      has_tobacco--; 
      has_paper--; 
      uthread_cond_signal(s->m_smoker);
    }
    if(has_match >= 1){
      has_paper--;
      has_match--; 
      uthread_cond_signal(s->t_smoker); 
    }
  }
  uthread_mutex_unlock(s->agent->mutex);
}

void* tobacco_watcher(void* av){
  struct Smoker* s = av; 
  uthread_mutex_lock(s->agent->mutex);
  while(1){
    
    uthread_cond_wait(s->agent->tobacco); 
    has_tobacco ++; 
    if(has_match >= 1){
      has_tobacco--; 
      has_match--; 
      uthread_cond_signal(s->p_smoker);
    }
    if(has_paper >= 1){
      has_paper--;
      has_tobacco--; 
      uthread_cond_signal(s->m_smoker); 
    }
  }
  uthread_mutex_unlock(s->agent->mutex);
}


void* match_smoker(void* av){
  struct Smoker* s = av; 

  uthread_mutex_lock(s->agent->mutex);
  while(1){
    uthread_cond_wait(s->m_smoker);
    smoke_count[MATCH] ++ ; 
    uthread_cond_signal(s->agent->smoke);
  }
  uthread_mutex_unlock(s->agent->mutex);
}

void* paper_smoker(void* av){
  struct Smoker* s = av; 

  uthread_mutex_lock(s->agent->mutex);
  while(1){
    uthread_cond_wait(s->p_smoker);
    smoke_count[PAPER] ++ ; 
    uthread_cond_signal(s->agent->smoke);
  }
  uthread_mutex_unlock(s->agent->mutex);
}

void* tobacco_smoker(void* av){
  struct Smoker* s = av; 

  uthread_mutex_lock(s->agent->mutex);
  while(1){
    uthread_cond_wait(s->t_smoker);
    smoke_count[TOBACCO] ++ ; 
    uthread_cond_signal(s->agent->smoke);
  }
  uthread_mutex_unlock(s->agent->mutex);
}
/**
 * This is the agent procedure.  It is complete and you shouldn't change it in
 * any material way.  You can re-write it if you like, but be sure that all it does
 * is choose 2 random reasources, signal their condition variables, and then wait
 * wait for a smoker to smoke.
 */
void* agent (void* av) {
  struct Agent* a = av;
  static const int choices[]         = {MATCH|PAPER, MATCH|TOBACCO, PAPER|TOBACCO};
  static const int matching_smoker[] = {TOBACCO,     PAPER,         MATCH};
  
  uthread_mutex_lock (a->mutex);
    for (int i = 0; i < NUM_ITERATIONS; i++) {
      int r = random() % 3;
      signal_count [matching_smoker [r]] ++;
      int c = choices [r];
      if (c & MATCH) {
        VERBOSE_PRINT ("match available\n");
        uthread_cond_signal (a->match);
         
      }
      if (c & PAPER) {
        VERBOSE_PRINT ("paper available\n");
        uthread_cond_signal (a->paper);
        
      }
      if (c & TOBACCO) {
        VERBOSE_PRINT ("tobacco available\n");
        uthread_cond_signal (a->tobacco);
        
      }
      VERBOSE_PRINT ("agent is waiting for smoker to smoke\n");
      uthread_cond_wait (a->smoke);
    }
  uthread_mutex_unlock (a->mutex);
  return NULL;
}

int main (int argc, char** argv) {
  
     
  uthread_init (7);
  struct Agent*  a = createAgent();
  struct Smoker* s = createSmoker(a); 

  uthread_create(match_watcher,s);
  uthread_create(paper_watcher,s);
  uthread_create(tobacco_watcher,s);

  uthread_create(match_smoker,s); 
  uthread_create(tobacco_smoker,s); 
  uthread_create(paper_smoker,s); 

  uthread_join (uthread_create (agent, a), 0);
  assert (signal_count [MATCH]   == smoke_count [MATCH]);
  assert (signal_count [PAPER]   == smoke_count [PAPER]);
  assert (signal_count [TOBACCO] == smoke_count [TOBACCO]);
  assert (smoke_count [MATCH] + smoke_count [PAPER] + smoke_count [TOBACCO] == NUM_ITERATIONS);
  printf ("Smoke counts: %d matches, %d paper, %d tobacco\n",
          smoke_count [MATCH], smoke_count [PAPER], smoke_count [TOBACCO]);
}