#include <iostream>
#include <thread>
#include <vector>
void worker(int id) {
    std::cout << "Worker " << id << " processing tasks..." << std::endl;
}

int main() {
    std::vector<std::thread> workers;

    for (int i = 0; i < 4; i++) {
       workers.emplace_back(worker, i);
    }
    for (auto& t : workers) {
        t.join();
    }
    std::cout << "Pipeline completed successfully." << std::endl;

    return 0;
}
