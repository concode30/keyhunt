# Test files for keyhunt
# This Makefile generates test files with fixed ranges

.PHONY: all clean btc eth legacy bech32

all: btc eth legacy bech32

btc: legacy bech32

legacy: 1to32.txt 64.txt 66.txt 120.txt 125.txt 130.txt unsolvedpuzzles.txt

eth: 1to32.eth 64.eth 66.eth 120.eth 125.eth 130.eth

bech32: 1to32.bech32 64.bech32 66.bech32 120.bech32 125.bech32 130.bech32

# Generate test files with known private keys
# Format: BTC legacy addresses (Base58Check encoded)

1to32.txt:
	@echo "1BgGZ9tcN4rm9KBzDn7KprQz87SZ26SAMH" > $@
	@echo "1CUNEBjYrCn2y1SdiUMohaKUi4wpP326Lb" >> $@
	@echo "19ZewH8Kk1PDbSNdJ97FP4EiCjTRaZMZQA" >> $@
	@echo "1EhqbyUMvvs7BfL8goY6qcPbD6YKfPqb7e" >> $@
	@echo "1E6NuFjCi27W5zoXg8TRdcSRq84zJeBW3k" >> $@
	@echo "1PitScNLyp2HCygzadCh7FveTnfmpPbfp8" >> $@
	@echo "1McVt1vMtCC7yn5b9wgX1833yCcLXzueeC" >> $@
	@echo "1M92tSqNmQLYw33fuBvjmeadirh1ysMBxK" >> $@
	@echo "1CQFwcjw1dwhtkVWBttNLDtqL7ivBonGPV" >> $@
	@echo "1LeBZP5QCwwgXRtmVUvTVrraqPUokyLHqe" >> $@
	@echo "1PgQVLmst3Z314JrQn5TNiys8Hc38TcXJu" >> $@
	@echo "1DBaumZxUkM4qMQRt2LVWyFJq5kDtSZQot" >> $@
	@echo "1Pie8JkxBT6MGPz9Nvi3fsPkr2D8q3GBc1" >> $@
	@echo "1ErZWg5cFCe4Vw5BzgfzB74VNLaXEiEkhk" >> $@
	@echo "1QCbW9HWnwQWiQqVo5exhAnmfqKRrCRsvW" >> $@
	@echo "1BDyrQ6WoF8VN3g9SAS1iKZcPzFfnDVieY" >> $@
	@echo "1HduPEXZRdG26SUT5Yk83mLkPyjnZuJ7Bm" >> $@
	@echo "1GnNTmTVLZiqQfLbAdp9DVdicEnB5GoERE" >> $@
	@echo "1NWmZRpHH4XSPwsW6dsS3nrNWfL1yrJj4w" >> $@
	@echo "1HsMJxNiV7TLxmoF6uJNkydxPFDog4NQum" >> $@
	@echo "14oFNXucftsHiUMY8uctg6N487riuyXs4h" >> $@
	@echo "1CfZWK1QTQE3eS9qn61dQjV89KDjZzfNcv" >> $@
	@echo "1L2GM8eE7mJWLdo3HZS6su1832NX2txaac" >> $@
	@echo "1rSnXMr63jdCuegJFuidJqWxUPV7AtUf7" >> $@
	@echo "15JhYXn6Mx3oF4Y7PcTAv2wVVAuCFFQNiP" >> $@
	@echo "1JVnST957hGztonaWK6FougdtjxzHzRMMg" >> $@
	@echo "128z5d7nN7PkCuX5qoA4Ys6pmxUYnEy86k" >> $@
	@echo "12jbtzBb54r97TCwW3G1gCFoumpckRAPdY" >> $@
	@echo "19EEC52krRUK1RkUAEZmQdjTyHT7Gp1TYT" >> $@
	@echo "1LHtnpd8nU5VHEMkG2TMYYNUjjLc992bps" >> $@
	@echo "1LhE6sCTuGae42Axu1L1ZB7L96yi9irEBE" >> $@
	@echo "1FRoHA9xewq7DjrZ1psWJVeTer8gHRqEvR" >> $@

64.txt:
	@echo "16jY7qLJnxb7CHZyqBP8qca9d51gAjyXQN" > $@

66.txt:
	@echo "13zb1hQbWVsc2S7ZTZnP2G4undNNpdh5so" > $@

120.txt:
	@echo "02CEB6CBBCDBDF5EF7150682150F4CE2C6F4807B349827DCDBDD1F2EFA885A2630" > $@

125.txt:
	@echo "0233709eb11e0d4439a729f21c2c443dedb727528229713f0065721ba8fa46f00e" > $@

130.txt:
	@echo "03633cbe3ec02b9401c5effa144c5b4d22f87940259634858fc7e59b1c09937852" > $@

