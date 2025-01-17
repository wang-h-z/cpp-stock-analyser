#include <iostream>
#include <string>
#include "stock_analyser.h"
#include <sstream>
#include <cstdlib>
#include <thread>
#include <asio.hpp>

using asio::ip::tcp;

void handleRequest(std::shared_ptr<tcp::socket> socket) {
    try {
        asio::streambuf buffer;
        asio::read_until(*socket, buffer, "\r\n\r\n"); // Read until end of HTTP headers

        // Skip HTTP headers
        std::istream input(&buffer);
        std::string line;
        while (std::getline(input, line) && line != "\r") {}

        // Read the remaining body (stock symbol)
        std::string stockSymbol;
        std::getline(input, stockSymbol);

        // Analyze the stock
        StockAnalyser analyser;
        std::string result = analyser.analyzeStock(stockSymbol);

        // Construct HTTP response with CORS headers
        std::ostringstream response;
        response << "HTTP/1.1 200 OK\r\n";
        response << "Content-Type: text/plain\r\n";
        response << "Access-Control-Allow-Origin: *\r\n"; // Allow all origins
        response << "Content-Length: " << result.size() + 1 << "\r\n\r\n";
        response << result << "\n";

        asio::write(*socket, asio::buffer(response.str()));
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
            auto socket = std::make_shared<tcp::socket>(ioContext);
            acceptor.accept(*socket);
            std::thread([socket]() { handleRequest(socket); }).detach();
        }
    } catch (std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }

    return 0;
}
