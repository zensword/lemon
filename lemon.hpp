#ifndef BB_DEFINITIONS_HPP
#define BB_DEFINITIONS_HPP

#include <cstdlib>
using namespace std;


/*
 * Types
 */
typedef uint8_t U8; typedef int8_t I8;
typedef uint16_t U16; typedef int16_t I16;
typedef uint32_t U32; typedef int32_t I32;
typedef uint64_t U64; typedef int64_t I64;
typedef U8 Square;
//typedef I8 Offset;
#define C64(constantU64) constantU64##ULL
#define iBitMask(i) (1ULL << (i))


/*
 * Boad & Piece definitions
 */
#define BOARD_SIZE                  8
#define MASK_COLOR                  0x8
#define MASK_PIECE                  0x7
#define FLIP(x) (((x)+1)%2)

#define NONE 0

enum Color {
    WHITE, BLACK
};

enum PieceType {
    PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
};

enum OccupancyType {
    WPAWN, WKNIGHT, WBISHOP, WROOK, WQUEEN, WKING, EMPTY,
    BPAWN=8, BKNIGHT, BBISHOP, BROOK, BQUEEN, BKING
};


/*
 * Movement definitions
 */
/*
 *northwest    north   northeast
  NW             N            NE

          +7    +8    +9
              \  |  /
  W       -1 <-  0 -> +1       E
              /  |  \
          -9    -8    -7

  SW             S            SE
  southwest    south   southeast
 *
 */
#define _SHIFT_N(x) ((x) << 8)
#define _SHIFT_NN(x) ((x) << 16) //pawn double step
#define _SHIFT_S(x) ((x) >> 8)
#define _SHIFT_SS(x) ((x) >> 16) //pawn double step
#define _SHIFT_W(x) ((x) >> 1)
#define _SHIFT_E(x) ((x) << 1)
#define _SHIFT_NE(x) ((x) << 9)
#define _SHIFT_SE(x) ((x) >> 7)
#define _SHIFT_SW(x) ((x) >> 9)
#define _SHIFT_NW(x) ((x) << 7)
//knight's jumps
#define _SHIFT_NNE(x) ((x) << 17)
#define _SHIFT_NNW(x) ((x) << 15)
#define _SHIFT_SSE(x) ((x) >> 15)
#define _SHIFT_SSW(x) ((x) >> 17)
#define _SHIFT_WNW(x) ((x) << 6)
#define _SHIFT_WSW(x) ((x) >> 10)
#define _SHIFT_ENE(x) ((x) << 10)
#define _SHIFT_ESE(x) ((x) >> 6)

static const int PAWN_MOVE_DIRECTIONS[2] = {8, -8};
static const int PAWN_CAP_EAST_DIRECTIONS[2] = {9, -7};
static const int PAWN_CAP_WEST_DIRECTIONS[2] = {7, -9};


/*
 * Rank & file definitions
 */
#define FILE_A 0x0101010101010101ULL
#define FILE_B 0x0202020202020202ULL
#define FILE_C 0x0404040404040404ULL
#define FILE_D 0x0808080808080808ULL
#define FILE_E 0x1010101010101010ULL
#define FILE_F 0x2020202020202020ULL
#define FILE_G 0x4040404040404040ULL
#define FILE_H 0x8080808080808080ULL

#define RANK_1 0x00000000000000FFULL
#define RANK_2 0x000000000000FF00ULL
#define RANK_3 0x0000000000FF0000ULL
#define RANK_4 0x00000000FF000000ULL
#define RANK_5 0x000000FF00000000ULL
#define RANK_6 0x0000FF0000000000ULL
#define RANK_7 0x00FF000000000000ULL
#define RANK_8 0xFF00000000000000ULL

#define EP_RANKS 0x0000FF0000FF0000ULL


#define SQ(f,r) (((r) << 3) | (f))
#define FILE(sq) ((sq) &  7)
#define RANK(sq) ((sq) >> 3)


/*
 * Movegen target tables
 */
