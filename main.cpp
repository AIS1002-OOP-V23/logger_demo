#include <iostream>
#include <string>
#include <fstream>

class logger {

public:
    virtual void log(const std::string& str) = 0;
};

class console_logger: public logger {

public:
    void log(const std::string &str) override {
        std::cout << str << std::endl;
    }
};

class file_logger: public logger {
public:
    file_logger(const std::string& path): of(path) {}

    void log(const std::string &str) override {
        of << str << std::endl;
    }

private:
    std::ofstream of;
};

class simulation {

public:

    void set_logger(std::unique_ptr<logger> logger) {
        logger_ = std::move(logger);
    }

    void simulate() {
        for (int i = 0; i < 10; i++) {
            if (logger_) {
                logger_->log(std::to_string(i));
            }
        }
    }

private:
    std::unique_ptr<logger> logger_;

};

int main() {
//    std::unique_ptr<logger> logger = std::make_unique<console_logger>();
//    logger->log("Hello");
//
//    auto fileLogger = std::make_unique<file_logger>("hello.txt");
//    fileLogger->log("Hello");

    simulation sim;
    sim.set_logger(std::make_unique<file_logger>("hello.txt"));
//    sim.set_logger(std::make_unique<console_logger>());
    sim.simulate();

    return 0;
}
