//
// Created by arqui on 10/10/2023.
//

#include "utils.h"

int main(int argc, char **argv) {

    int err = 0;
    err = handle_argvs(argc, argv, Dijkstra);
    if(err != 0) {
        return err;
    }
    return 0;
}