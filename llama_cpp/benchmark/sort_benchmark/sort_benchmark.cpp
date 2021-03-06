
#include "benchmark/benchmark.h"

#include "Sort/BruteForceSort.h"

static void StdSortInt(benchmark::State& state) {
    std::vector<int> a = {5, 4, 3, 2, 1};
    while (state.KeepRunning()) {
        std::sort(a.begin(), a.end());
    }
}

static void StdSortString(benchmark::State& state) {
    std::vector<std::string> a = {"5", "4", "3", "2", "1"};
    while (state.KeepRunning()) {
        std::sort(a.begin(), a.end());
    }
}

static void BFSortInt(benchmark::State& state) {
    llama::BruteForceSort<int> bfSort = llama::BruteForceSort<int>();
    std::vector<int> a = {5, 4, 3, 2, 1};
    while (state.KeepRunning()) {
        bfSort.sort(&a);
    }
}

static void BFSortString(benchmark::State& state) {
    llama::BruteForceSort<std::string> bfSort = llama::BruteForceSort<std::string>();
    std::vector<std::string> a = {"5", "4", "3", "2", "1"};
    while (state.KeepRunning()) {
        bfSort.sort(&a);
    }
}

static void BFSortDouble(benchmark::State& state) {
    llama::BruteForceSort<double> bfSort = llama::BruteForceSort<double>();
    std::vector<double> a = {5.0, 4.0, 3.0, 2.0, 1.0};
    while (state.KeepRunning()) {
        bfSort.sort(&a);
    }
}

class CustomisedClass {
public:
    CustomisedClass() {}
    CustomisedClass(int input) {
        this->input = input*10;
    }

    int getInput() const {
        return input;
    }

    operator std::string() const
    {
        return "CustomisedClass: "+std::to_string(getInput());
    }

private:
    int input;
};
namespace llama {
    template<>
    double SortObject<CustomisedClass>::getValue() const {
        return (double) (obj.getInput());
    }
}

static void BFSortClass(benchmark::State& state) {
    llama::BruteForceSort<CustomisedClass> bfSort = llama::BruteForceSort<CustomisedClass>();
    std::vector<CustomisedClass> a = {CustomisedClass(5), CustomisedClass(4),
                          CustomisedClass(3), CustomisedClass(2), CustomisedClass(1)};
    while (state.KeepRunning()) {
        bfSort.sort(&a);
    }
}

BENCHMARK(StdSortInt);
BENCHMARK(StdSortString);
BENCHMARK(BFSortInt);
BENCHMARK(BFSortString);
BENCHMARK(BFSortDouble);
BENCHMARK(BFSortClass);

BENCHMARK_MAIN();
