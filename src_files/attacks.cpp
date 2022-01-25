/****************************************************************************************************
 *                                                                                                  *
 *                                     Koivisto UCI Chess engine                                    *
 *                                   by. Kim Kahre and Finn Eggers                                  *
 *                                                                                                  *
 *                 Koivisto is free software: you can redistribute it and/or modify                 *
 *               it under the terms of the GNU General Public License as published by               *
 *                 the Free Software Foundation, either version 3 of the License, or                *
 *                                (at your option) any later version.                               *
 *                    Koivisto is distributed in the hope that it will be useful,                   *
 *                  but WITHOUT ANY WARRANTY; without even the implied warranty of                  *
 *                   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                  *
 *                           GNU General Public License for more details.                           *
 *                 You should have received a copy of the GNU General Public License                *
 *                 along with Koivisto.  If not, see <http://www.gnu.org/licenses/>.                *
 *                                                                                                  *
 ****************************************************************************************************/

//
// Created by Luecx on 25.01.2022.
//

#include "attacks.h"

using namespace bb;

constexpr bb::U64 attacks::bishopMasks[] {
    0x0040201008040200L, 0x0000402010080400L, 0x0000004020100a00L, 0x0000000040221400L,
    0x0000000002442800L, 0x0000000204085000L, 0x0000020408102000L, 0x0002040810204000L,
    0x0020100804020000L, 0x0040201008040000L, 0x00004020100a0000L, 0x0000004022140000L,
    0x0000000244280000L, 0x0000020408500000L, 0x0002040810200000L, 0x0004081020400000L,
    0x0010080402000200L, 0x0020100804000400L, 0x004020100a000a00L, 0x0000402214001400L,
    0x0000024428002800L, 0x0002040850005000L, 0x0004081020002000L, 0x0008102040004000L,
    0x0008040200020400L, 0x0010080400040800L, 0x0020100a000a1000L, 0x0040221400142200L,
    0x0002442800284400L, 0x0004085000500800L, 0x0008102000201000L, 0x0010204000402000L,
    0x0004020002040800L, 0x0008040004081000L, 0x00100a000a102000L, 0x0022140014224000L,
    0x0044280028440200L, 0x0008500050080400L, 0x0010200020100800L, 0x0020400040201000L,
    0x0002000204081000L, 0x0004000408102000L, 0x000a000a10204000L, 0x0014001422400000L,
    0x0028002844020000L, 0x0050005008040200L, 0x0020002010080400L, 0x0040004020100800L,
    0x0000020408102000L, 0x0000040810204000L, 0x00000a1020400000L, 0x0000142240000000L,
    0x0000284402000000L, 0x0000500804020000L, 0x0000201008040200L, 0x0000402010080400L,
    0x0002040810204000L, 0x0004081020400000L, 0x000a102040000000L, 0x0014224000000000L,
    0x0028440200000000L, 0x0050080402000000L, 0x0020100804020000L, 0x0040201008040200L};

constexpr bb::U64 attacks::rookMasks[] {
    0x000101010101017eL, 0x000202020202027cL, 0x000404040404047aL, 0x0008080808080876L,
    0x001010101010106eL, 0x002020202020205eL, 0x004040404040403eL, 0x008080808080807eL,
    0x0001010101017e00L, 0x0002020202027c00L, 0x0004040404047a00L, 0x0008080808087600L,
    0x0010101010106e00L, 0x0020202020205e00L, 0x0040404040403e00L, 0x0080808080807e00L,
    0x00010101017e0100L, 0x00020202027c0200L, 0x00040404047a0400L, 0x0008080808760800L,
    0x00101010106e1000L, 0x00202020205e2000L, 0x00404040403e4000L, 0x00808080807e8000L,
    0x000101017e010100L, 0x000202027c020200L, 0x000404047a040400L, 0x0008080876080800L,
    0x001010106e101000L, 0x002020205e202000L, 0x004040403e404000L, 0x008080807e808000L,
    0x0001017e01010100L, 0x0002027c02020200L, 0x0004047a04040400L, 0x0008087608080800L,
    0x0010106e10101000L, 0x0020205e20202000L, 0x0040403e40404000L, 0x0080807e80808000L,
    0x00017e0101010100L, 0x00027c0202020200L, 0x00047a0404040400L, 0x0008760808080800L,
    0x00106e1010101000L, 0x00205e2020202000L, 0x00403e4040404000L, 0x00807e8080808000L,
    0x007e010101010100L, 0x007c020202020200L, 0x007a040404040400L, 0x0076080808080800L,
    0x006e101010101000L, 0x005e202020202000L, 0x003e404040404000L, 0x007e808080808000L,
    0x7e01010101010100L, 0x7c02020202020200L, 0x7a04040404040400L, 0x7608080808080800L,
    0x6e10101010101000L, 0x5e20202020202000L, 0x3e40404040404000L, 0x7e80808080808000L};

