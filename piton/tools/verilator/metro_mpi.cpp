#include <iostream>
#include <mpi.h>
#include <vector>
#include <cstring>
#include "metro_mpi.h"


using namespace std;


void initialize(){
    MPI_Init(NULL, NULL);
    //cout << "initializing" << endl;
}

int getRank(){
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    return rank;
}

int getSize(){
    int size;
    MPI_Comm_rank(MPI_COMM_WORLD, &size);
    return size;
}

void finalize(){
    //cout << "[DPI CPP] Finalizing" << endl;
    MPI_Finalize();
}




// MPI finish functions
unsigned short mpi_receive_finish(){
    unsigned short message;
    int message_len = 1;
    //cout << "[DPI CPP] Block Receive finish from rank: " << origin << endl << std::flush;
    MPI_Bcast(&message, message_len, MPI_UNSIGNED_SHORT, 0, MPI_COMM_WORLD);
    /*if (short(message)) {
        cout << "[DPI CPP] finish received: " << std::hex << (short)message << endl << std::flush;
    }*/
    return message;
}

void mpi_send_finish(unsigned short message, int rank){
    int message_len = 1;
    /*if (message) {
        cout << "[DPI CPP] Sending finish " << std::hex << (int)message << " to All" << endl << std::flush;
    }*/
    MPI_Bcast(&message, message_len, MPI_UNSIGNED_SHORT, rank, MPI_COMM_WORLD);
}


void mpi_send_chan(void * chan, size_t len, int dest, int rank, int flag){
 // printf("send dest %u, rank=%u, flag=%u\n dat=0X",dest,rank,flag);
  //char * ch = (char *) chan;
  //for(int i=0; i<len; i++) printf("%X", ch[i]);
 // printf("\n");
  MPI_Send(chan, len,MPI_CHAR, dest, flag, MPI_COMM_WORLD);
}

void mpi_receive_chan(void * chan, size_t len, int origin, int flag){
    MPI_Status status;
    char * ch = (char *) chan;
    MPI_Recv(chan, len, MPI_CHAR, origin, flag, MPI_COMM_WORLD, &status);
    return;
    /*
    printf("MPI process received  from rank %d, with tag %d and error code %d.\n",                status.MPI_SOURCE,
                  status.MPI_TAG,
                  status.MPI_ERROR);
    printf("got origin%u, flag=%u\n dat=0X\n",origin,flag);

    for(int i=0; i<len; i++) printf("%X\n",  ch[i]);
    printf("\n");
    */
}


void print_static (MEM_STAT_t stat, uint64_t ticks){
    if (stat.mc_num==-1){
    std::cout<<"chipset, ";
    }else{
    std::cout << stat.mc_num << ", ";
}
    std::cout
     << stat.rank << ", "
     << stat.dest << ", "
     << stat.flit_in_num  << ", "
     << stat.flit_out_num  << ", "
     << ticks << ", "
     << ticks/500  << ", " << std::endl;
}


string get_mem_image_full_path (int argc, char **argv){
	vector<string> args(argv + 1, argv + argc);
	vector<string>::iterator tail_args = args.end();
	string path = "./";
	for(vector<string>::iterator it = args.begin(); it != args.end(); ++it) 
	{
	    if(it->find("+mem_image=") == 0) {
	       path=it->substr(strlen("+mem_image="));
	      // std::cout << "****************************" << path << "****************";
	    }   
	}
	return path;
}

