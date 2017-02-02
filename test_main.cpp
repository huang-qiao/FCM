#include "include/fcm.hpp"

#include <iostream>

using namespace fcm;

class TestRunnable : public Runnable
{
private:
  void run() override {
    for (int i=0; i<500; i++) {
      std::cout << "TestRunnable" << std::endl;
    }
  }
};

int main(int argc, char* argv[])
{
    std::cout << "hello world" << std::endl;
    TestRunnable test1;
    Thread t1(&test1, "test1");
    t1.start();
    t1.join();
    return 0;
}
