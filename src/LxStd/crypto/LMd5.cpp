#include "LMd5.h"

using namespace std;

/* Constants for MD5Transform routine. */
//向左位移数
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

////常量ti unsigned int(abs(sin(i+1))*(2pow32))
//const unsigned int k[] = {
//	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
//	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8,
//	0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193,
//	0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51,
//	0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
//	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905,
//	0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681,
//	0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60,
//	0xbebfbc70, 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
//	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244,
//	0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
//	0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314,
//	0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
//};

const byte CLMd5::PADDING[64] = { 0x80 };
const char CLMd5::HEX[16] = {
    '0', '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', 'a', 'b',
    'c', 'd', 'e', 'f'
};


/* F, G, H and I are basic MD5 functions.
定义4个MD5非线性函数F、G、H、I
*/
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits.
//右移的时候，高位一定要补零，而不是补充符号位
*/
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
Rotation is separate from addition to prevent recomputation.
*/
#define FF(a, b, c, d, x, s, ac) { \
    (a) += F((b), (c), (d)) + (x)+ac; \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}
#define GG(a, b, c, d, x, s, ac) { \
    (a) += G((b), (c), (d)) + (x)+ac; \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}
#define HH(a, b, c, d, x, s, ac) { \
    (a) += H((b), (c), (d)) + (x)+ac; \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}
#define II(a, b, c, d, x, s, ac) { \
    (a) += I((b), (c), (d)) + (x)+ac; \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}





/* Default construct. */
CLMd5::CLMd5() {
    reset();
}

/* Construct a MD5 object with a input buffer. */
CLMd5::CLMd5(const void* input, size_t length) {
    reset();
    update(input, length);
}

/* Construct a MD5 object with a string. */
CLMd5::CLMd5(const string& str) {
    reset();
    update(str);
}

/* Construct a MD5 object with a file. */
CLMd5::CLMd5(ifstream& in) {
    reset();
    update(in);
}

/* Return the message-digest */
const byte* CLMd5::digest() {

    if (!_finished) {
        _finished = true;
        final();
    }
    return _digest;
}

/* Reset the calculate state */
void CLMd5::reset() {

    _finished = false;
    /* reset number of bits. */
    _count[0] = _count[1] = 0;
    /* Load magic initialization constants. */
    _state[0] = 0x67452301;
    _state[1] = 0xefcdab89;
    _state[2] = 0x98badcfe;
    _state[3] = 0x10325476;
}

/* Updating the context with a input buffer. */
void CLMd5::update(const void* input, size_t length) {
    update((const byte*)input, length);
}

/* Updating the context with a string. */
void CLMd5::update(const string& str) {
    update((const byte*)str.c_str(), str.length());
}

/* Updating the context with a file. 加密文件*/
void CLMd5::update(ifstream& in) {

    if (!in) {
        return;
    }

    std::streamsize length;
    char buffer[BUFFER_SIZE];
    while (!in.eof()) {
        in.read(buffer, BUFFER_SIZE);
        length = in.gcount();
        if (length > 0) {
            update(buffer, length);
        }
    }
    in.close();
}

/* MD5 block update operation. Continues an MD5 message-digest
operation, processing another message block, and updating the
context.
*/
void CLMd5::update(const byte* input, size_t length) {

    uint32 i, index, partLen;

    _finished = false;

    /* Compute number of bytes mod 64 */
    index = (uint32)((_count[0] >> 3) & 0x3f);

    /* update number of bits */
    if ((_count[0] += ((uint32)length << 3)) < ((uint32)length << 3))
    {
        ++_count[1];
    }
    _count[1] += ((uint32)length >> 29);

    partLen = 64 - index;

    /* transform as many times as possible. */
    if (length >= partLen) {

        memcpy(&_buffer[index], input, partLen);
        transform(_buffer);

        for (i = partLen; i + 63 < length; i += 64) {
            transform(&input[i]);
        }
        index = 0;

    }
    else {
        i = 0;
    }

    /* Buffer remaining input */
    memcpy(&_buffer[index], &input[i], length - i);
}

