typedef int (*Score)(void *);

typedef void *(*Neighbor)(void *, void *config);

typedef void (*Destroy)(void *);

typedef struct SimAn {
   void *state;
   Score score;
   Neighbor neighbor;
   void *neighborConfig;
   Destroy destroy;
} SimAn;

void SimAnAdvance(SimAn *simAn);