constexpr int attacks::bishopShifts[] {
    58, 59, 59, 59, 59, 59, 59, 58,
    59, 59, 59, 59, 59, 59, 59, 59,
    59, 59, 57, 57, 57, 57, 59, 59,
    59, 59, 57, 55, 55, 57, 59, 59,
    59, 59, 57, 55, 55, 57, 59, 59,
    59, 59, 57, 57, 57, 57, 59, 59,
    59, 59, 59, 59, 59, 59, 59, 59,
    58, 59, 59, 59, 59, 59, 59, 58};

constexpr int attacks::rookShifts[] {
    52, 53, 53, 53, 53, 53, 53, 52,
    53, 54, 54, 54, 54, 54, 54, 53,
    53, 54, 54, 54, 54, 54, 54, 53,
    53, 54, 54, 54, 54, 54, 54, 53,
    53, 54, 54, 54, 54, 54, 54, 53,
    53, 54, 54, 54, 54, 54, 54, 53,
    53, 54, 54, 54, 54, 54, 54, 53,
    52, 53, 53, 53, 53, 53, 53, 52};

constexpr bb::U64 attacks::bishopMagics[] {
    0x0002020202020200L, 0x0002020202020000L, 0x0004010202000000L, 0x0004040080000000L,
    0x0001104000000000L, 0x0000821040000000L, 0x0000410410400000L, 0x0000104104104000L,
    0x0000040404040400L, 0x0000020202020200L, 0x0000040102020000L, 0x0000040400800000L,
    0x0000011040000000L, 0x0000008210400000L, 0x0000004104104000L, 0x0000002082082000L,
    0x0004000808080800L, 0x0002000404040400L, 0x0001000202020200L, 0x0000800802004000L,
    0x0000800400A00000L, 0x0000200100884000L, 0x0000400082082000L, 0x0000200041041000L,
    0x0002080010101000L, 0x0001040008080800L, 0x0000208004010400L, 0x0000404004010200L,
    0x0000840000802000L, 0x0000404002011000L, 0x0000808001041000L, 0x0000404000820800L,
    0x0001041000202000L, 0x0000820800101000L, 0x0000104400080800L, 0x0000020080080080L,
    0x0000404040040100L, 0x0000808100020100L, 0x0001010100020800L, 0x0000808080010400L,
    0x0000820820004000L, 0x0000410410002000L, 0x0000082088001000L, 0x0000002011000800L,
    0x0000080100400400L, 0x0001010101000200L, 0x0002020202000400L, 0x0001010101000200L,
    0x0000410410400000L, 0x0000208208200000L, 0x0000002084100000L, 0x0000000020880000L,
    0x0000001002020000L, 0x0000040408020000L, 0x0004040404040000L, 0x0002020202020000L,
    0x0000104104104000L, 0x0000002082082000L, 0x0000000020841000L, 0x0000000000208800L,
    0x0000000010020200L, 0x0000000404080200L, 0x0000040404040400L, 0x0002020202020200L
    
};
constexpr bb::U64 attacks::rookMagics[] {
    0x0080001020400080L, 0x0040001000200040L, 0x0080081000200080L, 0x0080040800100080L,
    0x0080020400080080L, 0x0080010200040080L, 0x0080008001000200L, 0x0080002040800100L,
    0x0000800020400080L, 0x0000400020005000L, 0x0000801000200080L, 0x0000800800100080L,
    0x0000800400080080L, 0x0000800200040080L, 0x0000800100020080L, 0x0000800040800100L,
    0x0000208000400080L, 0x0000404000201000L, 0x0000808010002000L, 0x0000808008001000L,
    0x0000808004000800L, 0x0000808002000400L, 0x0000010100020004L, 0x0000020000408104L,
    0x0000208080004000L, 0x0000200040005000L, 0x0000100080200080L, 0x0000080080100080L,
    0x0000040080080080L, 0x0000020080040080L, 0x0000010080800200L, 0x0000800080004100L,
    0x0000204000800080L, 0x0000200040401000L, 0x0000100080802000L, 0x0000080080801000L,
    0x0000040080800800L, 0x0000020080800400L, 0x0000020001010004L, 0x0000800040800100L,
    0x0000204000808000L, 0x0000200040008080L, 0x0000100020008080L, 0x0000080010008080L,
    0x0000040008008080L, 0x0000020004008080L, 0x0000010002008080L, 0x0000004081020004L,
    0x0000204000800080L, 0x0000200040008080L, 0x0000100020008080L, 0x0000080010008080L,
    0x0000040008008080L, 0x0000020004008080L, 0x0000800100020080L, 0x0000800041000080L,
    0x00FFFCDDFCED714AL, 0x007FFCDDFCED714AL, 0x003FFFCDFFD88096L, 0x0000040810002101L,
    0x0001000204080011L, 0x0001000204000801L, 0x0001000082000401L, 0x0001FFFAABFAD1A2L};

