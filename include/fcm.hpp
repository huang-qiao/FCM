#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <thread>

namespace fcm {

class Runnable
{
public:
  inline virtual void run() = 0;
  inline virtual ~Runnable(){}
};

class Thread
{
public:
  enum State { NEW, READY, RUNNING, WAITING, TERMINATED };
private:
  std::thread thread_;
  std::string name_;
  Runnable* target_;
  State state_;
public:
  inline Thread() { create(NULL, "default"); }
  inline Thread(Runnable* r) { create(r, "default"); }
  inline Thread(Runnable* r, const std::string& name) { create(r, name); }
  inline virtual ~Thread() {
      if(thread_.joinable()) {
          thread_.join();
      }
      //delete(target_);
  }
  inline std::string getName() { return name_; }
  inline void setName(const std::string& name) { name_ = name; }
  inline bool isAlive() { return thread_.joinable(); }
  inline void join() {
    if(isAlive()) {
      thread_.join();
    }
  }
  inline void start() {
    if (isAlive()){//} || target_ == NULL) {
      return;
    }
    //thread_ = std::unique_ptr<std::thread>(new std::thread([&]{target_->run();}));
    thread_ = std::thread([&]{target_->run();});
  }
  // static functions
  inline static void sleep(double millis = 0.0) {
    std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(millis));
  }

private:
  inline void create(Runnable* r, const std::string& name) {
    //thread_ = NULL;
    target_ = r;
    name_ = name;
  }
};

} // namespace fcm