unsolvedpuzzles.txt:
	@echo "13zb1hQbWVsc2S7ZTZnP2G4undNNpdh5so" > $@
	@echo "1BY8GQbnueYofwSuFAT3USAhGjPrkxDdW9" >> $@
	@echo "1MVDYgVaSN6iKKEsbzRUAYFrYJadLYZvvZ" >> $@
	@echo "19vkiEajfhuZ8bs8Zu2jgmC6oqZbWqhxhG" >> $@
	@echo "1PWo3JeB9jrGwfHDNpdGK54CRas7fsVzXU" >> $@
	@echo "1JTK7s9YVYywfm5XUH7RNhHJH1LshCaRFR" >> $@
	@echo "12VVRNPi4SJqUTsp6FmqDqY5sGosDtysn4" >> $@
	@echo "1FWGcVDK3JGzCC3WtkYetULPszMaK2Jksv" >> $@
	@echo "1DJh2eHFYQfACPmrvpyWc8MSTYKh7w9eRF" >> $@
	@echo "1Bxk4CQdqL9p22JEtDfdXMsng1XacifUtE" >> $@

# Generate test files with ETH addresses (hex format, 40 chars)
# Format: 0x + 40 hex characters

1to32.eth:
	@echo "0x7e5f4552091a69125d5dfcb7b8c2659029395bdf" > $@
	@echo "0x6813eb9362372eef6200f3b1dbc3f819671cba69" >> $@
	@echo "0xd41c057fd1c78805aac12b0a94a405c0461a6fbb" >> $@
	@echo "0xf1f6619b38a98d6de0800f1defc0a6399eb6d30c" >> $@
	@echo "0x157bfbecd023fd6384dad2bded5dad7e27bf92e4" >> $@
	@echo "0xf472086186382fca55cd182de196520abd76f69d" >> $@
	@echo "0x1ac6f9601f2f616badcea8a0a307e1a3c14767a4" >> $@
	@echo "0xf084bbaabee1a700a8faa404027db620a5aa0059" >> $@
	@echo "0x4aff4d8fa086e079584c5532569135d1ac620a87" >> $@
	@echo "0x86b1b106aeac5c5d2b16f9596755811cf976f34e" >> $@
	@echo "0x2c559fed4b8a8e12e170740d4dabb4fc7d3f9b49" >> $@
	@echo "0xd15a50df0d1d54b0931f462fda35a458aa301e42" >> $@
	@echo "0xdba02a942650eb93cf2566dbcb7d945b9544afcd" >> $@
	@echo "0x0fc0e54f047efb3fd041837213ecb572ad594263" >> $@
	@echo "0x8b7696dca505e006408f9b0e8bdffdd20993e15e" >> $@
	@echo "0xf1527b97640c3935df498110dccd4ce9181c7743" >> $@
	@echo "0x6ef0691fa9edd5a21e6be331d5c4aa21c18a520d" >> $@
	@echo "0x3224ebd2c99ca8afa709701d40868f16b38c70a2" >> $@
	@echo "0xf050fe24f538bf83140a0af5a725b4f8d16f242e" >> $@
	@echo "0x5abfc823a8b0691ebada0a41cd6fab2f15a0a628" >> $@
	@echo "0x4ec431274ed8e1996f1451775b9e11e7db613955" >> $@
	@echo "0x504ec8f62a160702b3414a2b460789e9c36b7a2a" >> $@
	@echo "0x86df25873cb695d3fa3781f34a6b55e5f17dba74" >> $@
	@echo "0xd2c71c0b28f045d0e6facc19a3a6a81a85a17ce4" >> $@
	@echo "0xa96e58a5ca39ed6baf8bc7692e7d79df039fbcb8" >> $@
	@echo "0xe392229bd7664f4ce539303ce60a2235d915caca" >> $@
	@echo "0x2dc9fb4b9ffa330b3c3371311a31e08e962241af" >> $@
	@echo "0xfda5c442e76a95f96c09782f1a15d3b58e32404f" >> $@
	@echo "0x5f3358241c45ac7987f5ed24e4003843d4c369cb" >> $@
	@echo "0x083522c909665aa7ac151892a3a847cbb382b5d4" >> $@
	@echo "0xbd21f11c662cad4fa062e5741310083004086e52" >> $@
	@echo "0xa1401f0c1e75cc40055d9e6a3f25adf11ea876ec" >> $@

64.eth:
	@echo "0x3ee4133d991f52fdf6a25c9834e0745ac74248a4" > $@

66.eth:
	@echo "0x7e5f4552091a69125d5dfcb7b8c2659029395bdf" > $@

120.eth:
	@echo "0x7e5f4552091a69125d5dfcb7b8c2659029395bdf" > $@

125.eth:
	@echo "0x6813eb9362372eef6200f3b1dbc3f819671cba69" > $@

130.eth:
	@echo "0xd41c057fd1c78805aac12b0a94a405c0461a6fbb" > $@

# Generate test files with BTC bech32 addresses
# Format: bc1q + 38-62 alphanumeric characters (bech32)

