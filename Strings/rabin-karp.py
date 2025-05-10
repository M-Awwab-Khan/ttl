def rabin_karp(text, pattern, p=31, mod=10**9+7):
    n, m = len(text), len(pattern)
    pattern_hash = 0
    text_hash = 0
    power = 1
    for i in range(m):
        pattern_hash = (pattern_hash + (ord(pattern[i]) - ord('a') + 1) * power) % mod
        text_hash = (text_hash + (ord(text[i]) - ord('a') + 1) * power) % mod
        if i != m - 1:
            power = (power * p) % mod
    result = []
    for i in range(n - m + 1):
        if pattern_hash == text_hash:
            if text[i:i+m] == pattern:
                result.append(i)
        if i + m < n:
            text_hash = (text_hash - (ord(text[i]) - ord('a') + 1) + mod) % mod
            text_hash = (text_hash * pow(p, mod - 2, mod)) % mod
            text_hash = (text_hash + (ord(text[i + m]) - ord('a') + 1) * power) % mod
    return result