#define MAGIC_MULT_NO1 0x0080402010080400ULL

static const U64 KNIGHT_TARGET_BBS[64] = {
    0x20400ULL, 0x50800ULL, 0xA1100ULL, 0x142200ULL, 0x284400ULL, 0x508800ULL, 0xA01000ULL, 0x402000ULL,
    0x2040004ULL, 0x5080008ULL, 0xA110011ULL, 0x14220022ULL, 0x28440044ULL, 0x50880088ULL, 0xA0100010ULL, 0x40200020ULL,
    0x204000402ULL, 0x508000805ULL, 0xA1100110AULL, 0x1422002214ULL, 0x2844004428ULL, 0x5088008850ULL, 0xA0100010A0ULL, 0x4020002040ULL,
    0x20400040200ULL, 0x50800080500ULL, 0xA1100110A00ULL, 0x142200221400ULL, 0x284400442800ULL, 0x508800885000ULL, 0xA0100010A000ULL, 0x402000204000ULL,
    0x2040004020000ULL, 0x5080008050000ULL, 0xA1100110A0000ULL, 0x14220022140000ULL, 0x28440044280000ULL, 0x50880088500000ULL, 0xA0100010A00000ULL, 0x40200020400000ULL,
    0x204000402000000ULL, 0x508000805000000ULL, 0xA1100110A000000ULL, 0x1422002214000000ULL, 0x2844004428000000ULL, 0x5088008850000000ULL, 0xA0100010A0000000ULL, 0x4020002040000000ULL,
    0x400040200000000ULL, 0x800080500000000ULL, 0x1100110A00000000ULL, 0x2200221400000000ULL, 0x4400442800000000ULL, 0x8800885000000000ULL, 0x100010A000000000ULL, 0x2000204000000000ULL,
    0x4020000000000ULL, 0x8050000000000ULL, 0x110A0000000000ULL, 0x22140000000000ULL, 0x44280000000000ULL, 0x88500000000000ULL, 0x10A00000000000ULL, 0x20400000000000ULL
};

static const U64 KING_TARGET_BBS[64] = {
    0x302ULL, 0x705ULL, 0xE0AULL, 0x1C14ULL, 0x3828ULL, 0x7050ULL, 0xE0A0ULL, 0xC040ULL,
    0x30203ULL, 0x70507ULL, 0xE0A0EULL, 0x1C141CULL, 0x382838ULL, 0x705070ULL, 0xE0A0E0ULL, 0xC040C0ULL,
    0x3020300ULL, 0x7050700ULL, 0xE0A0E00ULL, 0x1C141C00ULL, 0x38283800ULL, 0x70507000ULL, 0xE0A0E000ULL, 0xC040C000ULL,
    0x302030000ULL, 0x705070000ULL, 0xE0A0E0000ULL, 0x1C141C0000ULL, 0x3828380000ULL, 0x7050700000ULL, 0xE0A0E00000ULL, 0xC040C00000ULL,
    0x30203000000ULL, 0x70507000000ULL, 0xE0A0E000000ULL, 0x1C141C000000ULL, 0x382838000000ULL, 0x705070000000ULL, 0xE0A0E0000000ULL, 0xC040C0000000ULL,
    0x3020300000000ULL, 0x7050700000000ULL, 0xE0A0E00000000ULL, 0x1C141C00000000ULL, 0x38283800000000ULL, 0x70507000000000ULL, 0xE0A0E000000000ULL, 0xC040C000000000ULL,
    0x302030000000000ULL, 0x705070000000000ULL, 0xE0A0E0000000000ULL, 0x1C141C0000000000ULL, 0x3828380000000000ULL, 0x7050700000000000ULL, 0xE0A0E00000000000ULL, 0xC040C00000000000ULL,
    0x203000000000000ULL, 0x507000000000000ULL, 0xA0E000000000000ULL, 0x141C000000000000ULL, 0x2838000000000000ULL, 0x5070000000000000ULL, 0xA0E0000000000000ULL, 0x40C0000000000000ULL
};