1to32.bech32:
	@echo "bc1qar0rfrtma40x05y2s7k743e2lvkpgyvpz3l5t9" > $@
	@echo "bc1qxy2kgdygjrsqtzq2n0yrf2493p83kkfjhx2wlh" >> $@
	@echo "bc1q3q3l5m5z5k5z5k5z5k5z5k5z5k5z5k5z5k5z5k" >> $@
	@echo "bc1q5q5q5q5q5q5q5q5q5q5q5q5q5q5q5q5q5q5q5q" >> $@
	@echo "bc1q7q7q7q7q7q7q7q7q7q7q7q7q7q7q7q7q7q7q7q" >> $@
	@echo "bc1q9q9q9q9q9q9q9q9q9q9q9q9q9q9q9q9q9q9q9q" >> $@
	@echo "bc1q0q0q0q0q0q0q0q0q0q0q0q0q0q0q0q0q0q0q0q" >> $@
	@echo "bc1q2q2q2q2q2q2q2q2q2q2q2q2q2q2q2q2q2q2q2q" >> $@
	@echo "bc1q4q4q4q4q4q4q4q4q4q4q4q4q4q4q4q4q4q4q4q" >> $@
	@echo "bc1q6q6q6q6q6q6q6q6q6q6q6q6q6q6q6q6q6q6q6q" >> $@
	@echo "bc1q8q8q8q8q8q8q8q8q8q8q8q8q8q8q8q8q8q8q8q" >> $@
	@echo "bc1qaqaqaqaqaqaqaqaqaqaqaqaqaqaqaqaqaqaqaq" >> $@
	@echo "bc1qcqcqcqcqcqcqcqcqcqcqcqcqcqcqcqcqcqcq" >> $@
	@echo "bc1qeqeqeqeqeqeqeqeqeqeqeqeqeqeqeqeqeqeqeq" >> $@
	@echo "bc1qgqgqgqgqgqgqgqgqgqgqgqgqgqgqgqgqgqgqgq" >> $@
	@echo "bc1qiqiqiqiqiqiqiqiqiqiqiqiqiqiqiqiqiqiqiq" >> $@
	@echo "bc1qjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjq" >> $@
	@echo "bc1qlqlqlqlqlqlqlqlqlqlqlqlqlqlqlqlqlqlqlq" >> $@
	@echo "bc1qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq" >> $@
	@echo "bc1qzqzqzqzqzqzqzqzqzqzqzqzqzqzqzqzqzqzqzq" >> $@
	@echo "bc1q3q3q3q3q3q3q3q3q3q3q3q3q3q3q3q3q3q3q3q" >> $@
	@echo "bc1q5q5q5q5q5q5q5q5q5q5q5q5q5q5q5q5q5q5q5q" >> $@
	@echo "bc1q7q7q7q7q7q7q7q7q7q7q7q7q7q7q7q7q7q7q7q" >> $@
	@echo "bc1q9q9q9q9q9q9q9q9q9q9q9q9q9q9q9q9q9q9q9q" >> $@
	@echo "bc1q0q0q0q0q0q0q0q0q0q0q0q0q0q0q0q0q0q0q0q" >> $@
	@echo "bc1q2q2q2q2q2q2q2q2q2q2q2q2q2q2q2q2q2q2q2q" >> $@
	@echo "bc1q4q4q4q4q4q4q4q4q4q4q4q4q4q4q4q4q4q4q4q" >> $@
	@echo "bc1q6q6q6q6q6q6q6q6q6q6q6q6q6q6q6q6q6q6q6q" >> $@
	@echo "bc1q8q8q8q8q8q8q8q8q8q8q8q8q8q8q8q8q8q8q8q" >> $@
	@echo "bc1qaqaqaqaqaqaqaqaqaqaqaqaqaqaqaqaqaqaqaq" >> $@
	@echo "bc1qcqcqcqcqcqcqcqcqcqcqcqcqcqcqcqcqcqcq" >> $@
	@echo "bc1qeqeqeqeqeqeqeqeqeqeqeqeqeqeqeqeqeqeqeq" >> $@

64.bech32:
	@echo "bc1qar0rfrtma40x05y2s7k743e2lvkpgyvpz3l5t9" > $@

66.bech32:
	@echo "bc1qxy2kgdygjrsqtzq2n0yrf2493p83kkfjhx2wlh" > $@

120.bech32:
	@echo "bc1q3q3l5m5z5k5z5k5z5k5z5k5z5k5z5k5z5k5z5k" > $@

125.bech32:
	@echo "bc1q5q5q5q5q5q5q5q5q5q5q5q5q5q5q5q5q5q5q5q" > $@

130.bech32:
	@echo "bc1q7q7q7q7q7q7q7q7q7q7q7q7q7q7q7q7q7q7q7q" > $@

clean:
	@rm -f 1to32.txt 64.txt 66.txt 120.txt 125.txt 130.txt unsolvedpuzzles.txt
	@rm -f 1to32.rmd 64.rmd 66.rmd 120.rmd 125.rmd 130.rmd
	@rm -f 1to32.eth 64.eth 66.eth 120.eth 125.eth 130.eth
	@rm -f 1to32.bech32 64.bech32 66.bech32 120.bech32 125.bech32 130.bech32
	@rm -f 1to32.pub 64.pub 66.pub 120.pub 125.pub 130.pub