/* MD5 finalization. Ends an MD5 message-_digest operation, writing the
the message _digest and zeroizing the context.
*/
void CLMd5::final() {

    byte bits[8];
    uint32 oldState[4];
    uint32 oldCount[2];
    uint32 index;	// 原始信息的mod64余字节数
    uint32 padLen; // 需要补的长度字节数

    /* Save current state and count. */
    memcpy(oldState, _state, 16);
    memcpy(oldCount, _count, 8);

    /* Save number of bits */
    encode(_count, bits, 8);

    /* Pad out to 56 mod 64. 补位*/
    // 信息比特位长度mod 512 = 448,至少补1位，而最多可能补512位,字节就是bytes≡56（mode64)
    // 下面是用位运算求余数(只适合于除数是2的N次方的情况),X >> & (2^N - 1),
    //eg: 求11除以8的余数,11的二进制是1011，,把1011右移3位，该过程会把1011的低3位011给移走，
    //事实上，这个被移走的011就是11除以8的余数！但是，我们该如何把这个011给保存下来呢，用 & (2^N - 1)
    index = (uint32)((_count[0] >> 3) & 0x3f); // _count[0]表示有多少位，除以8得到字节数
    padLen = (index < 56) ? (56 - index) : (120 - index);
    update(PADDING, padLen);

    /* Append length (before padding) */
    update(bits, 8);

    /* Store state in digest */
    encode(_state, _digest, 16);

    /* Restore current state and count. */
    memcpy(_state, oldState, 16);
    memcpy(_count, oldCount, 8);
}

