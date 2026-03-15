#!/bin/bash
# Test runner for keyhunt test files
# This script demonstrates all test scenarios with fixed ranges

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Get the directory where this script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR/.."

echo "=========================================="
echo "keyhunt Test Suite"
echo "=========================================="
echo ""

# Check if keyhunt binary exists
if [ ! -f "keyhunt" ]; then
    echo -e "${RED}Error: keyhunt binary not found${NC}"
    echo "Please build the project first with: make"
    exit 1
fi

# Function to run a test
run_test() {
    local test_name=$1
    local mode=$2
    local file=$3
    local extra_args=$4
    
    echo -e "${YELLOW}Running: $test_name${NC}"
    echo "  Mode: $mode, File: $file"
    echo "  Command: ./keyhunt -m $mode -f $file $extra_args"
    echo ""
    
    # Run with timeout and quiet mode to avoid output spam
    timeout 5 ./keyhunt -m $mode -f $file $extra_args -q 2>&1 | head -20 || true
    echo ""
    echo "----------------------------------------"
    echo ""
}

# Function to run BSGS test
run_bsgs_test() {
    local test_name=$1
    local file=$2
    local bit_range=$3
    
    echo -e "${YELLOW}Running: $test_name${NC}"
    echo "  Mode: bsgs, File: $file, Bit Range: $bit_range"
    echo "  Command: ./keyhunt -m bsgs -f $file -b $bit_range -R -S -q"
    echo ""
    
    timeout 10 ./keyhunt -m bsgs -f $file -b $bit_range -R -S -q 2>&1 | head -20 || true
    echo ""
    echo "----------------------------------------"
    echo ""
}

# Function to run vanity test
run_vanity_test() {
    local test_name=$1
    local target=$2
    
    echo -e "${YELLOW}Running: $test_name${NC}"
    echo "  Mode: vanity, Target: $target"
    echo "  Command: ./keyhunt -m vanity -v $target -b 256 -R -q"
    echo ""
    
    timeout 5 ./keyhunt -m vanity -v $target -b 256 -R -q 2>&1 | head -20 || true
    echo ""
    echo "----------------------------------------"
    echo ""
}

echo "=== BTC Legacy Address Tests ==="
echo ""

# Test 1: Single address (puzzle 64)
run_test "BTC Legacy - Puzzle 64" "address" "tests/64.txt" "-b 64"

# Test 2: Multiple addresses (puzzles 1-32)
run_test "BTC Legacy - Puzzles 1-32" "address" "tests/1to32.txt" "-r 1:FFFFFFFF"

# Test 3: Random mode with bit range
run_test "BTC Legacy - Random Mode" "address" "tests/66.txt" "-b 66 -R"

echo ""
echo "=== BTC Bech32 Address Tests ==="
echo ""

# Test 4: Bech32 address
run_test "BTC Bech32 - Puzzle 64" "address" "tests/64.bech32" "-b 64"

# Test 5: Multiple Bech32 addresses
run_test "BTC Bech32 - Multiple" "address" "tests/1to32.bech32" "-r 1:FFFFFFFF"

echo ""
echo "=== Ethereum Address Tests ==="
echo ""

# Test 6: ETH address
run_test "ETH - Puzzle 64" "address" "tests/64.eth" "-c eth -b 64"

# Test 7: Multiple ETH addresses
run_test "ETH - Multiple" "address" "tests/1to32.eth" "-c eth -r 1:FFFFFFFF"

echo ""
echo "=== RMD160 Hash Tests ==="
echo ""

# Test 8: RMD160 hash
run_test "RMD160 - Puzzle 64" "rmd160" "tests/64.rmd" "-b 64"

# Test 9: Multiple RMD160 hashes
run_test "RMD160 - Multiple" "rmd160" "tests/1to32.rmd" "-r 1:FFFFFFFF"

echo ""
echo "=== XPoint (Public Key) Tests ==="
echo ""

# Test 10: Public key
run_test "XPoint - Puzzle 64" "xpoint" "tests/64.pub" "-b 64"

# Test 11: Multiple public keys
run_test "XPoint - Multiple" "xpoint" "tests/1to32.pub" "-r 1:FFFFFFFF"

echo ""
echo "=== BSGS Mode Tests ==="
echo ""

# Test 12: BSGS with small range
run_bsgs_test "BSGS - Puzzle 64" "tests/64.pub" "64"

# Test 13: BSGS with medium range
run_bsgs_test "BSGS - Puzzle 125" "tests/125.pub" "125"

echo ""
echo "=== Vanity Search Tests ==="
echo ""

# Test 14: Vanity search
run_vanity_test "Vanity - Single Target" "1Good1"

echo ""
echo "=== Minikey Tests ==="
echo ""

# Test 15: Minikey
run_test "Minikey" "minikeys" "tests/minikeys.txt" ""

echo ""
echo "=== Unsolved Puzzles Tests ==="
echo ""

# Test 16: Unsolved puzzles
run_test "Unsolved Puzzles" "address" "tests/unsolvedpuzzles.txt" "-r 1:FFFFFFFF"

echo ""
echo "=========================================="
echo "Test Suite Complete"
echo "=========================================="
echo ""
echo "To run individual tests manually:"
echo "  ./keyhunt -m address -f tests/64.txt -b 64 -R"
echo "  ./keyhunt -m address -f tests/64.eth -c eth -b 64 -R"
echo "  ./keyhunt -m bsgs -f tests/125.pub -b 125 -R -S"
echo "  ./keyhunt -m vanity -v 1Good1 -b 256 -R"
echo ""
