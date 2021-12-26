#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PROCESS_NAME 512
#define ESUCCESS        0
#define ENOPROC         1
#define ENONAME         2

/*
 * Measures the current (and peak) resident and virtual memories
 * usage of your linux C process, in kB
 */
void getMemory(int iPid,
    int* currRealMem, int* peakRealMem,
    int* currVirtMem, int* peakVirtMem) {

    // stores each word in status file
    char buffer[1024] = "";

    // linux file contains this-process info
    //FILE* file = fopen("/proc/self/status", "r");
    char* name = (char *) calloc(MAX_PROCESS_NAME, sizeof(char));
    sprintf(name, "/proc/%d/status", iPid);
    FILE* file = fopen(name, "r");

    // read the entire file
    while (fscanf(file, " %1023s", buffer) == 1) {

        if (strcmp(buffer, "VmRSS:") == 0) {
            fscanf(file, " %d", currRealMem);
        }
        if (strcmp(buffer, "VmHWM:") == 0) {
            fscanf(file, " %d", peakRealMem);
        }
        if (strcmp(buffer, "VmSize:") == 0) {
            fscanf(file, " %d", currVirtMem);
        }
        if (strcmp(buffer, "VmPeak:") == 0) {
            fscanf(file, " %d", peakVirtMem);
        }
    }
    fclose(file);
}



int main(int argc, char **argv)
{
    int iPid = 0;

    if (argc < 1) {
        printf("Usage: getpname [pid]\n");
        return 0;
    }


    iPid = atoi(argv[1]);


    printf("===================== %d %d ==============\n", iPid, getpid());



	int currRealMem=0;
	int peakRealMem=0;
	int currVirtMem=0;
	int peakVirtMem=0;
	while(1){
		getMemory(iPid, &currRealMem, &peakRealMem, &currVirtMem, &peakVirtMem);
		printf("======= %d %d %d %d ============\n",
			currRealMem, peakRealMem, currVirtMem, peakVirtMem);
		sleep(1);
	}
}

