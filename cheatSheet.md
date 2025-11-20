# Gray Code

```cpp
int gray(int n) {return n ^ (n >> 1);}
```

# Inverse Gray Code

```cpp
int invGray(int g) {
    int n = 0;
    while(g) {
        n ^= g;
        g >> 1;
    }
    return n;
}
```