constexpr bb::U64 attacks::KING_ATTACKS[] {
    0x0000000000000302L, 0x0000000000000705L, 0x0000000000000e0aL, 0x0000000000001c14L,
    0x0000000000003828L, 0x0000000000007050L, 0x000000000000e0a0L, 0x000000000000c040L,
    0x0000000000030203L, 0x0000000000070507L, 0x00000000000e0a0eL, 0x00000000001c141cL,
    0x0000000000382838L, 0x0000000000705070L, 0x0000000000e0a0e0L, 0x0000000000c040c0L,
    0x0000000003020300L, 0x0000000007050700L, 0x000000000e0a0e00L, 0x000000001c141c00L,
    0x0000000038283800L, 0x0000000070507000L, 0x00000000e0a0e000L, 0x00000000c040c000L,
    0x0000000302030000L, 0x0000000705070000L, 0x0000000e0a0e0000L, 0x0000001c141c0000L,
    0x0000003828380000L, 0x0000007050700000L, 0x000000e0a0e00000L, 0x000000c040c00000L,
    0x0000030203000000L, 0x0000070507000000L, 0x00000e0a0e000000L, 0x00001c141c000000L,
    0x0000382838000000L, 0x0000705070000000L, 0x0000e0a0e0000000L, 0x0000c040c0000000L,
    0x0003020300000000L, 0x0007050700000000L, 0x000e0a0e00000000L, 0x001c141c00000000L,
    0x0038283800000000L, 0x0070507000000000L, 0x00e0a0e000000000L, 0x00c040c000000000L,
    0x0302030000000000L, 0x0705070000000000L, 0x0e0a0e0000000000L, 0x1c141c0000000000L,
    0x3828380000000000L, 0x7050700000000000L, 0xe0a0e00000000000L, 0xc040c00000000000L,
    0x0203000000000000L, 0x0507000000000000L, 0x0a0e000000000000L, 0x141c000000000000L,
    0x2838000000000000L, 0x5070000000000000L, 0xa0e0000000000000L, 0x40c0000000000000L};
constexpr bb::U64 attacks::KNIGHT_ATTACKS[] {
    0x0000000000020400L, 0x0000000000050800L, 0x00000000000a1100L, 0x0000000000142200L,
    0x0000000000284400L, 0x0000000000508800L, 0x0000000000a01000L, 0x0000000000402000L,
    0x0000000002040004L, 0x0000000005080008L, 0x000000000a110011L, 0x0000000014220022L,
    0x0000000028440044L, 0x0000000050880088L, 0x00000000a0100010L, 0x0000000040200020L,
    0x0000000204000402L, 0x0000000508000805L, 0x0000000a1100110aL, 0x0000001422002214L,
    0x0000002844004428L, 0x0000005088008850L, 0x000000a0100010a0L, 0x0000004020002040L,
    0x0000020400040200L, 0x0000050800080500L, 0x00000a1100110a00L, 0x0000142200221400L,
    0x0000284400442800L, 0x0000508800885000L, 0x0000a0100010a000L, 0x0000402000204000L,
    0x0002040004020000L, 0x0005080008050000L, 0x000a1100110a0000L, 0x0014220022140000L,
    0x0028440044280000L, 0x0050880088500000L, 0x00a0100010a00000L, 0x0040200020400000L,
    0x0204000402000000L, 0x0508000805000000L, 0x0a1100110a000000L, 0x1422002214000000L,
    0x2844004428000000L, 0x5088008850000000L, 0xa0100010a0000000L, 0x4020002040000000L,
    0x0400040200000000L, 0x0800080500000000L, 0x1100110a00000000L, 0x2200221400000000L,
    0x4400442800000000L, 0x8800885000000000L, 0x100010a000000000L, 0x2000204000000000L,
    0x0004020000000000L, 0x0008050000000000L, 0x00110a0000000000L, 0x0022140000000000L,
    0x0044280000000000L, 0x0088500000000000L, 0x0010a00000000000L, 0x0020400000000000L};

