#include "stock_analyser.h"
#include <sstream>
#include <cstdlib>

std::string StockAnalyser::analyzeStock(const std::string& stockSymbol) {
    std::ostringstream result;
    result << "Stock: " << stockSymbol << "\n";
    result << "Current Price: $" << (100 + (rand() % 100)) << "\n";
    result << "Recommendation: " << (rand() % 2 ? "Buy" : "Sell") << "\n";
    return result.str();
}