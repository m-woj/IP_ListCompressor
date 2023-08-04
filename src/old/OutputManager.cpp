#include "OutputManager.hpp"


template<class RecordT>
void toFile(const std::vector<RecordT> &records, const OutputManagerConfig& config, std::fstream& fd) {
    if(!fd.is_open()) {
        fd.open(config.outputFilePath, std::ios_base::out);
    }

    if (fd.is_open()) {
        std::stringstream buffer;
        returnTo(buffer, records, config);
        fd << buffer.rdbuf();
        return;
    }

    std::cerr << "Cannot create an output file.\n";
}


template<class RecordT>
void send(const std::vector<RecordT> &records, const OutputManagerConfig& config, std::fstream& fd) {
    if(!config.outputFilePath.empty()) {
        toFile(records, config, fd);
    }
    else {
        toStandardOutput(records, config);
    }
}


template<class RecordT>
void toStandardOutput(const std::vector<RecordT> &records, const OutputManagerConfig& config) {
    returnTo(std::cout, records, config);
}


template<class RecordT>
void returnTo(std::ostream& out, const std::vector<RecordT>& records,
              const std::string& prefix, const std::string& suffix) {

    for (const auto& record : records) {
        out << prefix << record.toString() << suffix;
    }
}


OutputManager::OutputManager(const OutputManagerConfig &config) {
    set(config);
}


void OutputManager::send(const std::vector<Host>& hosts) {
    ::send(hosts, outputConfig, fd);
}


void OutputManager::send(const std::vector<Subnet>& subnets) {
    ::send(subnets, outputConfig, fd);
}


OutputManager::~OutputManager() {
    if (fd.is_open()) {
        fd.close();
    }
}


void OutputManager::set(OutputManagerConfig config) {
    outputConfig = std::move(config);
}


void returnTo(std::ostream &out, const std::vector<Host> &records, const OutputManagerConfig& config) {
    returnTo(out, records, config.hostPrefix, config.suffix);
}


void returnTo(std::ostream &out, const std::vector<Subnet> &records, const OutputManagerConfig& config) {
    returnTo(out, records, config.subnetPrefix, config.suffix);
}
