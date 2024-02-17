#include <iostream>
#include <random>
#include <cstdlib>


/// @brief Departures before arrivals single server queue.
class SingleServerQueue {
    const static unsigned int MAX_LENGTH = INT16_MAX;

public:
    SingleServerQueue(double l, double u)
    : gen(rd()), arrival(l), departure(u) {

        this->l = l;
        this->u = u;

        size = 0;
    }

    u_int16_t getSize() { return size; }    

    void step() {
        if(size > 0 && departure(gen)) {
            size--;
        }

        if(size < MAX_LENGTH && arrival(gen)) {
            size++;
        }
    }        

private:

    // queue parameters
    double l, u;

    std::random_device rd;
    std::mt19937 gen;

    std::bernoulli_distribution arrival;
    std::bernoulli_distribution departure;

    u_int16_t size;
};

void simulate(double l, double u, unsigned int depth) {

    SingleServerQueue ssq(l, u);
    u_int16_t sizes[depth];

    for(int i = 0; i < depth; ++i) {
        ssq.step();
        sizes[i] = ssq.getSize();
    }

    unsigned long sum = 0;
    for(int i = 0; i < depth; ++i) {
        sum += sizes[i];
    }

    double averageSize = (double) sum / depth;

    // littles law
    // average size = average delay * average arrival rate
    // average delay = average size / average arrival rate
    double averageDelay = averageSize / l;

    std::cout << averageDelay << std::endl;

}

int main(int argc, char *argv[]) {

    if(argc != 4) {
        std::cerr << "usage: " << argv[0] << " [l] [u] [depth]" << std::endl;
        return 1;
    }

    double l = atof(argv[1]);
    double u = atof(argv[2]);
    unsigned int depth = atoi(argv[3]);

    simulate(l, u, depth);

    return 0;
}