//TODO U8 instead? is casting expensive?
static const U8 RANK_ATTACK_BBS[8][64] = {
    {0xFE, 0x2, 0x6, 0x2, 0xE, 0x2, 0x6, 0x2, 0x1E, 0x2, 0x6, 0x2, 0xE, 0x2, 0x6, 0x2, 0x3E, 0x2, 0x6, 0x2, 0xE, 0x2, 0x6, 0x2, 0x1E, 0x2, 0x6, 0x2, 0xE, 0x2, 0x6, 0x2, 0x7E, 0x2, 0x6, 0x2, 0xE, 0x2, 0x6, 0x2, 0x1E, 0x2, 0x6, 0x2, 0xE, 0x2, 0x6, 0x2, 0x3E, 0x2, 0x6, 0x2, 0xE, 0x2, 0x6, 0x2, 0x1E, 0x2, 0x6, 0x2, 0xE, 0x2, 0x6, 0x2},
    {0xFD, 0xFD, 0x5, 0x5, 0xD, 0xD, 0x5, 0x5, 0x1D, 0x1D, 0x5, 0x5, 0xD, 0xD, 0x5, 0x5, 0x3D, 0x3D, 0x5, 0x5, 0xD, 0xD, 0x5, 0x5, 0x1D, 0x1D, 0x5, 0x5, 0xD, 0xD, 0x5, 0x5, 0x7D, 0x7D, 0x5, 0x5, 0xD, 0xD, 0x5, 0x5, 0x1D, 0x1D, 0x5, 0x5, 0xD, 0xD, 0x5, 0x5, 0x3D, 0x3D, 0x5, 0x5, 0xD, 0xD, 0x5, 0x5, 0x1D, 0x1D, 0x5, 0x5, 0xD, 0xD, 0x5, 0x5},
    {0xFB, 0xFA, 0xFB, 0xFA, 0xB, 0xA, 0xB, 0xA, 0x1B, 0x1A, 0x1B, 0x1A, 0xB, 0xA, 0xB, 0xA, 0x3B, 0x3A, 0x3B, 0x3A, 0xB, 0xA, 0xB, 0xA, 0x1B, 0x1A, 0x1B, 0x1A, 0xB, 0xA, 0xB, 0xA, 0x7B, 0x7A, 0x7B, 0x7A, 0xB, 0xA, 0xB, 0xA, 0x1B, 0x1A, 0x1B, 0x1A, 0xB, 0xA, 0xB, 0xA, 0x3B, 0x3A, 0x3B, 0x3A, 0xB, 0xA, 0xB, 0xA, 0x1B, 0x1A, 0x1B, 0x1A, 0xB, 0xA, 0xB, 0xA},
    {0xF7, 0xF6, 0xF4, 0xF4, 0xF7, 0xF6, 0xF4, 0xF4, 0x17, 0x16, 0x14, 0x14, 0x17, 0x16, 0x14, 0x14, 0x37, 0x36, 0x34, 0x34, 0x37, 0x36, 0x34, 0x34, 0x17, 0x16, 0x14, 0x14, 0x17, 0x16, 0x14, 0x14, 0x77, 0x76, 0x74, 0x74, 0x77, 0x76, 0x74, 0x74, 0x17, 0x16, 0x14, 0x14, 0x17, 0x16, 0x14, 0x14, 0x37, 0x36, 0x34, 0x34, 0x37, 0x36, 0x34, 0x34, 0x17, 0x16, 0x14, 0x14, 0x17, 0x16, 0x14, 0x14},
    {0xEF, 0xEE, 0xEC, 0xEC, 0xE8, 0xE8, 0xE8, 0xE8, 0xEF, 0xEE, 0xEC, 0xEC, 0xE8, 0xE8, 0xE8, 0xE8, 0x2F, 0x2E, 0x2C, 0x2C, 0x28, 0x28, 0x28, 0x28, 0x2F, 0x2E, 0x2C, 0x2C, 0x28, 0x28, 0x28, 0x28, 0x6F, 0x6E, 0x6C, 0x6C, 0x68, 0x68, 0x68, 0x68, 0x6F, 0x6E, 0x6C, 0x6C, 0x68, 0x68, 0x68, 0x68, 0x2F, 0x2E, 0x2C, 0x2C, 0x28, 0x28, 0x28, 0x28, 0x2F, 0x2E, 0x2C, 0x2C, 0x28, 0x28, 0x28, 0x28},
    {0xDF, 0xDE, 0xDC, 0xDC, 0xD8, 0xD8, 0xD8, 0xD8, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xDF, 0xDE, 0xDC, 0xDC, 0xD8, 0xD8, 0xD8, 0xD8, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0x5F, 0x5E, 0x5C, 0x5C, 0x58, 0x58, 0x58, 0x58, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x5F, 0x5E, 0x5C, 0x5C, 0x58, 0x58, 0x58, 0x58, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50},
    {0xBF, 0xBE, 0xBC, 0xBC, 0xB8, 0xB8, 0xB8, 0xB8, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xBF, 0xBE, 0xBC, 0xBC, 0xB8, 0xB8, 0xB8, 0xB8, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xB0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0},
    {0x7F, 0x7E, 0x7C, 0x7C, 0x78, 0x78, 0x78, 0x78, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40}
};

