# Detect architecture
UNAME_M := $(shell uname -m)

# Compiler flags
CXXFLAGS = -Wall -Wextra -Wno-deprecated-copy -Ofast -ftree-vectorize -flto
CFLAGS = -Wall -Wextra -Ofast -ftree-vectorize

# Architecture-specific flags
ifeq ($(UNAME_M),x86_64)
  ARCH_FLAGS = -m64 -march=native -mtune=native -mssse3
  SSE_OBJS = hash/ripemd160_sse.o hash/sha256_sse.o
  SSE_SRC = hash/ripemd160_sse.cpp hash/sha256_sse.cpp
else ifeq ($(UNAME_M),aarch64)
  ARCH_FLAGS = -march=native
  SSE_OBJS = hash/ripemd160_scalar.o hash/sha256_scalar.o
  SSE_SRC = hash/ripemd160_scalar.cpp hash/sha256_scalar.cpp
else
  # Default to portable scalar code
  ARCH_FLAGS = -march=native
  SSE_OBJS = hash/ripemd160_scalar.o hash/sha256_scalar.o
  SSE_SRC = hash/ripemd160_scalar.cpp hash/sha256_scalar.cpp
endif

default: $(SSE_OBJS)
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c oldbloom/bloom.cpp -o oldbloom.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c bloom/bloom.cpp -o bloom.o
	gcc $(ARCH_FLAGS) $(CFLAGS) -c base58/base58.c -o base58.o
	gcc $(ARCH_FLAGS) $(CFLAGS) -c rmd160/rmd160.c -o rmd160.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c sha3/sha3.c -o sha3.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c sha3/keccak.c -o keccak.o
	gcc $(ARCH_FLAGS) $(CFLAGS) -c xxhash/xxhash.c -o xxhash.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c util.c -o util.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c secp256k1/Int.cpp -o Int.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c secp256k1/Point.cpp -o Point.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c secp256k1/SECP256K1.cpp -o SECP256K1.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c secp256k1/IntMod.cpp -o IntMod.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -flto -c secp256k1/Random.cpp -o Random.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -flto -c secp256k1/IntGroup.cpp -o IntGroup.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -o hash/ripemd160.o -ftree-vectorize -flto -c hash/ripemd160.cpp
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -o hash/sha256.o -ftree-vectorize -flto -c hash/sha256.cpp
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -ftree-vectorize -o keyhunt keyhunt.cpp base58.o rmd160.o hash/ripemd160.o $(SSE_OBJS) hash/sha256.o bloom.o oldbloom.o xxhash.o util.o Int.o  Point.o SECP256K1.o  IntMod.o  Random.o IntGroup.o sha3.o keccak.o  -lm -lpthread
	rm -r *.o
clean:
	rm keyhunt
legacy: $(SSE_OBJS)
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c oldbloom/bloom.cpp -o oldbloom.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c bloom/bloom.cpp -o bloom.o
	gcc $(ARCH_FLAGS) $(CFLAGS) -Wno-unused-result -c base58/base58.c -o base58.o
	gcc $(ARCH_FLAGS) $(CFLAGS) -c xxhash/xxhash.c -o xxhash.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c util.c -o util.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c sha3/sha3.c -o sha3.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c sha3/keccak.c -o keccak.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c hashing.c -o hashing.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c gmp256k1/Int.cpp -o Int.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c gmp256k1/Point.cpp -o Point.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c gmp256k1/GMP256K1.cpp -o GMP256K1.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c gmp256k1/IntMod.cpp -o IntMod.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -flto -c gmp256k1/Random.cpp -o Random.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -flto -c gmp256k1/IntGroup.cpp -o IntGroup.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -o keyhunt keyhunt_legacy.cpp base58.o bloom.o oldbloom.o xxhash.o util.o Int.o  Point.o GMP256K1.o  IntMod.o  IntGroup.o Random.o hashing.o sha3.o keccak.o -lm -lpthread -lcrypto -lgmp	
	rm -r *.o
bsgsd: $(SSE_OBJS)
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c oldbloom/bloom.cpp -o oldbloom.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c bloom/bloom.cpp -o bloom.o
	gcc $(ARCH_FLAGS) $(CFLAGS) -c base58/base58.c -o base58.o
	gcc $(ARCH_FLAGS) $(CFLAGS) -c rmd160/rmd160.c -o rmd160.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c sha3/sha3.c -o sha3.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c sha3/keccak.c -o keccak.o
	gcc $(ARCH_FLAGS) $(CFLAGS) -c xxhash/xxhash.c -o xxhash.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c util.c -o util.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c secp256k1/Int.cpp -o Int.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c secp256k1/Point.cpp -o Point.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c secp256k1/SECP256K1.cpp -o SECP256K1.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -c secp256k1/IntMod.cpp -o IntMod.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -flto -c secp256k1/Random.cpp -o Random.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -flto -c secp256k1/IntGroup.cpp -o IntGroup.o
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -o hash/ripemd160.o -ftree-vectorize -flto -c hash/ripemd160.cpp
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -o hash/sha256.o -ftree-vectorize -flto -c hash/sha256.cpp
	g++ $(ARCH_FLAGS) $(CXXFLAGS) -ftree-vectorize -o bsgsd bsgsd.cpp base58.o rmd160.o hash/ripemd160.o $(SSE_OBJS) hash/sha256.o bloom.o oldbloom.o xxhash.o util.o Int.o  Point.o SECP256K1.o  IntMod.o  Random.o IntGroup.o sha3.o keccak.o  -lm -lpthread
	rm -r *.o
