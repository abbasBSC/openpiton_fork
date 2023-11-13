#include <iostream>
#include <mpi.h>

using namespace std;

const int ALL_NOC      = 1;
const int PRINT_STAT   = 2;
const int PRINT_CACHE  = 3;
// Compilation flags parameters
const int PITON_X_TILES = X_TILES;
const int PITON_Y_TILES = Y_TILES;

typedef struct MEM_STAT {
  uint64_t flit_in_num;
  uint64_t flit_out_num;
  int      rank;
  int      mc_num;
  int      dest;
} MEM_STAT_t;

void initialize();
int getRank();
int getSize();
void finalize();
unsigned short mpi_receive_finish();
void mpi_send_finish(unsigned short message, int rank);
void mpi_send_chan(void * chan, size_t len, int dest, int rank, int flag);
void mpi_receive_chan(void * chan, size_t len, int origin, int flag);
void print_static (MEM_STAT_t stat, uint64_t ticks);
string get_mem_image_full_path (int, char **);