bb::U64 *attacks::ROOK_ATTACKS  [bb::N_SQUARES]{};
bb::U64 *attacks::BISHOP_ATTACKS[bb::N_SQUARES]{};

U64 populateMask(U64 mask, U64 index) {
    
    U64    res = 0;
    Square i   = 0;
    
    while (mask) {
        Square bit = bitscanForward(mask);
        
        if (getBit(index, i)) {
            setBit(res, bit);
        }
        
        mask = lsbReset(mask);
        i++;
    }
    
    return res;
}

void attacks::init() {
    for (int n = 0; n < 64; n++) {
        auto rook_shift = rookShifts[n];
        auto bish_shift = bishopShifts[n];
        
        U64  rook_entries   = (ONE << (64 - rook_shift));
        U64  bish_entries   = (ONE << (64 - bish_shift));
        
        ROOK_ATTACKS    [n] = new U64[rook_entries];
        BISHOP_ATTACKS  [n] = new U64[bish_entries];
        
        for (int i = 0; i < rook_entries; i++) {
            U64 rel_occ            = populateMask(rookMasks[n], i);
            int index              = static_cast<int>((rel_occ * rookMagics[n]) >> rookShifts[n]);
            ROOK_ATTACKS[n][index] = generateRookAttacks(n, rel_occ);
        }
        
        for (int i = 0; i < bish_entries; i++) {
            U64 rel_occ              = populateMask(bishopMasks[n], i);
            int index                = static_cast<int>((rel_occ * bishopMagics[n]) >> bishopShifts[n]);
            BISHOP_ATTACKS[n][index] = generateBishopAttacks(n, rel_occ);
        }
    }
}

void attacks::cleanUp() {
    for (int n = 0; n < 64; n++) {
        delete[] ROOK_ATTACKS  [n];
        delete[] BISHOP_ATTACKS[n];
        
        ROOK_ATTACKS  [n] = nullptr;
        BISHOP_ATTACKS[n] = nullptr;
    }
}

bb::U64 attacks::generateSlidingAttacks(Square sq, Direction direction, U64 occ) {
    
    U64              res {0};
    
    static const U64 topBottom = RANK_1_BB | RANK_8_BB;
    static const U64 leftRight = FILE_A_BB | FILE_H_BB;
    
    if ((1ULL << sq) & RANK_1_BB && direction < -2) {
        return res;
    }
    if ((1ULL << sq) & RANK_8_BB && direction > 2) {
        return res;
    }
    if ((1ULL << sq) & FILE_A_BB
        && (direction == WEST || direction == SOUTH_WEST || direction == NORTH_WEST)) {
        return res;
    }
    if ((1ULL << sq) & FILE_H_BB
        && (direction == EAST || direction == SOUTH_EAST || direction == NORTH_EAST)) {
        return res;
    }
    
    while (true) {
        sq += direction;
        
        U64 currentSq = (U64) 1 << sq;
        
        res |= currentSq;
        
        if (occ & currentSq) {
            return res;
        }
        if (abs(direction) == 8) {
            if (currentSq & topBottom) {
                return res;
            }
        } else if (abs(direction) == 1) {
            if (currentSq & leftRight) {
                return res;
            }
        } else {
            if (currentSq & OUTER_SQUARES_BB) {
                return res;
            }
        }
    }
}

bb::U64 attacks::generateRookAttacks(bb::Square sq, bb::U64 occupied) {
    return   generateSlidingAttacks(sq, NORTH, occupied)
           | generateSlidingAttacks(sq, EAST, occupied)
           | generateSlidingAttacks(sq, WEST, occupied)
           | generateSlidingAttacks(sq, SOUTH, occupied);
}

bb::U64 attacks::generateBishopAttacks(bb::Square sq, bb::U64 occupied) {
    return   generateSlidingAttacks(sq, NORTH_WEST, occupied)
           | generateSlidingAttacks(sq, NORTH_EAST, occupied)
           | generateSlidingAttacks(sq, SOUTH_WEST, occupied)
           | generateSlidingAttacks(sq, SOUTH_EAST, occupied);
}