/* MD5 basic transformation. Transforms _state based on block. */
void CLMd5::transform(const byte block[64])
{
    uint32 a = _state[0];
    uint32 b = _state[1];
    uint32 c = _state[2];
    uint32 d = _state[3];
    uint32 x[16];

    decode(block, x, 64);

    /* Round 1 */
    FF(a, b, c, d, x[0], S11, 0xd76aa478); /* 1 */
    FF(d, a, b, c, x[1], S12, 0xe8c7b756); /* 2 */
    FF(c, d, a, b, x[2], S13, 0x242070db); /* 3 */
    FF(b, c, d, a, x[3], S14, 0xc1bdceee); /* 4 */
    FF(a, b, c, d, x[4], S11, 0xf57c0faf); /* 5 */
    FF(d, a, b, c, x[5], S12, 0x4787c62a); /* 6 */
    FF(c, d, a, b, x[6], S13, 0xa8304613); /* 7 */
    FF(b, c, d, a, x[7], S14, 0xfd469501); /* 8 */
    FF(a, b, c, d, x[8], S11, 0x698098d8); /* 9 */
    FF(d, a, b, c, x[9], S12, 0x8b44f7af); /* 10 */
    FF(c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
    FF(b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
    FF(a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
    FF(d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
    FF(c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
    FF(b, c, d, a, x[15], S14, 0x49b40821); /* 16 */

    /* Round 2 */
    GG(a, b, c, d, x[1], S21, 0xf61e2562); /* 17 */
    GG(d, a, b, c, x[6], S22, 0xc040b340); /* 18 */
    GG(c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
    GG(b, c, d, a, x[0], S24, 0xe9b6c7aa); /* 20 */
    GG(a, b, c, d, x[5], S21, 0xd62f105d); /* 21 */
    GG(d, a, b, c, x[10], S22, 0x2441453); /* 22 */
    GG(c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
    GG(b, c, d, a, x[4], S24, 0xe7d3fbc8); /* 24 */
    GG(a, b, c, d, x[9], S21, 0x21e1cde6); /* 25 */
    GG(d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
    GG(c, d, a, b, x[3], S23, 0xf4d50d87); /* 27 */
    GG(b, c, d, a, x[8], S24, 0x455a14ed); /* 28 */
    GG(a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
    GG(d, a, b, c, x[2], S22, 0xfcefa3f8); /* 30 */
    GG(c, d, a, b, x[7], S23, 0x676f02d9); /* 31 */
    GG(b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */

    /* Round 3 */
    HH(a, b, c, d, x[5], S31, 0xfffa3942); /* 33 */
    HH(d, a, b, c, x[8], S32, 0x8771f681); /* 34 */
    HH(c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
    HH(b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
    HH(a, b, c, d, x[1], S31, 0xa4beea44); /* 37 */
    HH(d, a, b, c, x[4], S32, 0x4bdecfa9); /* 38 */
    HH(c, d, a, b, x[7], S33, 0xf6bb4b60); /* 39 */
    HH(b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
    HH(a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
    HH(d, a, b, c, x[0], S32, 0xeaa127fa); /* 42 */
    HH(c, d, a, b, x[3], S33, 0xd4ef3085); /* 43 */
    HH(b, c, d, a, x[6], S34, 0x4881d05); /* 44 */
    HH(a, b, c, d, x[9], S31, 0xd9d4d039); /* 45 */
    HH(d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
    HH(c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
    HH(b, c, d, a, x[2], S34, 0xc4ac5665); /* 48 */

    /* Round 4 */
    II(a, b, c, d, x[0], S41, 0xf4292244); /* 49 */
    II(d, a, b, c, x[7], S42, 0x432aff97); /* 50 */
    II(c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
    II(b, c, d, a, x[5], S44, 0xfc93a039); /* 52 */
    II(a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
    II(d, a, b, c, x[3], S42, 0x8f0ccc92); /* 54 */
    II(c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
    II(b, c, d, a, x[1], S44, 0x85845dd1); /* 56 */
    II(a, b, c, d, x[8], S41, 0x6fa87e4f); /* 57 */
    II(d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
    II(c, d, a, b, x[6], S43, 0xa3014314); /* 59 */
    II(b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
    II(a, b, c, d, x[4], S41, 0xf7537e82); /* 61 */
    II(d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
    II(c, d, a, b, x[2], S43, 0x2ad7d2bb); /* 63 */
    II(b, c, d, a, x[9], S44, 0xeb86d391); /* 64 */

    _state[0] += a;
    _state[1] += b;
    _state[2] += c;
    _state[3] += d;
}

/* Encodes input (ulong) into output (byte). Assumes length is
a multiple of 4. ulong转换byte表示，length必须是4的整数倍 ok
*/
void CLMd5::encode(const uint32* input, byte* output, size_t length) {

    for (size_t i = 0, j = 0; j < length; ++i, j += 4)
    {
        output[j] = (byte)(input[i] & 0xff);
        output[j + 1] = (byte)((input[i] >> 8) & 0xff);
        output[j + 2] = (byte)((input[i] >> 16) & 0xff);
        output[j + 3] = (byte)((input[i] >> 24) & 0xff);
    }
}

/* Decodes input (byte) into output (ulong). Assumes length is
a multiple of 4. byte转换ulong表示，length必须是4的整数倍 ok
*/
void CLMd5::decode(const byte* input, uint32* output, size_t length)
{
    for (size_t i = 0, j = 0; j < length; ++i, j += 4)
    {
        output[i] = ((uint32)input[j])
            | (((uint32)input[j + 1]) << 8)
            | (((uint32)input[j + 2]) << 16)
            | (((uint32)input[j + 3]) << 24);
    }
}

/* Convert byte array to hex string. 转换字节数组成16进制字符串表示 ok*/
string CLMd5::bytesToHexString(const byte* input, size_t length)
{
    string str;
    str.reserve(length << 1);	// 左移表示乘以2
    for (size_t i = 0; i < length; ++i)
    {
        // 一个字节(最大255)有2个16进制位
        int t = input[i];
        int a = t / 16;
        int b = t % 16;
        str.append(1, HEX[a]);
        str.append(1, HEX[b]);
    }
    return str;
}

/* Convert digest to string value */
string CLMd5::toString() {
    return bytesToHexString(digest(), 16);
}
