#include <iostream>
#include <string>
#include "stock_analyser.h"
#include <sstream>
#include <cstdlib>
#include <thread>
#include <asio.hpp>

using asio::ip::tcp;

void handleRequest(tcp::socket& socket) {
    try {
        asio::streambuf buffer;
        asio::read_until(socket, buffer, "\n");

        std::istream input(&buffer);
        std::string stockSymbol;
        std::getline(input, stockSymbol);

        StockAnalyser analyser;
        std::string result = analyser.analyzeStock(stockSymbol);

        asio::write(socket, asio::buffer(result + "\n"));
    } catch (std::exception& e) {
        std::cerr << "Error handling request: " << e.what() << std::endl;
    }
}

int main() {
    try {
        asio::io_context ioContext;
        tcp::acceptor acceptor(ioContext, tcp::endpoint(tcp::v4(), 8080));

        std::cout << "Server is running on http://localhost:8080" << std::endl;

        while (true) {
            tcp::socket socket(ioContext);
            acceptor.accept(socket);
            std::thread(handleRequest, std::move(socket)).detach();
        }
    } catch (std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }

    return 0;
}