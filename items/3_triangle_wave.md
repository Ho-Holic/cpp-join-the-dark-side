```cpp
#include <x86intrin.h>

static int N = 20000;

static void TriangleMod(benchmark::State& state) {
  for (auto _ : state) {
    uint8_t x = 0;
    for (int i = 0; i < N; ++i) {

      auto r = std::abs(((x + 2) % 4) - 2);
      //if (r < 0) r *= -1;    
      benchmark::DoNotOptimize(r);
      x = x + 1;
    }      
  }
}
// Register the function as a benchmark
BENCHMARK(TriangleMod);

static void TriangleCache(benchmark::State& state) {

  static  uint8_t period[4] = {0, 1, 2, 1 };

  for (auto _ : state) {
    uint8_t x = 0;
    
    for (int i = 0; i < N; ++i) {      
      uint8_t r = period[x];
      x = (x + 1) % 4;      
      benchmark::DoNotOptimize(r);
    }    
  }
}
BENCHMARK(TriangleCache);


static void TriangleToggle(benchmark::State& state) {


  for (auto _ : state) {
    uint8_t x = 0;
    uint8_t up = 1;
    
    for (int i = 0; i < N; ++i) {      
      if (x >= 2) up = -1;
      else if (x <= 0) up = 1;
      x = x + up;
      benchmark::DoNotOptimize(x);
    }    
  }
}
BENCHMARK(TriangleToggle);

static void TriangleConditional(benchmark::State& state) {

  for (auto _ : state) {
    uint8_t x = 0;
    uint8_t dir = 1;

    for (int i = 0; i < N; ++i) {

      if (x == 2) dir = -1;
      if (x == 0) dir = 1;      
      x = x + dir * 1;
      benchmark::DoNotOptimize(x);
    }    
  }
}
BENCHMARK(TriangleConditional);

static void TriangleBits(benchmark::State& state) {


  for (auto _ : state) {
    
    uint8_t a = 0b00000001;
    uint8_t b = 0b00010001;

    for (int i = 0; i < N; ++i) {
      a = a ^ 0b00000001;
      b = __rorb(b, 1);      
      uint8_t x = a | (b & 0b00000010);
      benchmark::DoNotOptimize(x);
    }    
  }
}
BENCHMARK(TriangleBits);

static void TriangleVariableCache(benchmark::State& state) {


  for (auto _ : state) {
    
    uint8_t x = 0b01100100;

    for (int i = 0; i < N; ++i) {
                  
      uint8_t r = (x & 0b00000011);                  
      benchmark::DoNotOptimize(r);
      x = __rorb(x, 2);      
    }    
  }
}
BENCHMARK(TriangleVariableCache);

static void TriangleVariableCache64(benchmark::State& state) {


  for (auto _ : state) {
    
    unsigned long long x = 0b0000000000000001'0000000000000010'0000000000000001'0000000000000000;

    for (int i = 0; i < N; ++i) {
                  
      unsigned long long r = (x & 0b0000000000000000'0000000000000000'0000000000000000'1111111111111111);                   
      benchmark::DoNotOptimize(r);
      x = __rorq(x, 16);       
    }    
  }
}
BENCHMARK(TriangleVariableCache64);

static void TriangleVariableCache32(benchmark::State& state) {


  for (auto _ : state) {
    
    uint32_t x = 0b00000001'00000010'00000001'00000000;

    for (int i = 0; i < N; ++i) {
                  
      uint32_t r = (x & 0b00000000'00000000'00000000'11111111);                   
      benchmark::DoNotOptimize(r);
      x = __rord(x, 8);      
    }    
  }
}
BENCHMARK(TriangleVariableCache32);

static void TriangleVariableCache16(benchmark::State& state) {


  for (auto _ : state) {
    
    uint16_t x = 0b0001'0010'0001'0000;

    for (int i = 0; i < N; ++i) {
                  
      uint16_t r = (x & 0b0000'0000'0000'1111);                   
      benchmark::DoNotOptimize(r);
      x = __rorw(x, 4);      
    }    
  }
}
BENCHMARK(TriangleVariableCache16);
```
