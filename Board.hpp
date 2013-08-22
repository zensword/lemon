#ifndef BOARD_HPP
#define BOARD_HPP

/*
 * Board is an interface for arbitrary implementations of a chess board
 */

#include <string>
#include <cstdint>
using namespace std;

struct Board {
    virtual int32_t eval() = 0;
    virtual uint8_t get(uint8_t x, uint8_t y) = 0;
    virtual void set(uint8_t x, uint8_t y, uint8_t value) = 0;
    virtual string getFENCode() = 0;
    virtual void setFENCode(string fen) = 0;
    virtual void setStartingPosition() = 0;
    virtual void print() = 0;
};

#endif // BOARD_HPP
