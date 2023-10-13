//
// Created by arqui on 10/10/2023.
//

#include "utils.h"

int main(int argc, char **argv) {

//    argc = 3;
//
//    char *argvtest[13] = {"ble","-f", "C:\\Anarch\\graph-theory-algorithms\\brock200-1.mtx"};
//
//    argv = argvtest;

    int err = 0;
    err = handle_argvs(argc, argv, Kruskal);
    if(err != 0) {
        return err;
    }
    return 0;
}