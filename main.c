#define RELEASE 2
#define DEBUG 1

#define ARRAY_SIZE(x) ( sizeof(x) / sizeof((x)[0]) )

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <zconf.h>
#include "iLibX.h"

void cleanmenu(int note, char *notedata){
    system("clear");
    printf("==================\niPhone-rootFS-tool for macOS v%d\nDebug is %d\n==================\nLICENSE [DUFFYAPPIT[FREE]]\n==================\n", RELEASE, DEBUG);
    if (note !=0){
        printf("%s\n==================\n", notedata);
    }
}

int main(int argc, char *argv[]) {
    cleanmenu(1, "Initialising");
    system("rm -rf SENSETIVE");
    if (mkdir("SENSETIVE", 0777) == -1) {
        cleanmenu(0, "");
        printf("PRE-EXEC Check Failed -\> SENSETIVE Directory Already Exists And May Contain User Data.\nBackup & Remove SENSETIVE Directory Appropriately Before Executing...\n");
        exit(1);
    } else {
        cleanmenu(1, "Initialising");
        if(macos_run_ge("which iproxy")==0){
            printf("Starting Device Proxy\n");
            if(macos_run_ge("iproxy 7788 44 &")==0){
                printf("Started Device Proxy\n");
            }
        } else{
            printf("iProxy Not Found...Install Via Brew & Ensure PATH Entry\n");
            exit(1);
        }

        //SENSETIVE Directory Created
        //Check If AL Is In FirstLaunch State...
        cleanmenu(1, "Initialising Connected Device...");
        if (ios_fetch_access("127.0.0.1", "7788") == 0) {
            //Tunnel To Device Is Open, Send Companion
            if (DEBUG == 1) {
                printf("Mounting iDevice Disk...\n");
            }
            ios_run_ge("mount -o rw,union,update /"); //Does the disk need to be remounted?
            printf("Ready...\n");
            printf("Dumping Connected Device In Current State.\nThis may take some time...\n");
            system("resources/sshpass -p alpine ssh -o \"UserKnownHostsFile=/dev/null\" -o \"StrictHostKeyChecking=no\" root@127.0.0.1 -p7788 'tar zcf - / 2>/dev/null' | resources/pv > SENSETIVE/filesystem.tar");
            printf("Complete! filesystem.tar available in 'SENSETIVE/'\n");
        } else{
            printf("Stable Connection To Device Could Not Be Established.\n");
        }
        return 0;
    }
}
