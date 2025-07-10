import math


# === 1. Convert Number to Binary String ===
def to_binary(n, length=None):
    """
    Returns binary string of number n.
    Optionally pads to `length` bits.
    """
    s = bin(n)[2:]
    return s.zfill(length) if length else s


# === 2. Count Set Bits (1s in binary representation) ===
def count_set_bits(n):
    """
    Returns the number of set bits in n.
    Uses Brian Kernighan's Algorithm in O(log n).
    """
    count = 0
    while n:
        n &= n - 1
        count += 1
    return count


# === 3. Check if a number is power of 2 ===
def is_power_of_two(n):
    return n != 0 and (n & (n - 1)) == 0


# === 4. Get Least Significant Bit (LSB) ===
def get_lsb(n):
    return n & -n


# === 5. Get Most Significant Bit (MSB) position (0-indexed) ===
def get_msb_pos(n):
    """
    Returns the index (0-based) of the most significant bit.
    For n = 18 (10010), returns 4.
    """
    if n == 0:
        return -1
    return n.bit_length() - 1


# === 6. XOR Trick Examples ===
def xor_swap(a, b):
    """
    Swaps a and b using XOR (without temp variable).
    """
    a ^= b
    b ^= a
    a ^= b
    return a, b


def xor_upto(n):
    """
    Returns XOR from 1 to n (inclusive) in O(1)
    """
    # Pattern repeats every 4
    if n % 4 == 0:
        return n
    elif n % 4 == 1:
        return 1
    elif n % 4 == 2:
        return n + 1
    else:
        return 0


# === 7. Submask Enumeration ===
def get_all_submasks(mask):
    """
    Generates all submasks of a given bitmask `mask`.
    Useful for SOS DP, subset optimizations.
    """
    sub = mask
    while sub:
        yield sub
        sub = (sub - 1) & mask
    yield 0


# === SAMPLE DRIVER ===
if __name__ == "__main__":
    n = 42  # binary: 101010
    print(f"Binary of {n}:", to_binary(n))
    print(f"Set bits in {n}:", count_set_bits(n))
    print(f"Is {n} power of 2?:", is_power_of_two(n))
    print(f"LSB of {n}:", get_lsb(n))
    print(f"MSB position of {n}:", get_msb_pos(n))

    a, b = 5, 9
    print("XOR swap of 5 and 9:", xor_swap(a, b))

    print("XOR from 1 to 10:", xor_upto(10))

    mask = 0b1011
    print("All submasks of", to_binary(mask, 4) + ":")
    for sub in get_all_submasks(mask):
        print(to_binary(sub, 4))