static const U64 FILE_ATTACK_BBS[8][64] = {
    {0x101010101010100, 0x1010101010100, 0x10101010100, 0x10101010100, 0x101010100, 0x101010100, 0x101010100, 0x101010100, 0x1010100, 0x1010100, 0x1010100, 0x1010100, 0x1010100, 0x1010100, 0x1010100, 0x1010100, 0x10100, 0x10100, 0x10100, 0x10100, 0x10100, 0x10100, 0x10100, 0x10100, 0x10100, 0x10100, 0x10100, 0x10100, 0x10100, 0x10100, 0x10100, 0x10100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100},
    {0x101010101010001, 0x1010101010001, 0x10101010001, 0x10101010001, 0x101010001, 0x101010001, 0x101010001, 0x101010001, 0x1010001, 0x1010001, 0x1010001, 0x1010001, 0x1010001, 0x1010001, 0x1010001, 0x1010001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x101010101010001, 0x1010101010001, 0x10101010001, 0x10101010001, 0x101010001, 0x101010001, 0x101010001, 0x101010001, 0x1010001, 0x1010001, 0x1010001, 0x1010001, 0x1010001, 0x1010001, 0x1010001, 0x1010001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001},
    {0x101010101000101, 0x1010101000101, 0x10101000101, 0x10101000101, 0x101000101, 0x101000101, 0x101000101, 0x101000101, 0x1000101, 0x1000101, 0x1000101, 0x1000101, 0x1000101, 0x1000101, 0x1000101, 0x1000101, 0x101010101000101, 0x1010101000101, 0x10101000101, 0x10101000101, 0x101000101, 0x101000101, 0x101000101, 0x101000101, 0x1000101, 0x1000101, 0x1000101, 0x1000101, 0x1000101, 0x1000101, 0x1000101, 0x1000101, 0x101010101000100, 0x1010101000100, 0x10101000100, 0x10101000100, 0x101000100, 0x101000100, 0x101000100, 0x101000100, 0x1000100, 0x1000100, 0x1000100, 0x1000100, 0x1000100, 0x1000100, 0x1000100, 0x1000100, 0x101010101000100, 0x1010101000100, 0x10101000100, 0x10101000100, 0x101000100, 0x101000100, 0x101000100, 0x101000100, 0x1000100, 0x1000100, 0x1000100, 0x1000100, 0x1000100, 0x1000100, 0x1000100, 0x1000100},
    {0x101010100010101, 0x1010100010101, 0x10100010101, 0x10100010101, 0x100010101, 0x100010101, 0x100010101, 0x100010101, 0x101010100010101, 0x1010100010101, 0x10100010101, 0x10100010101, 0x100010101, 0x100010101, 0x100010101, 0x100010101, 0x101010100010000, 0x1010100010000, 0x10100010000, 0x10100010000, 0x100010000, 0x100010000, 0x100010000, 0x100010000, 0x101010100010000, 0x1010100010000, 0x10100010000, 0x10100010000, 0x100010000, 0x100010000, 0x100010000, 0x100010000, 0x101010100010100, 0x1010100010100, 0x10100010100, 0x10100010100, 0x100010100, 0x100010100, 0x100010100, 0x100010100, 0x101010100010100, 0x1010100010100, 0x10100010100, 0x10100010100, 0x100010100, 0x100010100, 0x100010100, 0x100010100, 0x101010100010000, 0x1010100010000, 0x10100010000, 0x10100010000, 0x100010000, 0x100010000, 0x100010000, 0x100010000, 0x101010100010000, 0x1010100010000, 0x10100010000, 0x10100010000, 0x100010000, 0x100010000, 0x100010000, 0x100010000},
    {0x101010001010101, 0x1010001010101, 0x10001010101, 0x10001010101, 0x101010001010101, 0x1010001010101, 0x10001010101, 0x10001010101, 0x101010001000000, 0x1010001000000, 0x10001000000, 0x10001000000, 0x101010001000000, 0x1010001000000, 0x10001000000, 0x10001000000, 0x101010001010000, 0x1010001010000, 0x10001010000, 0x10001010000, 0x101010001010000, 0x1010001010000, 0x10001010000, 0x10001010000, 0x101010001000000, 0x1010001000000, 0x10001000000, 0x10001000000, 0x101010001000000, 0x1010001000000, 0x10001000000, 0x10001000000, 0x101010001010100, 0x1010001010100, 0x10001010100, 0x10001010100, 0x101010001010100, 0x1010001010100, 0x10001010100, 0x10001010100, 0x101010001000000, 0x1010001000000, 0x10001000000, 0x10001000000, 0x101010001000000, 0x1010001000000, 0x10001000000, 0x10001000000, 0x101010001010000, 0x1010001010000, 0x10001010000, 0x10001010000, 0x101010001010000, 0x1010001010000, 0x10001010000, 0x10001010000, 0x101010001000000, 0x1010001000000, 0x10001000000, 0x10001000000, 0x101010001000000, 0x1010001000000, 0x10001000000, 0x10001000000},
    {0x101000101010101, 0x1000101010101, 0x101000101010101, 0x1000101010101, 0x101000100000000, 0x1000100000000, 0x101000100000000, 0x1000100000000, 0x101000101000000, 0x1000101000000, 0x101000101000000, 0x1000101000000, 0x101000100000000, 0x1000100000000, 0x101000100000000, 0x1000100000000, 0x101000101010000, 0x1000101010000, 0x101000101010000, 0x1000101010000, 0x101000100000000, 0x1000100000000, 0x101000100000000, 0x1000100000000, 0x101000101000000, 0x1000101000000, 0x101000101000000, 0x1000101000000, 0x101000100000000, 0x1000100000000, 0x101000100000000, 0x1000100000000, 0x101000101010100, 0x1000101010100, 0x101000101010100, 0x1000101010100, 0x101000100000000, 0x1000100000000, 0x101000100000000, 0x1000100000000, 0x101000101000000, 0x1000101000000, 0x101000101000000, 0x1000101000000, 0x101000100000000, 0x1000100000000, 0x101000100000000, 0x1000100000000, 0x101000101010000, 0x1000101010000, 0x101000101010000, 0x1000101010000, 0x101000100000000, 0x1000100000000, 0x101000100000000, 0x1000100000000, 0x101000101000000, 0x1000101000000, 0x101000101000000, 0x1000101000000, 0x101000100000000, 0x1000100000000, 0x101000100000000, 0x1000100000000},
    {0x100010101010101, 0x100010101010101, 0x100010000000000, 0x100010000000000, 0x100010100000000, 0x100010100000000, 0x100010000000000, 0x100010000000000, 0x100010101000000, 0x100010101000000, 0x100010000000000, 0x100010000000000, 0x100010100000000, 0x100010100000000, 0x100010000000000, 0x100010000000000, 0x100010101010000, 0x100010101010000, 0x100010000000000, 0x100010000000000, 0x100010100000000, 0x100010100000000, 0x100010000000000, 0x100010000000000, 0x100010101000000, 0x100010101000000, 0x100010000000000, 0x100010000000000, 0x100010100000000, 0x100010100000000, 0x100010000000000, 0x100010000000000, 0x100010101010100, 0x100010101010100, 0x100010000000000, 0x100010000000000, 0x100010100000000, 0x100010100000000, 0x100010000000000, 0x100010000000000, 0x100010101000000, 0x100010101000000, 0x100010000000000, 0x100010000000000, 0x100010100000000, 0x100010100000000, 0x100010000000000, 0x100010000000000, 0x100010101010000, 0x100010101010000, 0x100010000000000, 0x100010000000000, 0x100010100000000, 0x100010100000000, 0x100010000000000, 0x100010000000000, 0x100010101000000, 0x100010101000000, 0x100010000000000, 0x100010000000000, 0x100010100000000, 0x100010100000000, 0x100010000000000, 0x100010000000000},
    {0x1010101010101, 0x1000000000000, 0x1010000000000, 0x1000000000000, 0x1010100000000, 0x1000000000000, 0x1010000000000, 0x1000000000000, 0x1010101000000, 0x1000000000000, 0x1010000000000, 0x1000000000000, 0x1010100000000, 0x1000000000000, 0x1010000000000, 0x1000000000000, 0x1010101010000, 0x1000000000000, 0x1010000000000, 0x1000000000000, 0x1010100000000, 0x1000000000000, 0x1010000000000, 0x1000000000000, 0x1010101000000, 0x1000000000000, 0x1010000000000, 0x1000000000000, 0x1010100000000, 0x1000000000000, 0x1010000000000, 0x1000000000000, 0x1010101010100, 0x1000000000000, 0x1010000000000, 0x1000000000000, 0x1010100000000, 0x1000000000000, 0x1010000000000, 0x1000000000000, 0x1010101000000, 0x1000000000000, 0x1010000000000, 0x1000000000000, 0x1010100000000, 0x1000000000000, 0x1010000000000, 0x1000000000000, 0x1010101010000, 0x1000000000000, 0x1010000000000, 0x1000000000000, 0x1010100000000, 0x1000000000000, 0x1010000000000, 0x1000000000000, 0x1010101000000, 0x1000000000000, 0x1010000000000, 0x1000000000000, 0x1010100000000, 0x1000000000000, 0x1010000000000, 0x1000000000000}
};







/*
 * Bitscan & popcount
 */
const U32 index64[64] = {
    0, 47,  1, 56, 48, 27,  2, 60,
   57, 49, 41, 37, 28, 16,  3, 61,
   54, 58, 35, 52, 50, 42, 21, 44,
   38, 32, 29, 23, 17, 11,  4, 62,
   46, 55, 26, 59, 40, 36, 15, 53,
   34, 51, 20, 43, 31, 22, 10, 45,
   25, 39, 14, 33, 19, 30,  9, 24,
   13, 18,  8, 12,  7,  6,  5, 63
};
#define DEBRUIJN64 0x03f79d71b4cb0a89ULL

/**
 * bitScanForward
 * @author Kim Walisch (2012)
 * @param bb bitboard to scan
 * @precondition bb != 0
 * @return index (0..63) of least significant one bit
 */
U32 bitscanfwd(U64 bb) {
   return index64[((bb ^ (bb-1)) * DEBRUIJN64) >> 58];
}




#endif // BB_DEFINITIONS_HPP
