#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "maxqueue.h"

using namespace std;

int main(int argc, char *argv[]){

    // Run the current exercise
    MaxQueue queue;

    for(int i = 1; i < argc; i++){
        if (argv[i][0] == '.'){
            cout << queue.front() << endl;
            queue.pop();
        } else {
            queue.push(atoi(argv[i]));
        }
    }

	//cout << queue.elements_.front() << endl;
	//cout << queue.elements_.back() << endl;


    return 0;
}
